//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"



// Definir variables --------------------------------------------

//Salida al motor
const int m1 = 2, m2 = 3, v = 4;

// Entrada del sensor
const int in = A0;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Definir pins de salida
  for (int i = 2 ; i <= 4 ; i++) {
    pinMode(i, INPUT);
  }
}

// Variables de control  ------------------------------------------

// Valor temporal de posicion - Posicion deseada - Error
int tmp_pos, des_pos = 50, err, tmp_vel; 


// Constante de proporcionalidad - Velocidad del motor
double P = 0.1 , vel = 255;

// Ciclo principal ------------------------------------------------

void loop() {

  // Leer y Filtrar señal
  tmp_pos = filtro_promedios(10, in);

  // Calcular el error
  err = des_pos - tmp_pos;

  // Nueva velocida
  tmp_vel = control_p1(err);

  // Mover motor
  mover(m1, m2, v, tmp_vel);
  
  Serial.print(tmp_pos);
  Serial.print(" ");
  Serial.println(des_pos);


}

// Control P -----------------------------------------------------

void control_p(int error) {

  if (err > 0) {
    mover(m1, m2, v, 250);
  } else if (err < 0) {
    mover(m1, m2, v, -250);
  }

}

int control_p1(int error) {

  if (abs(error) < 15) {
    return 0;
  } else {
    return 250 * sgn(error);
  }
}
