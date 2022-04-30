#include_next <mcuconf.h>

#ifdef MCU_STM32

    #ifdef bastardPCB_A2_Pin

        #undef STM32_SERIAL_USE_USART2
        #define STM32_SERIAL_USE_USART2 TRUE

    #endif

    #ifndef bastardPCB_A2_Pin

        #undef STM32_SERIAL_USE_USART1
        #define STM32_SERIAL_USE_USART1 TRUE
    #endif
#endif
