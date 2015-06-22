/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

void initMotorController();
void setMotorSpeed(int i, int spd);
#ifdef QUAD_MOTOR_DRIVER
  void setMotorSpeeds(int leftSpeed, int rightSpeed,int leftBackSpeed,int rightBackSpeed);
#else
  void setMotorSpeeds(int leftSpeed, int rightSpeed);
#endif
