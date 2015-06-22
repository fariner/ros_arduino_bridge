/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#if defined POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined DUAL_MOTOR_DRIVER
 #include "DualMotorController.h"
 void RForward(){
   digitalWrite(RDIRPIN0,HIGH);
   digitalWrite(RDIRPIN1,LOW);
 }
 void RBackward(){
   digitalWrite(RDIRPIN0,LOW);
   digitalWrite(RDIRPIN1,HIGH);
 }
 void RPower(byte p){
   analogWrite(RPWRPIN,p);
 }
 void RStop(){
   digitalWrite(RPWRPIN,LOW);
 }
 void LForward(){
   digitalWrite(LDIRPIN0,HIGH);
   digitalWrite(LDIRPIN1,LOW);
 }
 void LBackward(){
   digitalWrite(LDIRPIN0,LOW);
   digitalWrite(LDIRPIN1,HIGH);
 }
 void LPower(byte p){
   analogWrite(LPWRPIN,p);
 }
 void LStop(){
   digitalWrite(LPWRPIN,LOW);
 }
 void initMotorController() {
   pinMode(RPWRPIN,OUTPUT);
   pinMode(RDIRPIN0,OUTPUT);
   pinMode(RDIRPIN1,OUTPUT);
   pinMode(LPWRPIN,OUTPUT);
   pinMode(LDIRPIN0,OUTPUT);
   pinMode(LDIRPIN1,OUTPUT);
   RStop();
   LStop();
   LForward();
   RForward();
 }
 void setMotorSpeed(int i, int spd){
   if(i==LEFT){
     if(spd>=0){
       LForward();
       LPower(spd);
     } else{ //spd<0
       LBackward();
       LPower(-spd);
     }
   } else {//i==RIGHT
     if(spd>=0){
       RForward();
       RPower(spd);
     } else{ //spd<0
       RBackward();
       RPower(-spd);
     }
   }
 }
  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  } 
#elif defined QUAD_MOTOR_DRIVER
 //share the include with dualMotorControler
 #include "DualMotorController.h"
 void RForward(){
   digitalWrite(RDIRPIN0,HIGH);
   digitalWrite(RDIRPIN1,LOW);
 }
 void RBackward(){
   digitalWrite(RDIRPIN0,LOW);
   digitalWrite(RDIRPIN1,HIGH);
 }
 void RPower(byte p){
   analogWrite(RPWRPIN,p);
 }
 void RStop(){
   digitalWrite(RPWRPIN,LOW);
 }
 void RBForward(){
   digitalWrite(RBDIRPIN,HIGH);
 }
 void RBBackward(){
   digitalWrite(RBDIRPIN,LOW);
 }
 void RBPower(byte p){
   analogWrite(RBPWRPIN,p);
 }
 void RBStop(){
   digitalWrite(RBPWRPIN,LOW);
 }
 void LForward(){
   digitalWrite(LDIRPIN0,HIGH);
   digitalWrite(LDIRPIN1,LOW);
 }
 void LBackward(){
   digitalWrite(LDIRPIN0,LOW);
   digitalWrite(LDIRPIN1,HIGH);
 }
 void LPower(byte p){
   analogWrite(LPWRPIN,p);
 }
 void LStop(){
   digitalWrite(LPWRPIN,LOW);
 }
 void LBForward(){
   digitalWrite(LBDIRPIN,HIGH);
 }
 void LBBackward(){
   digitalWrite(LBDIRPIN,LOW);
 }
 void LBPower(byte p){
   analogWrite(LBPWRPIN,p);
 }
 void LBStop(){
   digitalWrite(LBPWRPIN,LOW);
 }
 void initMotorController() {
   //Rigt
   pinMode(RPWRPIN,OUTPUT);
   pinMode(RDIRPIN0,OUTPUT);
   pinMode(RDIRPIN1,OUTPUT);
   pinMode(RBPWRPIN,OUTPUT);
   pinMode(RBDIRPIN,OUTPUT);
   //Left
   pinMode(LPWRPIN,OUTPUT);
   pinMode(LDIRPIN0,OUTPUT);
   pinMode(LDIRPIN1,OUTPUT);
   pinMode(LBPWRPIN,OUTPUT);
   pinMode(LBDIRPIN,OUTPUT);
   RStop();
   LStop();
   RBStop();
   LBStop();
   LForward();
   RForward();
   LBForward();
   RBForward();
 }
 void setMotorSpeed(int i, int spd){
   //Serial.print("speed=");
   //Serial.print(i);
   //Serial.print("=");
   //Serial.println(spd);
   if(i==LEFT){
     if(spd>=0){
       LForward();
       LPower(spd);
     } else{ //spd<0
       LBackward();
       LPower(-spd);
     }
   } if(i==RIGHT) {//i==RIGHT
     if(spd>=0){
       RForward();
       RPower(spd);
     } else{ //spd<0
       RBackward();
       RPower(-spd);
     }
   } if(i==LEFT_BACK){
     if(spd>=0){
       LBForward();
       LBPower(spd);
     } else{ //spd<0
       LBBackward();
       LBPower(-spd);
     }
   } else { //i==RIGHT_BACK
     if(spd>=0){
       RBForward();
       RBPower(spd);
     } else{ //spd<0
       RBBackward();
       RBPower(-spd);
     }
   }
 }
  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed,int leftBackSpeed,int rightBackSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
    setMotorSpeed(LEFT_BACK, leftBackSpeed);
    setMotorSpeed(RIGHT_BACK, rightBackSpeed);
  } 
#else
  #error A motor driver must be selected!
#endif

#endif
