/* 
 * File:   main.c
 * Author: TP-EO-5
 *
 * Created on 20 octobre 2021, 10:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChiConfig.h"
#include "IO.h"

int main (void){

// Initialisationde l?oscillateur
InitOscillator ( ) ;

// Configuration des �ntr�es sorties

InitIO ( ) ;
LED_BLANCHE = 1 ;
LED_BLEUE = 1 ;
LED_ORANGE = 1 ;

// Boucle Principale

while ( 1 ) {
} 
}// f i n main
