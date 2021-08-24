//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"

// Definir variables --------------------------------------------

//Salida al motor
const int ma[] = {2, 3, 4};

// Entradas
const int  sens_a = A0, pot_a = A1;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines del motor
  inicializar_motor(ma, sens_a, pot_a);
}

// Variables de control  ------------------------------------------

int vars_control_a[13] = {0, 0, 0, 0, 0, 0, 200, 0.0001, 0.0001, 10, 5, sens_a, pot_a};


// Error
float err_a;

// Ciclo principal ------------------------------------------------

void loop() {

  mover_y_controlar_potenciometro_LC(err_a, vars_control_a, ma);

}
