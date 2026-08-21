# AI-Based Secure Ad Hoc Wireless Sensor Network for Real-Time Bird Behavior Monitoring Using Edge Intelligence and Cloud Analytics

A complete AI-powered, secure ad hoc wireless sensor network system developed using the Silicon Labs SiWx917 Wi-Fi/BLE SoC.

The system collects audio and environmental data from sensor nodes deployed in remote forest environments, processes the data on-device using DSP and edge ML, securely forwards it over an ad hoc mesh network, and transmits results to an AWS cloud backend for storage, analytics, and dashboard visualization.

A virtual sensor node simulator is also provided for testing the complete software pipeline without physical hardware.

## System Architecture

```
                 PHYSICAL ENVIRONMENT (FOREST)
                             │
                             ▼
                  ┌─────────────────────┐
                  │  Silicon Labs       │
                  │     SiWx917         │
                  │                     │
                  │  Microphone / Audio │
                  │  Environmental      │
                  │  Sensors            │
                  └──────────┬──────────┘
                             │
                     DSP + Edge ML
                   (Noise Filtering,
                 Feature Extraction,
              Species/Behavior Inference)
                             │
                             ▼
                  ┌─────────────────────┐
                  │   Secure Ad Hoc     │
                  │   Mesh Network      │
                  │                     │
                  │  Encryption (AES)   │
                  │  Authentication     │
                  │  Packet Forwarding  │
                  └──────────┬──────────┘
                             │
                        Wi-Fi + HTTPS
                             │
                             ▼
                  ┌─────────────────────┐
                  │    AWS Cloud        │
                  │                     │
                  │  Data Storage       │
                  │  Analytics          │
                  │  Dashboards         │
                  └──────────┬──────────┘
                             │
                             ▼
                  ┌─────────────────────┐
                  │  Monitoring          │
                  │   Dashboard          │
                  │                      │
                  │  Live Bird Activity  │
                  │  Species Detected    │
                  │  Behavior Patterns   │
                  │  Alerts & History    │
                  └─────────────────────┘
```

## Features

- Silicon Labs SiWx917 Wi-Fi/BLE connectivity
- Ad hoc mesh communication between sensor nodes in remote terrain
- Secure routing with authentication and encrypted packet forwarding
- DSP-based noise removal, filtering, and feature extraction from bird sounds
- Edge ML inference for bird species identification and behavior classification
- Secure HTTPS communication with AWS cloud backend
- Cloud-based data storage, dashboards, and long-term analytics
- Real-time monitoring dashboard for live bird activity
- Virtual sensor node simulator for software-only testing

## Hardware

**Main Controller**
- Silicon Labs SiWx917 Wi-Fi/BLE SoC / development board

**Sensors**
- Audio sensor / microphone module for bird sound capture
- Environmental sensors (temperature, humidity — optional, site-dependent)

**Firmware Interfaces**
- Wi-Fi
- BLE (for local ad hoc communication)
- HTTPS/TLS
- I2C / SPI (sensor interfacing)
- FreeRTOS

## Sensor Data

The SiWx917 node sends processed detection data to the backend/cloud in JSON format.

Example:

```json
{
  "nodeId": "Node-001",
  "timestamp": "2026-08-21T09:15:00Z",
  "species": "Common Myna",
  "behavior": "foraging",
  "confidence": 0.91,
  "temperature": 29.4,
  "humidity": 68.2,
  "batteryLevel": 87
}
```

**Parameters**

| Parameter | Description | Unit |
|---|---|---|
| nodeId | Sensor node identifier | - |
| timestamp | Time of detection | ISO 8601 |
| species | Predicted bird species | - |
| behavior | Predicted behavior class (e.g. foraging, calling, flying) | - |
| confidence | Model prediction confidence | 0–1 |
| temperature | Environmental temperature | °C |
| humidity | Relative humidity | % |
| batteryLevel | Node battery status | % |

Note: Environmental fields are optional and depend on which sensors are attached to a given node.

## Repository Structure

```
BirdMonitoring/
│
├── app.c                    # Main application
├── app.h                    # Function declarations
├── autogen/
├── config/
├── resources/
│
├── sensor/
│   ├── sensor.c              # Sensor data acquisition (audio + environmental)
│   └── sensor.h
│
├── network/
│   ├── network.c             # Wi-Fi / ad hoc mesh communication
│   └── network.h
│
├── dsp/
│   ├── dsp.c                 # Noise filtering and signal processing
│   └── dsp.h
│
├── ml/
│   ├── ml.c                  # Edge ML inference (species/behavior)
│   └── ml.h
│
├── security/
│   ├── security.c            # AES encryption, authentication
│   └── security.h
│
├── cloud/
│   ├── aws.c                 # Send data to AWS
│   └── aws.h
│
├── config.h                  # System configuration (no secrets — see below)
├── cacert_new.pem.h          # TLS certificate for HTTPS
│
├── cloud-backend/
│   ├── ai_service/            # (optional) server-side model retraining/analytics
│   ├── backend/                # Node.js API server
│   │   ├── server.js
│   │   ├── controllers/
│   │   ├── models/
│   │   ├── routes/
│   │   └── package.json
│   └── virtual_device/
│       └── siwx917_simulator.py
│
├── dashboard/
│   ├── src/
│   ├── package.json
│   └── vite.config.ts
│
└── README.md
```

## Software Requirements

Install the following software:

- Git
- Node.js
- npm
- Python 3
- Silicon Labs Simplicity Studio V6
- Silicon Labs WiSeConnect SDK (required by the firmware project)
- Segger J-Link drivers

For physical-board testing, the SiWx917 development hardware (SIWX917) and required USB drivers are also needed.

## 1. Backend Setup

The Node.js backend is located at:

```
cloud-backend/backend
```

Open a terminal:

```
cd cloud-backend/backend
```

Install dependencies:

```
npm install
```

Start the backend:

```
node server.js
```

The backend runs on:

```
http://localhost:4000
```

Detection data endpoint:

```
POST /api/sensor-data
```

## 2. Dashboard Setup

The dashboard is located at:

```
dashboard
```

Open another terminal:

```
cd dashboard
```

Install dependencies:

```
npm install
```

Start the development server:

```
npm run dev
```

Vite will display the dashboard URL in the terminal. Open the displayed URL in a web browser.

## 3. Virtual SiWx917 Node Simulator

A virtual sensor node is provided for testing without physical hardware.

The simulator is located at:

```
cloud-backend/virtual_device
```

Open another terminal:

```
cd cloud-backend/virtual_device
```

Run:

```
python siwx917_simulator.py
```

The simulator periodically sends detection data to:

```
http://localhost:4000/api/sensor-data
```

The default transmission interval is 5 seconds.

**Simulator Modes**

Normal activity:

```
python siwx917_simulator.py --mode NORMAL
```

High activity (e.g. flock detected):

```
python siwx917_simulator.py --mode HIGH_ACTIVITY
```

Low battery / degraded node:

```
python siwx917_simulator.py --mode LOW_BATTERY
```

The transmission interval can also be changed:

```
python siwx917_simulator.py --mode NORMAL --interval 2
```

## 4. Running the Complete Software System

For testing without physical hardware, open three terminals.

**Terminal 1 — Backend**
```
cd cloud-backend/backend
node server.js
```

**Terminal 2 — Dashboard**
```
cd dashboard
npm run dev
```

**Terminal 3 — Virtual Device**
```
cd cloud-backend/virtual_device
python siwx917_simulator.py
```

The data flow is:

```
Virtual SiWx917 Node
       │
       ▼
Node.js Backend
       │
       ▼
AWS Cloud (Storage + Analytics)
       │
       ▼
Monitoring Dashboard
```

## 5. Physical SiWx917 Testing

For physical hardware testing:

1. Open the project in Silicon Labs Simplicity Studio.
2. Open the `.slcp` project file.
3. Configure the Wi-Fi credentials (see security note below).
4. Verify the TLS certificate configuration.
5. Build the firmware.
6. Flash the firmware to the SiWx917.
7. Open the serial terminal.
8. Verify Wi-Fi connection.
9. Verify sensor initialization.
10. Verify DSP and ML inference output.
11. Verify HTTPS transmission to AWS.
12. Observe the values on the dashboard.

Expected initialization output includes:

```
Wi-Fi client interface init success
Wi-Fi client connected
TLS Certificate Loaded
I2C Init Status = 0x0
Audio Sensor Init Status = 0x0
Mesh Network Join Status = 0x0
```

After initialization, the firmware continuously captures audio, runs on-device DSP and ML inference, and sends detection results to the backend over the secure ad hoc network.

## 6. Firmware Sensor & Signal Processing

The firmware:

1. Captures raw audio via the microphone module.
2. Applies DSP-based noise removal and filtering.
3. Extracts acoustic features from the filtered signal.
4. Runs on-device ML inference for species and behavior classification.
5. Packages the result into JSON and sends it over the secure ad hoc mesh network to the backend using HTTPS.

## 7. Secure Ad Hoc Communication

Sensor nodes form a mesh network to relay data across nodes that are out of direct range of the gateway/backend.

Security measures include:

- AES encryption of payloads
- Node authentication before joining the mesh
- Secure packet forwarding between intermediate nodes

## 8. HTTPS Communication

The firmware uses TLS-secured HTTP communication for the final hop to the backend/cloud.

The certificate used by the firmware is stored in:

```
cacert_new.pem.h
```

The certificate is used to establish a trusted TLS connection with the backend server.

**Do not place private keys, real passwords, API keys, or other secrets in the repository.**

## 9. Cloud Processing (AWS)

The Node.js backend forwards validated detection data to AWS for:

- Long-term storage
- Aggregated species/behavior analytics
- Trend and activity dashboards

## 10. Dashboard

The dashboard provides visualization of live and historical bird activity.

It includes:

- Live detection feed
- Species distribution
- Behavior pattern trends
- Node health (battery, connectivity)
- Alerts (e.g. unusual activity, low battery, node offline)
- Historical charts

## 11. Software-Only Testing

The physical SiWx917 hardware is not required to test the complete backend-to-dashboard pipeline.

The virtual node simulator can generate detection data and send it to the backend, allowing the following pipeline to be tested end-to-end:

```
Sensor Simulator
       ↓
Backend
       ↓
AWS Cloud
       ↓
Dashboard
```

Different simulator modes can be used to demonstrate changes in bird activity and node status.

## 12. API Example

**Detection Data**

```
POST /api/sensor-data
Content-Type: application/json
```

Example request:

```json
{
  "nodeId": "Node-001",
  "timestamp": "2026-08-21T09:15:00Z",
  "species": "Common Myna",
  "behavior": "foraging",
  "confidence": 0.91,
  "temperature": 29.4,
  "humidity": 68.2,
  "batteryLevel": 87
}
```

## 13. Important Notes

- Do not commit real Wi-Fi passwords.
- Do not commit private keys or API keys.
- `YOUR_WIFI_PASSWORD` should be used as a placeholder in documentation.
- Wi-Fi credentials should not be committed directly to `config.h`. Use a separate local config file, environment variables, or a secure provisioning method, and add that file to `.gitignore`.
- Node.js dependencies should be installed using `npm install`.
- Python dependencies should be installed using `requirements.txt`.
- Python virtual environments are not included in the repository.
- Node.js `node_modules` directories are not included in the repository.
- Silicon Labs SDK installations are not included in this repository.
- The trained ML models are required by the edge inference module.

## 14. Project Status

The software pipeline has been tested using simulated sensor data.

The final physical validation uses the SiWx917 with an audio sensor module in a live field environment.

Target end-to-end operation:

```
Physical Sensors (Audio)
       ↓
SiWx917
       ↓
DSP + Edge ML
       ↓
Secure Ad Hoc Mesh
       ↓
Wi-Fi + HTTPS
       ↓
Node.js Backend
       ↓
AWS Cloud
       ↓
Monitoring Dashboard
```

## 15. License

This project is licensed under the MIT License.

See the `LICENSE` file for details.