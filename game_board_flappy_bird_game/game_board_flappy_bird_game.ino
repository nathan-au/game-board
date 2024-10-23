#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LED 10
#define B1 2
#define B2 3
#define PEIZO 8
#define JOY_X A6
#define JOY_Y A7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int button1;

int birdX = 0;
int birdY = 0;
int birdJump = 6;
int birdFall = 2;


void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();

  pinMode(LED, OUTPUT);
  pinMode(B1, INPUT);
  pinMode(B1, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PEIZO, OUTPUT);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);  

  Serial.begin(9600);
}

void loop() {

  display.clearDisplay();

  button1 = digitalRead(B1);

  if (button1 == 1 and birdY > 0) {
    birdY -= birdJump;
  }

  if (birdY < 64) {
    birdY += birdFall;
  
  }
  birdX++;
  
  if (birdY > 64) {
    birdY = 0;
  }

  if (birdX > 128) {
    birdX = 0;
  }

  display.fillCircle(birdX, birdY, 5, 1);
  display.display();

}
