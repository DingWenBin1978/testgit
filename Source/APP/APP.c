/*
********************************************************************************
*
*                                 APP.c
*
* File          : APP.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     : 
* Description   : 主程序入口
*                
* History       :
* Date          : 2013.07.21
*******************************************************************************/


#include <string.h>

#include "APP.h"
#include "BSP.h"
#include "BSP_tim.h"


#include "HW_Config.h"

void LedHandler(void)
{
    IO_TOGGLE(eLED_1);
}

void Led2Handler(void)
{
    IO_TOGGLE(eLED_2);
}


/*******************************************************************************
* Function Name : int main(void)
* Description   : 主程序入口
* Input         : 
* Output        : 
* Other         : 
* Date          : 2013.07.21
*******************************************************************************/
int main(void)
{
    uint32_t count = 0;
    uint32_t len = 0;
    static uint8_t buf[200] = {0};
    
    BSP_Init();

//    BSP_TimOpen(TIM_2, 7200, 10000, LedHandler);
    BSP_TimOpen(TIM_3, 7200, 10000, Led2Handler);

    USB_Config();
    while (1)
    {
        if (count == 0) LED_ON(eLED_0);
        if (count == 0x4FFFF) LED_OFF(eLED_0);
        if (++count > 0x8FFFF) count = 0;


        len = USB_RxRead(buf, sizeof(buf));
        if (len > 0)
        {
            USB_TxWrite(buf, len);
        }
    }
}



