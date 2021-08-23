//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"

// Definir variables --------------------------------------------

//Salida al motor
const int ma1 = 2, ma2 = 3, va = 4, mb1 = 5, mb2 = 6, vb = 7;

// Entradas
const int  pot_a = A0, sens_a = A1, pot_b = A2, sens_b = A3;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Definir pins de salida
  for (int i = 2 ; i <= 7 ; i++) {
    pinMode(i, OUTPUT);
  }

  // Definir pines de entrada
  pinMode(pot_a, INPUT);
  pinMode(sens_a, INPUT);

  pinMode(pot_b, INPUT);
  pinMode(sens_b, INPUT);
}

// Variables de control  ------------------------------------------

// Valor temporal de posicion
// Posicion deseada 
// Velocidad temporal
// Derivada del error
// Valor anteriro de error
// Integral del error

int tmpPos_a, desPos_a, tmpVel_a, derErr_a, prevErr_a = 0, intErr_a;
int tmpPos_b, desPos_b, tmpVel_b, derErr_b, prevErr_b = 0, intErr_b;

// Error 
float err_a, err_b;

// Ciclo principal ------------------------------------------------

void loop() {

  // Des pos
  desPos_a = analogRead(sens_a);
  desPos_b = analogRead(sens_b);

  // Leer y Filtrar señal
  tmpPos_a = filtro_promedios(1, pot_a);
  tmpPos_b = filtro_promedios(1, pot_b);

  // Calcular el error
  err_a = desPos_a - tmpPos_a;
  err_b = desPos_b - tmpPos_b;

  // Integral del error

  intErr_a = int_error(intErr_a, err_a, 50);
  intErr_b = int_error(intErr_b, err_b, 50);

  // Derivada del error
  derErr_a = err_a - prevErr_a;
  derErr_b = err_b - prevErr_b;

  prevErr_a = err_a;
  prevErr_b = err_b;

  tmpVel_a = control_PI(err_a, intErr_a, 0.001);
  tmpVel_b = control_PI(err_b, intErr_b, 0.001);

  // Mover motor
  mover(ma1, ma2, va, tmpVel_a);
  mover(mb1, mb2, vb, tmpVel_b);
}
