#ifndef _FFT_H
#define _FFT_H

#include "main.h"

#include "arm_math.h"

#define FFT_LENGTH		64 		//FFT���ȣ�Ĭ����1024��FFT

extern float fft_inputbuf[FFT_LENGTH*2];	//FFT��������
extern float fft_outputbuf[FFT_LENGTH];	//FFT�������

void FFT_64_Init(void);
void FFT_Operation(void);







#endif
