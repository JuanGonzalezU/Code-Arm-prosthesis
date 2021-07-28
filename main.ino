//Configuración de los motores. 

//Motor 1 - Codo
const int mc1  = 2, mc2 = 3, vc =   4;

//Motor 2 - Radio
const int mr1  = 5, mr2 = 6, vr =   7;

// Motor 3 - Cubito
const int mcu1  = 8, mcu2 = 9, vcu =   10;

// Motor 4 - Mano (Meñique y anular)
const int mma1  = 11, mma2 = 12, mma3 =   13;



void setup(){

  // Open serial
  Serial.begin(9600); 
  
  // Definir pins de salida 
  for(int i = 2 ; i <= 13 ; i++){
     pinMode(i, INPUT);
  }

}

void loop(){  
  
  // Flexión del codo
  mover(mcu1,mcu2,vcu,1,255, 1000);

  // Extensión del codo
  mover(mcu1,mcu2,vcu,-1,255, 1000);



}

void mover(int m1, int m2, int v, int dir, int vel, int tiempo){

  if (dir == 1){
    digitalWrite(m1,0);
    digitalWrite(m2,1);
    }
  else if(dir == -1){ 
    digitalWrite(m1,1);
    digitalWrite(m2,0);
  }

  analogWrite(v,vel);
  delay(tiempo);

}
