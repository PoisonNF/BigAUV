#include "task_conf.h"
#include "bsp_io.h"

uint8_t Manipulator_flag = RESET; //��е�ִ������ݽ�����ɱ�־
uint8_t Manipulator_buf[15]; //��е�ִ��ڽ��ջ�����

enum{
	Notask_State = 'A', //������
	Progress_State, //���������
	Accomplish_State, //�������
	Abnormal_State, //����ִ���쳣
}; //��е�ֹ���״̬

enum{
	Notask = 'A', //������
	Extend, //���
	Release, //�豸�ͷ�
	Grab, //�Ӿ�����ץȡ
	Reset, //��λ
	Back, //�ջ�
}; //��е����������

//enum{
//	Extend, //���
//	Release, //��ʼ�豸�ͷ�����
//	Grab, //��ʼ����ץȡ����
//	Reset, //��λ
//	Back, //�ջ�
//}; //���������е����������

uint8_t Manipulator_Task = Notask; //��е�ֵ�ǰ��������
//extern uint8_t Manipulator_Uptask = Notask; //���������е����������

void Manipulator_Stateswitch(void) //��е��״̬�л�����
{
	switch(Manipulator_Task)
	{
		case Notask:
			
			break;
		case Extend:
			
			break;
		case Release:
			
			break;
		case Grab:
			
			break;
		case Reset:
			
			break;
		case Back:
			
			break;
		default:
			break;
	}
}

void Manipulator_Analysis(void)//��е�����ݷ�������
{
	if(Manipulator_flag == SET)
	{
		switch(Manipulator_buf[2])
		{
			
		}
		switch(Manipulator_buf[3])
		{
			
		}
		Manipulator_flag = RESET;
	}
}

