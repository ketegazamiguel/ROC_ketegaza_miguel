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
#include "ADC.h" 

int main(void) {

    // Initialisationde l?oscillateur
    InitOscillator();
    InitIO();

    // Configuration des éntrées sorties

    // moteur 
    InitPWM();
    //PWMSetSpeedConsigne(0,MOTEUR_GAUCHE);
    //PWMSetSpeedConsigne (150,MOTEUR_DROITE);
    ///////

    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    InitTimer23();
    InitTimer1();

    // Boucle Principale
    InitADC1();

    while (1) {
        //
        if (ADCIsConversionFinished() == 1) {

           /* ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            unsigned int ADCValue0 = result[0];
            unsigned int ADCValue1 = result[1];
            unsigned int ADCValue2 = result[2];

            if (ADCValue0 >= 300) LED_ORANGE = 1;
            else LED_ORANGE = 0;

            if (ADCValue1 >= 300) LED_BLEUE = 1;
            else LED_BLEUE = 0;
            if (ADCValue2 >= 300) LED_BLANCHE = 1;
            else LED_BLANCHE = 0;*/

                        ADCClearConversionFinishedFlag();
                        unsigned int * result = ADCGetResult();
                        float volts = ((float) result[2])*3.3/4096*3.2;
                        robotState.distanceTelemetreDroit=34/volts-5;
                        volts = ((float) result [1])*3.3/4096*3.2;
                        robotState.distanceTelemetreCentre = 34/volts-5;
                        volts = ((float) result[0])*3.3/4096*3.2;
                        robotState.distanceTelemetreGauche = 34/volts-5;



        }
    }
    //

}// f i n main

