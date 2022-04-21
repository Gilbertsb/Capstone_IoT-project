
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(5, 6); //Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels

 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
 
#define LED_BUILTIN 16
#define SENSOR  2
 
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
float totalLitres;

// StaticJsonBuffer<1000> jsonBuffer;
// JsonObject& data = jsonBuffer.createObject();
 
void pulseCounter()
{
  pulseCount++;
}
 

 
void setup()
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  delay(10);
 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);
 
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  nodemcu.begin(9600);
 
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
}
 
void loop()
{
  

  currentMillis = millis();
  if (currentMillis - previousMillis > interval) 
  {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;
 
  
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();
 
    flowMilliLitres = (flowRate / 60) * 1000;
    flowLitres = (flowRate / 60);
 
    totalMilliLitres += flowMilliLitres;
    totalLitres += flowLitres;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(float(flowRate));  // Print the integer part of the variable
    Serial.print("L/Sec");
    Serial.print("\t");       // Print tab space

    nodemcu.write(float(flowRate));
 
    display.clearDisplay();
    
    display.setCursor(5,0);  //oled display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Water Flow Status");
    display.println("------------------");

    if (float(flowRate)>0){
      display.println("WATER IS FLOWING");
    }
    else{
      display.println("WATER IS NOT FLOWING");
      
    }
    display.print("Amount of water:");
    display.print(float(flowRate));
    display.println("ml/s");
    display.display();
    
   
//    data["Water"] = float(flowRate);
//    //Send data to NodeMCU
//    data.printTo(nodemcu);
//    jsonBuffer.clear();
  }
}
