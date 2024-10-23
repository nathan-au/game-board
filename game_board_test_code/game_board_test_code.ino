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

int button1 = 0;
int button2= 0;
int joyX = 0;
int joyY = 0;

int circleX = 64;
int circleY = 32;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
    button2 = digitalRead(B2);
    joyX = analogRead(JOY_X);
    joyY = analogRead(JOY_Y);

    //Serial.println(joyX);
    //Serial.println(joyY);

    if (button2 == 1) {
      digitalWrite(LED, HIGH);
      //tone(PEIZO, 200);
    }
    else {
      digitalWrite(LED, LOW);
      //noTone(PEIZO);
    }

    display.drawRect(0, 0, 128, 64, 1); //border
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.print("X: ");
    display.println(joyX);
    display.setCursor(5, 15);
    display.print("Y: ");
    display.println(joyY);

    if (joyX > 1000 && circleX < 128) {
      circleX += 2;
    } else if (joyX < 10 && circleX > 0) {
      circleX -= 2;  
    }

    if (joyY > 1000 && circleY < 64) {
      circleY += 2;
    } else if (joyY < 10 && circleY > 0) {
      circleY -= 2;  
    }

    if (button1 == 1) {
      display.fillCircle(circleX, circleY, 5, 1);
    }
    else {
      display.drawCircle(circleX, circleY, 5, 1);
    }

    display.display();


}
