# ESP32 LED Controller Web Server

This project is a simple web-based LED controller using an ESP32 microcontroller. It sets up a web server that allows users to turn an LED on and off via a browser interface.

## Features
- Connects to WiFi and serves a web page
- Provides buttons to turn an LED ON and OFF
- Displays the current LED state
- Includes a portfolio section with links to GitHub and LinkedIn

## Hardware Requirements
- ESP32 development board
- LED (connected to GPIO 23)
- Resistor (optional, e.g., 220Ω)
- Breadboard and jumper wires

## Software Requirements
- Arduino IDE with ESP32 board support
- Required libraries:
  - `WiFiClient.h`
  - `WebServer.h`
  - `ESPmDNS.h`

## Installation & Setup
1. Clone this repository:
   ```bash
   git clone https://github.com/QueshYoda/ESP32-LED-Controller.git
   ```
2. Open the project in Arduino IDE.
3. Modify the WiFi credentials in the code:
   ```cpp
   const char* ssid = "your-SSID";
   const char* password = "your-PASSWORD";
   ```
4. Upload the code to your ESP32 board.
5. Open the Serial Monitor (115200 baud) to get the IP address assigned to the ESP32.
6. Enter the IP address in a web browser to access the controller.

## How It Works
- The ESP32 connects to a WiFi network.
- A web server is created on port 80.
- When a client accesses the web page, they can toggle the LED by clicking buttons.
- The ESP32 processes GET requests and updates the LED state accordingly.
- A simple HTML interface is generated dynamically and served to the client.

## Web Interface
- A minimalistic UI with ON and OFF buttons.
- Portfolio section with links to GitHub and LinkedIn.

## Example Output
### Serial Monitor Output
```
Connecting to your-SSID
WiFi Connected :)
IP address: 192.168.1.100
New Client : 192.168.1.105
LED ON
Client disconnected
```

### Web Page
- A page displaying buttons to control the LED state.

## License
This project is licensed under the MIT License.

## Author
**Baha Demirtaş**
- [GitHub](https://github.com/QueshYoda)
- [LinkedIn](https://www.linkedin.com/in/baha-demirta%C5%9F-175117199/)

