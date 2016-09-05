/* 
 * File:   control.h
 * Author: Jonathan
 *
 * Created on 7 de octubre de 2015, 05:48 PM
 */

#ifndef CONTROL_H
#define	CONTROL_H

float ControlP(float Reference, float Gainproportional,float ProcessScale, float variablesens,int periodo);//Funtion for control P
float ControlPi(float Reference, float Gainproportional,float GainIntegral,float ProcessScale, float variablesens,int periodo);//Function for controlPI
float ChangeRef(int character);//Change reference funtion.
#endif	/* CONTROL_H */
