#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// Motor control pins
const int IN1 = 32;
const int IN2 = 33;
const int IN3 = 26;
const int IN4 = 12;

// Ultrasonic sensor pins
const int trigPin = 4;
const int echoPin = 5;

// IR sensor pins
const int irFrontRight = 15;
const int irFrontLeft = 14;
const int irSideLeft = 13;
const int irSideRight = 23;

// Distance threshold (in cm)
const int stopDistance = 20;

// WiFi Credentials
const char* ssid = "Samer Malaeb";
const char* password = "Millo_Isac";

// Web Server
WebServer server(80);

void serveFile(const char* path, const char* contentType) {
  File file = SPIFFS.open(path, "r");
  server.streamFile(file, contentType);
  file.close();
}

void setupWebsite() {
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Configure routes
  server.on("/", HTTP_GET, []() {
    serveFile("/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, []() {
    serveFile("/style.css", "text/css");
  });

  server.on("/app.js", HTTP_GET, []() {
    serveFile("/app.js", "application/javascript");
  });

  server.on("/sensor-data", HTTP_GET, []() {
    server.send(200, "application/json", "{\"waterLevel\":75}"); // Example data
  });

  server.on("/control/refill-water", HTTP_GET, []() {
    server.send(200, "text/plain", "Refill Started");
  });

  // Start server
  server.begin();
  Serial.println("Web server started");
}

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // IR sensors
  pinMode(irFrontRight, INPUT);
  pinMode(irFrontLeft, INPUT);
  pinMode(irSideLeft, INPUT);
  pinMode(irSideRight, INPUT);

  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize website
  setupWebsite();
}

void loop() {
  // --- Read Ultrasonic Distance ---
  server.handleClient();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // --- Read IR sensors ---
  bool frontRight = digitalRead(irFrontRight); // 1 = no surface
  bool frontLeft = digitalRead(irFrontLeft);
  bool sideLeft = digitalRead(irSideLeft);
  bool sideRight = digitalRead(irSideRight);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Front IR L:");
  Serial.print(frontLeft);
  Serial.print(" R:");
  Serial.print(frontRight);
  Serial.print(" | Side IR L:");
  Serial.print(sideLeft);
  Serial.print(" R:");
  Serial.println(sideRight);

  // --- Main Logic ---
  if ((frontLeft == 0 && frontRight == 0) && distance > stopDistance) {
    // Move forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    // Stop first
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(300); // short pause

    // --- Decide turning ---
    if (sideLeft == 0 && sideRight == 1) {
      // Turn left: Right motors forward, Left motors backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (sideRight == 0 && sideLeft == 1) {
      // Turn right: Left motors forward, Right motors backward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {
      // Stay stopped
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }

  delay(100);
}
