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
    beep(650, 200);
    
    switch (letter)
    {
    case 'P':
        Kp = value;
        datos.putFloat("P", value);
        break;
    case 'I':
        // bot.setPID(-1, value, -1);
        break;
    case 'D':
        Kd = value;
        datos.putFloat("D", value);
        break;
    //-----------------------
    case 'W':
        white_line = value;
        datos.putBool("W", bool(value));
        break;
    case 'B':
        base = int(value);
        datos.putInt("B", int(value));
        break;
    case 'M':
        pot_limite = int(value);
        datos.putInt("M", int(value));
        break;
    //------------------------
    default:
        break;
    }

}




#endif