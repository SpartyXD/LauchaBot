#ifndef BLUETOOTH_APP
#define BLUETOOTH_APP

#include <LauchaBot.h>
#include <BluetoothSerial.h>

//------- VARIABLES ----------

BluetoothSerial server;
#define NOMBRE_BOT "LAUCHABOT"


void initApp();
void updateData();
void handleCommand(String &command);

//------- FUNCIONES ----------

void initApp(){
    server.begin(NOMBRE_BOT);
}

//Ver si hay datos nuevos por bluetooth
void updateData(){
    while(server.available()){
        String command = server.readStringUntil('\n');
        handleCommand(command);
    }
}


//Majear el comando recibido por bluetooth
void handleCommand(String &command){
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
        datos.putFloat("P", value);
        Serial.println("Kp ---> " + String(Kp) + "\n");
        break;
    case 'I':
        Ki = value;
        datos.putFloat("I", value);
        Serial.println("I ---> " + String(Ki) + "\n");
        break;
    case 'D':
        Kd = value;
        datos.putFloat("D", value);
        Serial.println("D ---> " + String(Kd) + "\n");
        break;
    //-----------------------
    case 'W':
        white_line = bool(value);
        datos.putBool("W", white_line);
        Serial.println("White line ---> " + String(white_line) + "\n");
        break;
    case 'B':
        base = int(value);
        datos.putInt("B", base);
        Serial.println("Base ---> " + String(base) + "\n");
        break;
    case 'M':
        pot_limite = int(value);
        datos.putInt("M", pot_limite);
        Serial.println("Pot limite ---> " + String(pot_limite) + "\n");
        break;
    //------------------------
    default:
        break;
    }

}




#endif