
# 🌾 Smart Irrigation for Furrow Farming

## 🧩 Problem Statement

In rural and semi-rural areas, farmers often rely on manual irrigation techniques without monitoring soil moisture levels. This leads to over-irrigation, under-irrigation, and significant water wastage. Additionally, the absence of smart systems makes it difficult to irrigate multiple furrows efficiently, especially when water resources are limited.

---

## 💡 Proposed Solution

We have developed a **Smart Irrigation System for Furrow Farming** that automatically waters crops based on real-time soil moisture levels. The system uses an ESP8266 microcontroller, multiple soil moisture sensors, and a CD4051BE multiplexer to read moisture from several furrows. Based on this data, the system controls solenoid valves using TIP31 NPN transistors, optimizing water use only where needed. It is also powered by lithium-ion batteries for off-grid rural deployment.

---

## 🔧 Features

- 🌱 Real-time soil moisture detection for multiple furrows  
- 🔁 Automated irrigation using solenoid valves  
- 🔌 Low-power operation using lithium-ion batteries  
- 📡 Wireless capability using ESP8266 (NodeMCU)  
- 🌿 Modular design for easy expansion  
- 💧 Water conservation and improved crop yield

---

## 🛠️ Technologies & Components Used

- **Microcontroller:** ESP8266 (NodeMCU)
- **Sensors:** Analog Soil Moisture Sensors
- **Multiplexer:** CD4051BE (8-channel analog multiplexer)
- **Transistor Switches:** TIP31 (NPN)
- **Power Supply:** 3.7V Lithium-ion Batteries with TP4056 Charging Modules
- **Voltage Regulation:** AMS1117 or Buck Converter
- **Solenoid Valve:** 12V DC
- **Software:** Arduino IDE (C++)

---

## 📦 Future Improvements

- Integration with mobile app/dashboard for monitoring
- Addition of temperature/humidity sensors
- Solar-based battery charging
- Crop-specific irrigation presets

---

## 📂 GitHub Repository Structure

```
Smart-Irrigation-Furrow-Farming/
├── code/
│   └── irrigation.ino
├── images/
│   └── wiring_diagram.png
├── docs/
│   └── problem_solution.md
│   └── components_list.pdf
├── README.md
└── LICENSE
```

---

## 🌐 Social Impact

This solution is aimed at improving water efficiency in agriculture, especially for **small and marginal farmers**. It reduces water consumption, lowers labor costs, and boosts yield — contributing to **sustainable farming practices** and **food security**.
