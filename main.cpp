#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "f73-rncontrol-lib/uart.h"
#include "f73-rncontrol-lib/adc.h"
#include "f73-rncontrol-lib/button.h"
#include "f73-rncontrol-lib/led.h"



int main()
{
  // init uart
  uartInit(9600, 8, 'N', 1);
 

  // init LED
  ledInit();

  // init Button (ADC PINA7)
  buttonInit();

  
  printf(" Vorwaertszaehler\n\r'"); // Print String 
  uint8_t Cnt=0; // Zählvariable
  uint8_t State=0;// Taster gedrückt

   while (1)
   {


     // Schalter in welchem Zustand das Programm ist.
   		switch (State)
   		{
   			// State == 0 => Diesen Programmabschnitt ausführen
   		  case 0:
           // Abfrage ob Taster_read()==2 == 1, d.h. Taste gedrückt
   			  // "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
   		    if (buttonRead()==2)
   		    {
             // Zähler um 1 erhöhen
     	      Cnt = Cnt + 1;

             // Zustandswechsel 0 => 1: Taste gedrückt
   			    State =   1;

             // Neuen Zählerstand auf den LEDs ausgeben
             PORTC = ~Cnt;

             // Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
   		       _delay_ms(10);
   		    }
   			  else
   			  {
   				  // Nur über den "Leer"-Übergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
   				  // Lässt man "normalerweise" weg.
   			  }
   			  break;

   			// State == 1 => Diesen Programmabschnitt ausführen
   			case 1:
           // Abfrage ob Taster_read()!=2, d.h. Taste nicht gedrückt

   		    // "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
       		if (buttonRead()!=2)
   		    {
             // Zustandswechsel 1 => 0: Taste nicht (mehr) gedrückt
   			    State = 0;

             // Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
   		      _delay_ms(10);
            
   		    }
   			  else
   			  {
   				  // Nur über den "Leer"-Übergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
   				  // Lässt man "normalerweise" weg.
   			  }
   			  break;

   			// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
   			default:
   			  break;
   		}
   	}
 return 0;
}


