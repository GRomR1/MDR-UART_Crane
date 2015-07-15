#ifndef __READ_MESSAGE_H
#define __READ_MESSAGE_H

#include "element.h"

char* itoa(int value, char* result, int base);
void makeCharSpeedElement(char *str, unsigned char status);
void readMessage(void);
void setPower(unsigned char status);
void setLight(unsigned char status);
void setSound(unsigned char status);
void setSpeed(unsigned char status);
void setPillarUp(unsigned char status);
void setPillarDown(unsigned char status);
void setDerrickUp(unsigned char status);
void setDerrickDown(unsigned char status);
void setOutriggerUp(unsigned char status);
void setOutriggerDown(unsigned char status);
void setTelescopicUp(unsigned char status);
void setTelescopicDown(unsigned char status);
void setHookUp(unsigned char status);
void setHookDown(unsigned char status);
void setLeftCrutchUp(unsigned char status);
void setLeftCrutchDown(unsigned char status);
void setRightCrutchUp(unsigned char status);
void setRightCrutchDown(unsigned char status);


#endif
