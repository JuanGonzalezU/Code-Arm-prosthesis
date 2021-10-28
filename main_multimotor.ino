//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"

// Definir variables --------------------------------------------

//Salida al motor
int ma[] = {26, 25, 33};

// Entradas
int  sens_a = 12, pot_a = 14, fin_c1 = 32, fin_c2 = 35;



// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(fin_c1, INPUT);
  pinMode(fin_c2, INPUT);
  // Inicializar pines del motor
  inicializar_motor(ma, sens_a);

}

// Variables de control  ------------------------------------------

int vars_control_a[13] = {0, 0, 0, 0, 0, 0, 200, 0.0001, 0.0001, 10, 5, sens_a, pot_a};


// Error
float err_a, err_b, err_c, err_d;

// Ciclo principal ------------------------------------------------

void loop() {

  digitalWrite(13, HIGH);

  if (digitalRead(fin_c1) == 1 || digitalRead(fin_c2) == 1 ) {
    mover(ma[0], ma[1], ma[2], 0);
  } else {
    mover(ma[0], ma[1], ma[2], 255);
  } 


}
