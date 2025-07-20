#define trigPin1 13
//#define trigPin2 7
#define echoPin1 2
//#define echoPin2 4
#define buzz 8

int duration;
float distance;
int intervalValue; //czas pomiędzy jednym a drugim piknięciem
unsigned int measureCounter = 0; //odliczanie czasu, który minął od piknięcia

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
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
