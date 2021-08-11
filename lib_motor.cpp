#include "lib_motor.h"


// -------------------------------------------------------------------------------------------------
// Esta funcion es para manejar el motor, las entradas son:

//  m1 : pin 2/10 del L293D - Salida digital que se va a manear
//  m2 : pin 7/15 del L293D - Salida digital que se va a manear
//  v  : pin 1/6  del L293D - Salida analoga que se va a manear
// dir : Dirección del motor
// vel : Valor de la velocidad (0 - 249 : Girar un sentido , 250 - 500 : Girar otro sentido)

void mover(int m1, int m2, int v, int vel) {

  if (vel >= 0 and vel <= 255) {

    if (vel > 250) {
      vel = 250;
    }
    digitalWrite(m1, 0);
    digitalWrite(m2, 1);
    analogWrite(v, vel);
  }
  else if (vel >= -255 and vel < 0)
  {
    vel = -vel;

    if (vel > 250) {
      vel = 250;
    }
    
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

int control_p(int error) {
  if (abs(error) < 15) {
    return 0;
  } else {
    return 250 * sgn(error);
  }
}
