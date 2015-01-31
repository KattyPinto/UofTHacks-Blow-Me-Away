#define RAISE_SPEED 2
#define LOWER_SPEED 3
#define START_ROTATE 4
#define STOP_ROTATE 5

char incomingByte;

void reset_pins()
{
	digitalWrite(RAISE_SPEED, LOW);			
	digitalWrite(LOWER_SPEED, LOW);			
	digitalWrite(START_ROTATE, LOW);			
	digitalWrite(STOP_ROTATE, LOW);			
}

void setup()
{
	Serial.begin(115200);
	pinMode(RAISE_SPEED, OUTPUT); 	
	pinMode(LOWER_SPEED, OUTPUT); 	
	pinMode(START_ROTATE, OUTPUT); 	
	pinMode(STOP_ROTATE, OUTPUT); 	
}

void loop()
{
	if (Serial.available() > 0)
	{
		incomingByte = Serial.read();
		
		Serial.print("Received: ");
		Serial.println(incomingByte);
	}
        else
        {
                incomingByte = ' '; 
        }

	switch(incomingByte)
	{
		case 'a':
			digitalWrite(RAISE_SPEED, HIGH);			
			break;
		case 's':
			digitalWrite(LOWER_SPEED, HIGH);			
			break;
		case 'd':
			digitalWrite(START_ROTATE, HIGH);			
			break;
		case 'f':
			digitalWrite(STOP_ROTATE, HIGH);			
			break;
		default:
			reset_pins();
	}

	delay(1000);
	reset_pins();
}
