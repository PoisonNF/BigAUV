#include "task_conf.h"
#include "bsp_io.h"

uint8_t Manipulator_flag = RESET; //机械手串口数据接收完成标志
uint8_t Manipulator_buf[15]; //机械手串口接收缓冲区

enum{
	Notask_State = 'A', //无任务
	Progress_State, //任务进行中
	Accomplish_State, //任务完成
	Abnormal_State, //任务执行异常
}; //机械手工作状态

enum{
	Notask = 'A', //无任务
	Extend, //伸出
	Release, //设备释放
	Grab, //视觉自主抓取
	Reset, //复位
	Back, //收回
}; //机械手任务类型

//enum{
//	Extend, //伸出
//	Release, //开始设备释放任务
//	Grab, //开始自主抓取任务
//	Reset, //复位
//	Back, //收回
//}; //上行命令机械手任务类型

uint8_t Manipulator_Task = Notask; //机械手当前任务类型
//extern uint8_t Manipulator_Uptask = Notask; //上行命令机械手任务类型

void Manipulator_Stateswitch(void) //机械手状态切换函数
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

void Manipulator_Analysis(void)//机械手数据分析函数
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

