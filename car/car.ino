#include <popx2.h>
#include "PS2X_lib.h"

//#define TRIG 30
//#define ECHO 29

#define PS2_DAT 27
#define PS2_CMD 28
#define PS2_SEL 30
#define PS2_CLK 29

#define LEFT 1
#define RIGHT 2

#define DEFAULT_SPEED 50

//#define LIGHT_LEFT in(26)
//#define LIGHT_RIGHT in(24)

long RAW;
float DIST;
PS2X ps2x;

int speed = DEFAULT_SPEED;

void setup()
{
  OK();
  Serial.begin(9600);
  Serial.print("Connecting..");
  while(true) {
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
    if(error == 0) {
      Serial.println(" ");
      Serial.println("Connected !!!");
      delay(200);
      break;
     }
     Serial.print(".");
     delay(500);
  }
}

void loop()
{
  ps2x.read_gamepad(false, false);
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("UP");
    move_up();
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("DOWN");
    move_down();
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("LEFT");
    turn_left();
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("RIGHT");
    turn_right();
  } else if (ps2x.Button(PSB_L1)) {
    Serial.println("L1");
    move_left();
  } else if (ps2x.Button(PSB_R1)) {
    Serial.println("R1");
    move_right();
  } else if (ps2x.ButtonPressed(PSB_L3)) {
    Serial.println("L3");
    beep();
  } else if (ps2x.ButtonPressed(PSB_R3)) {
    Serial.println("R3");
    beep();
  } else if (ps2x.Button(PSB_CROSS)) {
    Serial.println("CROSS");
    if (speed > 0) {
      speed--;
      Serial.print("SPEED DOWN ");
      Serial.println(speed);
    } else {
      speed = 0;
      Serial.print("MIXIMUM SPEED DOWN ");
      Serial.println(speed);
    }
    
  } else if (ps2x.Button(PSB_CIRCLE)) {
    Serial.println("CIRCLE");
  } else if (ps2x.Button(PSB_TRIANGLE)) {
    Serial.println("TRIANGLE");
    if (speed < 80) {
      speed++;
      Serial.print("SPEED UP ");
      Serial.println(speed);
    } else {
      speed = 80;
      Serial.print("MAX SPEED UP ");
      Serial.println(speed);
    }
  } else if (ps2x.Button(PSB_SQUARE)) {
    Serial.println("SQUARE");
  } else if (ps2x.Analog(PSS_LY) < 124) {
    speed  = map(ps2x.Analog(PSS_LY), 124, 0, 25, 80);
    move_up();
  } else if (ps2x.Analog(PSS_LY) > 130) {
    speed  = map(ps2x.Analog(PSS_LY), 130, 255, 25, 0);
    move_up();
  } else if (ps2x.Analog(PSS_LX) < 124) {
//    speed  = map(ps2x.Analog(PSS_LX), 124, 0, 25, 80);
    move_left();
  } else if (ps2x.Analog(PSS_LX) > 132) {
//    speed  = map(ps2x.Analog(PSS_LX), 124, 0, 25, 80);
    move_right();
  } else {
    Serial.print(ps2x.Analog(PSS_LY));
    Serial.print("\t");
    Serial.println(ps2x.Analog(PSS_LX));
    motor_stop(ALL);
  }
  delay(50);
}

void move_up()
{
  motor(LEFT, speed);
  motor(RIGHT, speed);
}

void move_down()
{
  motor(LEFT, speed * -1);
  motor(RIGHT, speed * -1);
}

void move_left()
{
  motor(LEFT, speed - 10);
  motor(RIGHT, speed + 10);
}

void move_right()
{
  motor(LEFT, speed + 10);
  motor(RIGHT, speed - 10);
}

void turn_left()
{
  motor(LEFT, 0);
  motor(RIGHT, speed);
}

void turn_right()
{
  motor(LEFT, speed);
  motor(RIGHT, 0);
}


//void move_forword()
//{
//  while (LIGHT_LEFT == 1 && LIGHT_RIGHT == 1) 
//  {
//    motor(LEFT, 50);
//    motor(RIGHT, 50);
//  }
//  motor(LEFT, 0);
//  motor(RIGHT, 0);
//}
//
//void moveLeft()
//{
//  motor(LEFT, 0);
//  motor(RIGHT, 0);
//}
//
//
//float distance()
//{
//  long RAW;
//  float DIST;
//  out(TRIG,HIGH);
//  delayMicroseconds(10);
//  out(TRIG, LOW);
//  RAW=pulseIn(ECHO,HIGH);
//  DIST=(float(RAW)/2)/29.1;
//  //glcd(1, 0, "#nDIST=%f  CM   ",DIST);
//  return DIST;
//}


