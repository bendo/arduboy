#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_WINC1500.h>

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);

Adafruit_SSD1306 display = Adafruit_SSD1306();

#if (SSD1306_LCDHEIGHT != 32)
 #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {  
  #ifdef WINC_EN
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
  #endif
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  printMacAddress();
}

void loop() {
  yield();
  listNetworks();
  delay(10000);
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];
  // print your MAC address:
  WiFi.macAddress(mac);
  display.clearDisplay();
  display.display();
  display.print("MAC: ");
  display.print(mac[5], HEX);
  display.print(":");
  display.print(mac[4], HEX);
  display.print(":");
  display.print(mac[3], HEX);
  display.print(":");
  display.print(mac[2], HEX);
  display.print(":");
  display.print(mac[1], HEX);
  display.print(":");
  display.println(mac[0], HEX);
  display.setCursor(0,0);
  display.display();
  delay(4000);
}

void listNetworks() {
  // scan for nearby networks:
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    display.println("Couldn't get a wifi connection");
    while (true);
  }
  // print the list of networks seen:
  display.print("Available networks:");
  display.println(numSsid);
  display.display();
  delay(4000);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(thisNet);
    display.print(") ");
    display.println(WiFi.SSID(thisNet));
    display.print("Signal: ");
    display.print(WiFi.RSSI(thisNet));
    display.println(" dBm");
    display.print("Encryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
    display.display();
    delay(4000);
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      display.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      display.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      display.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      display.println("None");
      break;
    case ENC_TYPE_AUTO:
      display.println("Auto");
      break;
  }
}
