# 🏡 SafeHaven
### An IoT platform that helps seniors stay independent, safely

## 👋 What is this?

This project started with a simple but important question: how do we help seniors keep their independence at home, while still giving their families peace of mind?

As people age, living alone becomes riskier — a fall, a door left open, a leaking pipe, or an unsafe temperature can turn dangerous fast, especially when no one's there to notice right away. Most smart home products only solve one piece of this puzzle at a time, spread across separate apps that don't talk to each other.

SafeHaven brings it all together. It's a full-stack IoT platform — sensors, cloud infrastructure, and a live web dashboard — that continuously watches over a home and immediately alerts caregivers the moment something looks wrong. Not to replace independence, but to protect it.

I led a 6-person multidisciplinary team through the entire process, from soldering the first sensor to deploying the final cloud pipeline, as our capstone design project.

## ❓ Why I built this

Caregivers and seniors both deserve better than fragmented, single-purpose gadgets. I wanted to build something that treats a home as one connected system — where a motion sensor, a door sensor, a leak detector, and a temperature sensor are all part of the same intelligent picture, feeding into one dashboard that tells the whole story at a glance. Leading the team through the full lifecycle — hardware, firmware, cloud, and frontend — taught me more about building real, reliable systems than any single course could.

## 🚀 What it actually does

Once set up, SafeHaven runs quietly in the background, no interaction needed:

1. **An ESP32 microcontroller reads live data** from five sensors: motion, door, temperature, water leak, and pressure.
2. **Edge processing filters out noise**, so only meaningful changes get sent onward.
3. **Data travels securely to AWS IoT Core** using MQTT over TLS with X.509 certificate authentication — the same level of security used to protect sensitive data in transit.
4. **AWS Lambda processes each event** and checks whether it looks like a hazard.
5. **Everything gets logged in DynamoDB**, building a historical record over time.
6. **If something's wrong, Amazon SNS immediately texts or emails the caregiver.**
7. **A React dashboard shows it all live** — sensor status, active alerts, and full history, updated in real time.

## 📈 Why it matters — a quick example

Imagine an elderly resident accidentally leaves the faucet running and steps out.

**Without SafeHaven:** the leak could go unnoticed for hours, causing real water damage, with the caregiver having zero visibility into what's happening.

**With SafeHaven:** the water sensor picks up the abnormal moisture within moments, the event is verified and sent securely to AWS, and the caregiver gets a text before the resident even realizes what happened. The dashboard updates instantly so they can see exactly what triggered the alert.

The same pipeline handles unexpected motion, doors left open, temperature spikes, and pressure anomalies — one system, watching everything.

## 🏆 How it performed

Across **86,000+ real sensor events**, SafeHaven maintained **98.7% system reliability** with sub-second alert processing — proof that this isn't just a proof-of-concept, but a system that holds up under real, sustained use.

## 👥 Who this is for

- Caregivers who want more visibility into a loved one's safety at home
- Seniors who want to stay independent without sacrificing safety
- Embedded systems and IoT engineers curious about a full ESP32-to-cloud pipeline
- Cloud engineers interested in serverless AWS architecture
- Students learning how AWS IoT Core, Lambda, and DynamoDB fit together in practice

## 🛠️ What you'll need to build this yourself

**Hardware:** ESP32 dev board, PIR motion sensor, magnetic door sensor, LM35 temperature sensor, water leak sensor, pressure sensor, breadboard, jumper wires, USB cable

**AWS services:** IoT Core, Lambda, DynamoDB, Amazon SNS, API Gateway, IAM

**Software:** Arduino IDE, Node.js, npm, Git

**Helpful background:** Arduino/Embedded C++, MQTT, REST APIs, React, and basic cloud security concepts — though the docs walk through setup either way.

## 💡 How it flows, visually

```
Sensor Detects Activity
        │
        ▼
ESP32 Reads Sensor Values
        │
        ▼
Edge Filtering & State Detection
        │
        ▼
Secure MQTT Transmission
        │
        ▼
AWS IoT Core
        │
        ▼
AWS Lambda Processing
        │
        ▼
Store Data in DynamoDB
        │
        ▼
   Hazard Detected?
    │            │
   No           Yes
    │            │
    ▼            ▼
Update Dashboard   Send SNS Alert
        │
        ▼
Caregiver Reviews Dashboard
```

## 🧰 Built with

JavaScript · C++ · React · Node.js · ESP32 · AWS IoT Core · AWS Lambda · DynamoDB · Amazon SNS

