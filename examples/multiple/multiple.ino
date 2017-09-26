#include <SPI.h>
#include <AD9850_SPI.h>

#define FQ_UD1 16                          // any pin
#define RESET1 15                          // any pin
#define CRYSTAL1 125000003                 // actual osc freq
#define SPI_BUS1 0                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

#define FQ_UD2 19                          // any pin
#define RESET2 18                          // any pin
#define CRYSTAL2 125000005                 // actual osc freq
#define SPI_BUS2 0                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

#define FQ_UD3 50                          // any pin
#define RESET3 49                          // any pin
#define CRYSTAL3 125000000                 // actual osc freq
#define SPI_BUS3 1                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

#define FQ_UD4 52                          // any pin
#define RESET4 51                          // any pin
#define CRYSTAL4 125000000                 // actual osc freq
#define SPI_BUS4 1                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

#define FQ_UD5 54                          // any pin
#define RESET5 53                          // any pin
#define CRYSTAL5 125000000                 // actual osc freq
#define SPI_BUS5 2                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

#define FQ_UD6 56                          // any pin
#define RESET6 55                          // any pin
#define CRYSTAL6 125000000                 // actual osc freq
#define SPI_BUS6 2                         // 0 = SPI, 1 = SPI1, 2 = SPI2 (lib is prepared for future 4xSPI boards, see .cpp file)

/*
   W_CLOCK <=> SCK                         // pin 13 on teensy LC/3.0/3.1/3.2/3.5/3.6 for SPI0
   DATA <=> MOSI                           // pin 11 on teensy LC/3.0/3.1/3.2/3.5/3.6 for SPI0
   MOSI1 = 0                               // on teensy LC, 3.5 and 3.6 for SPI1
   SCK1  = 20                              // on teensy LC for SPI1
   SCK1  = 32                              // on teensy 3.5 and 3.6 for SPI1
   MOSI2 = 44                              // on teensy 3.5 and 3.6 for SPI2
   SCK2  = 46                              // on teensy 3.5 and 3.6 for SPI2
*/

AD9850_SPI dds1(FQ_UD1, RESET1, CRYSTAL1, SPI_BUS1);
AD9850_SPI dds2(FQ_UD2, RESET2, CRYSTAL2, SPI_BUS2);
AD9850_SPI dds3(FQ_UD3, RESET3, CRYSTAL3, SPI_BUS3);
AD9850_SPI dds4(FQ_UD4, RESET4, CRYSTAL4, SPI_BUS4);
AD9850_SPI dds5(FQ_UD5, RESET5, CRYSTAL5, SPI_BUS5);
AD9850_SPI dds6(FQ_UD6, RESET6, CRYSTAL6, SPI_BUS6);
// edit line #define MAX_DDS_MODULES in the .cpp file if more than 10 DDS modules are needed

void setup() {
  AD9850_SPI::begin();                     // init all DDS modules

  dds1.freq(220.0);                        // set frequency
  dds2.freq(330.0);                        // set frequency
  dds3.freq(440.0);                        // set frequency
  dds4.freq(550.0);                        // set frequency
  dds5.freq(660.0);                        // set frequency
  dds6.freq(880.0);                        // set frequency

  delay(500);

  dds1.sleep();                            // stop DDS
  dds2.sleep();                            // stop DDS
  dds3.sleep();                            // stop DDS
  dds4.sleep();                            // stop DDS
  dds5.sleep();                            // stop DDS
  dds6.sleep();                            // stop DDS
}

void loop() {
}
