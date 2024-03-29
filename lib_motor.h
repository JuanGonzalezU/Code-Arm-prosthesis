#ifndef LIB_MOTOR_H
#define LIB_MOTOR_H

#include <Arduino.h>

// -------------------------------------------------------------------------------------------------
// Esta funcion es para manejar el motor, las entradas son:

//  m1 : pin 2/10 del L293D - Salida digital que se va a manear
//  m2 : pin 7/15 del L293D - Salida digital que se va a manear
//  v  : pin 1/6  del L293D - Salida analoga que se va a manear
// dir : Dirección del motor
// vel : Valor de la velocidad

void mover(int m1, int m2, int v, int vel);

// -------------------------------------------------------------------------------------------------
// Funcion para leer puerto analogo

// puerto : Puerto analogo que se va aleer (A0,A1,A2...)
// imprimir : Si se quiere mostrar los valores en el serial plotter, poner true, si no, false.
// var : Variable donde se guarda el valor temporal de la entrada

int leer_analogo(int puerto, bool imprimir);

// -------------------------------------------------------------------------------------------------
// Obtener y filtrar señal. Se hace un filtro de medianas

int filtro_promedios(int muestras, int puerto);

// -------------------------------------------------------------------------------------------------
// Obtener signo de un numero

int sgn(int x);

// -------------------------------------------------------------------------------------------------
// Control tipo P

int control_p(int error, int margen, int P);

// -------------------------------------------------------------------------------------------------
// Integral del error

int int_error(int int_err, int new_e, int margen);

// -------------------------------------------------------------------------------------------------
// Controlador PI

int control_PI(int error, int int_err, int I, int margen);

// -------------------------------------------------------------------------------------------------
// Controlador PID

int control_PID(int error, int int_err, int der_err,int P, int I, int D, int margen);

void mover_y_controlar_posicion_LC(int error, int * vars_control, int * motor);

void mover_y_controlar_potenciometro_LC(int error, int * vars_control, int * motor);

void inicializar_motor_pot(int * motor, int sensor, int potenciometro) ;

void inicializar_motor(int * motor, int sensor);

bool limites(int des_pos, int max_pos, int min_pos);

#endif
