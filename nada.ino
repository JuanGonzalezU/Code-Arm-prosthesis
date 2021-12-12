void setup() {

  // Open serial
  Serial.begin(9600);

  // Inicializar pines del motor
  inicializar_motor_pot(ma, sens_a, pot_a);
  inicializar_motor_pot(mb, sens_b, pot_b);
  inicializar_motor_pot(mc, sens_c, pot_c);
  inicializar_motor_pot(md, sens_d, pot_d);
}
