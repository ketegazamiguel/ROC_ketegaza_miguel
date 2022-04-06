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
           
            float volts = ((float) result[1])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;  
            volts = ((float) result [2])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;   
            volts = ((float) result[4])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [0])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeDroit = 34 / volts - 5;   
            volts = ((float) result[3])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            
          
             if(robotState.distanceTelemetreGauche<30  ||  robotState.distanceTelemetreExtremeGauche<30){
            
              LED_BLANCHE=1; 
            }
            else LED_BLANCHE=0; 
                
               if(robotState.distanceTelemetreCentre <30   ){
            
            LED_BLEUE=1; 
            }
            else LED_BLEUE=0;
//            
               if(robotState.distanceTelemetreDroit <30 || robotState.distanceTelemetreExtremeDroit<30){
             LED_ORANGE=1; 
            }
            else LED_ORANGE=0;
            
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
            PWMSetSpeedConsigne(25, MOTEUR_DROITE);
            PWMSetSpeedConsigne(25, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(20, MOTEUR_DROITE);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROITE);
            PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
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
//    unsigned char positionObstacle = PAS_D_OBSTACLE;
//
//    //Détermination de la position des obstacles en fonction des télémètres
//    if (robotState.distanceTelemetreDroit < 30 &&
//            robotState.distanceTelemetreDroit <30 &&
//            robotState.distanceTelemetreCentre > 20 &&
//            robotState.distanceTelemetreGauche > 30) //Obstacle à droite
//        positionObstacle = OBSTACLE_A_DROITE;
//    else if (robotState.distanceTelemetreDroit > 30 &&
//            robotState.distanceTelemetreCentre > 20 &&
//            robotState.distanceTelemetreGauche < 30 &&
//            robotState.distanceTelemetreExtremeGauche<30
//            ) //Obstacle à gauche
//        positionObstacle = OBSTACLE_A_GAUCHE;
//    else if (robotState.distanceTelemetreCentre < 30) //Obstacle en face
//        positionObstacle = OBSTACLE_EN_FACE;
//    else if (robotState.distanceTelemetreDroit > 30 &&
//            robotState.distanceTelemetreCentre > 20 &&
//            robotState.distanceTelemetreGauche > 30 &&
//            robotState.distanceTelemetreExtremeDroit>30 &&
//            robotState.distanceTelemetreExtremeGauche>30
//     ) //pas d?obstacle
//        positionObstacle = PAS_D_OBSTACLE;
//
//    //Détermination de l?état à venir du robot
//    if (positionObstacle == PAS_D_OBSTACLE)
//        nextStateRobot = STATE_AVANCE;
//    else if (positionObstacle == OBSTACLE_A_DROITE)
//        nextStateRobot = STATE_TOURNE_GAUCHE;
//    else if (positionObstacle == OBSTACLE_A_GAUCHE)
//        nextStateRobot = STATE_TOURNE_DROITE;
//    else if (positionObstacle == OBSTACLE_EN_FACE)
//        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;

 unsigned char sensorState = 0;

    if (robotState.distanceTelemetreExtremeGauche < 30)
        sensorState |= 0b10000;
    if (robotState.distanceTelemetreGauche < 30)
        sensorState |= 0b01000;
    if (robotState.distanceTelemetreCentre < 30)
        sensorState |= 0b00100;
    if (robotState.distanceTelemetreDroit < 30)
        sensorState |= 0b00010;
    if (robotState.distanceTelemetreExtremeDroit < 30)
        sensorState |= 0b00001;

    switch (sensorState) {
        case 0b00000:
            nextStateRobot = STATE_AVANCE;
            break;
        case 0b00001:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00010:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00011:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 0b00100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b00101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b00110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b00111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b01001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b01110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b01111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b10000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b10001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10011:
            nextStateRobot =STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
            break;
        case 0b10101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b10110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b10111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 0b11000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b11001:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b11010:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 0b11011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        case 0b11111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;
        
    }
    //Si l?on n?est pas dans la transition de l?étape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

