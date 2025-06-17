#include <SoftwareSerial.h>

// Configuración Bluetooth
SoftwareSerial bt_serial(10, 11);  // RX, TX - Pines 10 y 11

// Pin del LED integrado
const int LED_PIN = 13;

void setup() {
  // Configurar pin del LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Iniciar apagado
  
  // Iniciar comunicación serial
  Serial.begin(9600);
  bt_serial.begin(9600);
  
  Serial.println("Sistema iniciado. Enviar comandos:");
  Serial.println("R\\n - Encender LED");
  Serial.println("L\\n - Apagar LED");
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (bt_serial.available() > 0) {
    String comando = bt_serial.readStringUntil('\n');
    comando.trim();  // Eliminar espacios y saltos de línea adicionales
    
    Serial.print("Comando recibido: ");
    Serial.println(comando);

    if (comando == "R") {
      digitalWrite(LED_PIN, HIGH);  // Encender LED
      bt_serial.println("LED ENCENDIDO");
      Serial.println("LED encendido");
    }
    else if (comando == "L") {
      digitalWrite(LED_PIN, LOW);  // Apagar LED
      bt_serial.println("LED APAGADO");
      Serial.println("LED apagado");
    }
    else {
      bt_serial.println("COMANDO INVALIDO");
      Serial.println("Comando no reconocido");
    }
  }
  
  // Pequeño retardo para estabilidad
  delay(50);
}