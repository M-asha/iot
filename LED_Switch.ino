
int Switch = D3;
int L = D6;
int Switch1;

void setup() {
  pinMode(L,OUTPUT);
  pinMode(Switch,INPUT_PULLUP);
}
 void loop() {
  Switch1 = digitalRead(Switch);
  if ( Switch1 == LOW) 
    digitalWrite(L,HIGH);
  else 
    digitalWrite(L,LOW);
 }
