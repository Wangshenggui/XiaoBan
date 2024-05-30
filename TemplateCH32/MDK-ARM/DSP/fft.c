#include "fft.h"


float fft_inputbuf[FFT_LENGTH*2];	//FFT输入数组
float fft_outputbuf[FFT_LENGTH];	//FFT输出数组

arm_cfft_radix4_instance_f32 scfft;

void FFT_64_Init(void)
{
    uint16_t i=0;
    
    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);
    
    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
         fft_inputbuf[2*i]=100+
                           10*arm_sin_f32(2*PI*i/FFT_LENGTH)+
                           30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+
                           50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//生成输入信号实部
         fft_inputbuf[2*i+1]=0;//虚部全部为0
    }
    
    float value=2;
    float angle=0.0f;
    UNUSED(angle);
    float cycle=0;
    
    angle=-3.1415926/2;
            cycle+=0.1;
			for(i=0;i<FFT_LENGTH;i++)//生成信号序列
			{
                value+=80;
                if(value>180)value=0;
                
                fft_inputbuf[2*i]=value;	//生成输入信号实部
				fft_inputbuf[2*i+1]=0;//虚部全部为0
			}
}


void FFT_Operation()
{
    arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT计算（基4）
    arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);//把运算结果复数求模得幅值 
}










