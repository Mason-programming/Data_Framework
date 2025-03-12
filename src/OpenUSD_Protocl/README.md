# 🌐 Universal Live Sync Protocol (ULSP)

**A lightweight, open-source protocol for syncing USD scene data across DCCs in real time.**  
Inspired by the power of Omniverse Live Sync — reimagined as a modular, extendable framework for independent developers and smaller studios.

---

## 🚀 Overview

The **USD Bridge Protocol (UBP)** enables real-time collaboration between Digital Content Creation tools like Blender, Maya, and Unreal Engine through the OpenUSD format. Artists and technical directors can work in different apps while sharing and updating the same scene — seamlessly and live.

---

## 🧠 Key Features

- 🔄 **Live USD Updates** – Sync geometry, animation, and materials across tools in real time  
- ⚡ **Lightweight & Modular** – Built with Python, gRPC, and optional Redis backend  
- 🧩 **Pluggable Client SDKs** – Simple integration with Blender, Unreal, Maya & more  
- 🔓 **Open Protocol** – Define your own behavior for message passing and data handling  
- 🛠️ **Developer Friendly** – Built for experimentation, prototyping, and pipeline integration  

---

## 💡 Invented Tech

### USD Bridge Protocol (UBP)  
A standardized messaging format for real-time communication between DCCs using USD. Think *OSC (Open Sound Control)* for 3D pipelines — open, structured, and extensible.

#### Sample Message Schema
```json
{
  "type": "IMPORT_USD",
  "source": "blender",
  "department": "Lighting",
  "file type": "fbx", 
  "usd_path": "/path/to/scene.usd",
  "timestamp": "2025-03-11T15:00:00Z"
}

---

#### 
+-------------------+         gRPC/Socket         +--------------------+
|  Blender Client   |  <----------------------->  |  USD Sync Server   |
|  (Python Addon)   |                            |  (Command Center)   |
+-------------------+                            +--------------------+
        ▲                                                  ▲
        |                                                  |
        |             +------------------+                 |
        +------------>+   Unreal Client  +<----------------+
                      +------------------+

