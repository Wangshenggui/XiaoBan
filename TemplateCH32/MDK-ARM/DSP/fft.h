#ifndef _FFT_H
#define _FFT_H

#include "main.h"

#include "arm_math.h"

#define FFT_LENGTH		64 		//FFT长度，默认是1024点FFT

extern float fft_inputbuf[FFT_LENGTH*2];	//FFT输入数组
extern float fft_outputbuf[FFT_LENGTH];	//FFT输出数组

void FFT_64_Init(void);
void FFT_Operation(void);







#endif
