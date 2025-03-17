# WiFi-Controlled LED Ring Light

A creative exploration project combining 3D printing, web technology, and microcontroller programming to create a real-world IoT device. This project demonstrates how modern tools and AI (like Cursor) can help bridge the gap between software development and physical computing, even without extensive domain expertise.

![Project Status](https://img.shields.io/badge/status-prototype-orange)
![License](https://img.shields.io/badge/license-MIT-green)

## 🎯 Project Goals

- Explore the intersection of software and hardware
- Learn about IoT development with ESP8266
- Combine 3D printing with electronics
- Create a web-controlled LED system
- Test the capabilities of AI-assisted development

## 🛠️ Technologies Used

- **Hardware**
  - ESP8266 Microcontroller
  - 8 LEDs in ring configuration
  - 3D printed enclosure a ring light
- **Software**
  - PlatformIO for ESP8266 development
  - Arduino framework
  - ESP8266WebServer for web interface
  - HTML/CSS for control panel
- **Tools**
  - Cursor IDE with AI assistance
  - 3D printing software freeCAD & Bambu Studio
  - Git for version control

## ✨ Features

- WiFi-enabled LED control
- Web-based control panel
- Two operation modes:
  - Sequence Mode: LEDs light up in sequence
  - All LEDs Mode: All LEDs light simultaneously
- Adjustable sequence speed (10ms - 2000ms)
- Mobile-friendly interface
- Secure credentials management

## 📝 Prerequisites

- PlatformIO IDE (or VSCode with PlatformIO extension)
- ESP8266 development board
- 8 LEDs
- Basic electronic components (resistors, wires)
- 3D printer (for enclosure)
- WiFi network

## 🚀 Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/technala/Ring-light.git
   cd wifi-led-ring
   ```

2. **Set up WiFi credentials**
   - Copy `src/credentials.example.h` to `src/credentials.h`
   - Edit `credentials.h` with your WiFi details:
     ```cpp
     const char* WIFI_SSID = "Your_WiFi_Name";
     const char* WIFI_PASSWORD = "Your_WiFi_Password";
     ```

3. **Hardware Setup**
   - Connect 8 LEDs to pins D0-D7 on the ESP8266
   - Each LED should have an appropriate resistor
   - Print the enclosure using provided 3D models

4. **Upload the Code**
   - Open the project in PlatformIO
   - Build and upload to your ESP8266

5. **Access the Control Panel**
   - The ESP8266 will display its IP address in the serial monitor
   - Open that IP address in a web browser
   - Use the interface to control your LED ring

## 📐 Hardware Configuration

The LEDs are connected to the following GPIO pins:
- D0 (GPIO16)
- D1 (GPIO5)
- D2 (GPIO4)
- D3 (GPIO0)
- D4 (GPIO2)
- D5 (GPIO14)
- D6 (GPIO12)
- D7 (GPIO13)

## 🎨 Customization

You can customize this project by:
- Modifying the web interface design
- Adding new LED patterns
- Creating different 3D printed enclosures
- Implementing additional control features

## 📚 Learning Journey

This project serves as an example of how modern development tools and AI assistance can help create physical computing projects without extensive prior knowledge. It demonstrates:

- Rapid prototyping with AI assistance
- Integration of various technologies
- Practical application of web development
- Basic electronics and 3D printing

## 🤝 Contributing

Feel free to fork this project and adapt it to your needs. If you make improvements, consider submitting a pull request!

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

- Cursor IDE for AI assistance in development
- ESP8266 community for excellent documentation
- Open source community for various libraries and tools

---

*This project was created as an exploration of bringing programming skills into the physical world, combining 3D printing, web technology, and microcontroller programming with the assistance of AI tools.* 