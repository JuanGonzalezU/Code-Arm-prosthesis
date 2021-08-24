//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"



// Definir variables --------------------------------------------

//Salida al motor
const int m1 = 2, m2 = 3, v = 4;

// Entrada del sensor del motor - Entradad del sensor infrarojo
const int in = A0, sensor = A1;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Definir pins de salida
  for (int i = 2 ; i <= 4 ; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(sensor, INPUT);
  pinMode(in, INPUT);
}

// Variables de control  ------------------------------------------

// Valor temporal de posicion - Posicion deseada - Error - Derivada del error
int tmp_pos, des_pos, tmp_vel, der_err , prev_err = 0, int_err;


// Constante de proporcionalidad - Velocidad del motor
double P = 0.1 , vel = 255;

float err;

// Ciclo principal ------------------------------------------------

void loop() {

  // Des pos
  des_pos = analogRead(sensor);

  // Leer y Filtrar señal
  tmp_pos = filtro_promedios(1, in);

  // Calcular el error
  err = des_pos - tmp_pos;

  // Integral del error

  int_err = int_error(int_err, err, 1);

  // Derivada del error
  der_err = err - prev_err ;

  prev_err = err;

  // Nueva velocida
  tmp_vel = control_PID(err, int_err, der_err, 150, 0.000001, 0.00001, 20);

  // Mover motor
  mover(m1, m2, v, tmp_vel);

  Serial.print(tmp_pos);
  Serial.print(" ");
  Serial.println(des_pos);

}
