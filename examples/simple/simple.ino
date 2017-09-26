#include <SPI.h>
#include <AD9850_SPI.h>

#define FQ_UD 16                           // any pin
#define RESET 15                           // any pin
#define CRYSTAL 125000000                  // actual osc freq
#define SPI_BUS 0                          // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

/*
   W_CLOCK <=> SCK                         // pin 13 on teensy LC/3.0/3.1/3.2/3.5/3.6 for SPI0
   DATA <=> MOSI                           // pin 11 on teensy LC/3.0/3.1/3.2/3.5/3.6 for SPI0
*/

AD9850_SPI dds(FQ_UD, RESET, CRYSTAL, SPI_BUS);
// edit line #define MAX_DDS_MODULES in the .cpp file if more than 10 DDS modules are needed

void setup() {
  Serial.begin(115200);
  AD9850_SPI::begin();                     // init all DDS modules

// instant commands:
  dds.freq(440.0);                         // set frequency
  delay(500);
  dds.sleep();                             // stop DDS

// buffered commands:
  dds.buffered(1);                         // switch buffered command mode ON
  dds.freq_phase(330.0, 15);               // set frequency and phase = 0 to 31 x 11.25° (15 is good for square wave output)
  dds.update();                            // start buffered command
  delay(250);
  dds.sleep();                             // stop DDS
  delay(250);
  dds.update();                            // start buffered command
  dds.buffered(0);                         // switch buffered command mode OFF

  double freq = dds.calc_freq(9.73);       // calculate exact output frequency
  Serial.println(freq, 5);
}

void loop() {
}
