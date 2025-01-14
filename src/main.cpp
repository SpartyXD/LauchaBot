#include <Arduino.h>
#include <LauchaBot.h>
#include <BluetoothApp.h>

void WaitBoton();

void setup() {
  initApp();
  init_all();
  delay(500);

  startupBeep();
  delay(500);
  calibrateBeep();
  
  WaitBoton();
  calibracion();
}


void loop(){
  if(digitalRead(BUTTON_PIN_A))
    end_race();

  int p = GetPos();

  if(!ON_RACE){
    WaitBoton();
    ON_RACE = true;
    return;
  }

  //Obtener error
  int error = p - setpoint;
  int d = error - last_error;
  update_error(error);
  last_error = error;

  //Obtener PID
  int pot_giro = int(Kp * error) + int(Kd * (d)) + int(Ki * (error_sum));
  pot_giro = constrain(pot_giro, -pot_limite, pot_limite);
  
  Motores(base + pot_giro, base - pot_giro);
  last_error = error;
}


// Función para esperar el botón
void WaitBoton(){
  Serial.println("\nEsperando boton\n");
  delay(1000);

  while(!digitalRead(BUTTON_PIN_A))
    updateData();
  
  beep();
}