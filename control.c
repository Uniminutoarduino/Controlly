
#include "control.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float errorb=0;

float ControlActionb=0;

float erroranteriorb=0;

float Accionanteriorb=0;

int CharCount=0; //Variable for character count for change Reference

char Reference[20];//Reference




float ControlP(float Reference, float Gainproportional,float ProcessScale, float variablesens,int periodo){
  //Esta funcion permite generar un control proporcional, retornando la accion de control sobre la placa.
      errorb=Reference*ProcessScale-variablesens;
      ControlActionb=errorb*Gainproportional;
      ControlActionb=ControlActionb*periodo;
      return ControlActionb;

}
float ControlPi(float Reference, float Gainproportional,float GainIntegral,float ProcessScale, float variablesens,int periodo){
  //Esta funcion permite generar un control proporcional-integral, retornando la accion de control sobre la placa.
      errorb=Reference*ProcessScale-variablesens;
      ControlActionb=GainIntegral*errorb-Gainproportional*erroranteriorb+Accionanteriorb;
      erroranteriorb=errorb;
      Accionanteriorb=ControlActionb;
      ControlActionb=ControlActionb*periodo;
      return ControlActionb;
}

float ChangeRef(int character){//Funcion for change reference
    float Referenciaf=0;
    if(character!='\n'){//Si caracter diferente de n almacenar al valor en el vector reference.
     Reference[CharCount]=character; //Asign character to reference
     CharCount++;
    }else{
      Referenciaf=atof(Reference);
      CharCount=0;
      memset(Reference,0x00,20);//Clear vector
      return Referenciaf;

    }

}
