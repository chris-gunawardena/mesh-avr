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
 */

#include <WiFlyHQ.h> // Wireless Library for RN-XV Radio (For hardware see Sparkfun.com)
#include <SoftwareSerial.h>
#include <wifi_cfg.h>

// Define Software emulated serial 
SoftwareSerial wifiSerial(5,4);
// Initialize WiFly Software (Create instance...)
WiFly wifly;

void terminal();

void setup() {
	char buf[32]; // 32 byte buffer
	Serial.begin(57600); // serial to linux
	Serial.println("Begin WiFi Config ");

	delay(2000); // wait for the wifi controller to start before initializing.
	
	Serial.println("Waiting for controller to settle..."); // Print WiFly Device free memory as decimal value.
	delay(2000); // wait for the wifi controller to start before initializing.


	wifiSerial.begin(19200); // open software serial port to WiFly controller
	
	if (!wifly.begin(&wifiSerial, &Serial)) {
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
	
    /* Setup for UDP packets, sent automatically */
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
}

uint32_t lastSend = 0;
uint32_t count=0;

void loop()
{
    if ((millis() - lastSend) > 1000) {
        count++;
	Serial.print("Sending message ");
	Serial.println(count);

	wifly.print("Hello, count=");
	wifly.println(count);
	lastSend = millis();
    }

    if (Serial.available()) {
        /* if the user hits 't', switch to the terminal for debugging */
        if (Serial.read() == 't') {
	    terminal();
	}
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


