#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
									  
////////////////////////////////////////////////////////////////////////////////// 	 

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10���øߣ�����

}


void LEDFlicker(u16 cnt) { // ��������ΪLEDFlicker����дF��
  static u16 s_iCnt;    //���徲̬����s_iCnt��Ϊ������
  static u16 a_iCnt;
  a_iCnt = 0;
  s_iCnt++;             //�������ļ���ֵ��1
  
  if (s_iCnt >= cnt) {     //�������ļ���ֵ����cnt 
    a_iCnt = 1;
    //LED״̬ȡ����ʵ��LED��˸
    GPIO_WriteBit(GPIOG, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_13)));    
  }
  if (a_iCnt == 1 && s_iCnt >= 2 * cnt) {     //�������ļ���ֵ����cnt 
    s_iCnt = 0;         //���ü������ļ���ֵΪ0
    //LED״̬ȡ����ʵ��LED��˸
    GPIO_WriteBit(GPIOG, GPIO_Pin_14, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_14)));    
  }
}



