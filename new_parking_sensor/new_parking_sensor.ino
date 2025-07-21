#define trigPin1 13
#define echoPin1 2
#define buzz 8

unsigned long duration;
unsigned long distance;
int intervalValue; //czas pomiędzy jednym a drugim piknięciem
unsigned int measureCounter = 0; //odliczanie czasu, który minął od piknięcia
volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  attachInterrupt(digitalPinToInterrupt(2), echoEndTime, RISING); //mierzy czas kiedy echo zaczyna być HIGH
  digitalWrite(trigPin, HIGH);
  startTime = micros();
  delay(10);
  digitalWrite(trigPin, LOW);
  
  duration = endTime - startTime;
  distance = duration/58;

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

  Serial.println(distance);
}

//void echoStartTime(){
//  startTime = micros();
//  attachInterrupt(digitalPinToInterrupt(2), echoEndTime, FALLING); //mierzy czas kiedy echo przestaje być HIGH
//}

void echoEndTime(){
  endTime = micros();
  detachInterrupt(digitalPinToInterrupt(2));
}
