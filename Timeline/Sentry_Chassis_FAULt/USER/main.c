#include "main.h"

//º¯ÊýÉùÃ÷



//int main(void)
//{
//    BSP_Init();
//    
//    
//    
//    while(1);
//}

void BSP_Init()     
{
    configIO_Init();
    configUART_Init(); 
    configCAN_Init();
}