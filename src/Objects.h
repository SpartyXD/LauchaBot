#ifndef OBJECTS_H
#define OBJECTS_H

#include <Arduino.h>
#include <Pines.h>

//------- Motores ----------

void MotorIz(int val) {
  val = constrain(val, -255.0, 255.0);

  if (val >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    //atras
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    val *= -1;
  }

  // Setea Velocidad
  analogWrite(PWMA, val);
}


void MotorDe(int val) {
  val = constrain(val, -255.0, 255.0);

  if (val >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    //atras
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    val *= -1;
  }

  // Setea Velocidad
  analogWrite(PWMB, val);
}


void Motores(int left, int right){
  MotorIz(left);
  MotorDe(right);
}


//------- Perifericos ----------

// Función para emitir un sonido
void beep(unsigned int frec=2000, unsigned int dur=100){
  tone(PINBUZZER, frec, dur); // Emite un tono de 2000 Hz durante 100 ms
  delay(200);
}

void Peripherals_init() {
  // Configuración de pines
  pinMode(BUTTON_PIN_A, INPUT); // El pin del botón se configura como entrada
  pinMode(BUTTON_PIN_B, INPUT);
  pinMode(PINBUZZER, OUTPUT); // El pin del buzzer se configura como salida

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}


void startupBeep(){
    int C5 = 523;  
    int E5 = 659;  
    int G5 = 784;  
    int shortDuration = 200;
    int longDuration = 400; 

    beep(C5, shortDuration);
    beep(E5, shortDuration);
    beep(G5, longDuration);
}


void chillBeep(){
    beep(700, 100);
    delay(50);
    beep(1000, 100);
    delay(50);
    beep(1300, 100);
    delay(150);
    beep(1000, 150);
}


void calibrateBeep(){
    beep(700, 100);
    delay(50);
    beep(1000, 100);
    delay(50);
    beep(1300, 100);
    delay(150);
    beep(1000, 150);
}

#endif