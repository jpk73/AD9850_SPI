/*
  AD9850_SPI.cpp library for programming AD9850 DDS Module(s) via SPI
  Created by jpk, 9/2017
*/

#include "Arduino.h"
#include <math.h>
#include <SPI.h>
#include "AD9850_SPI.h"

#define MAX_DDS_MODULES 10

#if defined (__arm__) && defined (CORE_TEENSY)
#if defined (CHIPSET) // turn on and specify the pins in case your board has 4 SPI buses
 #define MOSI1 0
 #define MOSI2 44
 #define MOSI3 PIN_X
 #define SCK1 32
 #define SCK2 46
 #define SCK3 PIN_Y
 #define SECOND_SPI
 #define THIRD_SPI
 #define FOURTH_SPI
#elif defined (__MK64FX512__) || defined (__MK66FX1M0__) // teensy 3.5. and 3.6
 #define MOSI1 0
 #define MOSI2 44
 #define SCK1 32
 #define SCK2 46
 #define SECOND_SPI
 #define THIRD_SPI
#elif defined (__MKL26Z64__) // teensy LC
 #define MOSI1 0
 #define SCK1 20
 #define SECOND_SPI
#endif
#endif
 #define MOSI0 MOSI
 #define SCK0 SCK

SPISettings settings(20000000, LSBFIRST, SPI_MODE0);
size_t AD9850_SPI::instanceCount = 0;
AD9850_SPI* instances[MAX_DDS_MODULES] = {nullptr};

bool AD9850_SPI::spi0 = 0;
#if defined SECOND_SPI
bool AD9850_SPI::spi1 = 0;
#endif
#if defined THIRD_SPI
bool AD9850_SPI::spi2 = 0;
#endif
#if defined FOURTH_SPI
bool AD9850_SPI::spi3 = 0;
#endif

AD9850_SPI::AD9850_SPI(uint32_t fq_ud_pin, uint32_t reset_pin, uint32_t xtal, uint32_t spi) {
  osc = xtal;
  res = pow(2, 32); // AD9850: 32bit resolution (AD9833: 28bit resolution)
  reset_time = ceil(5000000 / osc); // minimum reset pulse width = 5 clock cycles
  res_by_osc = (double) res / osc;
  FQ_UD = fq_ud_pin;
  RESET = reset_pin;
  buf_mode = 0;
  if (spi == 0) {
    AD9850_SPI::spi0 = 1;
    spi_port = &SPI;
  }
  #if defined SECOND_SPI
  if (spi == 1) {
    AD9850_SPI::spi1 = 1;
    spi_port = &SPI1;
  }
  #endif
  #if defined THIRD_SPI
  if (spi == 2) {
    AD9850_SPI::spi2 = 1;
    spi_port = &SPI2;
  }
  #endif
  #if defined FOURTH_SPI
  if (spi == 3) {
    AD9850_SPI::spi3 = 1;
    spi_port = &SPI3;
  }
  #endif
  instances[instanceCount++] = this;
}

void AD9850_SPI::begin() {
	for (auto i : instances) {
	if (i) {
pinMode(i->FQ_UD, OUTPUT);
digitalWrite(i->FQ_UD, LOW);
pinMode(i->RESET, OUTPUT);
digitalWrite(i->RESET, LOW);
	}
	else break;
	}
	if (spi0 == 1) {
pinMode(MOSI0, OUTPUT);
digitalWrite(MOSI0, LOW);
pinMode(SCK0, OUTPUT);
digitalWrite(SCK0, LOW);
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
pinMode(MOSI1, OUTPUT);
digitalWrite(MOSI1, LOW);
pinMode(SCK1, OUTPUT);
digitalWrite(SCK1, LOW);
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
pinMode(MOSI2, OUTPUT);
digitalWrite(MOSI2, LOW);
pinMode(SCK2, OUTPUT);
digitalWrite(SCK2, LOW);
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
pinMode(MOSI3, OUTPUT);
digitalWrite(MOSI3, LOW);
pinMode(SCK3, OUTPUT);
digitalWrite(SCK3, LOW);
	}
	#endif
	for (auto i : instances) {
	if (i) {
digitalWrite(i->RESET, HIGH);
delayMicroseconds(i->reset_time);
digitalWrite(i->RESET, LOW);
	}
	else break;
	}
	if (spi0 == 1) {
pulse(SCK0);
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
pulse(SCK1);
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
pulse(SCK2);
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
pulse(SCK3);
	}
	#endif
	for (auto i : instances) {
	if (i) {
pulse(i->FQ_UD);
	}
	else break;
	}
	if (spi0 == 1) {
SPI.begin();
uint32_t ftw = 0;
SPI.beginTransaction(settings);
for (int b = 0; b < 4; b++, ftw >>= 8) {
SPI.transfer(ftw & 0xFF);
}
SPI.transfer(0x00);
SPI.endTransaction();
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
SPI1.begin();
uint32_t ftw = 0;
SPI1.beginTransaction(settings);
for (int b = 0; b < 4; b++, ftw >>= 8) {
SPI1.transfer(ftw & 0xFF);
}
SPI1.transfer(0x00);
SPI1.endTransaction();
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
SPI2.begin();
uint32_t ftw = 0;
SPI2.beginTransaction(settings);
for (int b = 0; b < 4; b++, ftw >>= 8) {
SPI2.transfer(ftw & 0xFF);
}
SPI2.transfer(0x00);
SPI2.endTransaction();
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
SPI3.begin();
uint32_t ftw = 0;
SPI3.beginTransaction(settings);
for (int b = 0; b < 4; b++, ftw >>= 8) {
SPI3.transfer(ftw & 0xFF);
}
SPI3.transfer(0x00);
SPI3.endTransaction();
	}
	#endif
	for (auto i : instances) {
	if (i) {
pulse(i->FQ_UD);
	}
	else break;
	}
	if (spi0 == 1) {
SPI.end();
pinMode(SCK0, OUTPUT);
digitalWrite(SCK0, LOW);
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
SPI1.end();
pinMode(SCK1, OUTPUT);
digitalWrite(SCK1, LOW);
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
SPI2.end();
pinMode(SCK2, OUTPUT);
digitalWrite(SCK2, LOW);
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
SPI3.end();
pinMode(SCK3, OUTPUT);
digitalWrite(SCK3, LOW);
	}
	#endif
	for (auto i : instances) {
	if (i) {
digitalWrite(i->RESET, HIGH);
delayMicroseconds(i->reset_time);
digitalWrite(i->RESET, LOW);
	}
	else break;
	}
	if (spi0 == 1) {
pulse(SCK0);
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
pulse(SCK1);
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
pulse(SCK2);
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
pulse(SCK3);
	}
	#endif
	for (auto i : instances) {
	if (i) {
pulse(i->FQ_UD);
	}
	else break;
	}
	if (spi0 == 1) {
SPI.begin();
SPI.beginTransaction(settings);
SPI.transfer(0x04);
SPI.endTransaction();
	}
	#if defined SECOND_SPI
	if (spi1 == 1) {
SPI1.begin();
SPI1.beginTransaction(settings);
SPI1.transfer(0x04);
SPI1.endTransaction();
	}
	#endif
	#if defined THIRD_SPI
	if (spi2 == 1) {
SPI2.begin();
SPI2.beginTransaction(settings);
SPI2.transfer(0x04);
SPI2.endTransaction();
	}
	#endif
	#if defined FOURTH_SPI
	if (spi3 == 1) {
SPI3.begin();
SPI3.beginTransaction(settings);
SPI3.transfer(0x04);
SPI3.endTransaction();
	}
	#endif
	for (auto i : instances) {
	if (i) {
pulse(i->FQ_UD);
	}
	else break;
	}
}

void AD9850_SPI::freq(double freq) {
  uint32_t ftw = uint32_t(freq * res_by_osc + 0.5); // ftw = frequency tuning word
  spi_port->beginTransaction(settings);
  for (int b = 0; b < 4; b++, ftw >>= 8) {
    spi_port->transfer(ftw & 0xFF);
  }
  spi_port->transfer(phase & 0xFF);
  spi_port->endTransaction();
  if (buf_mode == 0) update();
}

void AD9850_SPI::freq_phase(double f, uint32_t p) {
  phase = p << 3; // phase = 0 to 31 x 11.25°, 3 bits left shifted
  freq(f);
}

void AD9850_SPI::update() {
  pulse(FQ_UD);
}

void AD9850_SPI::sleep() {
  spi_port->beginTransaction(settings);
  spi_port->transfer(0x04);
  spi_port->endTransaction();
  if (buf_mode == 0) update();
}

double AD9850_SPI::calc_freq(double freq) {
  return (double) osc * uint32_t(freq * res_by_osc + 0.5) / res;
}

void AD9850_SPI::buffered(bool onoff) {
  buf_mode = onoff;
}

void AD9850_SPI::pulse(uint32_t pin) {
#if defined (__arm__) && defined (CORE_TEENSY) // teensy
  digitalWriteFast(pin, HIGH);
  digitalWriteFast(pin, LOW);
#elif defined (__arm__) && defined (__SAM3X8E__) // Arduino Due
  g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
#else
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
#endif
}
