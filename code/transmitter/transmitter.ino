#define BLYNK_TEMPLATE_ID "TMPL3_tA-Yi59"
#define BLYNK_TEMPLATE_NAME "soil moisture"
#define BLYNK_AUTH_TOKEN "uO_lvUzWKevfoFZS6J3xQc7XPHK621vs"
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
const char *ssid = "Anonymous";      // Replace with your Wi-Fi SSID
const char *pass = "01102003";  // Replace with your Wi-Fi Password

uint8_t receiverMAC[] = {0x40, 0xF5, 0x20, 0x33, 0xB7,0x79}; // Replace with receiver MAC

int A=5; //D1
int B=16;  //D0
int s1,s2,s3;
float value;
int sense_Pin;
int llimit=15;
int ulimit=75;

typedef struct struct_message{
  int id;
  float moisture;
  bool status;
} struct_message;

struct_message myData;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is ON for built-in LED)
  // pinMode(LED_BUILTIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  pinMode(A, OUTPUT); //D0
  pinMode(B, OUTPUT); //D1
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
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

  // Register send callback
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(onSent);

  // Add peer
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Initialize data
  myData.id = 1;
  myData.moisture = 25.0;
  myData.status = true;
  
 
  
}

// void blink(){
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(350);
//    digitalWrite(LED_BUILTIN, LOW);
// }

void onSent(uint8_t *macAddr, uint8_t sendStatus){
  Serial.print("Send Status: ");
  Serial.println(sendStatus == 0 ? "Success" : "Fail");
  // delay(200);
}

int action(struct_message myData) {
  Blynk.logEvent("system_start");

  if (myData.id == 1) {
        if (myData.moisture >= ulimit) {
            myData.status = false;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to reciever");
            Blynk.virtualWrite(V4,0);
            return 0;
        } else if (myData.moisture <= ulimit) { // Corrected `value` to `myData.moisture`
            // digitalWrite(valve1, HIGH);
            myData.status = true;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to reciever");
            Blynk.virtualWrite(V4, 1);
            return 1;
        }
    }else if (myData.id == 2){
        if (myData.moisture >= ulimit) {
            myData.status = false;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            // digitalWrite(valve2, LOW);
            Blynk.virtualWrite(V4, 0);
            return 0;
        } else if (myData.moisture <= ulimit) { // Corrected `value` to `myData.moisture`
            // digitalWrite(valve1, HIGH);
            Blynk.virtualWrite(V4, 1);
            myData.status = true;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            return 1;
        }
    } else if (myData.id == 3){
        if (myData.moisture >= ulimit) {
            myData.status = false;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            // digitalWrite(valve2, LOW);
            Blynk.virtualWrite(V4, 0);
            return 0;
        } else if (myData.moisture <= ulimit) { // Corrected `value` to `myData.moisture`
            // digitalWrite(valve1, HIGH);
            Blynk.virtualWrite(V4, 1);
            myData.status = true;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            return 1;
        }
    }else {
        if (myData.moisture >= ulimit) {
            myData.status = false;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            // digitalWrite(valve2, LOW);
            Blynk.virtualWrite(V4, 0);
            return 0;
        } else if (myData.moisture <= ulimit) { // Corrected `value` to `myData.moisture`
            // digitalWrite(valve1, HIGH);
            Blynk.virtualWrite(V4, 1);
            myData.status = true;
            esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
            // Serial.println("Packet sent to esp");
            return 1;
        }
    }
    
    // delay(1500);
    return 0; // Added default return to handle cases where no condition is met
}

void sendSensor(){
//////// ****SENSOR 1****///////////   
   digitalWrite(A,LOW);   // A=0
   digitalWrite(B,LOW);   // B=0
   delay(500);
   value = analogRead(sense_Pin);
  //  Serial.print(value);
   myData.moisture=map(value,300,800,100,0);
   myData.id=1;
   Serial.print("MOISTURE LEVEL of sensor ");
   Serial.print(myData.id);
   Serial.print(" ");
   Serial.println(myData.moisture);
   Blynk.virtualWrite(V1,myData.moisture);
   s1=action(myData);
   Serial.println(" ");
   delay(500);
  //  Blynk.virtualWrite(V4,s1);
//////// ****SENSOR 2****/////////// 
   digitalWrite(A,HIGH);   //A=1
   digitalWrite(B,LOW);  //B=0
   delay(500);
   value= analogRead(sense_Pin);
  //  Serial.print(value);
   myData.moisture=map(value,300,800,100,0);
   myData.id=2;
   Serial.print("MOISTURE LEVEL of sensor ");
   Serial.print(myData.id);
   Serial.print(" ");
   Serial.println(myData.moisture);
   Blynk.virtualWrite(V2,myData.moisture);
   s2=action(myData);
   Serial.println(" ");
   delay(500);
  //  Blynk.virtualWrite(V4,s2);
//////// ****SENSOR 3****/////////// 
   digitalWrite(A,LOW);   //A=0
   digitalWrite(B,HIGH);    //B=1
   delay(500);
   value= analogRead(sense_Pin);
  //  Serial.print(value);
   myData.moisture=map(value,300,800,100,0);
   myData.id=3;
   Serial.print("MOISTURE LEVEL of sensor ");
   Serial.print(myData.id);
   Serial.print(" ");   
   Serial.println(myData.moisture);
   Blynk.virtualWrite(V3,myData.moisture);
   s3=action(myData);
   Serial.println(" ");
   delay(500);
  //  Blynk.virtualWrite(V4,s3);
  Serial.println(s1);
  Serial.println(s2);
  Serial.println(s3);
  if(s1==0 & s2==0 & s3==0){
      myData.id=4;
      myData.status=false;
      myData.moisture=0;
      esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
      Blynk.virtualWrite(V0,0);
      Blynk.logEvent("water_pump_off");
    }
  else{
      myData.id=4;
      myData.status=true;
      myData.moisture=0;
      esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
      Blynk.virtualWrite(V0,1);
      Blynk.logEvent("water_pump_on");
  }
}


void loop(){
  // Update data
  // myData.temperature += 0.1;
  // myData.humidity -= 0.1;
  sendSensor();
  // Send data
  // esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));
  // Serial.println("Packet sent");
  delay(2000);
}
