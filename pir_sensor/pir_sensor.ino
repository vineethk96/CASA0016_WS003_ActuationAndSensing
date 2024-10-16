#define LED 3
#define PIR 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);

  digitalWrite(LED, LOW);

  delay(15000); // Let Sensor Warm Up
  Serial.println("rdy");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(PIR) == HIGH){
    Serial.println("Motion detected");
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
