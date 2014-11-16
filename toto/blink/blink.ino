int led_red = 1;
int led_grn = 2;

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_grn, OUTPUT);  
}

void loop() {
  digitalWrite(led_red, HIGH);
  digitalWrite(led_grn, LOW);
  delay(500);
  digitalWrite(led_red, LOW);
  digitalWrite(led_grn, HIGH);
  delay(500);
}
