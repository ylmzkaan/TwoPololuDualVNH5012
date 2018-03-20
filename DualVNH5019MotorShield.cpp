#include "DualVNH5019MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

DualVNH5019MotorShield::DualVNH5019MotorShield()
{
  //Pin map
  _INA1 = 2;
  _INB1 = 4;
  _EN1DIAG1 = 6;
  _CS1 = A0; 
  _PWM1 = 9;
  _INA2 = 7;
  _INB2 = 8;
  _EN2DIAG2 = 12;
  _CS2 = A1;
  _PWM2 = 10;
}

DualVNH5019MotorShield::DualVNH5019MotorShield(unsigned char INA1, unsigned char INB1, 
                                               unsigned char EN1DIAG1, unsigned char CS1, 
                                               unsigned char INA2, unsigned char INB2, 
                                               unsigned char EN2DIAG2, unsigned char CS2,
											   unsigned char INA3, unsigned char INB3, 
											   unsigned char EN3DIAG3, unsigned char CS3,
											   unsigned char INA4, unsigned char INB4, 
											   unsigned char EN4DIAG4, unsigned char CS4); //User-defined pin selection.
{
  //Pin map
  _INA1 = INA1;
  _INB1 = INB1;
  _EN1DIAG1 = EN1DIAG1;
  _CS1 = CS1;
  _PWM1 = 5;
  _INA2 = INA2;
  _INB2 = INB2;
  _EN2DIAG2 = EN2DIAG2;
  _CS2 = CS2;
  _PWM2 = 11;
  _INA3 = INA3;
  _INB3 = INB3;
  _EN3DIAG3 = EN3DIAG3;
  _CS3 = CS3;
  _PWM3 = 7;
  _INA4 = INA4;
  _INB4 = INB4;
  _EN4DIAG4 = EN4DIAG4;
  _CS4 = CS4;
  _PWM4 = 8;
}

DualVNH5019MotorShield::DualVNH5019MotorShield(unsigned char INA1, unsigned char INB1, 
                                               unsigned char EN1DIAG1, unsigned char CS1, 
                                               unsigned char PWM1, unsigned char INA2,
                                               unsigned char INB2, unsigned char EN2DIAG2, 
                                               unsigned char CS2, unsigned char PWM2,unsigned char INA3, unsigned char INB3, 
                                               unsigned char EN3DIAG3, unsigned char CS3, 
                                               unsigned char PWM3, unsigned char INA4,
                                               unsigned char INB4, unsigned char EN4DIAG4, 
                                               unsigned char CS4, unsigned char PWM4)
{
  //Pin map
  _INA1 = INA1;
  _INB1 = INB1;
  _EN1DIAG1 = EN1DIAG1;
  _CS1 = CS1;
  _PWM1 = PWM1;
  _INA2 = INA2;
  _INB2 = INB2;
  _EN2DIAG2 = EN2DIAG2;
  _CS2 = CS2;
  _PWM2 = PWM2;
  _INA3 = INA3;
  _INB3 = INB3;
  _EN3DIAG3 = EN3DIAG3;
  _CS3 = CS3;
  _PWM3 = PWM3;
  _INA4 = INA4;
  _INB4 = INB4;
  _EN4DIAG4 = EN4DIAG4;
  _CS4 = CS4;
  _PWM4 = PWM4;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualVNH5019MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_INA1,OUTPUT);
  pinMode(_INB1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_EN1DIAG1,INPUT);
  pinMode(_CS1,INPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_INB2,OUTPUT);
  pinMode(_PWM2,OUTPUT);
  pinMode(_EN2DIAG2,INPUT);
  pinMode(_CS2,INPUT);
  pinMode(_INA3,OUTPUT);
  pinMode(_INB3,OUTPUT);
  pinMode(_PWM3,OUTPUT);
  pinMode(_EN3DIAG3,INPUT);
  pinMode(_CS3,INPUT);
  pinMode(_INA4,OUTPUT);
  pinMode(_INB4,OUTPUT);
  pinMode(_PWM4,OUTPUT);
  pinMode(_EN4DIAG4,INPUT);
  pinMode(_CS4,INPUT);
  
  // initialize the register pointers to null. If not set we will use analogWrite
  _PWM1_REG = NULL; 
  _PWM2_REG = NULL;
  _PWM3_REG = NULL; 
  _PWM4_REG = NULL;
  
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  if(_PWM1 == 9 || _PWM1 == 10 || _PWM2 == 9 || _PWM2 == 10)
  {
    TCCR1A = 0;
    if(_PWM1 == 9)       { TCCR1A |= _BV(COM1A1); _PWM1_REG = &OCR1A; }
    else if(_PWM1 == 10) { TCCR1A |= _BV(COM1B1); _PWM1_REG = &OCR1B; }
    
    if(_PWM2 == 9)       { TCCR1A |= _BV(COM1A1); _PWM2_REG = &OCR1A; }
    else if(_PWM2 == 10) { TCCR1A |= _BV(COM1B1); _PWM2_REG = &OCR1B; }
  
    TCCR1B = _BV(WGM13) | _BV(CS10);
    ICR1 = 400;
  }
  /* ------------------------------- FOR THE MEGA ------------------------- */
  #elif defined(__AVR_ATmega2560__) 
  if(_PWM1 == 11 || _PWM1 == 12 || _PWM1 == 13 || 
     _PWM2 == 11 || _PWM2 == 12 || _PWM2 == 13)
  {
    //timer1
    TCCR1A = 0;
    if(_PWM1 == 11)      { TCCR1A |= _BV(COM1A1); _PWM1_REG = &OCR1A; }
    else if(_PWM1 == 12) { TCCR1A |= _BV(COM1B1); _PWM1_REG = &OCR1B; }
    else if(_PWM1 == 13) { TCCR1A |= _BV(COM1C1); _PWM1_REG = &OCR1C; }
    
    if(_PWM2 == 11)      { TCCR1A |= _BV(COM1A1); _PWM2_REG = &OCR1A; }
    else if(_PWM2 == 12) { TCCR1A |= _BV(COM1B1); _PWM2_REG = &OCR1B; }
    else if(_PWM2 == 13) { TCCR1A |= _BV(COM1C1); _PWM2_REG = &OCR1C; }
    
    TCCR1B = _BV(WGM13) | _BV(CS10);
    ICR1 = 400;
  }
  else if(_PWM1 == 2 || _PWM1 == 3 || _PWM1 == 5 || 
          _PWM2 == 2 || _PWM2 == 3 || _PWM2 == 5 || _PWM2 == 6 || 
		  _PWM3 == 7 || _PWM3 == 8 || 
          _PWM4 == 7 || _PWM4 == 8)
  {
    //timer3
    TCCR3A = 0;
    if(_PWM1 == 5)      { TCCR3A |= _BV(COM3A1); _PWM1_REG = &OCR3A; }
    else if(_PWM1 == 2) { TCCR3A |= _BV(COM3B1); _PWM1_REG = &OCR3B; }
    else if(_PWM1 == 3) { TCCR3A |= _BV(COM3C1); _PWM1_REG = &OCR3C; }
    
    if(_PWM2 == 5)      { TCCR3A |= _BV(COM3A1); _PWM2_REG = &OCR3A; }
    else if(_PWM2 == 2) { TCCR3A |= _BV(COM3B1); _PWM2_REG = &OCR3B; }
    else if(_PWM2 == 3) { TCCR3A |= _BV(COM3C1); _PWM2_REG = &OCR3C; }
	else if(_PWM2 == 6) { TCCR3A |= _BV(COM4A1); _PWM2_REG = &OCR4A; }
    
    TCCR3B = _BV(WGM33) | _BV(CS30);
    ICR3 = 400;

	//timer4
    TCCR4A = 0;
    if(_PWM3 == 7) { TCCR4A |= _BV(COM4B1); _PWM3_REG = &OCR4B; }
    else if(_PWM3 == 8) { TCCR4A |= _BV(COM4C1); _PWM3_REG = &OCR4C; }
    
    if(_PWM4 == 7) { TCCR4A |= _BV(COM4B1); _PWM4_REG = &OCR4B; }
    else if(_PWM4 == 8) { TCCR4A |= _BV(COM4C1); _PWM4_REG = &OCR4C; }
    
    TCCR4B = _BV(WGM43) | _BV(CS40);
    ICR4 = 400;
  }
  else if(_PWM1 == 44 || _PWM1 == 45 || _PWM1 == 46 || 
          _PWM2 == 44 || _PWM2 == 45 || _PWM2 == 46)
  {
    //timer5
    TCCR5A = 0;
    if(_PWM1 == 46)      { TCCR5A |= _BV(COM5A1); _PWM1_REG = &OCR5A; }
    else if(_PWM1 == 45) { TCCR5A |= _BV(COM5B1); _PWM1_REG = &OCR5B; }
    else if(_PWM1 == 44) { TCCR5A |= _BV(COM5C1); _PWM1_REG = &OCR5C; }
    
    if(_PWM2 == 46)      { TCCR5A |= _BV(COM5A1); _PWM2_REG = &OCR5A; }
    else if(_PWM2 == 45) { TCCR5A |= _BV(COM5B1); _PWM2_REG = &OCR5B; }
    else if(_PWM2 == 44) { TCCR5A |= _BV(COM5C1); _PWM2_REG = &OCR5C; }
    
    TCCR5B = _BV(WGM53) | _BV(CS50);
    ICR5 = 400;
  }
  #endif
}

// Set speed for motor 1, speed is a number between -400 and 400
void DualVNH5019MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;
    
  if(_PWM1_REG) {
    *_PWM1_REG = speed;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM1,speed * 51/80); // default to using analogWrite, mapping 400 to 255
  }

  if (speed == 0)
  {
    digitalWrite(_INA1,LOW);   // Make the motor coast no
    digitalWrite(_INB1,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA1,LOW);
    digitalWrite(_INB1,HIGH);
  }
  else
  {
    digitalWrite(_INA1,HIGH);
    digitalWrite(_INB1,LOW);
  }
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void DualVNH5019MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;

  if(_PWM2_REG) {
    *_PWM2_REG = speed;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM1,speed * 51/80); // default to using analogWrite, mapping 400 to 255
  }
    
  if (speed == 0)
  {
    digitalWrite(_INA2,LOW);   // Make the motor coast no
    digitalWrite(_INB2,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA2,LOW);
    digitalWrite(_INB2,HIGH);
  }
  else
  {
    digitalWrite(_INA2,HIGH);
    digitalWrite(_INB2,LOW);
  }
}

void DualVNH5019MotorShield::setM3Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;

  if(_PWM3_REG) {
    *_PWM3_REG = speed;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM3,speed * 51/80); // default to using analogWrite, mapping 400 to 255
  }
    
  if (speed == 0)
  {
    digitalWrite(_INA3,LOW);   // Make the motor coast no
    digitalWrite(_INB3,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA3,LOW);
    digitalWrite(_INB3,HIGH);
  }
  else
  {
    digitalWrite(_INA3,HIGH);
    digitalWrite(_INB3,LOW);
  }
}

void DualVNH5019MotorShield::setM4Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;

  if(_PWM4_REG) {
    *_PWM4_REG = speed;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM4,speed * 51/80); // default to using analogWrite, mapping 400 to 255
  }
    
  if (speed == 0)
  {
    digitalWrite(_INA4,LOW);   // Make the motor coast no
    digitalWrite(_INB4,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA4,LOW);
    digitalWrite(_INB4,HIGH);
  }
  else
  {
    digitalWrite(_INA4,HIGH);
    digitalWrite(_INB4,LOW);
  }
}

// Set speed for motors
void DualVNH5019MotorShield::setSpeeds(int m1Speed, int m2Speed,int m3Speed, int m4Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
  setM3Speed(m3Speed);
  setM4Speed(m4Speed);
}

// Brake motor 1, brake is a number between 0 and 400
void DualVNH5019MotorShield::setM1Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA1, LOW);
  digitalWrite(_INB1, LOW);
  if(_PWM1_REG) {
    *_PWM1_REG = brake;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM1,brake * 51/80); // default to using analogWrite, mapping 400 to 255
  }
}

// Brake motor 2, brake is a number between 0 and 400
void DualVNH5019MotorShield::setM2Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA2, LOW);
  digitalWrite(_INB2, LOW);
  if(_PWM2_REG) {
    *_PWM2_REG = brake;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM2,brake * 51/80); // default to using analogWrite, mapping 400 to 255
  }
}

// Brake motor 3, brake is a number between 0 and 400
void DualVNH5019MotorShield::setM3Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA3, LOW);
  digitalWrite(_INB3, LOW);
  if(_PWM3_REG) {
    *_PWM3_REG = brake;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM3,brake * 51/80); // default to using analogWrite, mapping 400 to 255
  }
}

// Brake motor 4, brake is a number between 0 and 400
void DualVNH5019MotorShield::setM4Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA4, LOW);
  digitalWrite(_INB4, LOW);
  if(_PWM4_REG) {
    *_PWM4_REG = brake;                // if the register is set then use the timer
  } else {
    analogWrite(_PWM4,brake * 51/80); // default to using analogWrite, mapping 400 to 255
  }
}

// Brake motors, brake is a number between 0 and 400
void DualVNH5019MotorShield::setBrakes(int m1Brake, int m2Brake,int m3Brake, int m4Brake)
{
  setM1Brake(m1Brake);
  setM2Brake(m2Brake);
  setM3Brake(m3Brake);
  setM4Brake(m4Brake);
}

// Return motor 1 current value in milliamps.
unsigned int DualVNH5019MotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS1) * 34;
}

// Return motor 2 current value in milliamps.
unsigned int DualVNH5019MotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS2) * 34;
}

// Return motor 3 current value in milliamps.
unsigned int DualVNH5019MotorShield::getM3CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS3) * 34;
}

// Return motor 4 current value in milliamps.
unsigned int DualVNH5019MotorShield::getM4CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS4) * 34;
}

// Return error status for motor 1 
unsigned char DualVNH5019MotorShield::getM1Fault()
{
  return !digitalRead(_EN1DIAG1);
}

// Return error status for motor 2 
unsigned char DualVNH5019MotorShield::getM2Fault()
{
  return !digitalRead(_EN2DIAG2);
}

// Return error status for motor 3
unsigned char DualVNH5019MotorShield::getM3Fault()
{
  return !digitalRead(_EN3DIAG3);
}

// Return error status for motor 4
unsigned char DualVNH5019MotorShield::getM4Fault()
{
  return !digitalRead(_EN4DIAG4);
}
