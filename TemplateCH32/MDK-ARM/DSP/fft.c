#include "fft.h"


float fft_inputbuf[FFT_LENGTH*2];	//FFT��������
float fft_outputbuf[FFT_LENGTH];	//FFT�������

arm_cfft_radix4_instance_f32 scfft;

void FFT_64_Init(void)
{
    uint16_t i=0;
    
    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);
    
    for(i=0;i<FFT_LENGTH;i++)//�����ź�����
    {
         fft_inputbuf[2*i]=100+
                           10*arm_sin_f32(2*PI*i/FFT_LENGTH)+
                           30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+
                           50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//���������ź�ʵ��
         fft_inputbuf[2*i+1]=0;//�鲿ȫ��Ϊ0
    }
    
    float value=2;
    float angle=0.0f;
    UNUSED(angle);
    float cycle=0;
    
    angle=-3.1415926/2;
            cycle+=0.1;
			for(i=0;i<FFT_LENGTH;i++)//�����ź�����
			{
                value+=80;
                if(value>180)value=0;
                
                fft_inputbuf[2*i]=value;	//���������ź�ʵ��
				fft_inputbuf[2*i+1]=0;//�鲿ȫ��Ϊ0
			}
}


void FFT_Operation()
{
    arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT���㣨��4��
    arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);//��������������ģ�÷�ֵ 
}










