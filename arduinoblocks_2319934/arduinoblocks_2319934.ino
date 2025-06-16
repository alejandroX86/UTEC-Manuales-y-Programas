#include <SoftwareSerial.h>

uint8_t VELOCIDAD = 150;  // Velocidad media (59% de potencia)
String s_ordenes;
SoftwareSerial bt_serial(10, 11);  // RX, TX - Cambiado a pines estándar

// Pines de control para el motor 1
const int M1_IN1 = 2;
const int M1_IN2 = 4;
const int M1_EN = 3;

// Pines de control para el motor 2
const int M2_IN1 = 6;
const int M2_IN2 = 7;
const int M2_EN = 5;

// Pin del LED indicador (integrado en Arduino)
const int LED_PIN = 13;

void adelante_m1() {
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);
  analogWrite(M1_EN, VELOCIDAD);
}

void adelante_m2() {
  digitalWrite(M2_IN1, HIGH);
  digitalWrite(M2_IN2, LOW);
  analogWrite(M2_EN, VELOCIDAD);
}

void atras_m1() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, HIGH);
  analogWrite(M1_EN, VELOCIDAD);
}

void atras_m2() {
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, HIGH);
  analogWrite(M2_EN, VELOCIDAD);
}

void parar_m1() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  analogWrite(M1_EN, 0);
}

void parar_m2() {
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
  analogWrite(M2_EN, 0);
}

void ADELANTE() {
  adelante_m1();
  adelante_m2();
  digitalWrite(LED_PIN, HIGH);  // LED encendido durante movimiento
  Serial.println("ADELANTE");
}

void ATRAS() {
  atras_m1();
  atras_m2();
  digitalWrite(LED_PIN, HIGH);  // LED encendido durante movimiento
  Serial.println("ATRAS");
}

void derecha() {
  adelante_m1();
  atras_m2();
  digitalWrite(LED_PIN, HIGH);  // LED encendido durante movimiento
  Serial.println("DERECHA");
}

void izquierda() {
  adelante_m2();
  atras_m1();
  digitalWrite(LED_PIN, HIGH);  // LED encendido durante movimiento
  Serial.println("IZQUIERDA");
}

void PARAR() {
  parar_m1();
  parar_m2();
  digitalWrite(LED_PIN, LOW);  // LED apagado al detenerse
  Serial.println("PARAR");
}

void setup() {
  // Configurar pines de control de motores
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M1_EN, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M2_EN, OUTPUT);
  
  // Configurar pin del LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Iniciar con LED apagado
  
  // Iniciar comunicación serial
  Serial.begin(9600);
  bt_serial.begin(9600);
  
  // Asegurar que los motores están detenidos al inicio
  PARAR();
  
  // Establecer velocidad inicial
  VELOCIDAD = 150;
  
  Serial.println("Sistema iniciado. Motores detenidos.");
  bt_serial.println("Sistema iniciado. Enviar comandos:");
  bt_serial.println("F - Adelante");
  bt_serial.println("B - Atras");
  bt_serial.println("R - Derecha");
  bt_serial.println("L - Izquierda");
  bt_serial.println("S - Parar");
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (bt_serial.available() > 0) {
    s_ordenes = bt_serial.readStringUntil('\n');
    s_ordenes.trim();  // Eliminar espacios y saltos de línea
    
    Serial.print("Comando recibido: ");
    Serial.println(s_ordenes);
    
    if (s_ordenes == "F") {
      ADELANTE();
      bt_serial.println("MOTOR: ADELANTE | LED: ON");
    }
    else if (s_ordenes == "B") {
      ATRAS();
      bt_serial.println("MOTOR: ATRAS | LED: ON");
    }
    else if (s_ordenes == "R") {
      derecha();
      bt_serial.println("MOTOR: DERECHA | LED: ON");
    }
    else if (s_ordenes == "L") {
      izquierda();
      bt_serial.println("MOTOR: IZQUIERDA | LED: ON");
    }
    else if (s_ordenes == "S") {
      PARAR();
      bt_serial.println("MOTOR: PARADO | LED: OFF");
    }
    else {
      bt_serial.println("COMANDO INVALIDO");
    }
  }
  
  // Pequeño retardo para evitar sobrecarga
  delay(10);
}