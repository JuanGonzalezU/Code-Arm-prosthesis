//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"

// Definir variables --------------------------------------------

//Salida al motor
const int ma[] = {2, 3, 4};
const int mb[] = {5, 6, 7};
const int mc[] = {8, 9, 10};
const int md[] = {11, 12, 13};

// Entradas
const int  sens_a = A1, pot_a = A0;
const int  sens_b = A3, pot_b = A2;
const int  sens_c = A5, pot_c = A4;
const int  sens_d = A7, pot_d = A6;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines del motor
  inicializar_motor(ma, sens_a, pot_a);
  inicializar_motor(mb, sens_b, pot_b);
  inicializar_motor(mc, sens_c, pot_c);
  inicializar_motor(md, sens_d, pot_d);
}

// Variables de control  ------------------------------------------

int vars_control_a[13] = {0, 0, 0, 0, 0, 0, 200, 0.0001, 0.0001, 10, 5, sens_a, pot_a};
int vars_control_b[13] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_b, pot_b};
int vars_control_c[13] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_c, pot_c};
int vars_control_d[13] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_d, pot_d};

// Error
float err_a, err_b, err_c, err_d;

// Ciclo principal ------------------------------------------------

void loop() {

  // MOVER DE ACUERDO A UN POTENCIOMETRO
  mover_y_controlar_potenciometro_LC(err_a, vars_control_a, ma);
  mover_y_controlar_potenciometro_LC(err_b, vars_control_b, mb);
  mover_y_controlar_potenciometro_LC(err_c, vars_control_c, mc);
  mover_y_controlar_potenciometro_LC(err_d, vars_control_d, md);
  

  /*
  vars_control_a[1] = 750;
  vars_control_b[1] = 750;
  vars_control_c[1] = 750;
  vars_control_d[1] = 750;
  
  mover_y_controlar_posicion_LC(err_a, vars_control_a, ma);
  mover_y_controlar_posicion_LC(err_b, vars_control_b, mb);
  mover_y_controlar_posicion_LC(err_c, vars_control_c, mc);
  mover_y_controlar_posicion_LC(err_d, vars_control_d, md);
  */
}
