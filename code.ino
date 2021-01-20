// h-Bridge Connection   
  
const int motorA1  = 9 ;  // Pin  2 of L293
  
const int motorA2  = 10;  // Pin  7 of L293
  
const int motorB1  = 3 ;  // Pin 10 of L293    //9
  
const int motorB2  = 5 ;  // Pin 14 of L293    //10
  
const int led = 13;
  
int sensorpin  = A0;
  
int sensorvalue;
  
int i =0;
  
float temperatureC= 0.0;
  
int ultrasonicState;

//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
  
const int BTState = 2; 


//Useful Variables
  
int state;
  
int vSpeed=185; 

int altrasonic_echo =4;

int altrasonic_trig = 2;

char data;

void setup() {

//Motors initialization
  
//pinMode(EmotorR, OUTPUT);
  
//pinMode(EmotorL, OUTPUT);
  
pinMode(motorA1, OUTPUT);
  
pinMode(motorA2, OUTPUT);
  
pinMode(motorB1, OUTPUT);
  
pinMode(motorB2, OUTPUT);

pinMode(12,OUTPUT);
  
  
//Ultrasonic initialization
  
pinMode(altrasonic_echo, INPUT);
  
pinMode(altrasonic_trig, OUTPUT);

  
Serial.begin(9600); //Communication initialization
 

}


void loop() {
  
//change speed
      
switch (state){
     
case '0': 
vSpeed = 0;
     
break;
    
case '1':
      
vSpeed=100;
      
break;
    
case  '2':
      
vSpeed=180;
      
break;
    
case '3':
      
vSpeed=200;
      
break;
    
case '4':
      
vSpeed=255;
      
break;
      
default:
      
break;
    
}

  
  
// put your main code here, to run repeatedly:
  
  
check();
  
if(data == 'E'){
    // All open

  do {
	check();
  
		if(data == 'F'){

      		forward();
      
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}
  
		else if(data == 'B'){
      
		backward();
     
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}

  
		else if(data == 'R'){
      
		turnRight();
      
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}
  
		else if(data == 'L'){
      
		turnLeft();
     
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}

  
		else if(data == 'S'){
      
		stopp();
      
    
		}

	}  while (data != 'N' && data !='T')  
}
  
else if(data == 'N'){
    
    //ultrasonic closed
    
  do {
	check();
  
		if(data == 'F'){
      
		forward();
     
		// ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}
  
		else if(data == 'B'){
      
		backward();
     
		//ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}

  
		else if(data == 'R'){
      
		turnRight();
      
		//ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}
  
		else if(data == 'L'){
      
		turnLeft();
     
		//ultrasonic(altrasonic_trig,altrasonic_echo);
      
		temperature();
  
		}

  
		else if(data == 'S'){
      
		stopp();
      
  
		}

  } while (data !='E' && data !='T')
}
  
else if(data == 'T'){
    //temp closed

    do {
	check();
  
		if(data == 'F'){
      
		forward();
      
		ultrasonic(altrasonic_trig,altrasonic_echo);
     
		// temperature();
  
		}
  
		else if(data == 'B'){
      
		backward();
     
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		//temperature();
  
		}

  
		else if(data == 'R'){
      
		turnRight();
      
		ultrasonic(altrasonic_trig,altrasonic_echo);
      
		//temperature();
  
		}
  
		else if(data == 'L'){
      
		turnLeft();
     
		ultrasonic(altrasonic_trig,altrasonic_echo);
     
		// temperature();
  
		}

  
		else if(data == 'S'){
      
		stopp();
      
  
		}
  
  } while (data!='E' && data!='N')    
    
}
  
delay(20);

}


void forward() {
  analogWrite(motorA1, vSpeed); analogWrite(motorA2, LOW);
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, LOW);
  
  }

void backward(){
  analogWrite(motorA1, LOW);    analogWrite(motorA2, vSpeed);
     analogWrite(motorB1, LOW);    analogWrite(motorB2, vSpeed);

 }

void turnRight(){
 
  analogWrite(motorA1, LOW); analogWrite(motorA2, LOW);
        analogWrite(motorB1, vSpeed); analogWrite(motorB2, LOW);
   }

void turnLeft(){
  analogWrite(motorA1, vSpeed); analogWrite(motorA2, LOW);
        analogWrite(motorB1, LOW); analogWrite(motorB2, LOW);
  
  }

void stopp(){
  
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  
  }





void check(){
  
int dataIn;
  
if (Serial.available() > 0)    //Check for data on the serial lines.
   
data = Serial.read();


}


void ultrasonic(int trig, int echo){
    
float distance;
    
int duration;
    
digitalWrite(trig, HIGH);
    
delayMicroseconds(10);
    
digitalWrite(trig, LOW);
    
duration = pulseIn(echo, HIGH);
    
distance = (duration /2)* 0.034;
   
    
	if (distance <6)
    {
      
     
  
        
	digitalWrite(motorA1, LOW);
  
	digitalWrite(motorA2, LOW);
  
  
	digitalWrite(motorB1, LOW);
  
	digitalWrite(motorB2, LOW);
  
  
  
	}

}

void temperature(){
  
   

temperatureC =   analogRead(sensorpin) * 0.48828125;
 
Serial.println(temperatureC);

if(temperatureC>45)
{
  
	digitalWrite(12,HIGH);
   
	digitalWrite(motorA1, LOW);
  
	digitalWrite(motorA2, LOW);
  
	digitalWrite(motorB1, LOW);
  
	digitalWrite(motorB2, LOW);
	}

else{
   digitalWrite(12,LOW);
forward();
	}


}
