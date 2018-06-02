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

#ifndef ASURO_MOVE_H
#define ASURO_MOVE_H


#endif /* ASURO_MOVE_H */

class AsuroMove {
  public:
    enum Direction {
      FORWARD,
      BACKWARD
    };

    AsuroMove();  
    void SetSpeed(unsigned char aSpeed);
    void SetDirection(AsuroMove::Direction aDirection);
    void SetAngle(unsigned char aAngle);

  private:
    unsigned char speed;
    AsuroMove::Direction direction;
    signed char angle;
    void Update();
};

