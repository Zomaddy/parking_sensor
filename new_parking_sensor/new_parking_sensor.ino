#define trigPin 13
#define echoPin 2
#define buzz 8

unsigned long duration;
unsigned long distance;
int intervalValue; 
unsigned int measureCounter = 0; 
volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  measureTimeAndDistance();

  distanceBeeping();

  Serial.println(distance);

}

void measureTimeAndDistance(){
  attachInterrupt(digitalPinToInterrupt(2), echoStartTime, RISING); 
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = endTime - startTime;
  distance = duration/58;
}

void echoStartTime(){
  startTime = micros();
  attachInterrupt(digitalPinToInterrupt(2), echoEndTime, FALLING); 
}

void echoEndTime(){
  endTime = micros();
  detachInterrupt(digitalPinToInterrupt(2));
}

void distanceBeeping(){

  measureCounter++;

  if(distance >= 60){
    intervalValue = -1;
  } else if(distance < 60 && distance >= 50){
    intervalValue = 1500;
  } else if(distance < 50 && distance >= 40){
    intervalValue = 1000;
  } else if(distance < 40 && distance >= 30){
    intervalValue = 500;
  } else if(distance < 30 && distance >= 20){
    intervalValue = 250;
  } else if(distance < 20){
    intervalValue = 0;
  }
  if(intervalValue < 0){
    noTone(8);
  }else if(measureCounter*10 > intervalValue){
    tone(8,294,intervalValue);
    measureCounter = 0;
  }
}



