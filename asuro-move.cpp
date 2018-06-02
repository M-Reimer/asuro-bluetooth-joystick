/*
    Arduino Asuro bluetooth joystick control application
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

#include "asuro-move.h"
#include "Arduino.h"

const int PIN_LEFT_FORWARD = 9;
const int PIN_LEFT_BACKWARD = 10;
const int PIN_RIGHT_FORWARD = 5;
const int PIN_RIGHT_BACKWARD = 3;

AsuroMove::AsuroMove() {
  pinMode(PIN_LEFT_FORWARD, OUTPUT);
  pinMode(PIN_LEFT_BACKWARD, OUTPUT);
  pinMode(PIN_RIGHT_FORWARD, OUTPUT);
  pinMode(PIN_RIGHT_BACKWARD, OUTPUT);
  angle = 88;
}

void AsuroMove::Update() {
  // Angle by default is in range from 65 to 110 with 88 for centered.
  // Subtracting 88 gives us -23 to 22 and 0 for centered.
  signed char a = angle - 88;
  int speed_change = (int)speed * a / 90;

  // Set default speed of both motors
  unsigned char speed_left = constrain((int)speed + speed_change, 0, 255);
  unsigned char speed_right = constrain((int)speed - speed_change, 0, 255);

  /*
  Serial.print("speed_left: ");
  Serial.println((byte)speed_left);
  Serial.print("speed_right: ");
  Serial.println((byte)speed_right);
  */

  // Set outputs based on direction and speed
  if (direction == Direction::FORWARD) {
    digitalWrite(PIN_LEFT_BACKWARD, LOW);
    digitalWrite(PIN_RIGHT_BACKWARD, LOW);
    analogWrite(PIN_LEFT_FORWARD, speed_left);
    analogWrite(PIN_RIGHT_FORWARD, speed_right);
  }
  else {
    digitalWrite(PIN_LEFT_FORWARD, LOW);
    digitalWrite(PIN_RIGHT_FORWARD, LOW);
    analogWrite(PIN_LEFT_BACKWARD, speed_left);
    analogWrite(PIN_RIGHT_BACKWARD, speed_right);
  }
}

// Setters. Take user-set value and call Update();
void AsuroMove::SetSpeed(unsigned char aSpeed) {
  speed = aSpeed;
  Update();
}
void AsuroMove::SetDirection(AsuroMove::Direction aDirection) {
  direction = aDirection;
  Update();
}
void AsuroMove::SetAngle(unsigned char aAngle) {
  angle = aAngle;
  Update();
}

