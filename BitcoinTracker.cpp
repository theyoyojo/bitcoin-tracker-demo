#include "BitcoinTracker.h"

double BitcoinTracker::getLatestBitcoinPrice()
{
  return _price ;
}

// This function was borrowed from the Google Paper Signals code.
// See: https://papersignals.withgoogle.com/ for more information
String makeLessPrettyJSON(String JSONData)
{
  String notPretty = "";
  for(int i = 0; i < JSONData.length(); i++)
  {
    if(JSONData.charAt(i) != '\n' && JSONData.charAt(i) != '\r' &&
      JSONData.charAt(i) != ' ' && JSONData.charAt(i) != '  ' &&
      JSONData.charAt(i) != '[' && JSONData.charAt(i) != ']')
    {
      notPretty += JSONData.charAt(i);
    }
  }

  return notPretty;
}

void BitcoinTracker::updatePrice()
{
  // MAKE THE API CALL BRO
  String payload = getJson(api_host, api_path) ;
  Serial.println(payload) ;

  DynamicJsonBuffer jsonBuffer ;
  JsonObject& root = jsonBuffer.parseObject(makeLessPrettyJSON(payload)) ;

  if(!root.success())
  {
    Serial.println("Failed to parse json payload\n");
  }

  _lastPrice = _price ;

  String strprice = root["price_usd"];

  Serial.printf("STRING price is %s\n",strprice.c_str());

  _price = strtod(strprice.c_str(),nullptr) ;
}

void BitcoinTracker::displayPriceUpdate()
{
  Serial.printf("Got BTC price: %lf\n", _price) ;
  double priceChange = _price - _lastPrice ;

  if ( priceChange > 0 )
  {
    servo.write(POS_UP) ;
    Serial.printf("Setting motor to POS_UP (%d degrees)\n", POS_UP) ;
  }
  else if ( priceChange < 0 )
  {
    servo.write(POS_DOWN) ;
    Serial.printf("Setting motor to POS_DOWN (%d degrees)\n", POS_DOWN) ;
  }
  else
  {
    servo.write(POS_CENTER) ;
    Serial.printf("Setting motor to POS_CENTER (%d degrees)\n", POS_CENTER) ;
  }
}

void BitcoinTracker::initialize()
{
  servo.attach(SERVO_PIN) ;
  servo.write(POS_CENTER) ;

}

String BitcoinTracker::getJson(String api_host, String api_path)
{
  Serial.printf("Attempting to fetch new price data from %s\n", api_host.c_str()) ;

  if (!client.connect(api_host.c_str(), httpsPort))
  {
    Serial.printf("Connection Failure!\n") ;
    return "FAIL" ;
  }

  Serial.printf("Connected. Requesting data from path %s\n", api_path.c_str()) ;

  String apiGetRequest = "GET " + api_path + " HTTP/1.1\r\n" +
                         "Host: " + api_host + "\r\n" +
                         "User-Agent: BuildFailureDetectorESP8266\r\n" +
                         "Connection: close\r\n\r\n" ;

  client.print(apiGetRequest) ;
  Serial.printf("Sent the following GET request:\n%s", apiGetRequest.c_str()) ;

  while (client.connected())
  {
    String line = client.readStringUntil('\n') ;
    if ( line.indexOf("Date") != -1 )
    {
      _dateLastUpdate = line ;
    }
    Serial.println(line) ;
    if ( line == "\r" )
    {
      Serial.println("Headers Recieved.") ;
      break ;
    }
  }

  String payload = client.readString() ;

  Serial.printf("RECIEVED REPLY:\n%s\nEND OF REPLY\n", payload.c_str()) ;

  return payload ;

}

