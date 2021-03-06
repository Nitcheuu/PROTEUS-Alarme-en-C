#include "D:\PIC\projet\main.h"
// Clavier
#define L1 input(pin_d3)
#define L2 input(pin_d4)
#define L3 input(pin_d5)
#define L4 input(pin_d6)
// Intrusion
#define intrusion1 input(pin_b1)
#define intrusion2 input(pin_b2)
#define intrusion3 input(pin_b3)
#define intrusion4 input(pin_b4)
#define intrusion1Led output_high(pin_c1)
#define intrusion2Led output_high(pin_c2)
#define intrusion3Led output_high(pin_c5)
#define intrusion4Led output_high(pin_c4)
#define intrusion1LedLow output_low(pin_c1)
#define intrusion2LedLow output_low(pin_c2)
#define intrusion3LedLow output_low(pin_c5)
#define intrusion4LedLow output_low(pin_c4
#define intrusionRetar1 input(pin_b5)
#define intrusionRetar2 input(pin_b6)
#define intrusionRetar1Led output_high(pin_e0)
#define intrusionRetar2Led output_high(pin_e1)
#define intrusionRetar1LedLow output_low(pin_e0)
#define intrusionRetar2LedLow output_low(pin_e1)
// buzzer et sirene
#define buzzer output_high(pin_a0)
#define buzzerLow output_low(pin_a0)
#define sirene output_high(pin_b7)
#define sireneLow output_low(pin_b7)

int32 n = 0, n1;
int16 codeArmement = 33, codeDesa = 1236, delaiSirene = 180, temps = 0, delai = 20, tempsSirene = 0, tempsIntruRetar = 0;
int16 changeCodeA = 10, changeCodeD = 11, changeTempo = 20, changeSirene = 30; 
int1 isArmed, intrusion, timerSirene, timerRetar, isDelay, clear;
float timeLeft = 0;

// Proc?dure qui permet de reset les diff?rents codes
void defaut(){
   codeArmement = 33;
   codeDesa = 1236;
   delaiSirene = 180;
   delai = 20;
}


// Proc?dure qui permet de lire le temps
// J'ai proc?d? ainsi car que le rtos faisait bugger mon programme
// J'ai mis 10 delay de 100 ms pour ne pas que la coupure ne se sente
// trop lors de l'execution du programme
void time(){
   //printf("Temps = %lu\r\n",temps);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   delay_ms(100);
   temps ++;
   // Ici on d?marre le compteur des zonnes diff?r?s quand isArmed = 1
   if (isArmed){
      tempsIntruRetar ++;
   }
   // De m?me pour le compteur de la sir?ne quand intrusion = 1
   if (intrusion){ 
      tempsSirene ++;
   }
   
}

// proc?dure cls qui permet de nettoyer le LCD
void cls(void){
  printf("%c%c",254,1);
}


// Proc?dure qui permet de remettre le syst?me dans son ?tat initial
void reset(){
   isArmed = 0;
         intrusion = 0;
         tempsSirene = 0;
         tempsIntruRetar = 0;
         isDelay = 0;
         timerSirene = 0;
         timerRetar = 0;
         clear = 0;
         intrusion1LedLow;
         intrusion1LedLow;
         intrusion1LedLow;
         intrusion1LedLow;
         buzzerLow;
         intrusionRetar1LedLow;
         intrusionRetar2LedLow;
}

//Lecture du clavier + gestion du code entr? avec des sinon si
#int_EXT
void  EXT_isr(void) 
{
  disable_interrupts(INT_EXT);
  output_high(pin_d0);// active la colonne de gauche
  output_low(pin_d1);
  output_low(pin_d2);
  if (L1) {
     printf("1"); n=10*n+1;
  } 
  if (L2) {
     printf("4"); n=10*n+4;
  }
  if (L3) {
     printf("7");n=10*n+7;
  }
  if (L4) {
     printf("*");
     
  }
  
  output_high(pin_d1);
  output_low(pin_d0);
  output_low(pin_d2);// active la colonne du milieu
  if (L1) {
     printf("2");n=10*n+2;
  } 
  if (L2) {
     printf("5");n=10*n+5;
  }
  if (L3) {
     printf("8");n=10*n+8;
  }
  if (L4) {
     printf("0");n=10*n;
  }
  
  output_high(pin_d2);
  output_low(pin_d0);
  output_low(pin_d1);// active la colonne de droite
  if (L1) {
     printf("3");n=10*n+3;
  } 
  if (L2) {
     printf("6");n=10*n+6;
  }
  if (L3) {
     printf("9");n=10*n+9;
  }
  if (L4) {
    //n = n *0.01;
    n1 = n;
    n = 0;
    cls();
    //printf("n1 vaut : %lu\n\r",n1);
    if(n1 == codeArmement && !isArmed){
         cls();
         printf("%c%cAlarme arm?e ",254,128);
         delay_ms(1000);
         cls();
         isArmed = 1;
         n1 = 0;
    }
    // ici le cas o? l'utilisateur rentre le code lors d'une intrusion
    else if(n1 == codeArmement && intrusion && isArmed){
         cls();
         printf("%c%cOk",254,128);
         delay_ms(1000);
         cls();
         reset();        
    }
   
    else if(n1 == codeDesa && isArmed){
         cls();
         printf("%c%cAlarme desarmee",254,128);
         delay_ms(1000);
         cls();
         isArmed = 0;
         n1 = 0;
         printf("%d", isArmed);
         reset();
    }
    else if(n1 == codeDesa && !isArmed){
         cls();
         printf("%c%cAlarme non armee",254,128);
         delay_ms(1000);
         cls();
         n1 = 0;
    }
    else if(n1/100 == changeCodeA){
         cls();
         codeArmement = n1 %100;
         printf("%c%cNouveau code : %lu",254,128,codeArmement);
         delay_ms(1000);
         cls();
    }
    else if(n1/10000 == changeCodeD){
         cls();
         codeDesa = n1 %10000;
         printf("%c%cNouveau code desa : %lu",254,128,codeDesa);
         delay_ms(1000);
         cls();
    }
    else if(n1/100 == changeTempo){
         cls();
         delai = n1%100;
         printf("%c%cNouveau delai : %lu",254,128,delai);
         delay_ms(1000);
         cls();
    }
    else if(n1/1000 == changeSirene){
         cls();
         if (n1%1000 > 180){
            printf("%c%cDuree trop longue",254,128);
         }
         else{
            delaiSirene = n1%1000;
            printf("%c%cNouveau delai : %lu",254,128,delaiSirene);
         }
         delay_ms(1000);
         cls();
    }
    else if (n1 == 99000){
         defaut();
         printf("%c%cParametres resets",254,128);
         delay_ms(1000);
         cls();
    }
    
   }

  
  output_high(pin_d0);
  output_high(pin_d1);
  output_high(pin_d2); //activation des colonnes
  enable_interrupts(INT_EXT);
}



void main()
{

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   output_high(pin_d0);
   output_high(pin_d1);
   output_high(pin_d2);
   while(true){
      
      time();
      
      //printf("%lu\r\n",CodeArmement);
      if (isArmed){
      
         output_high(pin_c0); // allume la led "Alarme active"
         
         // ici quand le delai n'est pas encore atteint, on affiche sur le
         // LCD le nombre de secondes restantes pour sortir par une zone
         // diff?r?e 
         if(!isDelay){
            timeLeft = delai-tempsIntruRetar; 
            printf("%c%cTemps restant : %f",254,128, timeLeft );
            // Permet de faire clignoter le buzzer une seconde sur deux
            if(temps % 2 == 0){
               buzzer;
            }
            else{
               buzzerLow;
            }
         }
         
         // Permet de clear le LCD ? la fin du d?compte
         if(isDelay && !clear){
            cls();
            clear =1;
         }
         // D?clenchements divers en cas d'intrusion
         if (intrusion1){
            intrusion1Led;
            intrusion = 1;
         }
      
         if (intrusion2){
            intrusion2Led;
            intrusion = 1;
         }
   
         
         if (intrusion3){
            intrusion3Led;
            intrusion = 1;
         }
         
         if (intrusion4){
            intrusion4Led;
            intrusion = 1;
         }
         if(intrusionRetar1 && isDelay){
            intrusionRetar1Led;
            intrusion = 1;
         }
         if(intrusionRetar2 && isDelay){
            intrusionRetar2Led;
            intrusion = 1;
         }
      }
      else{
         output_low(pin_c0); // si !isArmed on ?teint la led "Alarme active"
      }
      // Gestion de la sir?ne on v?rifie qu'il y a bien une intrusion et que
      // la dur?e de d?clenchement de la sir?ne est inf?rieur au d?lai max
      if(intrusion && tempsSirene <= delaiSirene){
         sirene;
      }
      else{
         sireneLow; // sinon on coupe la sir?ne
      }
      if (tempsIntruRetar >= delai){
         isDelay = 1;
      }
      if(intrusion){
         isDelay = 1;
         buzzerLow;
         cls();
         printf("%c%cIntrusion detectee",254,128);
      }
      
      
      //printf("TempsNow: %lu\n\r",tempsSirene);
      //printf("TempsIntru: %lu\n\r",tempsIntruRetar);
      //printf("Temps: %lu\n\r",temps);
   }
   
}
