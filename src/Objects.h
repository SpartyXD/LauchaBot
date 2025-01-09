#ifndef OBJECTS_H
#define OBJECTS_H

#include <Arduino.h>
#include <Pines.h>

//------- Motores ----------

void MotorIz(int val) {
  val = constrain(val, -255.0, 255.0);

  if (val >=0.0){
      analogWrite(AIN1, val);
      analogWrite(AIN2, 0.0);
  }
  else{
      //Atras
      analogWrite(AIN1, 0.0);
      analogWrite(AIN2, -val);
  }
}


void MotorDe(int val) {
  val = constrain(val, -255.0, 255.0);

  if (val >=0.0){
      analogWrite(BIN1, val);
      analogWrite(BIN2, 0.0);
  }
  else{
      //Atras
      analogWrite(BIN1, 0.0);
      analogWrite(BIN2, -val);
  }
}


void Motores(int left, int right) {
  MotorIz(left);
  MotorDe(right);
}


//------- Perifericos ----------

// Función para emitir un sonido
void beep(unsigned int frec=2000, unsigned int dur=100){
  // tone(PINBUZZER, frec, dur); // Emite un tono de 2000 Hz durante 100 ms
  // delay(200);
}

void Peripherals_init() {
  // Configuración de pines
  pinMode(BUTTON_PIN_A, INPUT); // El pin del botón se configura como entrada
  pinMode(BUTTON_PIN_B, INPUT);
  pinMode(PINBUZZER, OUTPUT); // El pin del buzzer se configura como salida

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}


void startupBeep(){
    int C5 = 523;  
    int E5 = 659;  
    int G5 = 784;  
    int A5 = 880; 
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

#endif