#include <main.h>

void SDCard::SDCardInitialization (){               //constructor to initialize sd Card
            if (!SD.begin(SDCARD_SS_PIN)) {
            SerialUSB.println("initialization failed!");
            return;
            }
            SerialUSB.println("initialization done.");
        }
void SDCard::WriteDataToSD(float XAcc, float Yacc, float Zacc){
    dataLogFile = SD.open("DATA.txt", FILE_WRITE);
    
    if (dataLogFile){
        dataLogFile.print("X Acceleration difference ");
        dataLogFile.println(XAcc,6);
        dataLogFile.print("Y Acceleration difference ");
        dataLogFile.println(Yacc,6);
        dataLogFile.print("Z Acceleration difference");
        dataLogFile.println(Zacc,6);
        
        dataLogFile.println(" ");

        dataLogFile.close();
    }
    else {
    // if the file didn't open, print an error:
    SerialUSB.println("error opening data log file");
    }
}
