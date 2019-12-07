const int xpin = A0;
const int ypin = A1;
const int zpin = A2;

void setup() {
  Serial.begin(9600);
  Serial.println("x,y,z");
}

void loop() {
  double x = readX();
  double y = readY();
  double z = readZ();

  print(x, y, z);

  delay(100);
}

double readX() {
  int offset = 325;
  double max = 65.0;
  double value = (analogRead(xpin) - offset) / max;
  return max(min(value, 1), -1);
}

double readY() {
  int offset = 325;
  double max = 65.0;
  double value = (analogRead(ypin) - offset) / max;
  return max(min(value, 1), -1);
}

double readZ() {
  int offset = 325;
  double max = 65.0;
  double value = (analogRead(zpin) - offset) / max;
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