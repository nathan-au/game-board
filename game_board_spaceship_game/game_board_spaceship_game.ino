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

const unsigned char ship [] PROGMEM = {
  0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x0b, 0xa0, 0x0b, 0xa0, 
  0x4a, 0xa4, 0xcf, 0xe6, 0xdc, 0x7e, 0xfd, 0x7e, 0xff, 0xfe, 0x3f, 0xf8, 0x05, 0x40
};

int joyX;
int button1;
int button2;

int shipX = 64;
int shipSpeed = 4;

bool rock = true;
int rockX;
int rockXPos[] = {0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112};
int rockY = 0;
int rockSpeed = 2;
int rockSize = 4;

bool laser = false;
int laserX;
int laserY;
int laserSpeed = 4;

int points = 0;
bool gameOver = false;
bool rockLaserCollision;

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

  if (gameOver == false) {
    digitalWrite(LED, LOW);
  
    joyX = analogRead(JOY_X);
    button1 = digitalRead(B1);

    //SHIP MOVEMENT
    if (joyX > 1000 and shipX < 112) {
      shipX += shipSpeed;  
    }
    else if (joyX < 20 and shipX > 0) {
      shipX -= shipSpeed;  
    }

    //ROCK MOVEMENT
    rockY += rockSpeed;
  
    if (rockY > 64) {
      rock = true;
      rockY = 0;  
      rockX = rockXPos[random(0, 31)] + 7;
    }

    //LASER PROJECTION
    if (button1 == 1 and laser == false) {
      laserY = 50;
      laser = true;
      laserX = shipX + 7;
      //tone(PEIZO, 900, 75);
    }
  
    //LASER MOVEMENT
    if (laser == true) {
      laserY -= laserSpeed;
      display.drawFastVLine(laserX, laserY, 10, 1);
    }
    
    if (laserY < 0) {
      laser = false;
      laserX = 200;
    }

    //ROCK-LASER COLLISION
    if (rockX == laserX or rockX == laserX + 4 or rockX == laserX - 4) {
      for (int y = laserY; y < laserY + 10; y++) {
        if (rockY == y) {
          rockLaserCollision = true;
        }  
      }
    } 
  
    if (rockLaserCollision == true) {
      points++;  
      rock = false;
      rockLaserCollision = false;
      analogWrite(LED, 1);
    }

    //POINTS
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 54);
    display.print(points);
    
    //ROCK
    if (rock == true) {
      display.fillCircle(rockX, rockY, rockSize, 1);
    }

    //ROCK-SHIP COLLISION
    if (rockY > 48 and rock == true) {
      if (rockX == shipX + 7 or rockX == shipX + 7 + 4 or rockX == shipX + 7 - 4) {
        gameOver = true;
      }
    }

    //SHIP
    display.drawBitmap(shipX, 49, ship, 15, 15, 1);   
  
  }
  //GAME OVER
  else if (gameOver == true) {
    display.setTextColor(WHITE);

    display.setTextSize(2);
    display.setCursor(10, 10);
    display.print("GAME OVER");
    
    display.setTextSize(1);
    display.setCursor(10, 35);
    display.print("score: ");
    display.print(points);
    display.setCursor(10, 45);
    display.print("B2 to restart");
    
    button2 = digitalRead(B2);
    if (button2 == 1) {
      gameOver = false;
      rockY = 0;
      rockX = rockXPos[random(0, 31)] + 7;
      laser = false;
      points = 0;
      shipX = 64;
    }
  }

  display.display();
}
