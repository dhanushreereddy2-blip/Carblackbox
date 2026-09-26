#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_ADDRESS_WRITE   0XA0
#define EEPROM_ADDRESS_READ    0XA1

void write_EEPROM(unsigned char address, unsigned char data);
unsigned char read_EEPROM(unsigned char address);

#endif