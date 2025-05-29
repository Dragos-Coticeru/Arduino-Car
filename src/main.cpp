#include <AFMotor.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#define LED_PIN PC1
#define BUZZER_PIN PC0

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ); 
AF_DCMotor motor4(4, MOTOR34_1KHZ); 

int Speeed = 255;
bool blinking = false;

ISR(TIMER1_COMPA_vect) {
  if (blinking) {
    PORTC ^= (1 << LED_PIN);
  }
}

void startBlinkTimer() {
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  OCR1A = 31249;
  TIMSK1 |= (1 << OCIE1A);
  blinking = true;
}

void stopBlinkTimer() {
  TCCR1B = 0;
  TIMSK1 &= ~(1 << OCIE1A);
  blinking = false;
  PORTC &= ~(1 << LED_PIN);
}

void signal_on() {
  PORTC |= (1 << BUZZER_PIN);
}

void signal_off() {
  PORTC &= ~(1 << BUZZER_PIN);
}

void forward() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed);  motor1.run(FORWARD);
  motor2.setSpeed(Speeed);  motor2.run(FORWARD);
  motor3.setSpeed(Speeed);  motor3.run(FORWARD);
  motor4.setSpeed(Speeed);  motor4.run(FORWARD);
}

void back() {
  startBlinkTimer();
  signal_on();
  motor1.setSpeed(Speeed);  motor1.run(BACKWARD);
  motor2.setSpeed(Speeed);  motor2.run(BACKWARD);
  motor3.setSpeed(Speeed);  motor3.run(BACKWARD);
  motor4.setSpeed(Speeed);  motor4.run(BACKWARD);
}

void left() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed);  motor1.run(BACKWARD);
  motor2.setSpeed(Speeed);  motor2.run(BACKWARD);
  motor3.setSpeed(Speeed);  motor3.run(FORWARD);
  motor4.setSpeed(Speeed);  motor4.run(FORWARD);
}

void right() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed);  motor1.run(FORWARD);
  motor2.setSpeed(Speeed);  motor2.run(FORWARD);
  motor3.setSpeed(Speeed);  motor3.run(BACKWARD);
  motor4.setSpeed(Speeed);  motor4.run(BACKWARD);
}

void topleft() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed);             motor1.run(FORWARD);
  motor2.setSpeed(Speeed);             motor2.run(FORWARD);
  motor3.setSpeed(Speeed / 3.1);       motor3.run(FORWARD);
  motor4.setSpeed(Speeed / 3.1);       motor4.run(FORWARD);
}

void topright() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed / 3.1);       motor1.run(FORWARD);
  motor2.setSpeed(Speeed / 3.1);       motor2.run(FORWARD);
  motor3.setSpeed(Speeed);             motor3.run(FORWARD);
  motor4.setSpeed(Speeed);             motor4.run(FORWARD);
}

void bottomleft() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed);             motor1.run(BACKWARD);
  motor2.setSpeed(Speeed);             motor2.run(BACKWARD);
  motor3.setSpeed(Speeed / 3.1);       motor3.run(BACKWARD);
  motor4.setSpeed(Speeed / 3.1);       motor4.run(BACKWARD);
}

void bottomright() {
  stopBlinkTimer();
  PORTC |= (1 << LED_PIN);
  signal_on();
  motor1.setSpeed(Speeed / 3.1);       motor1.run(BACKWARD);
  motor2.setSpeed(Speeed / 3.1);       motor2.run(BACKWARD);
  motor3.setSpeed(Speeed);             motor3.run(BACKWARD);
  motor4.setSpeed(Speeed);             motor4.run(BACKWARD);
}

void Stop() {
  stopBlinkTimer();
  signal_off();
  motor1.setSpeed(0);  motor1.run(RELEASE);
  motor2.setSpeed(0);  motor2.run(RELEASE);
  motor3.setSpeed(0);  motor3.run(RELEASE);
  motor4.setSpeed(0);  motor4.run(RELEASE);
}

void setup() {
  DDRC |= (1 << LED_PIN) | (1 << BUZZER_PIN);
  Serial.begin(9600);
  sei();
}

void loop() {
  if (Serial.available() > 0) {
    char val = Serial.read();
    Stop();

    switch (val) {
      case 'F': forward(); break;
      case 'B': back(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'I': topright(); break;
      case 'J': topleft(); break;
      case 'K': bottomright(); break;
      case 'M': bottomleft(); break;
      case 'T': Stop(); break;
    }
  }
}
