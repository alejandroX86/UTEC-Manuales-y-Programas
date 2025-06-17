// Programa Simple de Prueba de Motores
// Para carritos robóticos con driver L298N
//  Para estudiantes principiantes de la UTEC

// Pines de control del motor DERECHO
const int DER_IN1 = 2;   // Dirección 1
const int DER_IN2 = 4;   // Dirección 2
const int DER_EN = 3;    // Control de velocidad (PWM)

// Pines de control del motor IZQUIERDO
const int IZQ_IN1 = 6;   // Dirección 1
const int IZQ_IN2 = 7;   // Dirección 2
const int IZQ_EN = 5;    // Control de velocidad (PWM)

// LED indicador
const int LED_PIN = 13;

// Velocidad de los motores (0-255)
const int VELOCIDAD = 150;  // Velocidad media

void setup() {
  // Configurar todos los pines como salidas
  pinMode(DER_IN1, OUTPUT);
  pinMode(DER_IN2, OUTPUT);
  pinMode(DER_EN, OUTPUT);
  pinMode(IZQ_IN1, OUTPUT);
  pinMode(IZQ_IN2, OUTPUT);
  pinMode(IZQ_EN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Iniciar comunicación serial
  Serial.begin(9600);
  Serial.println("PRUEBA DE MOTORES INICIADA");
  Serial.println("-------------------------");
  
  // Encender LED para indicar inicio
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

// Función para mover un motor individual
void moverMotor(int in1, int in2, int en, int direccion) {
  /*
   * direccion:
   *   1 = Adelante
   *  -1 = Atrás
   *   0 = Detenido
   */
   
  if (direccion == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(en, VELOCIDAD);
  } 
  else if (direccion == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(en, VELOCIDAD);
  } 
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
  }
}

// Función para detener ambos motores
void detenerMotores() {
  moverMotor(DER_IN1, DER_IN2, DER_EN, 0);
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, 0);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  Serial.println("\nProbando motor DERECHO hacia adelante...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, 1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("Probando motor DERECHO hacia atras...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, -1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("Probando motor IZQUIERDO hacia adelante...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, 1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("Probando motor IZQUIERDO hacia atras...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, -1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("AVANZANDO (ambos motores adelante)...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, 1);
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, 1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("RETROCEDIENDO (ambos motores atras)...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, -1);
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, -1);
  delay(2000);
  detenerMotores();
  delay(500);
  
  Serial.println("GIRO DERECHA...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, -1);  // Derecha atrás
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, 1);   // Izquierda adelante
  delay(1000);
  detenerMotores();
  delay(500);
  
  Serial.println("GIRO IZQUIERDA...");
  digitalWrite(LED_PIN, HIGH);
  moverMotor(DER_IN1, DER_IN2, DER_EN, 1);   // Derecha adelante
  moverMotor(IZQ_IN1, IZQ_IN2, IZQ_EN, -1);  // Izquierda atrás
  delay(1000);
  detenerMotores();
  delay(1000);
}