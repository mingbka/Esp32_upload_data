#include <WiFi.h>
#include <HTTPClient.h>

// Thông tin Wi-Fi
const char* ssid = "Tien Duong";
const char* password = "tumotden9";

// Server URL
const char* serverURL = "https://wsnweb.pythonanywhere.com/espdata/api/receive-data/";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    float temperature = random(200, 300) / 10.0;  
    float humidity = random(500, 800) / 10.0; 
    int node = random(1,3);

    String jsonData = "{\"node\": " + String(node) + ", \"temperature\": " + String(temperature, 1) + ", \"humidity\": " + String(humidity, 1) + "}";
    Serial.println("Sending data: " + jsonData); 
    // Gửi dữ liệu
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println("HTTP Request successful");
      String response = http.getString();
      Serial.println(response);
    } 
    else {
      Serial.print("HTTP Request failed, error code: ");
      Serial.println(httpResponseCode);

      Serial.print("Error message: ");
      Serial.println(http.errorToString(httpResponseCode));
    }
    http.end();
  }
  delay(60000);  // Gửi mỗi 60 giây
}

