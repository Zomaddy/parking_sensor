#define trigPin 13
#define echoPin 2
#define buzz 8

unsigned long duration;
unsigned long distance;
unsigned long startTrigTime;
int intervalValue;
unsigned long measureCounter;
unsigned long previousCounter = 0;
volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;
volatile bool wholeTime = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), echoStartTime, RISING);

  Serial.begin(9600);

}

void loop() {
  measureTimeAndDistance();

  distanceBeeping();

  Serial.println(distance);
}

void measureTimeAndDistance(){

  if (wholeTime){
    noInterrupts();
    duration = endTime - startTime;
    distance = duration/58;
    wholeTime = false;
    interrupts();

    attachInterrupt(digitalPinToInterrupt(2), echoStartTime, RISING);
  } else {
    startTrigTime = micros();
    while(micros() - startTrigTime < 10){
      digitalWrite(trigPin, HIGH);
    }
      digitalWrite(trigPin, LOW);
    }
}

void echoStartTime(){
  startTime = micros();
  attachInterrupt(digitalPinToInterrupt(2), echoEndTime, FALLING);
}

void echoEndTime(){
  endTime = micros();
  wholeTime = true;
  detachInterrupt(digitalPinToInterrupt(2));
}

void distanceBeeping(){

  measureCounter = millis();

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
    noTone(buzz);
  }else if(measureCounter - previousCounter >= intervalValue){
    tone(buzz,294,intervalValue);
    previousCounter = measureCounter;
  }
}
