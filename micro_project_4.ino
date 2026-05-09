#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>   // If NodeMCU ESP8266

// ================= LCD =================
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// ================= BMP280 =================
Adafruit_BMP280 bmp;

// ================= WiFi =================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

// ================= Pins =================
int tempPin = A0;      // LM35
int gasPin = A1;       // MQ2
int pirPin = 8;        // PIR Sensor

void setup() {

  Serial.begin(9600);

  // LCD
  lcd.begin(16, 2);

  // PIR
  pinMode(pirPin, INPUT);

  // BMP280
  if (!bmp.begin(0x77)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  // WiFi Connect
  WiFi.begin(ssid, password);

  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Gas M Pre");
}

void loop() {

  // ================= READ SENSORS =================

  // LM35
  int tempReading = analogRead(tempPin);
  float voltage = tempReading * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  // MQ2
  int gasValue = analogRead(gasPin);

  // PIR
  int motion = digitalRead(pirPin);

  // BMP280
  float pressure = bmp.readPressure() / 100.0;

  // ================= LCD DISPLAY =================

  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 1);
  lcd.print((int)temperature);

  lcd.setCursor(5, 1);
  lcd.print(gasValue);

  lcd.setCursor(10, 1);
  lcd.print(motion ? "Y" : "N");

  lcd.setCursor(12, 1);
  lcd.print((int)pressure);

  // ================= SERIAL MONITOR =================

  Serial.print("Temp: ");
  Serial.println(temperature);

  Serial.print("Gas: ");
  Serial.println(gasValue);

  Serial.print("Motion: ");
  Serial.println(motion);

  Serial.print("Pressure: ");
  Serial.println(pressure);

  Serial.println("------");

  // ================= ALERT CONDITIONS =================

  bool tempAlert = temperature > 40;
  bool gasAlert = gasValue > 400;   // Adjust threshold
  bool motionAlert = motion == 1;

  // ================= WEB SERVER =================

  WiFiClient client = server.available();

  if (client) {

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<html><head>");
    client.println("<meta http-equiv='refresh' content='2'>");
    client.println("<title>LAB SECURITY</title>");
    client.println("</head><body>");

    client.println("<h1>LAB SECURITY SYSTEM</h1>");

    client.print("<p>Temperature: ");
    client.print(temperature);
    client.println(" C</p>");

    client.print("<p>Gas Level: ");
    client.print(gasValue);
    client.println("</p>");

    client.print("<p>Motion: ");
    client.println(motionAlert ? "DETECTED" : "SAFE");

    client.print("<p>Pressure: ");
    client.print(pressure);
    client.println(" hPa</p>");

    // ALERTS
    if (tempAlert || gasAlert || motionAlert) {

      client.println("<h2 style='color:red;'>🚨 ALERT ACTIVE 🚨</h2>");

      if (tempAlert)
        client.println("<p>🔥 HIGH TEMPERATURE!</p>");

      if (gasAlert)
        client.println("<p>💨 GAS LEAK DETECTED!</p>");

      if (motionAlert)
        client.println("<p>👤 PERSON DETECTED!</p>");

    } else {

      client.println("<h2 style='color:green;'>ALL SAFE ✅</h2>");
    }

    client.println("</body></html>");

    delay(1);
    client.stop();
  }

  delay(1000);
}