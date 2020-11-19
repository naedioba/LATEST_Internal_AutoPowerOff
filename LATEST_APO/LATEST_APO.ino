/*
Author:Mamadou BA Neige from MBA PRO TECH
Email: naedioba1@gmail.com   / mamadou.ba@ugb.edu.sn
Date: Latest version 19 November 2020
My YouTube Channel:https://www.youtube.com/channel/UCzC1VqRaFkubLkrMLdj2lmA
Title of video: ?
Link of video: 

This is a modified version of my previous system available here: https://youtu.be/gNGvbSk3R0k
I'm using an infra-red proximity sensor as a detector when the print job is done. Then
after 20 to 30 seconds, the printer turns off autimatically.

===👇Le GüeroLoco 👇===
Fermeture automatique de l'imprimante à moins de 5$ !
https://youtu.be/1jNsF7NxjuU

===👇Get the IR Proximity Sensor / Acheter le capteur IR👇===
from Banggood: https://www.banggood.com/search/ir-sensor.html?from=nav
from dealextreme: https://www.dx.com/p/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-smart-car-robotg-2726126.html#.X6h6c2j7TIU

*/
#include <SoftwareSerial.h>
#include <Wire.h>

int relayEnder3Pro = 4;         		// pin for the relay of socket where the Ender 3 Pro is pluged
int sensor_Ender3Pro = 7;       		// pin of the IR sensor for the ender 3 Pro
boolean stateSensor_Ender3Pro;  		// state of the IR sensor for the ender 3 Pro
unsigned long initialTime_E3Pro = 0;  	// initialization time for Ender 3 Pro
unsigned long currentMillis;
unsigned long previousMillisE3Pro = 0;		// previous millis for Ender 3 Pro
unsigned long currentMillisE3Pro;         	// current millis for Ender 3 Pro
long printer_TunOn_Confirmation = 10000;   	// delay to confirm the state of the sensor to avoid untimely power on
long printer_TunOff_Confirmation = 30000;  	// maximum delay to power off

//=========================
void setup() {

  Serial.begin(9600);
  
// setting up the relays pins a OUTPUT
  pinMode(relayEnder3Pro,OUTPUT);

  // setting up tge sensors pins as INPUT
  pinMode(sensor_Ender3Pro,INPUT);
  
// initial state of the relays
  digitalWrite(relayEnder3Pro, LOW);  // Ender 3 Pro turned off

// digital reading of sensors
  stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);  

} // end of setup
//=========================
void loop(){

// digital reading of sensors
  stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);

  if(stateSensor_Ender3Pro == HIGH){
    currentMillisE3Pro = millis();
    if(currentMillisE3Pro - previousMillisE3Pro >= printer_TunOn_Confirmation){
      stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);
      if(stateSensor_Ender3Pro == HIGH){
        digitalWrite(relayEnder3Pro, HIGH);
        previousMillisE3Pro = currentMillisE3Pro;
      } 
    } 
  } 
  else 
  if(stateSensor_Ender3Pro == LOW){  
    currentMillisE3Pro = millis();
    if(currentMillisE3Pro - previousMillisE3Pro >= printer_TunOff_Confirmation){ 
      stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);
      if(stateSensor_Ender3Pro == LOW){ 
        digitalWrite(relayEnder3Pro, LOW);
        previousMillisE3Pro = currentMillisE3Pro;
      } 
    } 
  }  
} // end of loop
