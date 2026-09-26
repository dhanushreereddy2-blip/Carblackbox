#define _XTAL_FREQ 20000000 
#include "adc.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "sensor.h"
#include "eeprom.h"
#include "main.h"

extern unsigned char time[9];

uint8_t write_count;
static uint8_t gear_pos;
uint8_t speed;
char gear[9]={'N','1','2','3','4','5','6','R','C'};
static uint8_t col=1;

void get_speed()
{
    // Implement the speed function
    uint16_t temp=read_adc(CHANNEL4);   //Digital value of ADC will 0 to 1023

    temp =(((unsigned long)temp * 99)/1023);  //Now it is converted between the ranges 0 to 99 speed
    
    speed=temp;
    
    if(col==0) speed=0;
    clcd_print("SPD", LINE1(9));
    clcd_putch((speed/10%10)+48, LINE2(9)); 
    clcd_putch((speed%10)+48, LINE2(10)); 
}

void get_gear_pos()
{
    static uint8_t bck=20,bck2=30,bck3=0;
   
    // Implement the gear function
   unsigned char key = read_mkp(EDGE);
   if(key==MK_SW1)   //Gear up
   {
       
       if(gear_pos!=bck && col)
          upload_eeprom();
       bck=gear_pos;
       gear_pos++;
       if(gear_pos>7) gear_pos=7;
   }
   else if(key==MK_SW2)   //Gear down
   {
       if(gear_pos!=bck2 && col)
          upload_eeprom();
      bck2=gear_pos;
      gear_pos--;
      if(gear_pos<=0) gear_pos=0;
   }
   else if(key==MK_SW3)    //Collision
   {
       gear_pos=8;
       if(gear_pos!=bck3 && col)
         upload_eeprom();
       bck3=gear_pos;
       col=0;
   }
   else if(key==MK_SW4)    //Menu
   {
        clcd_write(1, INSTRUCTION_COMMAND);
        key=enter_password();
        if(key)
        menu();
        clcd_write(1, INSTRUCTION_COMMAND);
    }
   if(col==0) gear_pos=0;
       
   clcd_print("GR", LINE1(14));
   clcd_putch(gear[gear_pos], LINE2(14));
}

void upload_eeprom()
{
    static uint8_t count=0;
    static unsigned char write=0X00;
    if(count==11)
    {
        write_count=10;
        write=0X00;
        count=0;
    }
    //Writing time in EEPROM
    write_EEPROM(write,time[0]);
    write++;
    write_EEPROM(write,time[1]);
    write++;
    write_EEPROM(write,time[3]);
    write++;
    write_EEPROM(write,time[4]);
    write++;
    write_EEPROM(write,time[6]);
    write++;
    write_EEPROM(write,time[7]);
    write++;
    
    //Writing GEAR POSITION
    write_EEPROM(write,gear[gear_pos]);
    write++;
    
    //Writing Speed
    write_EEPROM(write,(char)speed);
    write++;
    
    write_count++;
    count++;
}