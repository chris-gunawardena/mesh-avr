#include "Arduino.h"
void setup();
void loop();
/* 
 * Example RN-XV Wireless Congiguration...
 * 
 * This program simply configures the network stack and joins network
 *
 * http://jeelabs.net/projects/hardware/wiki/JeeNode
 * Note: This version assumes wifi controller setup is completed before initializing software.
 * 
 * Testing Notes:
 * 1.) max stable SoftwareSerial baud rate (Wifly) = 19200. 38400 baud rate and higher fail to initialize the controller  
 * 2.) Hardware modification required if using the Sparkfun Xbee Explore board (remove and jumper board diode for DIN)
 * 3.) Sparkfun USB XBee explore board (unmodified) works well for configuring network parameters. You can leave ssid & passphrase out of code :). 
 * 4.) *** Note *** Sanguino board operates at 5V (including serial voltage). Modify board to include voltage divider to reduce single strength to 3.3v

 */

#include <WiFlyHQ.h> // Wireless Library for RN-XV Radio (For hardware see Sparkfun.com)

// Define Software emulated serial 
//SoftwareSerial wifiSerial(14,13);
// Initialize WiFly Software (Create instance...)
WiFly wifly;
int Pin_0 = 0;
int Pin_1 = 1;
int Pin_2 = 2;
int Pin_3 = 3;
int Pin_4 = 4;
int Pin_14 = 14;
int Pin_20 = 20;
int Pin_21 = 21;
int Pin_17 = 17;


void terminal();

void setup() {
	char buf[32]; // 32 byte buffer

	Serial.begin(57600); // serial to linux
	pinMode(Pin_1, OUTPUT);
	pinMode(Pin_2, OUTPUT);
	pinMode(Pin_3, OUTPUT);
	pinMode(Pin_4, OUTPUT);
	pinMode(Pin_14, OUTPUT);
	pinMode(Pin_20, OUTPUT);
	pinMode(Pin_21, OUTPUT);
	pinMode(Pin_17, OUTPUT);
	Serial.println("Powering On Pins 1-4");
	digitalWrite(Pin_0, HIGH);
	digitalWrite(Pin_1, HIGH);
	digitalWrite(Pin_2, HIGH);
	digitalWrite(Pin_3, HIGH);
	digitalWrite(Pin_4, HIGH);
	digitalWrite(Pin_14, HIGH);
	digitalWrite(Pin_20, HIGH);
	digitalWrite(Pin_21, HIGH);
	digitalWrite(Pin_17, HIGH);

/*
	Serial.println("Begin WiFi Config ");

	delay(200); // wait for the wifi controller to start before initializing.
	
	Serial.println("Waiting for controller to settle..."); // Print WiFly Device free memory as decimal value.
	delay(200); // wait for the wifi controller to start before initializing.


	Serial1.begin(19200); // open software serial port to WiFly controller (Sanguino)
	
	if (!wifly.begin(&Serial1, NULL)) {
		// Check to see if the libraries are loaded...
		Serial.println("Failed to start wifly controller\n\rPlease check configuration and try again...");
		terminal();
	}

	if (wifly.getFlushTimeout() != 10) {
		// Reset the message flush timeout to 10ms
		Serial.println("Reseting WiFly controller flush timeout to 10ms");
		wifly.setFlushTimeout(10); // do the setup...
		wifly.save(); // save config
		wifly.reboot(); // reboot controller...
	}

	// Join Wifi network....


	if (!wifly.isAssociated() ) {
		// configure wifly for network 
		Serial.println("Joining Network... Please wait");
		//wifly.setSSID(mySSID);
		//wifly.setPassphrase(myPassword);
		//wifly.enableDHCP(); // Note: Setup DDNS for wifly contolller... 

		// Check to see if the join worked.
		//if (!wifly.join()) {
		//	Serial.println("Joined wifi network!!! ");
		//} else {
		//	Serial.println("Failed to join wifi network :( ");
		//	terminal();
		//}

	} else {
		Serial.println("Aleady Joined Network..." );
	}
	
	// read wifi configuration...
	wifly.getGateway(buf, sizeof(buf));

	Serial.print("ping ");
	// print gateway
	Serial.print(buf);
	Serial.print(" ... ");

	if (wifly.ping(buf)) {
		// Attempt to ping the gateway
		Serial.println(" Ok! ");
	} else {
		Serial.println(" Failed to ping Gateway");
	}


	// Attempt to ping the outside world

	Serial.print("ping google.com... ");
	if (wifly.ping("google.com")) {
		Serial.println( " Ok " );	
	} else {
		Serial.println(" Failed to ping Google");
	}
	Serial.print("ping network host... ");
	if (wifly.ping("10.42.8.35")) {
		Serial.println( " Ok " );	
	} else {
		Serial.println(" Failed to ping network host");
	}
	
    // Setup for UDP packets, sent automatically /
    wifly.setIpProtocol(WIFLY_PROTOCOL_UDP);
    wifly.setHost("192.168.1.60", 8042);	// Send UDP packet to this server and port

    Serial.print("MAC: ");
    Serial.println(wifly.getMAC(buf, sizeof(buf)));
    Serial.print("IP: ");
    Serial.println(wifly.getIP(buf, sizeof(buf)));
    Serial.print("Netmask: ");
    Serial.println(wifly.getNetmask(buf, sizeof(buf)));
    Serial.print("Gateway: ");
    Serial.println(wifly.getGateway(buf, sizeof(buf)));

    wifly.setDeviceID("Wifly-UDP");
    Serial.print("DeviceID: ");
    Serial.println(wifly.getDeviceID(buf, sizeof(buf)));

    wifly.setHost("10.42.8.35", 8042);	// Send UPD packets to this server and port

    Serial.println("WiFly ready");

*/
}

uint32_t lastSend = 0;
uint32_t count=0;

void loop()
{
/*    
    digitalWrite(Pin_1, HIGH);
    Serial.println("1 On");
    delay(1500);
    Serial.println("1 OFF");
    digitalWrite(Pin_1, LOW);
    digitalWrite(Pin_2, HIGH);
    Serial.println("2 On");
    delay(1500);
    Serial.println("2 OFF");
    digitalWrite(Pin_2, LOW);
    digitalWrite(Pin_3, HIGH);
    Serial.println("3 On");
    delay(1500);
    Serial.println("3 OFF");
    digitalWrite(Pin_3, LOW);
    digitalWrite(Pin_4, HIGH);
    Serial.println("4 On");
    delay(1500);
    Serial.println("4 OFF");
    digitalWrite(Pin_4, LOW);

    if ((millis() - lastSend) > 1000) {
        count++;
	Serial.print("Sending message ");
	Serial.println(count);

	wifly.print("Hello, count=");
	wifly.println(count);
	lastSend = millis();
    }

    if (Serial.available()) {
       //  if the user hits 't', switch to the terminal for debugging 
        if (Serial.read() == 't') {
	    terminal();
	}
    }
   */

}






void terminal() {
	Serial.println("Terminal ready");
	while(1) {
		if(wifly.available() > 0 ) {
			// write wifi to serial 
			Serial.write(wifly.read());
		} 
		if (Serial.available()) {
			// Write serial to wifi
			wifly.write(Serial.read());
		}
	}

}


