#include <SoftwareSerial.h>

// Pin which is used for the main button
#define MAIN_BUTTON 8
// Pin which switches motor to counterclockwise direction
#define TOP_MOTOR_BUTTON 19
// Pin which switches motor to clockwise direction
#define BOTTOM_MOTOR_BUTTON 18

// Motor pins
#define MOTOR_PWM 3
#define MOTOR_IN1 4
#define MOTOR_IN2 2
#define DC_MOTOR_SPEED 80

// Serial port which is used to communicate with audio device
SoftwareSerial SoundSerial(15, 14);

// the current state of an algorithm
// true - means that santa is playing until the end
// false - means that MAIN_BUTTON has to be pressed
bool isPlaying = false;
int totalSongs = 0;
int currentTrackIdx = 0;

bool DEBUG = false;

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    Serial.println("starting serial to communicate with audio player");
  }
  SoundSerial.begin(9600);

  pinMode(MAIN_BUTTON, INPUT_PULLUP);
  pinMode(TOP_MOTOR_BUTTON, INPUT_PULLUP);
  pinMode(BOTTOM_MOTOR_BUTTON, INPUT_PULLUP);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  pause();
}

void loop() {
  if (digitalRead(MAIN_BUTTON) == LOW) {
    isPlaying = !isPlaying;
    while (digitalRead(MAIN_BUTTON) == LOW);
  }

  if (isPlaying) {
    if (DEBUG) {
      Serial.println("playing");
    }
    play();
    runDCMotor();
  } else {
    if (DEBUG) {
      Serial.println("paused");
    }
    pause();
    stopDCMotor();
  }
}


bool isPlayerActive = false;
void play() {
  if (!isPlayerActive) {
    isPlayerActive = true;
    playMusic();
  }
}

void pause() {
  if (DEBUG) {
    Serial.println("pausing");
  }
  stopMusic();
  isPlayerActive = false;
}

int currDirection = 1;
int getDCMotorDirection() {
  bool isAtTop = digitalRead(TOP_MOTOR_BUTTON) == LOW;
  bool isAtBottom = digitalRead(BOTTOM_MOTOR_BUTTON) == LOW;
  if (isAtTop && !isAtBottom) {
    currDirection = 1;
  } else if (isAtBottom && !isAtTop) {
    currDirection = -1;
  }
  return currDirection;
}

void runDCMotor() {
  if (DEBUG) {
    Serial.print("running DC motor in dir: ");
  }
  analogWrite(MOTOR_PWM, DC_MOTOR_SPEED);
  int dir = getDCMotorDirection();
  if (dir == -1) {
    // CCW
    if (DEBUG) {
      Serial.println("CCW");
    }
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
  } else if (dir == 1) {
    if (DEBUG) {
      Serial.println("CW");
    }
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
  }
}

void stopDCMotor() {
  if (DEBUG) {
    Serial.println("Stopping DC Motor");
  }
  analogWrite(MOTOR_PWM, 0);
}

void playMusic() {
  if (DEBUG) {
    Serial.println("Starting audio-player");
  }
  setVolume(0x1A);
  unsigned char play[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0x01+0xB3};
  SoundSerial.write(play, 6);
}

void stopMusic() {
  if (DEBUG) {
    Serial.println("Pausing music and setting volume to 0");
  }
  unsigned char pause[4] = {0xAA, 0x03, 0x00, 0xAD};
  SoundSerial.write(pause, 4);
  setVolume(0x00);
}

void setVolume(unsigned char vol) {
  if (DEBUG) {
    Serial.print("setting volume to:");
    Serial.println(vol);
  }
  unsigned char volume[5] = {0xAA, 0x13, 0x01, vol, vol + 0xBE};
  SoundSerial.write(volume, 5);
}
