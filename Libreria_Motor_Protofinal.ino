//Codigo para controlar motores teniendo en cuenta la libreria creada

#include "lib_motor.h"
#include <Arduino.h>
#include <analogWrite.h>

// Definir variables --------------------------------------------

// Definir motores
int m_radio[] = {1, 2, 3};
int m_cubito[] = {4, 5, 6};
int m_mano1[] = {7, 8, 9};
int m_mano2[] = {10, 11, 12};
int m_codo[]  = {13, 14, 15};

// Sensores de entrada
int sens_radio = 16;
int sens_cubito = 17;
int sens_mano1 = 18;
int sens_mano2 = 19;
int sens_codo = 20;

// Inicalización ------------------------------------------------

void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines que van al driver del motor
  inicializar_motor(m_radio, sens_radio);
  inicializar_motor(m_cubito, sens_cubito);
  inicializar_motor(m_mano1, sens_mano1);
  inicializar_motor(m_mano2, sens_mano2);
  inicializar_motor(m_codo, sens_codo);

}

// Variables de control  ------------------------------------------

int vc_radio[12] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_radio};
int vc_cubito[12] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_cubito};
int vc_mano1[12] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_mano1};
int vc_mano2[12] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_mano2};
int vc_codo[12] = {0, 0, 0, 0, 0, 0, 255, 0.0001, 0.0001, 10, 5, sens_codo};

// Error
float err_radio, err_cubito, err_mano1, err_mano2, err_codo;

// Vector de posiciones de todo el brazo
int posiciones[5] = {500, 500, 500, 500, 500};

// Ciclo principal ------------------------------------------------

void loop() {

  // Definir las posiciones en los vectores de control
  vc_radio[1] = posiciones[0];
  vc_cubito[1] = posiciones[1];
  vc_mano1[1] = posiciones[2];
  vc_mano2[1] = posiciones[3];
  vc_codo[1] = posiciones[4];

  // Mover motores
  mover_y_controlar_posicion_LC(err_radio, vc_radio, m_radio);
  mover_y_controlar_posicion_LC(err_cubito, vc_cubito, m_cubito);
  mover_y_controlar_posicion_LC(err_mano1, vc_mano1, m_mano1);
  mover_y_controlar_posicion_LC(err_mano2, vc_mano2, m_mano2);
  mover_y_controlar_posicion_LC(err_codo, vc_codo, m_codo);
  


}
