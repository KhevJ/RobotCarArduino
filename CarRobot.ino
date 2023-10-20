const int RIGHT = 4;
const int LEFT = 5;
const int MIDDLE = 6;

const int LED_1 = 2;
const int LED_2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(MIDDLE, INPUT);
  pinMode(LED_1 ,OUTPUT);
  pinMode(LED_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //checking for left
    
  if(digitalRead(LEFT) == LOW ){
    digitalWrite(LED_1 ,HIGH);
  }
  else{
    digitalWrite(LED_1 ,LOW);
  }

  if(digitalRead(RIGHT) == LOW ){
    digitalWrite(LED_2 ,HIGH);
  }
  else{
    digitalWrite(LED_2 ,LOW);
  }

  Serial.println( digitalRead(RIGHT));
 
}
