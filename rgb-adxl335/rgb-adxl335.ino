// PINS - ACCELEROMETER

int xpin = A3;
int ypin = A2;
int zpin = A1;
int groundpin = A0;
int powerpin = A4;

// PINS - RGB

int redPin = 12;
int greenPin = 13;
int bluePin = 11;

// CONFIGURATION

float tiltThreshold = 0.4;
float hueStep = 0.01;

// STATE

float h = 0;

struct RGB {
    float r, g, b;
};

// SETUP

void setup() {
  Serial.begin(9600);

  setupADXL335();
  setupRGBLED();

  Serial.println("y,h");
}

void setupADXL335() {
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void setupRGBLED() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // input
  float y = readAxis(ypin);

  // calculation
  float h = calculateHue(y);
  RGB rgb = hsvToRgb(h, 1, 1);

  // output
  print(y, h);
  writeRGB(rgb);

  delay(100);
}

// INPUT

float readAxis(int pin) {
  int offset = 325;
  float max = 65.0;
  float value = (analogRead(pin) - offset) / max;
  return max(min(value, 1), -1);
}

// CALCULATION

float calculateHue(float tilt) {
  if (abs(tilt) >= tiltThreshold) {
    float m = tilt / abs(tilt) * ((abs(tilt) - tiltThreshold) / (1 - tiltThreshold));
    h = h + hueStep * m;
  }

  h = h - floor(h);

  return h;
}

RGB hsvToRgb(float h, float s, float v) {
  int i = floor(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);
  float r, g, b;

  switch (i % 6) {
    case 0: r = v, g = t, b = p; break;
    case 1: r = q, g = v, b = p; break;
    case 2: r = p, g = v, b = t; break;
    case 3: r = p, g = q, b = v; break;
    case 4: r = t, g = p, b = v; break;
    case 5: r = v, g = p, b = q; break;
  }

  return {
    .r = r * 255,
    .g = g * 255,
    .b = b * 255
  };
}

// OUTPUT

void print(float y, float h) {
  Serial.print(y, 4);
  Serial.print(",");
  Serial.print(h, 4);
  Serial.println();
}

void writeRGB(RGB rgb) {
  analogWrite(redPin, rgb.r);
  analogWrite(greenPin, rgb.g);
  analogWrite(bluePin, rgb.b);
}
