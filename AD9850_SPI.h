/*
  AD9850_SPI.cpp library for programming AD9850 DDS Module(s) via SPI
  Created by jpk, 9/2017
*/

#ifndef AD9850_SPI_h
#define AD9850_SPI_h
#include "Arduino.h"
#include <SPI.h>

class AD9850_SPI {
  public:
    AD9850_SPI(uint32_t fq_ud_pin, uint32_t reset_pin, uint32_t xtal, uint32_t spi);
    static size_t instanceCount;
    static void begin();
    void freq(double freq);
    void freq_phase(double f, uint32_t p);
    void sleep();
    void update();
    double calc_freq(double freq);
    void buffered(bool onoff);
  private:
    uint32_t FQ_UD;
    uint32_t RESET;
    uint64_t osc;
    uint64_t res;
    double res_by_osc;
    uint32_t reset_time;
    uint32_t phase;
    bool buf_mode;
    static bool spi0;
    static bool spi1;
    static bool spi2;
    static bool spi3;
    static void pulse(uint32_t pin);
    SPIClass* spi_port;
};

#endif
