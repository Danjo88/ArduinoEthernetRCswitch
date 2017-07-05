/*
  Erweiterung der RCSwitch Klasse
  Created by D.Herick, 03.07.2017
*/



#ifndef aSwitch_h
#define aSwicht_h
 #include <RCSwitch.h>


#include <Arduino.h>





class aSwitch
{
public:
  aSwitch(int pin , int group,const char* FirstDIP ,const char* SecondDIP);
  void setPulseLengthX(int pLength);
  void TurnON();
  void TurnOFF();
  void Switch();
  int _pulseLength;
  bool isON();

private:
  int _group;
  int _pin;
  const char* _FirstDIP;
  const char* _SecondDIP;
  bool _isON;
  RCSwitch _thisSwitch;
};


#endif
