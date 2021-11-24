/* 
 * File:   adc.h
 * Author: TP-EO-5
 *
 * Created on 17 novembre 2021, 10:57
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
void InitADC1(void);
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void);
void ADC1StartConversionSequence();
void ADCClearConversionFinishedFlag(void);
unsigned int * ADCGetResult(void);
unsigned char ADCIsConversionFinished(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

