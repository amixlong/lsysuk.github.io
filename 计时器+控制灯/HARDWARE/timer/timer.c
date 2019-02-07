#include "timer.h"
#include "usart.h"
#include "My_Usart.h"
TIM_HandleTypeDef TIM3_Handler;
int count=0;

void TIM3_Init(u16 arr,u16 psc)
{ 
 TIM3_Handler.Instance=TIM3; //通用定时器 3
 TIM3_Handler.Init.Prescaler=psc; //分频系数
 TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数器
 TIM3_Handler.Init.Period=arr; //自动装载值
 TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //时钟分频因子
 HAL_TIM_Base_Init(&TIM3_Handler); //初始化定时器 3
 
 HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器 3 和定时器 3 更新中断
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
 __HAL_RCC_TIM3_CLK_ENABLE(); //使能 TIM3 时钟
 HAL_NVIC_SetPriority(TIM3_IRQn,1,2); //设置中断优先级，抢占 1，子优先级 2
 HAL_NVIC_EnableIRQ(TIM3_IRQn); //开启 ITM3 中断 
}

void TIM3_IRQHandler(void)
{
	 HAL_TIM_IRQHandler(&TIM3_Handler);

}
struct MyTime
{
	int m;
	int s;

}Time={0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if(htim==(&TIM3_Handler))
 {	 
	Time.s++;
	 
			
	 printf("\r\n已上电 %2d分%2d秒 按键事件：%2d次\r\n",Time.m,Time.s,count);
	 
   if(Time.s>=60)
	{
		
		Time.s%=60;	
		Time.m++;
	}		
	 
  }
}


