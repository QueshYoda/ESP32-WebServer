#include <Arduino.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Network credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// Set webserver on port 80
WiFiServer server(80);

// Store HTTP request
String header;

// To store current output state
String ledstate = "off";

// Set GPIO pin for LED
const int led_GPIO = 23;

// Current Time
unsigned long currTime = millis();
// Previous Time
unsigned long prevTime = 0;
// Define timeout in milliseconds
const long timeout = 70000;

void wifiConnect() {
  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" . ");
  }

  // Print IP and status
  Serial.println("\nWiFi Connected :)");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  // Set output
  pinMode(led_GPIO, OUTPUT);

  wifiConnect();

  server.begin();
}

void loop() {
  // Listen for clients
  WiFiClient client = server.available();

  if (client) {
    currTime = millis();
    prevTime = currTime;

    Serial.printf("New Client : ");
    Serial.println(client.remoteIP());

    String currLine = ""; // Hold data from client

    while (client.connected() && currTime - prevTime <= timeout) {
      currTime = millis();

      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n') {
          if (currLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Select LED status
            if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("LED ON");
              ledstate = "on";
              digitalWrite(led_GPIO, HIGH);
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("LED OFF");
              ledstate = "off";
              digitalWrite(led_GPIO, LOW);
            }

            // Display HTML page
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; margin: 50px; }");
            client.println(".button { font-size: 20px; padding: 10px 20px; border: none; cursor: pointer; border-radius: 5px; }");
            client.println(".on { background-color: green; color: white; }");
            client.println(".off { background-color: red; color: white; }");
            client.println(".portfolio { margin-top: 50px; padding: 20px; background-color: #f4f4f4; border-radius: 10px; }");
            client.println("a { text-decoration: none; color: blue; }");
            client.println("</style>");
            client.println("</head><body>");
            client.println("<h1>ESP32 LED Controller</h1>");

            if (ledstate == "off") {
              client.println("<p><a href=\"/led/on\"><button class=\"button on\">TURN ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/led/off\"><button class=\"button off\">TURN OFF</button></a></p>");
            }

            // Portfolio Section
            client.println("<div class=\"portfolio\">");
            client.println("<h2>About Me</h2>");
            client.println("<p>Hi, I'm a Computer Engineering student passionate about embedded systems, IoT, network automation and cloud native.</p>");
            client.println("<p>Check out my projects:</p>");
            client.println("<p><a href=\"https://github.com/QueshYoda\" target=\"_blank\">GitHub</a> | <a href=\"https://www.linkedin.com/in/baha-demirtas/\" target=\"_blank\">LinkedIn</a></p>");
            client.println("</div>");

            client.println("</body></html>");
            client.println();

            break;
          } else {
            currLine = "";
          }

        } else if (c != '\r') {
          currLine += c;
        }
      }
    }

    // Clear header
    header = "";
    // Close connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
