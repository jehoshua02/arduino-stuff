const int xpin = A3;
const int ypin = A2;
const int zpin = A1;
const int powerpin = A4;
const int groundpin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("x,y,z");
  pinMode(powerpin, OUTPUT);
  pinMode(groundpin, OUTPUT);
  digitalWrite(powerpin, HIGH);
  digitalWrite(groundpin, LOW);
}

void loop() {
  double x = readAxis(xpin);
  double y = readAxis(ypin);
  double z = readAxis(zpin);

  print(x, y, z);

  delay(100);
}

double readAxis(int pin) {
  int offset = 325;
  double max = 65.0;
  double value = (analogRead(pin) - offset) / max;
  return max(min(value, 1), -1);
}

void print(double x, double y, double z) {
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println();
}