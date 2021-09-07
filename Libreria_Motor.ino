//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"
#include <Arduino.h>
#include <analogWrite.h> 

// Definir variables --------------------------------------------

//Salida al motor
int ma[] = {25, 33, 32};

// Entradas
int  sens_a = 27, pot_a = 26;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines del motor
  inicializar_motor_pot(ma, sens_a, pot_a);
}

// Variables de control  ------------------------------------------

int vars_control_a[13] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_a, pot_a};


// Error
float err_a;

// Ciclo principal ------------------------------------------------

void loop() {

  // mover_y_controlar_potenciometro_LC(err_a, vars_control_a, ma);
  mover(ma[0],ma[1],ma[2],255);
  
  Serial.print(analogRead(sens_a));
  Serial.print(" ");
  Serial.println(analogRead(pot_a));

}


 
