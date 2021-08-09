//Codigo para contrlar motores

// Inicalización ------------------------------------------------

//Salida al motor
const int m1 = 2, m2 = 3, v = 4;

// Entrada del senosr
const int in = A0;

void setup(){

  // Open serial
  Serial.begin(9600); 
  
  // Definir pins de salida 
  for(int i = 2 ; i <= 4 ; i++){
     pinMode(i, INPUT);
  }
}

// Variables de control  ------------------------------------------------

// Valor temporal de posicion
int tmp_pos = 0;

// Posicion deseada
int des_pos;

// Error
int err;

// Constante de proporcionalidad
double P = 0.1;

// Velocidad del motor
double vel = 255;

// Ciclo principal ------------------------------------------------

void loop(){  

  // Leer la posición
  //tmp_pos = leer_analogo(in, true);

  // Filtrar señal
  tmp_pos = filtro_promedios(10,in);

  // Calcular el error
  err = 700 - tmp_pos;

  // Nueva velocida
  control_p(err);

  Serial.println(err);
 
}

// Funcion para mover motor --------------------------------------

void mover(int m1, int m2, int v, int dir, int vel){

  if (dir == 1){
    digitalWrite(m1,0);
    digitalWrite(m2,1);
    }
  else if(dir == -1){ 
    digitalWrite(m1,1);
    digitalWrite(m2,0);
  }
  analogWrite(v,vel);

}

// Funcion para leer puerto analogo ------------------------

int leer_analogo(int puerto, bool imprimir){
  tmp_pos = analogRead(puerto);
  if (imprimir){
    Serial.println(tmp_pos);
  }
  return tmp_pos;
}

// Obtener y filtrar señal ----------------------------------

int avg_val;

int filtro_promedios(int muestras, int puerto){
  
  // Average value
  avg_val = leer_analogo(puerto,false);

  // Make filter
  for (int i = 1 ; i < muestras  ; i++){ 
      avg_val = (int) ((avg_val + leer_analogo(puerto,false))/2);
  }
  return avg_val;
}
  


// Control P ------------------------------------------------

void control_p(int error){
    
  if (err > 0){
    mover(m1, m2, v, -1, 250);
  } else if (err < 0) {
    mover(m1, m2, v, 1, 250);
  }
  
}
