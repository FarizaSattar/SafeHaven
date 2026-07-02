# 🎯 Project Overview

As people age, maintaining independence while ensuring their safety becomes increasingly challenging. Family members and caregivers cannot always be physically present, making it difficult to detect emergencies such as falls, unauthorized entry, water leaks, or unsafe environmental conditions in a timely manner.

Traditional home security systems often focus on intrusion detection but lack comprehensive environmental monitoring and real-time health and safety insights. They also tend to operate as isolated systems without centralized dashboards or intelligent alerting.

**SafeHaven** is a cloud-connected IoT home monitoring platform that combines embedded systems, cloud computing, and web technologies to continuously monitor a living environment and notify caregivers when potentially dangerous situations occur.

Using an ESP32 microcontroller and multiple environmental sensors, SafeHaven collects real-time telemetry, securely transmits it to AWS, processes sensor events using serverless services, stores historical data, and displays live information through a modern web dashboard.

Rather than simply collecting sensor readings, SafeHaven transforms raw environmental data into actionable alerts that help caregivers respond quickly to potential safety risks while allowing seniors to maintain their independence.

---

# ❓ Why SafeHaven?

Many seniors prefer living independently, but doing so introduces safety concerns for both individuals and their caregivers.

Some common challenges include:

* Falls or unexpected movement
* Doors left open or unauthorized entry
* Water leaks causing property damage
* Dangerous temperature conditions
* Delayed emergency response
* Limited visibility for remote caregivers

Commercial smart home products often solve only one problem at a time and require multiple disconnected applications.

SafeHaven demonstrates how an integrated IoT platform can combine multiple sensors, cloud services, and real-time visualization into a single system that provides continuous monitoring and immediate notifications.

The result is:

* Continuous home monitoring
* Faster emergency awareness
* Reduced caregiver uncertainty
* Secure remote access to sensor data
* Centralized monitoring dashboard
* Scalable cloud-based architecture

---

# 👥 Who Is This Project For?

SafeHaven is designed as a demonstration of a modern Internet of Things (IoT) platform and is suitable for:

* Caregivers monitoring loved ones remotely
* Seniors living independently
* Smart home enthusiasts
* Embedded systems engineers
* IoT developers
* Cloud engineers
* Students learning AWS IoT architecture

The project also serves as a portfolio demonstrating embedded programming, cloud infrastructure, serverless computing, full-stack web development, and secure IoT communication.

---

# 🚀 What Does SafeHaven Do?

Once deployed, SafeHaven continuously monitors environmental conditions inside a home using an ESP32 connected to multiple sensors.

The system operates automatically without requiring user interaction.

A typical monitoring cycle consists of the following steps:

1. The ESP32 reads data from connected sensors, including:

   * Motion sensor
   * Door sensor
   * Temperature sensor
   * Water leak sensor
   * Pressure sensor

2. Edge processing logic filters sensor readings to eliminate noise and identify meaningful state changes.

3. Sensor data is securely transmitted to AWS IoT Core using MQTT over TLS with X.509 certificate authentication.

4. AWS Lambda processes incoming telemetry and determines whether an alert condition has been detected.

5. Sensor readings and event history are stored in DynamoDB for future analysis.

6. If a hazardous condition is identified, Amazon SNS automatically sends notifications to caregivers via email or SMS.

7. The Node.js backend exposes REST APIs that retrieve live sensor data and historical events.

8. The React dashboard displays the current status of every sensor, active alerts, and historical logs in real time.

This end-to-end pipeline allows caregivers to remotely monitor the safety of a home while providing immediate awareness of abnormal conditions.

---

# 🛠️ Prerequisites

Before deploying SafeHaven, you will need access to the following hardware and cloud resources.

### Hardware

* ESP32 Development Board
* PIR Motion Sensor
* Magnetic Door Sensor
* LM35 Temperature Sensor
* Water Leak Sensor
* Pressure Sensor
* Breadboard and jumper wires
* USB cable for programming

### AWS Services

* AWS IoT Core
* AWS Lambda
* DynamoDB
* Amazon SNS
* API Gateway
* IAM

### Software

* Arduino IDE
* Node.js
* npm
* Git
* AWS CLI (optional)

### Recommended Knowledge

Although the project includes deployment instructions, familiarity with the following technologies is helpful:

* Arduino programming
* Embedded C++
* MQTT
* AWS IoT Core
* REST APIs
* React
* Node.js
* Basic networking
* Cloud security concepts

---

# 💡 How to Use SafeHaven

After completing the hardware setup and cloud deployment, SafeHaven begins monitoring automatically.

The ESP32 continuously samples sensor readings and sends updates whenever meaningful changes occur.

A typical workflow is shown below:

```text
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
     │             │
    No            Yes
     │             │
     ▼             ▼
Update Dashboard   Send SNS Alert
           │
           ▼
Caregiver Reviews Dashboard
```

From the user's perspective, the dashboard provides:

* Live environmental sensor readings
* Current system status
* Active alerts
* Historical event logs
* Notification history

If an abnormal condition is detected, such as a water leak, unexpected motion, or an open door, the system automatically generates an alert so caregivers can take appropriate action.

---

# 📈 Example Scenario

Imagine an elderly resident accidentally leaves a faucet running while leaving the house.

Without SafeHaven:

* The leak may go unnoticed for hours.
* Water damage can spread before anyone becomes aware.
* Caregivers have no visibility into the situation.

With SafeHaven:

* The water sensor detects abnormal moisture.
* The ESP32 confirms the event.
* Sensor data is securely transmitted to AWS.
* Lambda processes the incoming event.
* An alert is generated immediately.
* Amazon SNS sends an email or SMS notification.
* The dashboard updates in real time with the detected hazard.
* A caregiver can quickly investigate and respond.

This same workflow applies to other monitored events, including unauthorized door openings, unexpected motion, elevated temperatures, and pressure anomalies.

