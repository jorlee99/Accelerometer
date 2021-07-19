#include <SPI.h>
#ifndef SDCARD_SPI
    #define SDCARD_SPI SD_SPI
#endif
#include <SD.h>
#define chipSelect SS_PIN
class SDCard{
    public:
        File dataLogFile;
        void WriteDataToSD(float,float,float);

        void SDCardInitialization ();

};