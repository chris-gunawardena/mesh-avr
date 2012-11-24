/* 
 * Example RN-XV Wireless Congiguration...
 * 
 * This program simply configures the network stack and joins network
 *
 * http://jeelabs.net/projects/hardware/wiki/JeeNode
 * 
 * Remove WiFlyHQ library, use manual method instead...
 * Note: This progeam assumes wifi controller has been manually configured (and saved).
 * This eliminates the requirement to configure network information (ssid, passphrase, etc)
 * Goal, reduction in program size
 */

//#include <WiFlyHQ.h> // Wireless Library for RN-XV Radio (For hardware see Sparkfun.com)
#include <SoftwareSerial.h>
#include <wifi_cfg.h>

// Define Software emulated serial 
SoftwareSerial wifi(SoftSerialWifi_RX, SoftSerialWifi_TX); // RX, TX
// Initialize WiFly Software (Create instance...)

void terminal();
void enterCmdMode();
void exitCmdMode();
void readWifi();

void setup() {
	Serial.begin(57600); // serial to linux
	Serial.println("Begin WiFi Config ");

	
	Serial.println("Waiting for controller to settle..."); // Print WiFly Device free memory as decimal value.


	Serial.println("Opening software serial port 57600 baud.");
	wifi.begin(9600); // open software serial port to WiFly controller
	
	

	// Attempt to ping the outside world

}

uint32_t lastSend = 0;
uint32_t count=0;

void readWifi() {
	//char buf[256]; // 32 byte buffer
        //if (wifi.available()) {
                //read controller, stuff output into computer connected serial port
        //        Serial.write(wifi.read());
        //}
	//buf = wifi.read();
	Serial.println("Is data there?");
        if (wifi.available()) {	
		Serial.println("Yes, reading...");
		while(wifi.available()) {
			Serial.write(wifi.read());
		}
	} else {
		Serial.println("No Data to collect...");
		
	}

}

void loop()
{

	delay(2000);   
	enterCmdMode();
	delay(250);
	//enterCmdMode();
	//delay(250);

	//wifi.println();
	wifi.println("get mac");
	delay(250);
	readWifi();
	delay(250);
	exitCmdMode();
	delay(250);
	readWifi();
	

	//terminal();
	//Serial.print("Ping count = ");
	//Serial.println(count);
	//enterCmdMode();
	//enterCmdMode();
	
//	for (int i = 0 ; i < 2; i++ ) {
//		//Ping terminal 20 times 
//		wifi.println("ping 10.42.8.35");
//		delay(500); // wait 500 ms
//	}	
	//exitCmdMode();


/*
    if ((millis() - lastSend) > 1000) {
        count++;
	Serial.print("Sending message ");
	Serial.println(count);

	wifi.print("Hello, count=");
	wifi.println(count);
	lastSend = millis();
    }


*/
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
		if(wifi.available() > 0 ) {
			// write wifi to serial 
			Serial.write(wifi.read());
		} 
		if (Serial.available()) {
			// Write serial to wifi
			wifi.write(Serial.read());
		}
	}

}

void enterCmdMode() {
	for (int x = 0; x < 3; x++ ) {
		wifi.print("$");
		delay(150);
	}
	delay(250);
	//wifi.println();
}
void exitCmdMode() {
	//wifi.print("exit");
	wifi.println();
}


