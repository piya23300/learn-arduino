


void setup()
{
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	pinMode(4, OUTPUT);
	pinMode(7, OUTPUT);

	// digitalWrite(5, 1); // direction
	// analogWrite(6, 255); //value = 0-255

	// digitalWrite(4, 1); // direction
	// analogWrite(7, 255); //value = 0-255

	// delay(1000);
	// analogWrite(6, 0);
	// analogWrite(7, 0);
	
	motor(1, 50);
	motor(2, 50);
	delay(1000);
	motor(1, -50);
	motor(2, -50);
	delay(1000);
	motor(1, 0);
	motor(2, 0);
}

void loop()
{
	
}

void motor(int ch, int pow)
{
	int direction;
	int power;
	int directionPin;
	int analogPin;
	
	pow = (pow*255)/100;

	if(pow > 0) {
		direction = 1;
		power = pow;
	} else {
		direction = 0;
		power = pow * -1;
	}

	switch (ch) {
	    case 1:
	      directionPin = 5;
	      analogPin = 6;
	      break;
	    case 2:
	      directionPin = 4;
	      analogPin = 7;
	      break;
	}

	digitalWrite(directionPin, direction); // direction
    analogWrite(analogPin, power); //value = 0-255
}


