#include <ESP8266WiFi.h>
#include <espnow.h>


const char *ssid = "Anonymous";      // Replace with your Wi-Fi SSID
const char *password = "01102003";  // Replace with your Wi-Fi Password

int valve1=14;  //D5
int valve2=12; //D6
int valve3=13; //D7
int pump=15; //D8

typedef struct struct_message {
  int id;
  float moisture;
  bool status;
} struct_message;

struct_message myData;

void onReceive(uint8_t *macAddr, uint8_t *data, uint8_t dataLen) {
  memcpy(&myData, data, sizeof(myData));
  Serial.println("Packet received:");
  digitalWrite(LED_BUILTIN, HIGH);
   delay(150);
   digitalWrite(LED_BUILTIN, LOW);
   delay(50);
  Serial.print("ID: ");
  Serial.print(myData.id);
  Serial.print("  Moisture:  ");
  Serial.print(myData.moisture);
  Serial.print("  Status : ");
  Serial.println(myData.status);
  // Print received data
  // if(myData.id==1 && myData.status== false){
  //    digitalWrite(valve1,LOW);
  //    Serial.println("water level high, solonoid valve OFF");
  // }else{
  //   digitalWrite(valve1,HIGH);
  //   Serial.println("water level low, solonoid valve ON");
  // }else if(myData.id==2 && myData.status== false){
  //    digitalWrite(valve2,LOW);
  //    Serial.println("water level high, solonoid valve OFF");
  // }else{
  //   digitalWrite(valve2,HIGH);
  //   Serial.println("water level low, solonoid valve ON");
  // }
  // else if(myData.id==3 && myData.status== false){
  //    digitalWrite(valve3,LOW);
  //    Serial.println("water level high, solonoid valve OFF");
  // }else{
  //   digitalWrite(valve3,HIGH);
  //   Serial.println("water level low, solonoid valve ON");
  // }
  // if(myData.id==4 && myData.status==false){
  //   digitalWrite(pump,LOW);
  //   Serial.println("all valve is close and so pump ");
  // }
  // else{
  //   digitalWrite(pump,HIGH);
  //   Serial.println("pump is on");
  // }
  switch (myData.id) {
  case 1:
    if (myData.status == false) {
      digitalWrite(valve1, LOW);
      Serial.println("Water level high, solenoid valve 1 OFF");
    } else {
      digitalWrite(valve1, HIGH);
      Serial.println("Water level low, solenoid valve 1 ON");
    }
    break;

  case 2:
    if (myData.status == false) {
      digitalWrite(valve2, LOW);
      Serial.println("Water level high, solenoid valve OFF");
    } else {
      digitalWrite(valve2, HIGH);
      Serial.println("Water level low, solenoid valve ON");
    }
    break;

  case 3:
    if (myData.status == false) {
      digitalWrite(valve3, LOW);
      Serial.println("Water level high, solenoid valve OFF");
    } else {
      digitalWrite(valve3, HIGH);
      Serial.println("Water level low, solenoid valve ON");
    }
    break;

  case 4:
    if (myData.status == false) {
      digitalWrite(pump, LOW);
      Serial.println("All valves are closed, so the pump is OFF");
    } else {
      digitalWrite(pump, HIGH);
      Serial.println("Pump is ON");
    }
    break;

  default:
    Serial.println("Invalid ID");
    break;
}

    
  
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(valve3, OUTPUT);
  pinMode(pump, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW Initialization Failed");
    return;
  }

  // Register receive callback
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onReceive);
}

void loop() {
  // Do nothing, wait for data
}
