#include <popx2.h>

#define LEFT 1
#define RIGHT 2
#define SPEED 50
#define TRIG 30
#define ECHO 29

#define DIRECTION_LEFT 1
#define DIRECTION_CENTER 2
#define DIRECTION_RIGHT 3

#define MIN_DISTANCE 30

int sonar_direction;
bool detecting;
float left_distance;
float center_distance;
float right_distance;



void setup() {
  // put your setup code here, to run once:
  detecting = true;
  spin_sonar(DIRECTION_CENTER);
  delay(1000);
  sonar_direction = DIRECTION_CENTER;
  OK();
}

void loop() {
  direction_distance();
  if(center_distance < MIN_DISTANCE) {
    detect_direction();
  } else {
    move_up();
  }
}

void spin_sonar(char direction) {
  switch(direction) {
   case DIRECTION_LEFT:
      sonar_direction = DIRECTION_LEFT;
      servo(1, 180);
      break;
   case DIRECTION_CENTER:
      sonar_direction = DIRECTION_CENTER;
      servo(1, 90);
      break;
   case DIRECTION_RIGHT:
      sonar_direction = DIRECTION_RIGHT;
      servo(1, 1);
      break;
  }
  delay(1000);
  direction_distance();
}

void move_up()
{
  motor(LEFT, SPEED);
  motor(RIGHT, SPEED);
}

void move_down()
{
  motor(LEFT, SPEED * -1);
  motor(RIGHT, SPEED * -1);
}

void move_left()
{
  motor(LEFT, SPEED - 10);
  motor(RIGHT, SPEED + 10);
}

void move_right()
{
  motor(LEFT, SPEED + 10);
  motor(RIGHT, SPEED - 10);
}

void turn_left()
{
  motor(LEFT, 0);
  motor(RIGHT, SPEED);
}

void turn_right()
{
  motor(LEFT, SPEED);
  motor(RIGHT, 0);
}

void direction_distance() {
  switch(sonar_direction) {
    case DIRECTION_LEFT:
      left_distance = distance();
      break;
    case DIRECTION_CENTER:
      center_distance = distance();
      break;
    case DIRECTION_RIGHT:
      right_distance = distance();
      break;
  }
}

float distance() {
  return sonar(TRIG, ECHO);
}

void detect_direction() {
  motor_stop(ALL);
  delay(1000);
  spin_sonar(DIRECTION_CENTER);
  delay(1000);
  spin_sonar(DIRECTION_LEFT);
  delay(1000);
  spin_sonar(DIRECTION_RIGHT);
  delay(1000);

  move_down();
  delay(500);
  if(left_distance > right_distance) {
    turn_left();
  } else {
    turn_right();
  }
  delay(500);
  motor_stop(ALL);
  spin_sonar(DIRECTION_CENTER);
}
