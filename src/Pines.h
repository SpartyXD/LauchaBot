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
#define BUTTON_PIN_A 0
#define BUTTON_PIN_B 5
#define PINBUZZER 15

//------- Motores ----------
//Izq
# define AIN1 23    
# define AIN2 19   

//Der
# define BIN1 2 
# define BIN2 12    

//------- Sensores IR ----------

#define SENSOR_COUNT 8
const int sensorCentralPins[SENSOR_COUNT] = {27, 26, 25, 33, 32, 34, 35, 39};

#define LEFT_PIN 14
#define RIGHT_PIN 36

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
