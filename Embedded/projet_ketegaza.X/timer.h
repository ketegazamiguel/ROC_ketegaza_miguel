    #ifndef TIMER_H
#define TIMER_H
void InitTimer23 ( void ) ;
void InitTimer1 ( void ) ;
///
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void);
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
void SetFreqTimer1(float freq); 
void my_delay(int i);
#endif 