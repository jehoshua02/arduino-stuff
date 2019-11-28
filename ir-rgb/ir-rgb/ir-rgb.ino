#include <IRremote.h>

// IR REMOTE
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

// RGB LED
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;
float hue = 0;
float saturation = 1;
float value = 1;
bool play = true;

struct RGB {
    float r, g, b;
};

void setup() {
  Serial.begin(9600);
  setupIRRemote();
  setupRGBLED();
}

void setupIRRemote() {
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void setupRGBLED() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  readIRRemoteKey();
  writeToRgbLed();
}

void readIRRemoteKey() {
  if (irrecv.decode(&results)) {

    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch(results.value){
      case 0xFFA25D: // "powerToggle"
        break;
      case 0xFF629D: // "volumeUp"
        valueUp();
        break;
      case 0xFFE21D: // "funcStop"
        break;
      case 0xFF22DD: // "back"
        hueDown();
        break;
      case 0xFF02FD: // "playToggle"
        playToggle();
        break;
      case 0xFFC23D: // "forward"
        hueUp();
        break;
      case 0xFFE01F: // "down"
        saturationDown();
        break;
      case 0xFFA857: // "volumeDown"
        valueDown();
        break;
      case 0xFF906F: // "up"
        saturationUp();
        break;
      case 0xFF6897: // "0"
        break;
      case 0xFF9867: // "EQ"
        break;
      case 0xFFB04F: // "rept"
        break;
      case 0xFF30CF: // "1"
        break;
      case 0xFF18E7: // "2"
        break;
      case 0xFF7A85: // "3"
        break;
      case 0xFF10EF: // "4"
        break;
      case 0xFF38C7: // "5"
        break;
      case 0xFF5AA5: // "6"
        break;
      case 0xFF42BD: // "7"
        break;
      case 0xFF4AB5: // "8"
        break;
      case 0xFF52AD: // "9"
        break;
    }
    key_value = results.value;
    irrecv.resume();
    Serial.println(hue);
    Serial.println(saturation);
    Serial.println(value);
  }
}

void hueUp(float step) {
  Serial.println("hueUp");
  hue = hue >= 1 ? step : hue + step;
}

void hueUp() {
  hueUp(0.01);
}

void hueDown() {
  Serial.println("hueDown");
  hue = hue <= 0 ? 0.99 : hue - 0.01;
}

void valueUp() {
  Serial.println("valueUp");
  value = min(1, value + 0.01);
}

void valueDown() {
  Serial.println("valueDown");
  value = max(0, value - 0.01);
}

void saturationUp() {
  Serial.println("saturationUp");
  saturation = min(1, saturation + 0.01);
}

void saturationDown() {
  Serial.println("saturationDown");
  saturation = max(0, saturation - 0.01);
}

void writeToRgbLed() {
  if (play) {
    hueUp(0.0001);
  }
  RGB rgb = hsvToRgb(hue, saturation, value);
  analogWrite(redPin, rgb.r);
  analogWrite(greenPin, rgb.g);
  analogWrite(bluePin, rgb.b);
}

void playToggle() {
  play = !play;
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
