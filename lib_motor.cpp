#include "lib_motor.h"


// -------------------------------------------------------------------------------------------------
// Esta funcion es para manejar el motor, las entradas son:

//  m1 : pin 2/10 del L293D - Salida digital que se va a manear
//  m2 : pin 7/15 del L293D - Salida digital que se va a manear
//  v  : pin 1/6  del L293D - Salida analoga que se va a manear
// dir : Dirección del motor
// vel : Valor de la velocidad (0 - 249 : Girar un sentido , 250 - 500 : Girar otro sentido)

void mover(int m1, int m2, int v, int vel) {

  if (sgn(vel) > 0) {
    digitalWrite(m1, 0);
    digitalWrite(m2, 1);
    analogWrite(v, vel);
  }

  else if (sgn(vel) <= 0)
  {
    vel = -vel;
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    analogWrite(v, vel);
  }

}


// -------------------------------------------------------------------------------------------------
// Funcion para leer puerto analogo

// puerto : Puerto analogo que se va aleer (A0,A1,A2...)
// imprimir : Si se quiere mostrar los valores en el serial plotter, poner true, si no, false.
// var : Variable donde se guarda el valor temporal de la entrada

int leer_analogo(int puerto, bool imprimir) {
  int tmp_pos;
  tmp_pos = analogRead(puerto);
  if (imprimir) {
    Serial.println(tmp_pos);
  }
  return tmp_pos;
}


// -------------------------------------------------------------------------------------------------
// Obtener y filtrar señal. Se hace un filtro de medianas

// Muestras : Numero de muestras que se usan para hacer el filtro
// puerto   : Puerto del cual se toman los datos

int filtro_promedios(int muestras, int puerto) {

  int avg_val, tmp_pos;

  // Average value
  avg_val = leer_analogo(puerto, false);

  // Make filter
  for (int i = 1 ; i < muestras  ; i++) {
    avg_val = (int) ((avg_val + leer_analogo(puerto, false)) / 2);
  }
  return avg_val;
}

// -------------------------------------------------------------------------------------------------
// Obtener el signo del numero
int sgn(int x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

// -------------------------------------------------------------------------------------------------
// Control tipo P

int control_p(int error, int margen, int P) {
  if (abs(error) < margen) {
    return 0;
  } else {
    return P * error;
  }
}

// -------------------------------------------------------------------------------------------------
// Integral del error

int int_error(int int_err, int new_e, int margen) {

  int_err = int_err + new_e;

  if (abs(new_e) < margen) {
    int_err = 0;
  }

  return int_err;
}

// -------------------------------------------------------------------------------------------------
// Controlador PI

int control_PI(int error, int int_err, int I, int margen) {

  if (abs(error) < margen) {
    return 0;
  } else {
    return 255 * sgn(error) + int_err * I ;
  }
}

// -------------------------------------------------------------------------------------------------
// Controlador PID

int control_PID(int error, int int_err, int der_err, int P, int I, int D, int margen) {

  if (abs(error) < margen) {
    return 0;
  } else {
    return  sgn(error) * P + int_err * I + der_err * D;
  }
}

// -------------------------------------------------------------------------------------------------
// Mover y contrlar dada una posicion

// Variables de control  ------------------------------------------

// Valor temporal de posicion - 0
// Posicion deseada - 1
// Velocidad temporal - 2
// Derivada del error - 3
// Valor anteriro de error - 4
// Integral del error - 5
// constante P - 6
// constante I - 7
// constante D - 8
// margen de error maximo (0 1023) - 9
// Numero de muestras a promediar - 10
// Sensor del motor - 11
// Posicion deseada dada por un potenciometro - 12

void mover_y_controlar_posicion_LC(int error, int * vars_control, int * motor) {

  // Extraer variables

  // Leer y Filtrar señal - Temp pos
  vars_control[0] = filtro_promedios(vars_control[10], vars_control[11]);

  // Calcular el error
  error = vars_control[1] - vars_control[0];

  // Integral del error
  vars_control[5] = int_error(vars_control[5], error, 50);

  // Derivada del error
  vars_control[3] = error - vars_control[4];

  // Nuevo valor temporal de error
  vars_control[4] = error;

  // Control PID para devolver velocidad del motor
  vars_control[2] = control_PID(error, vars_control[5] , vars_control[3], vars_control[6], vars_control[7], vars_control[8], vars_control[9]);

  // Mover motor
  mover(motor[0], motor[1], motor[2], vars_control[2]);

}

// -------------------------------------------------------------------------------------------------
// Mover y contrlar dada una entrada analoga

// Variables de control  ------------------------------------------

// Valor temporal de posicion - 0
// Posicion deseada - 1
// Velocidad temporal - 2
// Derivada del error - 3
// Valor anteriro de error - 4
// Integral del error - 5
// constante P - 6
// constante I - 7
// constante D - 8
// margen de error maximo (0 1023) - 9
// Numero de muestras a promediar - 10
// Sensor del motor - 11
// Posicion deseada dada por un potenciometro - 12

void mover_y_controlar_potenciometro_LC(int error, int * vars_control, int * motor) {
  // Extraer variables

  // Posicion deseada
  vars_control[1] = analogRead(vars_control[12]);

  // Leer y Filtrar señal - Temp pos
  vars_control[0] = filtro_promedios(vars_control[10], vars_control[11]);

  // Calcular el error
  error = vars_control[1] - vars_control[0];

  // Integral del error
  vars_control[5] = int_error(vars_control[5], error, 50);

  // Derivada del error
  vars_control[3] = error - vars_control[4];

  // Nuevo valor temporal de error
  vars_control[4] = error;

  // Control PID para devolver velocidad del motor
  vars_control[2] = control_PID(error, vars_control[5] , vars_control[3], 250 , 0.000001, 0.00001, 20);

  // Mover motor
  mover(motor[0], motor[1], motor[2], vars_control[2]);

}

// -------------------------------------------------------------------------------------------------
// Inicializar motor con y sin potenciometro (El potenciometro marca la posición deseada)

void inicializar_motor_pot(int * motor, int sensor, int potenciometro) {

  // Definir pins de salida
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);

  // Definir pines de entrada
  pinMode(potenciometro, INPUT);
  pinMode(sensor, INPUT);

}

void inicializar_motor(int * motor, int sensor) {

  // Definir pins de salida
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);


  // Definir pines de entrada
  pinMode(sensor, INPUT);

}
