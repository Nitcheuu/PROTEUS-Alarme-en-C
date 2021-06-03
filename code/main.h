#include <18C452.h>
#device adc=8

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES RC_IO                 	//Resistor/Capacitor Osc
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NOOSCSEN              	//Oscillator switching is disabled, main oscillator is source
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES BORV25                	//Brownout reset at 2.5V
#FUSES NOPUT                 	//No Power Up Timer
#FUSES STVREN                	//Stack full/underflow will cause reset

#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

