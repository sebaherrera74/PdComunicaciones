/*=====[Nombre del programa]===================================================
 * Copyright YYYY Nombre completo del autor <author@mail.com>
 * All rights reserved.
 * Licencia: Texto de la licencia o al menos el nombre y un link
         (ejemplo: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.0
 * Fecha de creacion: YYYY/MM/DD
 */

/*=====[Inclusiones de dependencias de funciones]============================*/

#include "sapi.h"
#include "ADS1015.h"

/*=====[Macros de definición de constantes privadas]=========================*/

/*=====[Definiciones de variables globales externas]=========================*/

/*=====[Definiciones de variables globales publicas]=========================*/


/*=====[Definiciones de variables globales privadas]=========================*/

/*=====[Funcion principal, punto de entrada al programa luegp de encender]===*/

//Test para Driver del ads1015

int main (void)
{
   // ----- Configuraciones -------------------------
   boardInit();
   i2cInit( I2C0, 100000 );
   int16_t adc0, adc1, adc2, adc3=0;
    setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
   //setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   // setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
   // setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
   // setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
   // setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

   // ----- Repetir por siempre ---------------------
   while(TRUE) {



	     adc0 = readADC_SingleEnded(0);
	     adc1 = readADC_SingleEnded(1);
	     adc2 = readADC_SingleEnded(2);
	     adc3 = readADC_SingleEnded(3);
	     printf("AIN0: %i \r\n ",adc0);
	     printf("AIN1: %i \r\n ",adc1);
	     printf("AIN2: %i \r\n ",adc2);
	     printf("AIN3: %i \r\n ",adc3);
	     printf(" ");

	     delay(1000);




   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontrolador y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}




















