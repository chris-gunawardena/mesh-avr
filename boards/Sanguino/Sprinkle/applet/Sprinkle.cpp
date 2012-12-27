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
 *  
 * Weather Listings (REST)
 * http://graphical.weather.gov/xml/rest.php
 */

// Include PROGMEM library (Access Flash Memory instead of SRAM...)
// reduce data copy from flash to SRAM with static content...
#include <avr/pgmspace.h>
#include <WiFlyHQ.h> // Wireless Library for RN-XV Radio (For hardware see Sparkfun.com)

//Define a section of flash for program memory 
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
// Define routine for accessing PROGMEM strings...
#undef PSTR
#define PSTR(s) (__extension__({ static prog_char __c[] PROGMEM = (s); &__c[0];}))


// Define Software emulated serial 
//SoftwareSerial wifiSerial(14,13);
// Initialize WiFly Software (Create instance...)
WiFly wifly;

/*
Map IO Port to Sprinkler Manifold Solnoids
*/

// define 10 sprinkling zones. Zone map to be determined by wiring....
int zones[] = {5,1,2,3,4,20,19,18,17,16};
// Note Relays 0 & 15 not connected at this time.

void terminal();
void setup() {
	char buf[32]; // 32 byte buffer

    // set all the zone pins to outputs...
    for ( int x =0; x < sizeof(zones); x++) {
	    // Set Relay Pins to Outputs
        pinMode(zones[x], OUTPUT);
    }	
	// Serial coniguration for devices
	Serial.begin(57600); // serial to linux
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

    //wifly.setDeviceID("Wifly-UDP");
    //Serial.print("DeviceID: ");
    //Serial.println(wifly.getDeviceID(buf, sizeof(buf)));

    //wifly.setHost("10.42.8.35", 8042);	// Send UPD packets to this server and port

    Serial.println("WiFly ready");

}

uint32_t lastSend = 0;
uint32_t count=0;
int delay_time = 300000; // approximately 5 mintes
void loop()
{


    for (int x=0; x < sizeof(zones); x++) {
        // turn on each zone 
        // Wait 
        digitalWrite(zones[x], HIGH);
        // Wait
        delay(delay_time);
        digitalWrite(zones[x], LOW);
    }
    delay(delay_time);





}


void testNetwork() {
    // perform additional network connectivity tests.

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


