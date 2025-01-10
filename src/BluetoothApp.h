#ifndef BLUETOOTH_APP
#define BLUETOOTH_APP

#include <LauchaBot.h>

//------- VARIABLES ----------
void initApp();
void updateData();
void handleCommand(String &command);

//------- FUNCIONES ----------

void initApp(){
    Serial.begin(9600);
}

//Ver si hay datos nuevos por bluetooth
void updateData(){
    while(Serial.available()){
        String command = Serial.readStringUntil('\n');
        handleCommand(command);
    }
}


//Majear el comando recibido por bluetooth
void handleCommand(String &command){
    // p=0, i=1, d=2, base=3, limite=4, white=5
    char letter = command[0];

    //STOP
    if(letter == 'X'){
        end_race();
        Serial.println("STOP!\n");
        return;
    }

    double value = command.substring(1).toDouble();
    beep(350, 200);
    
    switch (letter)
    {
    case 'P':
        Kp = value;
        EEPROM.put(0, Kp);
        Serial.println("Kp ---> " + String(Kp) + "\n");
        break;
    case 'I':
        Ki = value;
        EEPROM.put(1, Ki);
        Serial.println("I ---> " + String(Ki) + "\n");
        break;
    case 'D':
        Kd = value;
        EEPROM.put(2, Kd);
        Serial.println("D ---> " + String(Kd) + "\n");
        break;
    //-----------------------
    case 'W':
        white_line = bool(value);
        EEPROM.put(5, white_line);
        Serial.println("White line ---> " + String(white_line) + "\n");
        break;
    case 'B':
        base = int(value);
        EEPROM.put(3, base);
        Serial.println("Base ---> " + String(base) + "\n");
        break;
    case 'M':
        pot_limite = int(value);
        EEPROM.put(4, pot_limite);
        Serial.println("Pot limite ---> " + String(pot_limite) + "\n");
        break;
    //------------------------
    default:
        break;
    }

}




#endif