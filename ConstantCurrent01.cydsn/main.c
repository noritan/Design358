/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "stdio.h"
#include "project.h"

int32 idac_value = 0;

void update_idac() {
    char buf[16];
    if (idac_value < 0) idac_value = 0;
    if (idac_value > 255) idac_value = 255;
    IDAC_SetValue(idac_value);
    sprintf(buf, "\r\n%ld", idac_value);
    UART_UartPutString(buf);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    IDAC_Start();
    Opamp_Start();
    
    UART_UartPutString("\r\nHELLO WORLD!\r\n");

    for (;;) {
        uint32 ch;
        UART_UartPutString("\r\n> ");
        do {
            ch = UART_UartGetByte();
        } while (ch & 0xFF00);
        UART_UartPutChar(ch);
        switch (ch) {
            case 'u':
                idac_value++;
                update_idac();
                break;
            case 'U':
                idac_value += 16;
                update_idac();
                break;
            case 'd':
                idac_value--;
                update_idac();
                break;
            case 'D':
                idac_value -= 16;
                update_idac();
                break;
        }
    }
}

/* [] END OF FILE */
