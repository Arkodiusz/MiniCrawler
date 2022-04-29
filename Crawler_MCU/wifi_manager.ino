const IPAddress WIFI_AP_LOCAL_IP(192,168,44,1);
const IPAddress WIFI_AP_GATEWAY(192,168,44,1);
const IPAddress WIFI_AP_SUBNET(255,255,255,0);
const char* WIFI_AP_SSID = "ESP_crawler_01";

void setupAccessPoint() {  
  Serial.println("ACCESS POINT");  
  prepareWiFiModule(); 
  Serial.print("Setting soft-AP configuration... ");
  Serial.println(WiFi.softAPConfig(WIFI_AP_LOCAL_IP, WIFI_AP_GATEWAY, WIFI_AP_SUBNET) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP SSID... ");
  Serial.println(WiFi.softAP(WIFI_AP_SSID) ? "Ready" : "Failed!");
  
  Serial.print("SSID: ");
  Serial.println(WIFI_AP_SSID);
    
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());   
  
  digitalWrite(LED_WIFI, LOW);
}

void connectToWiFi() {   
  Serial.println("STATION");  
  prepareWiFiModule(); 
  Serial.print("Connecting.");
  WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASSWORD); // wifi credentials imported from WiFiCredentials.h (not staged to git) 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
  }
  Serial.println();
  Serial.print("Connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_WIFI, LOW);    
}

void prepareWiFiModule() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("\nWiFi mode selected via SD2 pin: ");
}
