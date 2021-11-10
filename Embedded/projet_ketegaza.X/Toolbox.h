/* 
 * File:   Toolbox.h
 * Author: TP-EO-5
 *
 * Created on 27 octobre 2021, 11:18
 */
#define PI 3.141592653589793
#ifndef TOOLBOX_H
#define	TOOLBOX_H
float Abs(float value);
float Max(float value, float value2);
float Min(float value, float value2);
float LimitToInterval(float value, float lowLimit, float highLimit);
float RadianToDegree(float value);
float DegreeToRadian(float value);

#endif	/* TOOLBOX_H */

