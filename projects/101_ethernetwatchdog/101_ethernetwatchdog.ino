/*********************************************************************************************************
*
* Project              : 101_ethernetwatchdog
* Hardware Environment : MEGA2560 + Ethernet Shield W5100 + 0.91 inch OLED Module 
* Build Environment    : Arduino
* Version              : V1.0.0
* By                   : RM
* References           : https://www.waveshare.com/wiki/0.91inch_OLED_Module
*
*********************************************************************************************************/
// generic include
#include <SPI.h>
#include <Wire.h>
// necessary for OLED Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// necessary for Ethernet Shield
#include <Ethernet.h>

// initialize vars for OLED Display
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// initialize vars for Ethernet shield
// MAC address
byte mac[] = {
  0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xBB
};
// Set the static IP address to use if the DHCP fails to assign
//IPAddress ip(192, 168, 1, 248);
//IPAddress myDns(192, 168, 1, 1);
// initialize the library instance:
EthernetClient client;
// target URL
char server[] = "www.perdu.com";  // must be same within httpRequest()

// Ethernet connectivity status
bool connectionStatus = false;

int counterx = 1;

void setup() {
  // display init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay(); // just in case
  initDisplay(); // init OLED screen for text display
  // init done

  // ethernet init
  //Ethernet.init(10); // configure the Chip Select Pin
  // rest of Ethernet init is done in ethernetSetup()

  /*
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
}

/**
 * Here we modify the loop structure: if we have no connection we try again every 1000ms
 */
void loop() {
  ethernetSetup (); // try to connect 
  while (connectionStatus) { // while we are connected
    
  }
}

void ethernetSetup () {
  Ethernet.init(10);
  printString(String("Connecting..."));
  // we try to get an IP address using DHCP
  if (Ethernet.begin(mac) == 0) { // if it fails
    printString(String("DHCP Fail"));
    display.print("Fails: ");
    display.println(counterx);
    display.display();
    delay(500);
    counterx++;
  }
  else { // if we got an IP address using DHCP
    printString(String("Connected"));
    display.print("IP: ");
    display.println(Ethernet.localIP());
    display.display();
    connectionStatus = true;
  }
}

/**
 * Initialize display for text
 */
void initDisplay (void) {
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

/**
 * Basic function to print string
 */
void printString (String input) {
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(input);
  display.display();
}
