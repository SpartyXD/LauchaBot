#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Pines.h>
#include <Objects.h>

//------- ARRAYS GLOBALES ----------

int v_s_min[SENSOR_COUNT+2];
int v_s_max[SENSOR_COUNT+2];
int v_s[SENSOR_COUNT+2];

volatile int s_p[SENSOR_COUNT];
bool white_line = true;
bool online;

int pos;
int l_pos;

#define LEFT_IDX SENSOR_COUNT
#define RIGHT_IDX SENSOR_COUNT+1

//------- FUNCIONES SENSORES ----------

void Sensors_init(){
  //Modo pines
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  rep(i, SENSOR_COUNT)
    pinMode(sensorCentralPins[i], INPUT);

  //Inicializar arrays
  rep(i, SENSOR_COUNT+2){
    v_s_min[i] = 4096;
    v_s_max[i] = 0;
  }
}


void readAll(){
  rep(i, SENSOR_COUNT)
    v_s[i] = analogRead(sensorCentralPins[i]);
  
  v_s[LEFT_IDX] = analogRead(LEFT_PIN);
  v_s[RIGHT_IDX] = analogRead(RIGHT_PIN);
}


void calibracion(){
  for (int j = 0; j < 100; j++) {
    delay(30);
    readAll();

    //Imprimir lecturas y actualizar arrays
    rep(i, SENSOR_COUNT+2){
      Serial.print(v_s[i]);
      Serial.print("\t");

      v_s_min[i] = min(v_s_min[i], v_s[i]);
      v_s_max[i] = max(v_s_max[i], v_s[i]);
    }
    Serial.println();
  }

  beep();
  beep();

  Serial.print("\n\nMinimos\t");
  rep(i, SENSOR_COUNT){
    Serial.print(v_s_min[i]);
    Serial.print("\t");
  }
  Serial.println();


  Serial.print("\n\nMaximos\t");
  rep(i, SENSOR_COUNT){
    Serial.print(v_s_max[i]);
    Serial.print("\t");
  }
  Serial.println();
}


void readSensors(){
  volatile int s[SENSOR_COUNT];

  rep(i, SENSOR_COUNT){
    s[i] = analogRead(sensorCentralPins[i]);
    s[i] = constrain(s[i], v_s_min[i], v_s_max[i]);

    if(white_line)
      s_p[i] = map(s[i], v_s_min[i], v_s_max[i], 100, 0);
    else
      s_p[i] = map(s[i], v_s_min[i], v_s_max[i], 0, 100);
  }

  volatile int sum = 0;
  rep(i, SENSOR_COUNT)
    sum += s_p[i];
  
  if(sum > 100)
    online = 1;
  else{
    online = 0;
    sum = 100;
  }

}


int GetPos(){
  readSensors();
  int prom = 0;

  double w = -3.5;
  rep(i, SENSOR_COUNT){
    prom += w*s_p[i];
    w += 1.0;
  }

  int sum = 0;
  rep(i, SENSOR_COUNT)
    sum += s_p[i];

  if (online)
    pos = int(100.0 * prom / sum);
  else
    l_pos = (l_pos < 0) ? -255 : 255;
  
  l_pos = pos;
  return pos;
}

#endif