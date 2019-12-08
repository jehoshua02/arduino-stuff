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
float hueStep = 0.003;
float strobeStep = 0.01;
float strobeAmplitude = 7.0 / 8.0;

// STATE

float h = 0;
float v = 1;
float strobePhase = 0;
float isStrobing = 1;

struct RGB {
    float r, g, b;
};

// SETUP

void setup() {
  Serial.begin(9600);

  setupADXL335();
  setupRGBLED();

  Serial.println("y,h,v");
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
  float v = calculateValue();
  RGB rgb = hsvToRgb(h, 1, v);

  // output
  print(y, h, v);
  writeRGB(rgb);

  delay(50);
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
    isStrobing = false;
  } else {
    isStrobing = true;
  }

  h = h - floor(h);

  return h;
}

float calculateValue() {
  if (isStrobing) {
    strobePhase = strobePhase >= 1 ? 0 : strobePhase + strobeStep;
    v = strobeAmplitude * ((sin(strobePhase * 360 * DEG_TO_RAD) + 1) / 2) + (1 - strobeAmplitude);
  } else {
    v = 1;
  }
  return v;
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

void print(float y, float h, float v) {
  Serial.print(y, 4);
  Serial.print(",");
  Serial.print(h, 4);
  Serial.print(",");
  Serial.print(v, 4);
  Serial.println();
}

void writeRGB(RGB rgb) {
  analogWrite(redPin, rgb.r);
  analogWrite(greenPin, rgb.g);
  analogWrite(bluePin, rgb.b);
}
