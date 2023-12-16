#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#define SDA 13 //Define SDA pins
#define SCL 14 //Define SCL pins
LiquidCrystal_I2C lcd(0x27,16,2);
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>                                                                                                                    
WiFiUDP udp;    

const char* ssid = "Darshul Phone";
const char* password = "GoogleWarrior";
const char* mqttServer = "darshilpsheth.duckdns.org";
const int mqttPort = 1883;
const char* subTopic = "game";

const char *host = "darshilpsheth.duckdns.org"; // Replace with your daemon's IP
const int port = 8080;       // Replace with your daemon's port


// define the symbols on the buttons of the keypad
char keys[4][4] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
};
byte rowPins[4] = {14, 27, 26, 25}; // connect to the row pinouts of the keypad
byte colPins[4] = {13, 21, 22, 23}; // connect to the column pinouts of the keypad

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Convert payload to a string
  payload[length] = '\0'; // Null-terminate the payload
  char *message = (char*)payload;
  lcd.clear();
  lcd.setCursor(0,0);

   if (length > 16) {
      char part1[17];  // Part 1 can contain up to 16 characters
      char part2[17];  // Part 2 can contain the remaining characters

      strncpy(part1, message, 16);
      part1[16] = '\0';  // Null-terminate the string

      strcpy(part2, message + 16);

      lcd.print(part1);
      lcd.setCursor(0,1);
      lcd.print(part2);
      
  } else {
      lcd.print(message);
  }

}

void reconnect() {
  while (!client.connected()) {
  Serial.println("Connecting to MQTT...");
  if (client.connect("ESP32Client")) {
    Serial.println("Connected to MQTT");
    client.subscribe(subTopic);
  } else {
    Serial.print("Failed with state ");
    Serial.print(client.state());
    delay(2000);
  }
  }
}

void setup() {
 Wire.begin(SDA, SCL); // attach the IIC pin
 Serial.begin(115200); // Start serial communication at 115200 baud rate
 setup_wifi();
 client.setServer(mqttServer, mqttPort);
 client.setCallback(callback);
 if (!i2CAddrTest(0x27)) {
 lcd = LiquidCrystal_I2C(0x3F, 16, 2);
 }
 lcd.init(); // LCD driver initialization
 lcd.backlight(); // Open the backlight
 lcd.setCursor(0,0); // Move the cursor to row 0, column 0
}
void loop() {
  if (!client.connected()) {
  reconnect();
  }
  client.loop();
 
  // Get the character input
 char keyPressed = myKeypad.getKey();
 // If there is a character input, sent it to the serial port
 if (keyPressed == '2') {
  Serial.println("North");
  //lcd.setCursor(0,0);
  //lcd.print("North");
  sendUDP("north");
 }
 if (keyPressed == '4') {
  Serial.println("West");
  //lcd.setCursor(0,0);
  //lcd.print("West");
  sendUDP("west");
 }
 if (keyPressed == '5') {
  Serial.println("East");
  //lcd.setCursor(0,0);
  //lcd.print("East");
  sendUDP("east");
 }
 if (keyPressed == '8') {
  Serial.println("South");
  //lcd.setCursor(0,0);
  //lcd.print("South");
  sendUDP("south");
 }
}

bool i2CAddrTest(uint8_t addr) {
 Wire.begin();
 Wire.beginTransmission(addr);
 if (Wire.endTransmission() == 0) {
 return true;
 }
 return false;
}

//receives and listens to any data is put through sendUDP()
void sendUDP(const char *message) {
  udp.beginPacket(host, port);
  udp.print(message);
  udp.endPacket();
}
