# AD9850_SPI
A library to host multiple AD9850 DDS modules using SPI

This is a library which controls the widely available low-cost Direct Digital Synthesis ('DDS') modules based on the Analog Devices 9850 chip.

The module's W_CLOCK line and DATA line are connected to SCK and MISO respectively. 

Two IO lines are required for the other control lines to the AD9850 modul: RESET and FQ_UD.
