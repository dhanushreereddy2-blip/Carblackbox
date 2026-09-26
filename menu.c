#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "main.h"
#include "eeprom.h"
#include "uart.h"
#include "ds1307.h"

extern  uint8_t write_count;
extern unsigned char time[9];
uint8_t count=10;

void menu()
{
    unsigned char key;
    int count=0; 
    while(1)
    {
        key=read_mkp(EDGE);
        
        if(key==MK_SW1)   //Scroll up
        {
           clcd_write(1, INSTRUCTION_COMMAND);
           count--;
           if(count<0) count=0;
        }
        else if(key==MK_SW2)   //Scroll down
        {
            clcd_write(1, INSTRUCTION_COMMAND);
            count++;
            if(count>7) count=7;
        }
        else if(key==MK_SW5)   //Enter button
        {
            clcd_write(1, INSTRUCTION_COMMAND);
            if(count==0 )
            {
                view_log();
            }
            else if(count==1 || count==2)
            {
                clear_log();
            }
            else if(count==3 || count==4)
            {
                download_log();
            }
            else if(count==5 || count==6)
            {
                set_time();
            }
            if(count==7)
            {
                change_password();
                return;
            }
            clcd_write(1, INSTRUCTION_COMMAND);
        }
        else if(key==MK_SW6) return;
        
        //Menu option
        if(count==0 || count==1)
        {
            clcd_print("VIEW LOG", LINE1(4)); 
            clcd_print("CLEAR LOG", LINE2(4)); 
        }
        else if(count==2 || count==3)
        {
            
            clcd_print("CLEAR LOG", LINE1(4)); 
            clcd_print("DOWNLOAD LOG", LINE2(4)); 
        }
        else if(count==4 || count==5)
        {
            
            clcd_print("DOWNLOAD LOG", LINE1(4)); 
            clcd_print("SET TIME", LINE2(4)); 
        }
        else if(count==6 || count==7)
        {
            
            clcd_print("SET TIME", LINE1(4)); 
            clcd_print("CHANGE PASS", LINE2(4)); 
        }
        
        if(count%2)
        {
            clcd_print("->", LINE2(1)); 
        }
        else
        {
            clcd_print("->", LINE1(1)); 
        }
        
       
    }
}

void view_log()
{
    if(write_count==0)
    {
        for(int i=0; i<3000; i++)
        {
          clcd_print("LOG IS EMPTY", LINE1(0));
        }
        return;
    }
    unsigned char read=0X00;
    unsigned char key,time[9],gear,speed;
    int i=1;
    
    time[2]=':';
    time[5]=':';
    time[8]=0;
    
    time[0]=read_EEPROM(read);
    read++;
    time[1]=read_EEPROM(read);
    read++;
    time[3]=read_EEPROM(read);
    read++;
    time[4]=read_EEPROM(read);
    read++;
    time[6]=read_EEPROM(read);
    read++;
    time[7]=read_EEPROM(read);
    read++;
          
    //Read Gear
    gear=read_EEPROM(read);
    read++;
          
    //Read Speed
    speed=read_EEPROM(read);
    read++;
    
    while(1)
    {
        key=read_mkp(EDGE);
        
        clcd_print("I", LINE1(0));
        clcd_print("TIME", LINE1(2));
        clcd_print("GR", LINE1(11));
        clcd_print("SP", LINE1(14));
        
        if(key==MK_SW6) return;
        
        if(key==MK_SW1)       //Scroll up
        {
          i--;
          if(i<=1)
          {
             i=1;
             read=0X00;
          }
          else
           read=read-16;
          //Reading time from the EEPROM
          time[0]=read_EEPROM(read);
          read++;
          time[1]=read_EEPROM(read);
          read++;
          time[3]=read_EEPROM(read);
          read++;
          time[4]=read_EEPROM(read);
          read++;
          time[6]=read_EEPROM(read);
          read++;
          time[7]=read_EEPROM(read);
          read++;
          
          //Read Gear
          gear=read_EEPROM(read);
          read++;
          
          //Read Speed
          speed=read_EEPROM(read);
          read++;
        }
        else if(key==MK_SW2)       //Scroll down
        {
          i++;
          if(i>write_count)
          {
              i=write_count;
              continue;
          }
          time[0]=read_EEPROM(read);
          read++;
          time[1]=read_EEPROM(read);
          read++;
          time[3]=read_EEPROM(read);
          read++;
          time[4]=read_EEPROM(read);
          read++;
          time[6]=read_EEPROM(read);
          read++;
          time[7]=read_EEPROM(read);
          read++;
          
          //Read Gear
          gear=read_EEPROM(read);
          read++;
          
          //Read Speed
          speed=read_EEPROM(read);
          read++;
        }
        
        clcd_putch(i+'0',LINE2(0));
        clcd_print(time, LINE2(2));
        clcd_putch(gear, LINE2(11));
        clcd_putch(speed/10%10+48, LINE2(14));
        clcd_putch(speed%10+48, LINE2(15));
    }
}

void clear_log()
{
    write_count=0;
    for(int i=0; i<3000; i++)
    {
        clcd_print("LOG IS CLEARED", LINE1(0));
    }
}

void download_log()
{
    char data[30],read=0;
    data[2]=':';
    data[5]=':';
    data[6]=' ';
    data[7]=' ';
    data[8]=' ';
    data[9]=' ';
    data[10]=' ';
    data[11]=' ';
    data[12]=' '; data[13]=' '; data[14]=' '; data[15]=' ';
    data[16]=' '; data[17]=' '; data[18]=' '; data[19]=' '; data[20]=' ';
    
    
    if(write_count==0)
    {
        puts("LOG IS EMPTY\n\r");
        return;
    }
    
    puts("TIME        GEAR    SPEED\n\r");
    for(int i=0; i<write_count; i++)
    {
        //Read from the EEPROM
        data[0]=read_EEPROM(read);
        read++;
        data[1]=read_EEPROM(read);
        read++;
        data[3]=read_EEPROM(read);
        read++;
        data[4]=read_EEPROM(read);
        read++;
        data[6]=read_EEPROM(read);
        read++;
        data[7]=read_EEPROM(read);
        read++;
          
        //Read Gear
        data[13]=read_EEPROM(read);
        read++;
          
        //Read Speed
        data[28]=read_EEPROM(read);
        data[21]=data[28]/10%10;
        data[22]=data[28]%10;
        read++;
        data[23]='\0';
        
        puts(data);   //PRINTING IN THE TERA TERM
        puts("\n\r");
    }
}

void set_time()
{
    int delay=0,flag=0;
    count=0;
    unsigned char key,data=0;
    clcd_print("EDIT HOUR",LINE1(0));
    while(1)
    {
        key=read_mkp(EDGE);
        
        if(delay++<500)
         clcd_print(time, LINE2(0));
        else if(delay<1500)
        clcd_print("  ", LINE2(flag));
        else delay=0;
        
        
        if(key==MK_SW1)   //Increment time
        {
            if(count==0)   //Increment hour
            {
                
                time[1]++;
                if(time[0]=='2' && time[1]=='4')
                {
                    time[0]='0';
                    time[1]='0';
                }
                if(time[1]>'9')
                {
                    time[0]++;
                    time[1]='0';
                }
            }
            else if(count==1)  //Increment minute
            {
               
                time[4]++;
                if(time[3]=='5' && time[4]>'9')
                {
                    time[3]='0';
                    time[4]='0';
                }
                if(time[4]>'9')
                {
                    time[3]++;
                    time[4]='0';
                }
            }
            else if(count==2)   //Increment seconds
            {
                time[7]++;
                if(time[6]=='5' && time[7]>'9')
                {
                    time[6]='0';
                    time[7]='0';
                }
                if(time[7]>'9')
                {
                    time[6]++;
                    time[7]='0';
                }
            }
        }
        else if(key==MK_SW2)     //Decrement time
        {
            if(count==0)       //Decrement hour
            {  
                if(time[0]=='0' && time[1]=='0')
                {
                 time[1]--;
                 time[0]--;
                }
                else  time[1]--;
             
                if((signed)time[0]<'0' && (signed)time[1]<'0')
                {
                    time[0]='2';
                    time[1]='3';
                }
                if((signed)time[1]<'0')
                {
                    time[0]--;
                    time[1]='9';
                }
            }
            else if(count==1)   //Decrement minute
            {
                if(time[3]=='0' && time[4]=='0')
                {
                 time[4]--;
                 time[3]--;
                }
                else  time[4]--;
                if((signed)time[3]<'0' && (signed)time[4]<'0')
                {
                    time[3]='5';
                    time[4]='9';
                }
                if((signed)time[4]<'0')
                {
                    time[3]--;
                    time[4]='9';
                }
            }
            else if(count==2)     //Decrement seconds
            {
                if(time[6]=='0' && time[7]=='0')
                {
                 time[7]--;
                 time[6]--;
                }
                else  time[7]--;
                    
                if((signed)time[6]<'0' && (signed)time[7]<'0')
                {
                    time[6]='5';
                    time[7]='9';
                }
                if((signed)time[7]<'0')
                {
                    time[6]--;
                    time[7]='9';
                }
            }
        }
        else if(key==MK_SW3)           //Toggling edit option
        {
            clcd_write(1, INSTRUCTION_COMMAND);
            if(++count>2) count=0;
            
            if(count==0)
            {
                flag=0;
                clcd_print("EDIT HOUR",LINE1(0));
            }
            else if(count==1)
            {
                flag=3;
                clcd_print("EDIT MINUTE",LINE1(0));
            }
            else if(count==2)   
            {
                flag=6;
                clcd_print("EDIT SECONDS",LINE1(0));
            }
        }
        else if(key==MK_SW5)       //Save the time
        {
            count=10;
            clcd_write(1, INSTRUCTION_COMMAND);
            //Write hours in RTC
            data|=(time[0]-'0')<<4;
            data|=(time[1]-'0');
            write_ds1307(HOUR_ADDR, data);
            
            //Write MINUTES in RTC
            data=(time[3]-'0')<<4;
            data|=(time[4]-'0');
            write_ds1307(MIN_ADDR, data);
            
            //Write SECONDS in RTC
            data=(time[6]-'0')<<4;
            data|=(time[7]-'0');
            write_ds1307(SEC_ADDR, data);
            
            for(int i=0; i<3000; i++)
            {
              clcd_print("TIME CHANGED", LINE1(0));
            }
            return;
        }
        else if(key==MK_SW6) return;
    }
}