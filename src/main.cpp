#include <Arduino.h>
#include <LauchaBot.h>
#include <BluetoothApp.h>

void WaitBoton();
void Read_hits();
void detectGeo();

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
  detectGeo();

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


void Read_hits(){
    HL = analogRead(LEFT_PIN);
    HR = analogRead(RIGHT_PIN);

    HL = (HL > umbral_l) ? 0 : 1;
    HR = (HR > umbral_r) ? 0: 1;

    if(!white_line){
        HL = !HL;
        HR = !HR;
    }
}


void detectGeo() {
    Read_hits();

    //Detectar geo actual
    if(HL == HR)
        geo = (HL == 0) ? 0 : 3; // 0 0 | 1 1
    else
        geo = (HL == 1) ? 1 : 2; // 1 0 | 0 1

    //Ver si algo ha cambiado xd
    if(l_geo == geo)
        return;

    if(geo == 0 && l_geo == 2 && ll_geo == 0){
      fin++;

      if(fin >= 2)
        end_race();
    }

    // //Llamar a funcion correspondiente
    // if (geo == 0 && l_geo == 1 && ll_geo == 0)
    //     funcion_HL();
    // else if(geo == 0 && l_geo == 2 && ll_geo == 0)
    //     funcion_HR();
    // else if(geo == 0 && ((l_geo == 3) || (ll_geo == 3) || (lll_geo == 3)))
    //     funcion_Cruce();
    
    //Actualizar valores de geo
    lll_geo = ll_geo;
    ll_geo = l_geo;
    l_geo = geo;
}