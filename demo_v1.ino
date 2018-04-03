/*
 * (C) 2018 Engaging Computing Group
 *  License (TBD)
 */

#include "BitcoinTracker.h"
#include "Keys.h"

#define NETWORK_STATUS_LED 2
#define ACTION_LED LED_BUILTIN

#define LED_ON false
#define LED_OFF true



BitcoinTracker tracker ;

void connectLEDs()
{
  pinMode(ACTION_LED, OUTPUT) ;
  pinMode(NETWORK_STATUS_LED, OUTPUT) ;
}

void setNetworkLEDState(bool state)
{
  digitalWrite(NETWORK_STATUS_LED, state) ;
}

void setActionLEDState(bool state)
{
  digitalWrite(ACTION_LED, state) ;
}

void blinkActionLED()
{
  setActionLEDState(LED_ON) ;
  delay(50) ;
  setActionLEDState(LED_OFF) ;
  
}

void setup() {
  Serial.begin(115200) ;
  connectLEDs() ;
  
  setNetworkLEDState(LED_OFF) ;
  setActionLEDState(LED_OFF) ;

  Serial.printf("Attempting to connect to WiFi network with SSID = %s\n", WiFiSSID.c_str()) ;
  WiFi.begin(WiFiSSID.c_str(), WiFiPassword.c_str()) ;

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100) ;
    Serial.print(".") ;
  }

  setNetworkLEDState(LED_ON) ;
  Serial.printf("\nConnection Successful. IP: %s\n", WiFi.localIP().toString().c_str()) ;

  tracker.initialize() ;
  
}

void loop() {
    if( WiFi.status() == WL_CONNECTED)
    {
      blinkActionLED() ;
      setNetworkLEDState(LED_ON) ;
      tracker.updatePrice() ;
      tracker.displayPriceUpdate() ;
    }
    else setNetworkLEDState(LED_OFF) ;
    delay(5000) ;
    Serial.printf("end of main loop.\n") ;
}
