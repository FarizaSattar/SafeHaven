/***********************************************************************
 * SafeHaven Lambda Backend
 ***********************************************************************/

import { DynamoDBClient } from "@aws-sdk/client-dynamodb";
import { DynamoDBDocumentClient, PutCommand, QueryCommand } from "@aws-sdk/lib-dynamodb";
import { SNSClient, PublishCommand } from "@aws-sdk/client-sns";

// ---------------- CONFIGURATION ----------------

const REGION = "ca-central-1";
const TABLE_NAME = "SafeHavenSensorDatabaseV2";
const SNS_TOPIC_ARN = "arn:aws:sns:ca-central-1:905418170126:SafeHavenAlerts";
const ALERT_COOLDOWN = 900;

// ---------------- AWS CLIENTS ----------------

const client = new DynamoDBClient({ region: REGION });
const ddb = DynamoDBDocumentClient.from(client);
const sns = new SNSClient({ region: REGION });

// ---------------- DEFAULT THRESHOLDS ----------------

const DEFAULT_THRESHOLDS = {
    TEMP: 40,
    WATER: 10,
    PRESSURE: 20,
    LOW_BATTERY: 15
};

// ---------------- HELPERS ----------------

function formatEST(unixSeconds) {
    return new Date(unixSeconds * 1000)
        .toLocaleString("en-CA", { timeZone: "America/Toronto" });
}

async function sendSNS(subject, message) {
    await sns.send(new PublishCommand({
        TopicArn: SNS_TOPIC_ARN,
        Subject: subject,
        Message: message
    }));
}

// ---------------- MAIN HANDLER ----------------

export const handler = async (event) => {

    console.log("RAW EVENT:", JSON.stringify(event));

    try {

        // 🔥 FIX 1: Properly parse API Gateway body
        const body = typeof event.body === "string"
            ? JSON.parse(event.body)
            : event;

        console.log("PARSED BODY:", JSON.stringify(body));

        // 🔥 FIX 2: Accept ESP32 "device"
        const deviceId = body.device || body.deviceId;

        if (!deviceId) {
            console.log("Missing device ID");
            return { statusCode: 400 };
        }

        const now = Math.floor(Date.now() / 1000);
        const unixTime = body.ts || now;
        const timestamp = formatEST(unixTime);

        // ---------------- SENSOR VALUES ----------------

        const door = body.door ?? -1;
        const motion = body.motion ?? -1;
        const tempC = body.tempC ?? -1;
        const water_pct = body.water_pct ?? -1;
        const pressure_pct = body.pressure_pct ?? -1;
        const battery_pct = body.battery_pct ?? 100;

        // ---------------- ALERT EVALUATION ----------------

        const alertMap = {
            "Motion Detected": motion === 1,
            "High Temperature": tempC > DEFAULT_THRESHOLDS.TEMP,
            "Water Leak": water_pct > DEFAULT_THRESHOLDS.WATER,
            "High Pressure": pressure_pct > DEFAULT_THRESHOLDS.PRESSURE,
            "Low Battery": battery_pct < DEFAULT_THRESHOLDS.LOW_BATTERY
        };

        const alertsActive = Object.keys(alertMap).filter(a => alertMap[a]);

        // ---------------- GET LAST RECORD (FAST QUERY) ----------------

        let lastAlertTimes = {};
        let alertAcknowledged = {};

        try {

            const query = await ddb.send(new QueryCommand({
                TableName: TABLE_NAME,
                KeyConditionExpression: "deviceId = :d",
                ExpressionAttributeValues: {
                    ":d": deviceId
                },
                ScanIndexForward: false,
                Limit: 1
            }));

            if (query.Items && query.Items.length > 0) {
                const lastPayload = query.Items[0].payload || {};
                lastAlertTimes = lastPayload.lastAlertTimes || {};
                alertAcknowledged = lastPayload.alertAcknowledged || {};
            }

        } catch (err) {
            console.log("Query error:", err);
        }

        // ---------------- COOLDOWN LOGIC ----------------

        const unacknowledgedAlerts = [];

        for (const alert of alertsActive) {

            const lastSent = lastAlertTimes[alert] || 0;
            const ack = alertAcknowledged[alert] || false;

            if (!ack && (now - lastSent >= ALERT_COOLDOWN)) {
                unacknowledgedAlerts.push(alert);
                lastAlertTimes[alert] = now;
            }
        }

        // ---------------- SEND ALERT ----------------

        if (unacknowledgedAlerts.length > 0) {
            await sendSNS(
                "🚨 SafeHaven Alert",
                `Device ${deviceId}: ${unacknowledgedAlerts.join(", ")}`
            );
        }

        // ---------------- OFFLINE CHECK ----------------

        const offline =
            door === -1 &&
            motion === -1 &&
            tempC === -1 &&
            water_pct === -1 &&
            pressure_pct === -1;

        // ---------------- FINAL PAYLOAD ----------------

        const payload = {
            door,
            motion,
            tempC,
            water_pct,
            pressure_pct,
            battery_pct,
            alertsActive,
            lastAlertTimes,
            alertAcknowledged,
            offline,
            unixTime
        };

        // ---------------- SAVE TO DYNAMODB ----------------

        await ddb.send(new PutCommand({
            TableName: TABLE_NAME,
            Item: {
                deviceId,
                timestamp,
                deviceType: "sensors",
                unixTime,
                payload
            }
        }));

        console.log("DynamoDB write success");

        return { statusCode: 200 };

    } catch (error) {

        console.log("LAMBDA ERROR:", error);
        return { statusCode: 500 };
    }
};
