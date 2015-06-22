/* *************************************************************
   Encoder definitions
   
   Add a "#if defined" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#if defined ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined ARDUINO_ENC_COUNTER
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	//enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
	enc_last |= PINC & 3; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#elif defined ARDUINO_ENC_COUNTER_QUAD
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  volatile long left_back_enc_pos = 0L;
  volatile long right_back_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  /* this routine get 3 encoders signals, we must differenciate them */
  /* encoder and interrupt have to be 2bits groups, in this case A0A1,A2A3,A4A5 */
  ISR (PCINT1_vect){
        static uint8_t lastIntValue=0;
        static uint8_t a0a1_enc_last=0;
        static uint8_t a2a3_enc_last=0;
        static uint8_t a4a5_enc_last=0;
        //Check A0A1
        uint8_t a0a1_now=PINC & 0b00000011;
        uint8_t a0a1_lst=lastIntValue & 0b00000011;
        if(a0a1_now!=a0a1_lst){//State changed?
	 a0a1_enc_last <<=2; //shift previous state two places
	 a0a1_enc_last |= a0a1_now; //read the current state into lowest 2 bits
         //update encoder position counter
  	 right_enc_pos += ENC_STATES[(a0a1_enc_last & 0x0f)];
        }
        uint8_t a2a3_now=PINC & 0b00001100;
        uint8_t a2a3_lst=lastIntValue & 0b00001100;
        if(a2a3_now!=a2a3_lst){//State changed?
	 a2a3_enc_last <<=2; //shift previous state two places
	 a2a3_enc_last |= a2a3_now >> 2; //read the current state into lowest 2 bits
         //update encoder position counter
  	 right_back_enc_pos += ENC_STATES[(a2a3_enc_last & 0x0f)];
        }
        uint8_t a4a5_now=PINC & 0b00110000;
        uint8_t a4a5_lst=lastIntValue & 0b00110000;
        if(a4a5_now!=a4a5_lst){//State changed?
	 a4a5_enc_last <<=2; //shift previous state two places
	 a4a5_enc_last |= a4a5_now>>4; //read the current state into lowest 2 bits
         //update encoder position counter
  	 left_back_enc_pos += ENC_STATES[(a4a5_enc_last & 0x0f)];
        }
        lastIntValue=PINC;
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else if(i==RIGHT) return right_enc_pos;
    else if(i==LEFT_BACK) return left_back_enc_pos;
    else return right_back_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else if (i==RIGHT){ 
      right_enc_pos=0L;
      return;
    } else if (i==LEFT_BACK){
      left_back_enc_pos=0L;
      return;
    } else {
      right_back_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
  resetEncoder(LEFT_BACK);
  resetEncoder(RIGHT_BACK);
}

#endif

