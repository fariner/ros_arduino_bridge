/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */

// CAUTION!!!
//if you change encoders pins you must change encoder_driver code
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PORTD2  //pin 2
  #define LEFT_ENC_PIN_B PORTD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  //#define RIGHT_ENC_PIN_A PORTC4  //pin A4
  //#define RIGHT_ENC_PIN_B PORTC5   //pin A5
  #define RIGHT_ENC_PIN_A PORTC0   //pin A0
  #define RIGHT_ENC_PIN_B PORTC1   //pin A1
#endif
#ifdef ARDUINO_ENC_COUNTER_QUAD
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PORTD2  //pin 2
  #define LEFT_ENC_PIN_B PORTD3  //pin 3
  // Must be PORTC
  #define LEFT_BACK_ENC_PIN_A PORTC4  //pin A4
  #define LEFT_BACK_ENC_PIN_B PORTC5  //pin A5
  
  //below can be changed, but should be PORTC pins
  //#define RIGHT_ENC_PIN_A PORTC4  //pin A4
  //#define RIGHT_ENC_PIN_B PORTC5   //pin A5
  #define RIGHT_ENC_PIN_A PORTC0   //pin A0
  #define RIGHT_ENC_PIN_B PORTC1   //pin A1
  #define RIGHT_BACK_ENC_PIN_A PORTC2  //pin A2
  #define RIGHT_BACK_ENC_PIN_B PORTC3   //pin A3
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

