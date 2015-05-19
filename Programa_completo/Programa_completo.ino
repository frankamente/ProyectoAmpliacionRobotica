#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"

// Variables para interrupciones
volatile int etat2 = HIGH ;
volatile int etat3 = HIGH ;

// Contadores de distancia de ruedas por encoder
int distD=0;
int distI=0;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;
unsigned long t_actualizado1 = 0;
unsigned long t_actualizado2 = 0;

// Control
boolean avance=1;
boolean colision=0;
boolean marcha=0;
int dis1,dis2,dis3,dis4,dis5;

/* Definimos cada ultrasonido*/

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.

  configInterrupciones();
  configMotores();
 
}

void loop() {
  tiempo = millis();
  
  mover_adelante();
 
   if (distD==0 && marcha)
  {
    velocidad(0);
    t_actualizado = tiempo;
    marcha=0;
  }
  if (tiempo > (t_actualizado1 + tmotoreson) && !colision)
  {
    velocidad(80);
    t_actualizado1 = tiempo;
  }
  
  if(distD>0){
    marcha=1;
  }
  // Apagamos el motor y esperamos 5 seg
 if (tiempo > (t_actualizado2 + tsensores))
  {
   leer_sensores();
    t_actualizado2 = tiempo;
  }
}


