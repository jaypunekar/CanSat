# CanSat
A remote Temperature & Humidity sensing device using NodeMCU ESP8266.

## Hardware Reqiurements

1. NodeMCU ESP8266/ESP32.
2. DTH11 Sensor.
3. Jumber Cables.
4. Data Cable.
5. 9 Volt Battery.
6. Breadboard.

## Blynk Setup
1. Go to [Blynk Link](https://blynk.io/).
2. Make a Blynk Account.
3. Add the parameters you want to measure.
4. Find the Authentication Key.
5. Open main.ino in Text Editor.
6. Put the Authentication Key, WiFi SSID & WiFi Password.


## Final Setup
[![img22.png](https://i.postimg.cc/WztmtLD1/img22.png)](https://postimg.cc/7J8JQRMF)
1. Connect the circuit as shown in the figure.
2. For Battery, the black wire will go to ground and the red wire will go to Vin.
3. Connect ESP8266 to a computer using Data Cable.
4. Open main.ino in Arduino IDE and transfer it to ESP8266.
5. It will now show readings in your Blynk App.
