# arduino_temp_light_meter
The purpose of the project is to measure the temperature and light in an outdoor environment using an Arduino board and sensor equipment and then send the data collected to Thingspeak to analyze and display them. 

The Arduino Uno microprocessor in combination with the add-on Ethernet shield module and an additional module with sensors. The Ethernet Shield allows the Arduino Uno to connect to the internet via a simple RJ45 cable and connects to the Arduino via the SPI port.

The Arduino IDE was used to develop the code In C as it allows direct uploading of the code to the Arduino. The Cloud platform Thingspeak is an IOT data analysis service that allows for the collection, visualization and analysis of IOT data in the cloud designed by Mathworks.

The #secrets.h file contains the private credentials and connection details to connect the Arduino to the Thingspeak server. These details are the MAC address of the Arduino Board as well as the WEATHER STATION ID and API KEY of the Thingspeak server.

The #main.ino file is a Arduinio IDE file conating the main code and parameters for the sensor setup and establishing connection with the Thingspeak server.
