#include <Ethernet.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

byte mac[] = SECRET_MAC;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

//channel number
unsigned long channelnumber = 1817654;
//private write key
const char * mywriteapikey = "C47G1D0L181NLKNE";

/* variables */

//initialize variables
float tempK=0,tempC=0;
int light_res_pin = 0;
int led_pin = 7;
int buzzer_pin = 9;
int light_value;
//flag to initiate buzzer
int buzz_init=0;


void setup() {
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
      
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

  // Initialize ThingSpeak server
  ThingSpeak.begin(client);  

  //set pin 7 to output for led
  pinMode(led_pin, OUTPUT);

  //set pin 9 to output for buzzer
  pinMode(buzzer_pin, OUTPUT);


}

void loop() {
  //read light value from sensor
  light_value = analogRead(light_res_pin);
  //read raw temp value from sensor and convert to kelvin
  tempK = analogRead(3) * 0.004882812 * 100;
  //convert temp from kelvin to celsius
  tempC = tempK - 273.15;

  //collect data until sunrise
  if(light_value<450)
  {
    if (buzz_init<1)
    {
      //tone buzzer when start collecting data
      tone(buzzer_pin, 1000);
      delay(1000);
      noTone(buzzer_pin);
      delay(1000); 
      //set buzzer to flag to 1 to stop continuous buzzing
      buzz_init=1;
    }
    //blinking led
    digitalWrite(led_pin, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000); // wait for a second
    digitalWrite(led_pin, LOW); // turn the LED off by making the voltage LOW
    delay(1000);
    //write values to ThingSpeak server
    ThingSpeak. setField(1,tempC);
    ThingSpeak. setField(2,light_value);
    ThingSpeak. writeFields(channelnumber, mywriteapikey);
  }
  else
  {
    //tone buzzer when stop collecting data
    tone(buzzer_pin, 1000); 
    delay(1000); 
    noTone(buzzer_pin);
    delay(1000); 
  }
  
  delay(10000); // No need to read the counter too often.
 
}
