#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"

// Variables para interrupciones
volatile int etat2 = HIGH ;
volatile int etat3 = HIGH ;

// Contadores de distancia de ruedas por encoder
int distD=0;
int distI=0;
int intI =0,intD=0;
int estado=1;
int errorposicionI=0,errorposicionD=0, errorvelocidadI=0,errorvelocidadD=0;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;
unsigned long t_actualizado1 = 0;
unsigned long t_actualizado2 = 0;


// Control
boolean avance=1;
boolean colision=0;
boolean marcha=0;
int girar=0; // 1 Si izquierda 2 si derecha
int dis1,dis2,dis3,dis4,dis5;
int dif_tiempo=0,tiempo_a=50;
int vueltasqueremosI=0,vueltasqueremosD=0,pa_atras=0,pa_alante=0,vueltashayI=0,vueltashayD=0;

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
  Serial.print("IZQUIERDA: ");
  Serial.println(distI);
  Serial.print("DERECHA: ");
  Serial.println(distD);
  
  switch(estado){
    case 0:
    delay(100);
    vueltasqueremosD=3;
    vueltasqueremosI=3;
    control(vueltasqueremosD, vueltasqueremosI);
  break;
    case 1:
    delay(100);
    
    vueltasqueremosI=24;
    vueltasqueremosD=0;
    girar=1;//Izquierda
    control(vueltasqueremosI, vueltasqueremosD);
   break;
   
   case 2:
    delay(100);
    
    vueltasqueremosI=22;
    vueltasqueremosD=3;
    girar=2;//Izquierda
    control(vueltasqueremosI, vueltasqueremosD);
   break;
   }
}


