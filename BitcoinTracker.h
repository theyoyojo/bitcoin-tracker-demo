#ifndef BITBOIN_TRACKER_H
#define BITCOIN_TRACKER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>

#define SERVO_PIN 14

#define POS_CENTER 90
#define POS_UP 110
#define POS_DOWN 70

class BitcoinTracker {
  double _price ;
  double _lastPrice ;
  String _dateLastUpdate ;
public:
  BitcoinTracker() {} ;
  ~BitcoinTracker() {} ;

  WiFiClientSecure client ;
  const int httpsPort = 443 ;

  String api_host = "api.coinmarketcap.com" ;
  String api_path = "/v1/ticker/bitcoin/" ;

  Servo servo ;

  void initialize() ;
  
  double getLatestBitcoinPrice() ;
  void displayPriceUpdate() ;
  void updatePrice() ;
  String getJson(String api_host, String api_path) ;
} ;

#endif // BITCOIN_TRACKER_H
