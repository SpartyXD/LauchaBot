#include <Arduino.h>
#include <LauchaBot.h>
#include <BluetoothApp.h>

void WaitBoton();

void setup() {
  init_all();
  initApp();
  delay(500);

  startupBeep();
  WaitBoton();
  calibracion();
}


void loop(){
  int p = GetPos();
  detectGeo();

  if(!ON_RACE){
    WaitBoton();
    ON_RACE = true;
    return;
  }

  //Obtener error
  int error = pos - setpoint;
  int d = error - last_error;
  last_error = error;

  //Obtener PID
  int pot_giro = int(Kp * error) + int(Kd * (d));
  pot_giro = constrain(pot_giro, -pot_limite, pot_limite);

  Motores(base + pot_giro, base - pot_giro);
  last_error = error;
}


// Función para esperar el botón
void WaitBoton(){
  Serial.println("\nEsperando boton\n");
  delay(1000);

  while(digitalRead(BUTTON_PIN_A))
    updateData();
  
  beep();
}