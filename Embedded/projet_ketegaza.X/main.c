/* 
 * File:   main.c
 * Author: TP-EO-5
 *
 * Created on 20 octobre 2021, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
 #include "Robot.h"
#include "PWM.h" 
int main (void){

// Initialisationde l?oscillateur
InitOscillator ( ) ;

// Configuration des éntrées sorties

// moteur 
InitPWM ( );
//PWMSetSpeedConsigne(0,MOTEUR_GAUCHE);
//PWMSetSpeedConsigne (150,MOTEUR_DROITE);
///////

InitIO ( ) ;
LED_BLANCHE = 1 ;
LED_BLEUE = 1 ;
LED_ORANGE = 1 ;
 
InitTimer23(); 
InitTimer1();

// Boucle Principale

while ( 1 ) {
    //
} 
//
 
}// f i n main

