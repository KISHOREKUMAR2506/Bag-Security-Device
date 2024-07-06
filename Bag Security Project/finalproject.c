#include<reg51.h>
//#include<lcd.h>
sbit rs=P3^5;
sbit rw=P3^4;
sbit en=P3^3;
sfr lcd=0x90;

void lcd_display(unsigned int x)  // lcd display fuction
{
	unsigned int i;
	lcd=x;
	rs=1;
	rw=0;
	en=1;
	for(i=0;i<100;i++);
	en=0; 
}
 
void cmd(unsigned char m)  // lcd command fuction
{
	unsigned int i;
	lcd=m;
	rs=0;
	rw=0;
	en=1;
	for(i=0;i<10;i++);
	en=0;
}
 
void lcd_ini()   // lcd initilize
{
	cmd(0x38);
	cmd(0x0e);
	cmd(0x01);
	cmd(0x06);
	cmd(0x90);
}	

void lcd_str(unsigned char *str)   // display string on lcd
{
	while(*str!='\0')  
	{
	  lcd_display(*str);
	  str++;
	}
}

sbit sensor1=P0^2;
sbit sensor2=P0^3;
sbit load1=P2^2;
sbit ir1=P0^0;    // sensor 1
sbit ir2=P0^1;    // sensor 2

unsigned int m='0',n='0',p,q;
 
void loop1();
 
void loop2();
 
void delay_fv(unsigned int x,unsigned int y);
void main()
{
load1=0;
sensor1=sensor2=0;

p=q=0;
	lcd_ini();	        // lcd intialize
	lcd_str(" BOOKS COUNT");
	while(1)
	{
		if(sensor1==1 && sensor2==1)
	{
	load1=1;
	}
	if(sensor1==1 && sensor2==0)
	{
	load1=0;
	}
	if(sensor1==0 && sensor2==1)
	{
	load1=0;
	}
	if(sensor1==0 && sensor2==0)
	{
	load1=0;
	}
      	p=q=0;
		if(ir1==0)
		{
			while(p==0)
			{
			    loop1();
				delay_fv(100,100);
			}
    	}
          else if(ir2==0)
       		{
	        	while(q==0)
		        {
		        	loop2();
			        delay_fv(100,100);
		        }
       		} 	
    }
}
 
void loop1()   //books exiting
{
  if(ir2==0)
	{ 
		m++;
		if(m==':')
		{
			m='0';
			n++;
		}
		cmd(0x01);
		delay_fv(100,150);
		lcd_str("NO. OF books:");
		lcd_display(n);
		lcd_display(m);
		cmd(0xc0);
		lcd_str("in bag");
		delay_fv(100,150);
		p=1;
		delay_fv(100,100);
    	delay_fv(100,100);
    	while(ir2==0);				
	}		
 }	
 
void loop2()   // books entering
{
  if(ir1==0)
	{
		m--;
		if(m==':')
		{
			m='9';
        	n--;					
        }				
		cmd(0x01);
		delay_fv(100,150);
		lcd_str("NO. OF books:");
		lcd_display(n);
		lcd_display(m);
		cmd(0xc0);
		lcd_str("in bag");
		delay_fv(100,150);
		q=1;
		delay_fv(100,100);
		delay_fv(100,100);
		if(m=='0' && n=='0')
		{ 
			cmd(0x01);
			lcd_str(" BAG IS EMPTY");
			return;
		}
    	while(ir1==0);
     }			
}
 
void delay_fv(unsigned int x,unsigned int y)  // delay
{
   unsigned int i,j;
   for(i=0;i<x;i++)
   for(j=0;j<y;j++);
}