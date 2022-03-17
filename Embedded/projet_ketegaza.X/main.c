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
#include "main.h"

int main(void) {

    // Initialisationde l?oscillateur
    InitOscillator();
    InitIO();

    // Configuration des éntrées sorties

    // moteur 
    InitPWM();
    //PWMSetSpeedConsigne(50,MOTEUR_GAUCHE);
   // PWMSetSpeedConsigne (150,MOTEUR_DROITE);
    ///////

    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    InitTimer23();
    InitTimer1();
    InitTimer4();
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
           
            float volts = ((float) result[0])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;  
            volts = ((float) result [1])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;   
            volts = ((float) result[2])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [4])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeDroit = 34 / volts - 5;   
            volts = ((float) result[3])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            
          
            if(robotState.distanceTelemetreGauche <30 ){
            
              LED_BLANCHE=1; 
            }
            else LED_BLANCHE=0; 
                
               if(robotState.distanceTelemetreCentre <30 ){
            
            LED_BLEUE=1; 
            }
            else LED_BLEUE=0;
//            
               if(robotState.distanceTelemetreDroit <30 ){
             LED_ORANGE=1; 
            }
            else LED_ORANGE=0;
            if(robotState.distanceTelemetreExtremeDroit <30 ){
             LED_BLANCHE=1; 
            }
            else LED_BLANCHE=0;
            if(robotState.distanceTelemetreExtremeGauche <30 ){
             LED_ORANGE=1; 
            }
            else LED_ORANGE=0;
//           
//                
//                
       }
    }
}
//
unsigned char stateRobot;

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROITE);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;

        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;

        case STATE_AVANCE:
            PWMSetSpeedConsigne(30, MOTEUR_DROITE);
            PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(30, MOTEUR_DROITE);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROITE);
            PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(15, MOTEUR_DROITE);
            PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-15, MOTEUR_DROITE);
            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}

unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;

    //Détermination de la position des obstacles en fonction des télémètres
    if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //Obstacle à droite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 30) //Obstacle à gauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreCentre < 20) //Obstacle en face
        positionObstacle = OBSTACLE_EN_FACE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //pas d?obstacle
        positionObstacle = PAS_D_OBSTACLE;

    //Détermination de l?état à venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;

    //Si l?on n?est pas dans la transition de l?étape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

