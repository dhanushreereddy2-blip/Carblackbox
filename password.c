
#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#define _XTAL_FREQ 20000000

char password[9];

void set_password()
{
    for(int i=0; i<8; i++)
    {
        password[i]=1;
    }
}

int check(char*arr)
{
    for(int i=0; i<8; i++)
    {
        if(arr[i]!=password[i])
            return 0;
    }
    return 1;
}

int enter_password()
{
    clcd_write(1, INSTRUCTION_COMMAND);
    unsigned char key;
    char arr[9];
    int count=0,try=0,delay=0;

    while (1)
    {
        clcd_print("ENTER PASSWORD", LINE1(0)); 
        key=read_mkp(EDGE);
        
        if(delay++<500)
        clcd_putch('_', LINE2(count)); 
        else if(delay<1000)
        clcd_putch(' ', LINE2(count));
        else delay=0;
        
        if(key==MK_SW4 || key==MK_SW6) return 0;
        
        if(key != ALL_RELEASED)
        {
            arr[count] = key;
            clcd_putch('*', LINE2(count)); 
            count++;
        }
        
        if(count==8)
        {
                
            if(check(arr)==0)
            {
                try++;
                count=0;
                if(try==5)
                {
                    while(1)
                    {
                        clcd_print("PASSWORD WRONG", LINE1(0));
                        clcd_print("GO TO DASH", LINE2(0));
                        __delay_ms(2000);
                        clcd_write(1, INSTRUCTION_COMMAND);
                        return 0;
                    }
                }
                clcd_write(1, INSTRUCTION_COMMAND);   //clear the display 
                for(int i=0; i<2000; i++)
                {
                    clcd_print("PASSWORD WRONG", LINE1(0));
                    clcd_putch((5-try)+48, LINE2(0)); 
                    clcd_print("TRIES ARE LEFT", LINE2(2));
                }
                clcd_write(1, INSTRUCTION_COMMAND);  //clear the display 
                continue;
            }
            else
            {
                while(1)
                {
                    clcd_print("PASSWORD ENTERED", LINE1(0));
                    clcd_print("SUCCESSFULLY", LINE2(0));
                    __delay_ms(800);
                    clcd_write(1, INSTRUCTION_COMMAND);
                    return 1;
                }
            }
        }
        
    }
}

void change_password()
{
    unsigned char key;
    int count=0,delay=0;
    clcd_write(1, INSTRUCTION_COMMAND);
    while(1)
    {
        clcd_print("ENTER NEW PASSWORD", LINE1(0)); 
        key=read_mkp(EDGE);
      
        if(delay++<500)
        clcd_putch('_', LINE2(count)); 
        else if(delay<1000)
        clcd_putch(' ', LINE2(count));
        else delay=0;
      
        if(key != ALL_RELEASED)
        {
            password[count] = key;
            clcd_putch('*', LINE2(count)); 
            count++;
        }
        
        if(count>=8)
        {
            clcd_write(1, INSTRUCTION_COMMAND);
            for(int i=0; i<3000; i++)
            {
                clcd_print("PASSWORD CHANGED", LINE1(0));
            }
            return;
        }
    }
}
