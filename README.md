# hubbub
Project repository for INF1510: User Oriented Design at the University of Oslo.
Goal of the project is to prototype an arduino-based solution to assist the visually impaired traveling with public transit.

## Solution
The solution consists of three parts: a sender component on the buss-stop, a receiver component on the buss and a simple webserver to facilitate communication between the two components.
To communicate over the internet, an [arduino-enabled](https://github.com/esp8266/Arduino) ESP8266-module is used by both components. The server is programmed with [Node.js](https://nodejs.org/en/).
