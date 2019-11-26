int redPin = 7;
int greenPin = 6;
int bluePin = 5;
int max = 360;
int hue = 50;

struct RGB {
    float r;
    float g;
    float b;
};

void setup() {
    Serial.begin(9600);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Serial.println("setup");
}

void loop() {
    Serial.print("hue: ");
    Serial.println(hue, HEX);

    // convert to rgb
    struct RGB rgb = hsv2rgb(hue, 1, 1);
    Serial.print("r: ");
    Serial.print(rgb.r);
    Serial.print(", g: ");
    Serial.print(rgb.g);
    Serial.print(", b: ");
    Serial.println(rgb.b);

    // set color
    setColor(rgb.r, rgb.g, rgb.b);

    // increment color
    hue = (hue >= max) ? 0 : hue + 1;
    delay(10);
}

void setColor(int r, int g, int b) {
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
}

struct RGB hsv2rgb(int h, float s, float v) {
    struct RGB rgb;
    rgb.r = max(0, sineWave(h + 300) * 255);
    rgb.g = max(0, sineWave(h + 180) * 255);
    rgb.b = max(0, sineWave(h + 60) * 255);
    return rgb;
}

float sineWave(int d) {
    return sin(d * DEG_TO_RAD);
}
