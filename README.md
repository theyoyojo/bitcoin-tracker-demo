# bitcoin-tracker-demo
A basic bitcoin tracker for an ESP8266 chip, written in Arduino sketch/C++

Under the influence of this program, your device will:

0. Initialize serial output at 115200 baud and a servo connection to pin 14
1. Attempt to connect to a WiFi network given the credentials in Keys.h
2. Query the coinmarketcap API to find the latest price of bitcoin
3. Adjust the servo arm to reflect a change in the price of bitcoin since the last API query
4. GOTO step 2

The angles that are writen to the servo arm on update are defined in BitcoinTracker.h on lines 13 to 15.
This program produces a lot of debug output. Fine by me, as this is a very simple demo.
Address any complaints to the Issues section.

In case it may not be obvious, please do not take financial advice from a robot.
