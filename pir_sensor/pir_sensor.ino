#define LED 3
#define PIR 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);

  // one min delay time
  delay(60000);
  Serial.println("1 min init done.");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(PIR) == HIGH){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }

  delay(60000);
  Serial.println("Ready...");
}
