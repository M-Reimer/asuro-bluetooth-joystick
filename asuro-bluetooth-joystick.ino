/*
    Arduino Asuro bluetooth joystick control application
    Some portions used from: https://sites.google.com/site/bluetoothrccar/home/6-Joystick-Control
    Copyright (C) 2018 Manuel Reimer <manuel.reimera@gmx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// Get the app from here: https://play.google.com/store/apps/details?id=com.andico.control.joystick
// More information: https://sites.google.com/site/bluetoothrccar/home/6-Joystick-Control

#include "asuro-move.h"

// Structure used for cummunicating back to the App (set sensor display)
struct TSensors {
  TSensors() : header(0xee), footer(0xcc) {}
  byte header;
  float sensor1;
  float sensor2;
  byte sensor3;
  byte sensor4;
  byte sensor5;
  byte sensor6;
  byte footer;
};

// Structure used for communication switches from App to our code
struct TSwitches {
  bool e:1;
  bool d:1;
  bool c:1;
  bool b:1;
  bool a:1;
  bool horn:1;
  bool back:1;
  bool front:1;
};

AsuroMove asuro;

void setup() {      
  Serial.begin(9600); 
}

void loop() {
  byte commands[4] = {0x00,0x00,0x00,0x00};
  static byte prevCommands[4] = {0x01,0x01,0x01,0x01};
  static unsigned long timer_last_write = 0;
  static unsigned long timer_last_read = 0;

  if (Serial.available() >= 4) {
    // Store the time when last command was received
    timer_last_read = millis();
    // Read 4 bytes
    for (int index = 0; index < 4; index++) {
      commands[index] = Serial.read();
    }

    // Plasubility check. Are the bytes, we got, a valid command?
    if((commands[2] <= 0xb4) && ((commands[0] <= 0xf5) && (commands[0]>=0xf1))) {
      // Handle the movement commands
      if(commands[0] <= 0xf3){
        // Process command byte
        if (prevCommands[0] != commands[0]) {
          if(commands[0] == 0xf1){  //Check if the move forward command was received
            asuro.SetDirection(AsuroMove::Direction::FORWARD);
            //Serial.println("Updated direction FWD");
          }
          else if(commands[0] == 0xf2){  //Check if the move back command was received
            asuro.SetDirection(AsuroMove::Direction::BACKWARD);
            //Serial.println("Updated direction BAK");
          }
          else{  //Check if the stop command was received   
            //Serial.println("Updated direction STP");
          }
        }

        // Process speed byte
        if(prevCommands[1] != commands[1]){
          asuro.SetSpeed(commands[1]);
          //Serial.print("Updated speed: ");
          //Serial.println(commands[1]);
        }         

        // Process angle byte
        if(prevCommands[2] != commands[2]){
          asuro.SetAngle(commands[2]);
          //Serial.print("Updated angle: ");
          //Serial.println(commands[2]);
        }        
      }
      // Handle stop command
      else if(commands[0] == 0xf5){
        if(prevCommands[0] != 0xf5){
          //Serial.println("Stop everything!");
          asuro.SetSpeed(0);
        }
      }

      // Read toggle switches. Todo: Do something with them :P
      if(prevCommands[3] != commands[3]){
        TSwitches buttons;
        memcpy(&buttons, &commands[3], 1);
        /*
        Serial.print("Buttons: ");
        Serial.print(buttons.horn ? " horn " : "");
        Serial.print(buttons.front ? " front " : "");
        Serial.print(buttons.back ? " back " : "");
        Serial.print(buttons.a ? " a " : "");
        Serial.print(buttons.b ? " b " : "");
        Serial.print(buttons.c ? " c " : "");
        Serial.print(buttons.d ? " d " : "");
        Serial.print(buttons.e ? " e " : "");
        Serial.println(commands[3]);
        */
      }     

      // Remember current command for next run
      memcpy(prevCommands,commands,4);
    }
    // Plausiblity check above failed --> Reset serial port and retry.
    else{
      Serial.end();
      Serial.begin(9600);
    }
  }
  else{
    // No read in the last 400 ms --> Stop.    
    if ((millis() - timer_last_read) > 400) {
      asuro.SetSpeed(0);
      //Serial.println("Emergancy stop!");
    }

    // Send out sensors every 477ms. Todo. Get wheel speeds and send them?
    if((millis() - timer_last_write) >= 477) {
      TSensors sensors;
      sensors.sensor1 = 1.1;
      sensors.sensor2 = 2.2;
      sensors.sensor3 = 3;
      sensors.sensor4 = 4;
      sensors.sensor5 = 5;
      sensors.sensor6 = 6;
      
      Serial.write((char*)&sensors,14);
      //Store the time when the sensor readings were sent
      timer_last_write = millis();
    }
  }
}

