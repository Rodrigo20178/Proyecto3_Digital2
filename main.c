

/**
 * Proyecto3_digital2
 * Rodrigo García 20178
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"


#define XTAL 16000000


uint32_t Green1 = 0;
uint32_t Red1 = 0;


uint32_t Green2 = 0;
uint32_t Red2 = 0;


uint32_t Green3 = 0;
uint32_t Red3 = 0;


uint32_t Green4 = 0;
uint32_t Red4 = 0;

int sensorActivated = -1;
uint8_t debounceFlag = 0;       // Bandera para el debounce
uint32_t debounceCount = 0;     // Contador para el debounce

int sensorActivated2 = -1;
uint8_t debounceFlag2 = 0;       // Bandera para el debounce
uint32_t debounceCount2 = 0;     // Contador para el debounce

int sensorActivated3 = -1;
uint8_t debounceFlag3 = 0;       // Bandera para el debounce
uint32_t debounceCount3 = 0;     // Contador para el debounce

int sensorActivated4 = -1;
uint8_t debounceFlag4 = 0;       // Bandera para el debounce
uint32_t debounceCount4 = 0;     // Contador para el debounce






int main(void)
{

    // Configurar el sistema
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ);

    // Habilitar el periférico
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);



    // Configurar el pin PF4 (botón) como entrada
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);



    // Configurar el pin PF1, PF3 (LED) como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1 | GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    // Habilitamos UART5
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Configuramos los pines para UART5
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    // Inicializamos el UART5
    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);







    while (1)
    {
        int sensor1 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        int sensor2 = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_5);
        int sensor3 = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0);
        int sensor4 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);
        //SENSOR 1


        if (sensor1 != sensorActivated)
        {
            debounceCount = 0;
            debounceFlag = 1;
        }
        else if (debounceFlag)
        {
            // Incrementar el contador de debounce si el estado sigue siendo el mismo
            debounceCount++;

            // Si el contador de debounce alcanza un cierto límite, considerar el estado estable
            if (debounceCount > 10) // Ajusta este valor según sea necesario
            {
                debounceFlag = 0;

                // Determinar el estado del sensor y enviar por UART
                if (sensor1 == 0)
                {
                    // El sensor infrarrojo detecta algo, enviar 'A' por UART
                    UARTCharPut(UART5_BASE, 'A');
                    Red1 = GPIO_PIN_1;
                    Green1 = 0;
                }
                else
                {
                    // El sensor infrarrojo no detecta nada, enviar 'B' por UART
                    UARTCharPut(UART5_BASE, 'B');
                    Green1 = GPIO_PIN_3;
                    Red1 = 0;
                }
            }
        }

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_1, Green1 | Red1);
        sensorActivated = sensor1;


        //SENSOR 2
        if (sensor2 != sensorActivated2)
        {
            debounceCount2 = 0;
            debounceFlag2 = 1;
        }
        else if (debounceFlag2)
        {
            // Incrementar el contador de debounce si el estado sigue siendo el mismo
            debounceCount2++;

            // Si el contador de debounce alcanza un cierto límite, considerar el estado estable
            if (debounceCount2 > 10) // Ajusta este valor según sea necesario
            {
                debounceFlag2 = 0;

                // Determinar el estado del sensor y enviar por UART
                if (sensor2 == 0)
                {
                    // El sensor infrarrojo detecta algo, enviar 'C' por UART
                    UARTCharPut(UART5_BASE, 'C');
                    Red2 = GPIO_PIN_1;
                    Green2 = 0;
                }
                else
                {
                    // El sensor infrarrojo no detecta nada, enviar 'D' por UART
                    UARTCharPut(UART5_BASE, 'D');
                    Green2 = GPIO_PIN_0;
                    Red2 = 0;
                }
            }
        }

        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, Green2 | Red2);
        sensorActivated2 = sensor2;

        //SENSOR 3
        if (sensor3 != sensorActivated3)
        {
            debounceCount3 = 0;
            debounceFlag3 = 1;
        }
        else if (debounceFlag3)
        {
            // Incrementar el contador de debounce si el estado sigue siendo el mismo
            debounceCount3++;

            // Si el contador de debounce alcanza un cierto límite, considerar el estado estable
            if (debounceCount3 > 10) // Ajusta este valor según sea necesario
            {
                debounceFlag3 = 0;

                // Determinar el estado del sensor y enviar por UART
                if (sensor3 == 0)
                {
                    // El sensor infrarrojo detecta algo, enviar 'E' por UART
                    UARTCharPut(UART5_BASE, 'E');
                    Red3 = GPIO_PIN_2;
                    Green3 = 0;
                }
                else
                {
                    // El sensor infrarrojo no detecta nada, enviar 'F' por UART
                    UARTCharPut(UART5_BASE, 'F');
                    Green3 = GPIO_PIN_1;
                    Red3 = 0;
                }
            }
        }
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1 | GPIO_PIN_2, Green3 | Red3);
        sensorActivated3 = sensor3;

        //SENSOR 4
        if (sensor4 != sensorActivated4)
        {
            debounceCount4 = 0;
            debounceFlag4 = 1;
        }
        else if (debounceFlag4)
        {
            // Incrementar el contador de debounce si el estado sigue siendo el mismo
            debounceCount4++;

            // Si el contador de debounce alcanza un cierto límite, considerar el estado estable
            if (debounceCount4 > 10) // Ajusta este valor según sea necesario
            {
                debounceFlag4 = 0;

                // Determinar el estado del sensor y enviar por UART
                if (sensor4 == 0)
                {
                    // El sensor infrarrojo detecta algo, enviar 'G' por UART
                    UARTCharPut(UART5_BASE, 'G');
                    Red4 = GPIO_PIN_3;
                    Green4 = 0;
                }
                else
                {
                    // El sensor infrarrojo no detecta nada, enviar 'H' por UART
                    UARTCharPut(UART5_BASE, 'H');
                    Green4 = GPIO_PIN_2;
                    Red4 = 0;
                }
            }
        }
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3, Green4 | Red4);
        sensorActivated4 = sensor4;
        SysCtlDelay(100000);
    }
}

