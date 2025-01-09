#ifndef LAUCHABOT_H
#define LAUCHABOT_H

#include <Arduino.h>
#include <Preferences.h>

#include <Pines.h>
#include <Objects.h>
#include <Sensors.h>

//------- FUNCIONES ----------

//Main
void init_all();
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

Preferences datos;

//Velocidades
#define CANT_VELOCIDADES 3
int velocidades[CANT_VELOCIDADES] = {50, 80, 100};

//PID
int base = 50;
float Kp = 1.0;
float Kd = 6.0;

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
    Serial.begin(115200);
    datos.begin("LauchaBot", false);

    Serial.println("Iniciando LauchaBot...\n");
    Peripherals_init();
    Sensors_init();

    Motores(0, 0);
    load_data();
}


void load_data(){
    Kp = datos.getFloat("P", 0.0);
    Kd = datos.getFloat("D", 0.0);
    base = datos.getInt("B", 0);
    pot_limite = datos.getInt("M", 250);
    white_line = datos.getBool("W", true);
}


void start_Race(){
    ON_RACE = true;
    fin = 0;
    error = 0;
    last_error = 0;

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

    int umbral_L = (v_s_min[LEFT_IDX] + v_s_max[LEFT_IDX])/2;
    int umbral_R = (v_s_min[RIGHT_IDX] + v_s_max[RIGHT_IDX])/2;

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
    beep(2500, 50);
}


void funcion_HL(){
    beep(2000, 50);
}


void funcion_HR() {
  beep(1800, 50);
  fin++;

  Serial.println("Hit " + String(fin));

  if(fin >= 2)
    end_race();
}


#endif