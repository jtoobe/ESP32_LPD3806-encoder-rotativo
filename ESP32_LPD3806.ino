// Se deberan conectar resistencias de 10k entre el cable verde (A) a 5v
// y el cable blanco (B) a 5v

// Pines del encoder
const int pinA = 33;
const int pinB = 32;

volatile long contador = 0;

void IRAM_ATTR encoderISR() {
  bool estadoA = digitalRead(pinA);
  bool estadoB = digitalRead(pinB);

  // Dirección: A antes que B = horario, B antes que A = antihorario
  if (estadoA == estadoB) {
    contador++;  // Horario
  } else {
    contador--;  // Antihorario
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
Serial.print(" Demo: ");
  // Interrupción en flanco de subida de A
  attachInterrupt(digitalPinToInterrupt(pinA), encoderISR, RISING);
}

void loop() {
  static long ultimoContador = 0;

  if (contador != ultimoContador) {
    Serial.print("Pulsos: ");
    Serial.print(contador);
    Serial.print(" | Vueltas: ");
    Serial.println((float)contador / 600.0);  // 600 PPR se debera ajustar para el modelo de encoder
    ultimoContador = contador;
  }

  delay(50);  // Evita saturar el puerto serie
}
