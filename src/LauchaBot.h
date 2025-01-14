#ifndef LAUCHABOT_H
#define LAUCHABOT_H

#include <Arduino.h>
#include <EEPROM.h>

#include <Pines.h>
#include <Objects.h>
#include <Sensors.h>

//------- FUNCIONES ----------

//Main
void init_all();
void restart_errors();
void update_error(int &e);
void load_data();
void start_Race();
void end_race();

//Hits
void Read_hits();
void detectGeo();

void funcion_HL();
void funcion_HR();
void funcion_Cruce();


//------- PARAMETROS GLOBALES ----------

//Velocidades
#define CANT_VELOCIDADES 3
int velocidades[CANT_VELOCIDADES] = {50, 80, 100};

//PID
int base = 200;
float Kp = 1.0;
float Kd = 6.0;
float Ki = 0.0;

#define CANT_ERRORES 25
int error_sum = 0;
int errors[CANT_ERRORES];
int current_idx = 0;

int setpoint = 0;
int error = 0;
int last_error = 0;
int pot_limite = 250;

//Hits
int fin = 0;
bool ON_RACE = false;

int l_geo, ll_geo, lll_geo;
int geo = 0;

int HL, HR = 0;

//------- FUNCIONES MAIN ----------

void init_all(){
    Serial.println("Iniciando LauchaBot...\n");
    Peripherals_init();
    Sensors_init();

    Motores(0, 0);
    load_data();
}

void restart_errors(){
    error = 0;
    error_sum = 0;
    last_error = 0;
    current_idx = 0;

    rep(i, CANT_ERRORES)
        errors[i] = 0;
}


void update_error(int &e){
    error_sum -= errors[current_idx];
    errors[current_idx] = e;
    error_sum += e;
    current_idx = (current_idx+1)%CANT_ERRORES;
}


void load_data(){
    // p=0, i=1, d=2, base=3, limite=4, white=5
    // EEPROM.get(0, Kp);
    // EEPROM.get(2, Kd);
    // EEPROM.get(1, Ki);
    // EEPROM.get(3, base);
    // EEPROM.get(4, pot_limite);
    // EEPROM.get(5, white_line);

    //Imprimir
    Serial.println("Datos:\n");
    Serial.println("KP: " + String(Kp));
    Serial.println("KD: " + String(Kd));
    Serial.println("KI: " + String(Ki));
    Serial.println("Base: " + String(base));
    Serial.println("Pot limite: " + String(pot_limite));
    Serial.println("White line: " + String(white_line));
    Serial.println("=====================\n");
}


void start_Race(){
    ON_RACE = true;
    fin = 0;
    restart_errors();

    beep(2000, 100);
    beep(2300, 200);
}


void end_race(){
    //Parar todo
    Motores(0, 0);
    ON_RACE = false;
    fin = 0;

    //Musiquita de final
    chillBeep();
}

//------- FUNCIONES HITS ----------

void Read_hits(){
    HL = analogRead(LEFT_PIN);
    HR = analogRead(RIGHT_PIN);

    int umbral_L = (v_s_min[LEFT_IDX] + v_s_max[LEFT_IDX]) * 0.6;
    int umbral_R = (v_s_min[RIGHT_IDX] + v_s_max[RIGHT_IDX]) * 0.6;

    Serial.println(String(HL) + " " + String(HR));


    HL = (HL > umbral_L) ? 0 : 1;
    HR = (HR > umbral_R) ? 0: 1;

    if(!white_line){
        HL = !HL;
        HR = !HR;
    }

    Serial.println(String(HL) + " " + String(HR) + "\n");
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

    //Llamar a funcion correspondiente
    if (geo == 0 && l_geo == 1 && ll_geo == 0)
        funcion_HL();
    else if(geo == 0 && l_geo == 2 && ll_geo == 0)
        funcion_HR();
    else if(geo == 0 && ((l_geo == 3) || (ll_geo == 3) || (lll_geo == 3)))
        funcion_Cruce();
    
    //Actualizar valores de geo
    lll_geo = ll_geo;
    ll_geo = l_geo;
    l_geo = geo;
}


void funcion_Cruce(){
    // beep(2500, 50);
}


void funcion_HL(){
    // beep(2000, 50);
}


void funcion_HR() {
  beep(1800, 50);
  fin++;

  Serial.println("Hit " + String(fin));

  if(fin >= 2)
    end_race();
}


#endif