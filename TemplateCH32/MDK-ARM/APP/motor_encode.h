#ifndef _MOTOR_ENCODE_H
#define _MOTOR_ENCODE_H

#include "main.h"
#include <stdbool.h>
#include "exti_it.h"

uint16_t GetMotorSpeed(bool bit);

extern uint16_t M1Speed;
extern uint16_t M2Speed;



#endif
