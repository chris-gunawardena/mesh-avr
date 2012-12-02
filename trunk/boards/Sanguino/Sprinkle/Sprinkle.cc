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

/*
Map IO Port to Sprinkler Manifold Solnoids
*/
int Relay_0 = 5;
int Relay_1 = 1;
int Relay_2 = 2;
int Relay_3 = 3;
int Relay_4 = 4;
int Relay_5 = 20;
int Relay_6 = 19;
int Relay_7 = 18;
int Relay_8 = 17;
int Relay_9 = 16;
// Note Relays 0 & 15 not connected at this time.

void terminal();

void setup() {
	char buf[32]; // 32 byte buffer

	// Set Relay Pins to Outputs
	pinMode(Relay_0, OUTPUT);
	pinMode(Relay_1, OUTPUT);
	pinMode(Relay_2, OUTPUT);
	pinMode(Relay_3, OUTPUT);
	pinMode(Relay_4, OUTPUT);
	pinMode(Relay_5, OUTPUT);
	pinMode(Relay_6, OUTPUT);
	pinMode(Relay_7, OUTPUT);
	pinMode(Relay_8, OUTPUT);
	pinMode(Relay_9, OUTPUT);
	
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

    //wifly.setDeviceID("Wifly-UDP");
    //Serial.print("DeviceID: ");
    //Serial.println(wifly.getDeviceID(buf, sizeof(buf)));

    //wifly.setHost("10.42.8.35", 8042);	// Send UPD packets to this server and port

    Serial.println("WiFly ready");

}

uint32_t lastSend = 0;
uint32_t count=0;
int delay_time = 500;
void loop()
{


    digitalWrite(Relay_0, HIGH);
    delay(delay_time);
    digitalWrite(Relay_0, LOW);
    
    digitalWrite(Relay_1, HIGH);
    delay(delay_time);
    digitalWrite(Relay_1, LOW);
    
    digitalWrite(Relay_2, HIGH);
    delay(delay_time);
    digitalWrite(Relay_2, LOW);
    
    digitalWrite(Relay_3, HIGH);
    delay(delay_time);
    digitalWrite(Relay_3, LOW);
    
    digitalWrite(Relay_4, HIGH);
    delay(delay_time);
    digitalWrite(Relay_4, LOW);

    digitalWrite(Relay_5, HIGH);
    delay(delay_time);
    digitalWrite(Relay_5, LOW);

    digitalWrite(Relay_6, HIGH);
    delay(delay_time);
    digitalWrite(Relay_6, LOW);
    
    digitalWrite(Relay_7, HIGH);
    delay(delay_time);
    digitalWrite(Relay_7, LOW);
    
    digitalWrite(Relay_8, HIGH);
    delay(delay_time);
    digitalWrite(Relay_8, LOW);
    
    digitalWrite(Relay_9, HIGH);
    delay(delay_time);
    digitalWrite(Relay_9, LOW);


    delay(delay_time);
    delay(delay_time);




    /*
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


