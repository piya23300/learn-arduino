#include <popx2.h>

#define LEFT 1
#define RIGHT 2
#define SPEED 50

String dataString;
int i;

char directionString;
String speedString;
int speed;

void setup()
{
  Serial.begin(9600);
  dataString = "";
}

void loop()
{
  while (Serial.available()) {
    dataString += (char)Serial.read();  
  };
  
  if(dataString.length() > 0) {
    Serial.print(dataString);
    Serial.print(" ---- ");
    
    speedString = "";
    for (i = 0; i < dataString.length(); i++){
      if(i == 0) {
        directionString = dataString[i];
      } else {
        speedString += dataString[i];
      }
    }
    String text = "Direction: ";
    text += directionString;
    text += " Speed: ";
    text += speedString;
    Serial.println(text);
  }
  
  delay(1000);
  dataString ="";
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
