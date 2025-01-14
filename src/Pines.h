#ifndef PINES_H
#define PINES_H

/*

Modulo para administrar de mejor manera los pines :D

*/

//Libraries
#include <Arduino.h>

//Macros
#define rep(i, n) for(int i=0; i<n; i++)


//=============================
//Pins

//------- Perifericos ----------
#define BUTTON_PIN_A 2
#define BUTTON_PIN_B 5
#define PINBUZZER 10

//------- Motores ----------
//Izq
# define AIN1 9
# define AIN2 8
# define PWMA 5

//Der
# define BIN1 7 
# define BIN2 4 
# define PWMB 6 

//------- Sensores IR ----------

#define SENSOR_COUNT 6
const int sensorCentralPins[SENSOR_COUNT] = {A6, A5, A4, A3, A2, A1};
const double weights[SENSOR_COUNT] = {-2.5, -1.5, -0.5, 0.5, 1.5, 2.5};

#define LEFT_PIN A7
#define RIGHT_PIN A0

//ENCODERS
const int C1_L = 4;
const int C2_L = 16;

const int C1_R = 18;
const int C2_R = 17;


//Pin manager
const int INPUT_PINS[] = {C1_L, C1_R, C2_L, C2_R};
const int OUTPUT_PINS[] = {};

const int N_INPUT = sizeof(INPUT_PINS)/sizeof(int);
const int N_OUTPUT = sizeof(OUTPUT_PINS)/sizeof(int);


//=============================
//Code

//Inicializar todos los pines de input_output que no sean objetos
void initPins(){
    rep(i, N_INPUT)
        pinMode(INPUT_PINS[i], INPUT);
    rep(i, N_OUTPUT)
        pinMode(OUTPUT_PINS[i], OUTPUT);  
}


#endif
