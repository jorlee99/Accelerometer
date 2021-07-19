#include <Arduino.h>
#include <SDCard.h>
#define errorSignal A5

//SPI Pins
#define SSPin 10


//NEW IO

#define RX_PIN 0 // //
#define TX_PIN 1 // //

#define TMCEnPin 4 // //
#define TMCDirPin 5 // //
#define TMCStepPin 6 // //

//Constants
#define encoderStepsToMM 0.004077730776
#define eSteps 405
#define minimumStepTime 200

#define EncoderDistanceTravelled AMT11.EncoderGetter()*float(encoderStepsToMM) //get the encoder distance travelled in MM

#define TMCDistanceSent Duet.TMCStepsToMM() //get the desired distance sent to the driver


// open pins

// 11,12,13
// A0, A1, A2
// A3, A4, A5
// 18, 19
// 3.3 5 GND
