/* 
 * File:   PWM.h
 * Author: TP-EO-5
 *
 * Created on 10 novembre 2021, 08:47
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR_GAUCHE 0
#define MOTEUR_DROITE 1

#ifdef	__cplusplus
extern "C" {
#endif


void InitPWM(void);
void PWMSetSpeed(float vitesseEnPourcents,unsigned char nbMotor);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

