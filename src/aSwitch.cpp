/*
  Erweiterung der RCSwitch Klasse
  Created by D.Herick, 03.07.2017
*/


 #include <RCSwitch.h>
 #include <Arduino.h>
 #include <aSwitch.h>


//Initialisieren der Klasse
 aSwitch::aSwitch(int pin,int group, const char* FirstDIP, const char* SecondDIP)
 {
   _pin = pin;
   _group = group;
   _FirstDIP = FirstDIP;
   _SecondDIP = SecondDIP;
   _pulseLength = 500;
   _isON = 0;
   _thisSwitch = RCSwitch();
   _thisSwitch.setPulseLength(_pulseLength);
   _thisSwitch.enableTransmit(_pin);
 }

//Possibily to set the Pulse Length for the RCSwitch class manually
  void aSwitch::setPulseLengthX(int pLength)
{
  _pulseLength = pLength;
 _thisSwitch.setPulseLength(_pulseLength);
}

//Turns the RC-Switch On
 void aSwitch::TurnON()
 {
   _thisSwitch.switchOn(_FirstDIP, _SecondDIP);
   delay(50);
   _isON = 1;
 }
//Turns the RC-Switch Off
 void aSwitch::TurnOFF()
 {
   _thisSwitch.switchOff(_FirstDIP,_SecondDIP);
   delay(50);
   _isON = 0;
 }

//Switch between on and off
 void aSwitch::Switch()
 {
   RCSwitch thisSwitch = RCSwitch();
   if (_isON)
   {
     _thisSwitch.switchOff(_FirstDIP, _SecondDIP);
     delay(50);
     _isON = 0;
   }
   else
   {
     _thisSwitch.switchOn(_FirstDIP,_SecondDIP);
     delay(50);
     _isON = 1;
   }
 }

//Get the Status of the RC-Switch
 bool aSwitch::isON()
 {
   if (_isON)
   {
     return 1;
   }
   else
  {
    return 0;
  }

 }
