//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"

// Definir variables --------------------------------------------

// Salida al motor
const int ma[] = {2, 3, 4};
const int mb[] = {5, 6, 7};
const int mc[] = {8, 9, 10};
const int md[] = {11, 12, 13};

// Entradas
const int  sens_a = A1, pot_a = A0;
const int  sens_b = A3, pot_b = A2;
const int  sens_c = A5, pot_c = A4;   
const int  sens_d = A7, pot_d = A6;

// Senensor de proximidad
const int  sens_IR = A8;


// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines del motor
  inicializar_motor_pot(ma, sens_a, pot_a);
  inicializar_motor_pot(mb, sens_b, pot_b);
  inicializar_motor_pot(mc, sens_c, pot_c);
  inicializar_motor_pot(md, sens_d, pot_d);

  // Inicliaizar sensor IR
  pinMode(sens_IR, INPUT);
  
}

// Variables de control  ------------------------------------------

int vars_control_a[15] = {0, 0, 0, 0, 0, 0, 200, 0.0001, 0.0001, 10, 5, sens_a, pot_a,1023,0};
int vars_control_b[15] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_b, pot_b,1023,0};
int vars_control_c[15] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_c, pot_c,1023,0};
int vars_control_d[15] = {0, 0, 0, 0, 0, 0, 250, 0.0001, 0.0001, 10, 5, sens_d, pot_d,1023,0};

// Error
float err_a, err_b, err_c, err_d;

// Posicion inicial de los motores. Este vector debe ser de igual longitud que el numero de motores
int pos[4] =  {0,1000,0,1000};

// Ciclo principal ------------------------------------------------



void loop() {

  /* MOVER DE ACUERDO A UN POTENCIOMETRO
  mover_y_controlar_potenciometro_LC(err_a, vars_control_a, ma);
  mover_y_controlar_potenciometro_LC(err_b, vars_control_b, mb);
  mover_y_controlar_potenciometro_LC(err_c, vars_control_c, mc);
  mover_y_controlar_potenciometro_LC(err_d, vars_control_d, md);
  */

  //  Detectar se
  

  
  // Actualizar posiciones
  
  vars_control_a[1] = pos[0];
  vars_control_b[1] = pos[1];
  vars_control_c[1] = pos[2];
  vars_control_d[1] = pos[3];

  // Mover y contrlar motores
  
  mover_y_controlar_posicion_LC(err_a, vars_control_a, ma);
  mover_y_controlar_posicion_LC(err_b, vars_control_b, mb);
  mover_y_controlar_posicion_LC(err_c, vars_control_c, mc);
  mover_y_controlar_posicion_LC(err_d, vars_control_d, md);

}
