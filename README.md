<!-- Smart Fencing Security System for Theft Protection - README (HTML version) -->

<h1 align="center">🛡️ Smart Fencing Security System for Theft Protection</h1>

<p
  align="center">
  A <strong>smart security solution</strong> built with <strong>ESP32, touch sensors, servo motor, buzzer, LED, and Blynk IoT</strong>.<br>
  This project detects intrusions via capacitive touch sensors and triggers
  <strong>alarms, servo movement, LED blinking, and Blynk notifications</strong>.
  <img alt="ESP32" src="https://img.shields.io/badge/ESP32-IoT-blue?logo=espressif">
  <img alt="License" src="https://img.shields.io/badge/license-MIT-green">
  <img alt="Platform" src="https://img.shields.io/badge/platform-Arduino-orange">
</p>

<hr>

<h2>🚀 Features</h2>
<ul>
  <li>📲 <strong>Blynk IoT Integration</strong> – Remote monitoring &amp; control.</li>
  <li>⚡ <strong>Touch Sensors (T0 &amp; T3)</strong> – Detects intrusion attempts.</li>
  <li>🔔 <strong>Buzzer + LED Alerts</strong> – Audible &amp; visual alarms.</li>
  <li>🔄 <strong>Servo Motor Control</strong> – Automatic movement on intrusion.</li>
  <li>🔐 <strong>Area-based Alerts</strong> – Separate events for Area 1 and Area 2.</li>
  <li>✅ <strong>Alarm Reset</strong> – Auto reset when area is clear.</li>
</ul>

<hr>

<h2>🛠️ Hardware Requirements</h2>
<ul>
  <li>ESP32 development board</li>
  <li>2× Touch sensors (T0, T3 pins used)</li>
  <li>Servo motor (SG90 / MG90 recommended)</li>
  <li>2× Buzzers</li>
  <li>1× LED</li>
  <li>WiFi connection</li>
</ul>

<hr>

<h2>📂 Project Structure</h2>
<pre><code>Smart-Fencing-Security-System-for-Theft-Protection/
│
├── sketch_aug8a.ino    # Telegram API Setup to send Notification
├── sketch_aug8a2.ino   # Blynk app control logic
├── sketch_aug8a3.ino   # Latest code (optimized logic)
├── sketch_may24a.ino   # Touch detect → Buzzer & LED Blink
└── README.md
</code></pre>

<hr>

<h2>⚙️ Installation &amp; Setup</h2>
<ol>
  <li>
    Clone the repo:
    <pre><code>git clone https://github.com/smjoy222/Smart-Fencing-Security-System-for-Theft-Protection.git
cd Smart-Fencing-Security-System-for-Theft-Protection
</code></pre>
  </li>
  <li>Open the <code>.ino</code> file in <strong>Arduino IDE</strong> or <strong>PlatformIO</strong>.</li>
  <li>Install required libraries:
    <ul>
      <li><strong>Blynk</strong> (ESP32 version)</li>
      <li><strong>ESP32Servo</strong></li>
      <li><strong>WiFi.h</strong> (built-in for ESP32)</li>
    </ul>
  </li>
  <li>
    Update your WiFi and Blynk credentials in code:
    <pre><code class="language-cpp">char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";
char auth[] = "YourBlynkAuthToken";
</code></pre>
  </li>
  <li>Upload to your ESP32 board.</li>
</ol>

<hr>

<h2>📲 Blynk App Setup</h2>
<ul>
  <li>Add switches linked to Virtual Pins:
    <ul>
      <li><code>V0</code> → System ON/OFF</li>
      <li><code>V1</code> → LED Control</li>
      <li><code>V2</code> → Buzzer Control</li>
      <li><code>V3</code> → Notifications</li>
      <li><code>V5</code> → Touch Sensor Control</li>
    </ul>
  </li>
  <li>Add Events in Blynk Console:
    <ul>
      <li><code>area1_alert</code> → 🚨 Someone in Area 1</li>
      <li><code>area2_alert</code> → 🚨 Someone in Area 2</li>
      <li><code>alarm_cleared</code> → ✅ Safe, Alarm OFF</li>
    </ul>
  </li>
</ul>

<hr>

<h2>📸 Demo</h2>
<p><em>Add images or video links here — circuit diagram, mobile app screenshots, working demo GIFs.</em></p>

<hr>

<h2>🔮 Future Improvements</h2>
<ul>
  <li>Add <strong>Telegram / WhatsApp</strong> notifications if needed.</li>
  <li>Integrate with <strong>CCTV camera</strong>.</li>
  <li>Add <strong>battery backup</strong>.</li>
</ul>

<hr>

<h2>🤝 Contribution</h2>
<ol>
  <li>Fork this repository.</li>
  <li>Create your feature branch: <code>git checkout -b feature/new-idea</code></li>
  <li>Commit changes: <code>git commit -m "Added new feature"</code></li>
  <li>Push to the branch: <code>git push origin feature/new-idea</code></li>
  <li>Open a Pull Request.</li>
</ol>

<hr>

## 📜 License

![NOT OPEN SOURCE](https://img.shields.io/badge/license-NOT%20OPEN%20SOURCE-red)
![All Rights Reserved](https://img.shields.io/badge/copyright-All%20Rights%20Reserved-blueviolet)
![Year](https://img.shields.io/badge/year-2025-informational)

> This project is **NOT open source**.  
> **All rights reserved © 2025 Sazzad Mahmud Joy.**  
> Usage of this code requires **prior written permission** from the author.

**Contact:** <smjoy222@gmail.com>

<hr>


<p align="center">
  Made 💚 by Sazzad Mahmud Joy</strong>
</p>
