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

int ballX = 64;
int ballY = 32;
bool ballRight = true;
bool ballUp = true;
int ballSpeed = 2;
int ballR = 2;

//PADDLE 1
int paddle1Y = 10;
int paddle1X = 8;
int paddle1End;

//PADDLE 2
int paddle2Y = 10;
int paddle2X = 118;
int paddle2End;

int paddleH = 20;
int paddleW = 2;
int paddleSpeed = 3;

//POINTS
int player1Points = 0;
int player2Points = 0;
bool pointCollision = false;

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
    pointCollision = false;

    display.clearDisplay();
    
    button1 = digitalRead(B1);
    button2 = digitalRead(B2);
    joyX = analogRead(JOY_X);
    joyY = analogRead(JOY_Y);

    display.drawRect(0, 0, 128, 64, 1); //border

    //BALL MOVEMENT
    if (ballRight == true) {
      ballX += ballSpeed;  
    } else if (ballRight == false) {
      ballX -= ballSpeed;  
    }
    if (ballUp == true) {
      ballY += ballSpeed;
    } else if (ballUp == false) {
      ballY -= ballSpeed;  
    }

    //BALL-WALL COLLISION
    if (ballX > 128 - ballR) {
      ballRight = false;  
      player1Points++;
      pointCollision = true;
    } else if (ballX < 0 + ballR) {
      ballRight = true;
      player2Points++;
      pointCollision = true;
    }
    if (ballY > 64 - ballR) {
      ballUp = false;  
    } else if (ballY < 0 + ballR) {
      ballUp = true;
    }

    //BALL-PADDLE COLLISION
    paddle1End = paddle1Y + paddleH;
    paddle2End = paddle2Y + paddleH;

    if (ballX == paddle1X + paddleW && ballY >= paddle1Y && ballY <= paddle1End && ballRight == false) {
      ballRight = true;
    } else if (ballX == paddle2X && ballY >= paddle2Y && ballY <= paddle2End && ballRight == true) {
      ballRight = false;  
    }

    //PADDLE 1 MOVEMENT
    if (joyY > 1000 && paddle1End < 64) {
      paddle1Y += paddleSpeed;
    } else if (joyY < 10 && paddle1Y > 0) {
      paddle1Y -= paddleSpeed;  
    }
    //PADDLE 2 MOVEMENT
    if (button1 == 1 && paddle2End < 64) {
      paddle2Y += paddleSpeed;
    } 
    if (button2 == 1 && paddle2Y > 0) {
      paddle2Y -= paddleSpeed;  
    }

    //PLAYER POINTS
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(32, 5);
    display.print("P1:");
    display.print(player1Points);
    display.print(" P2:");
    display.print(player2Points);

    if (pointCollision == true) {
      digitalWrite(LED, HIGH);
    }
    else {
      digitalWrite(LED, LOW);  
    }

    display.fillRect(paddle1X, paddle1Y, paddleW, paddleH, 1);
    display.fillRect(paddle2X, paddle2Y, paddleW, paddleH, 1);
    display.fillCircle(ballX, ballY, ballR, 1);

    display.display();


}
