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
  RGB rgb = hsvToRgb(hue / 360, 1, 1);

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

/**
 * Converts an HSV color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
 * Assumes h, s, and v are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  v       The value
 * @return  Array           The RGB representation
 */
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

  return { .r = r * 255, .g = g * 255, .b = b * 255 };
}