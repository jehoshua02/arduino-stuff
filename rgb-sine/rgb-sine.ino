int redPin = 7;
int greenPin = 6;
int bluePin = 5;
float hue = 0;
int max = 360;

struct RGB {
    float r, g, b;
};

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // calculate hue to rgb
  RGB rgb = sineRgb(hue / 360, 1, 1);

  // update led
  analogWrite(redPin, rgb.r);
  analogWrite(greenPin, rgb.g);
  analogWrite(bluePin, rgb.b);

  // calculate next hue
  hue = hue >= max ? 0 : hue + 0.1;
  delay(10);
}

RGB sineRgb(float hue) {
  return {
    .r = max(0, sin(hue * DEG_TO_RAD) * 255),
    .g = max(0, sin((hue + 120) * DEG_TO_RAD) * 255),
    .b = max(0, sin((hue + 240) * DEG_TO_RAD) * 255)
  };
}
