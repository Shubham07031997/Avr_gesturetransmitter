#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#include<lcdavr.h>
#include<stdio.h>

void adc_init1()
{
	ADMUX = 0B01000000;//for vcc +5v aNd vref =5v| ADC0 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}

  void adc_init2()
{
	ADMUX = 0B01000001;//for vcc +5v aNd vref =5v| ADC1 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}


  void adc_init3()
{
	ADMUX = 0B01000010;//for vcc +5v aNd vref =5v| ADC2 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}

   
	unsigned int adc_read(unsigned char channel)
{	
	
	ADMUX=0x40|channel;
	ADCSRA |= (1<<ADSC);//for starting the conversion
	while(!(ADCSRA & (1<<ADIF)));//for progress report //for converting the data

	ADCSRA |= (1<<ADIF);//for updating the data the data and previous task is done
	
	return ADC;
}





int main()
{

//	unsigned char i[5],j[5];
	unsigned int value1,value2,value3;
	DDRB = 0XFF;
	DDRC=0xff;
	lcd_init();

	adc_init1();//calling user defined function adc
	adc_init2();
	adc_init3();
while(1)
{ // adc_init1();
  value1=adc_read(0);//0th pin is used 0f adc channel

  lcd_clear();
	lcd_command(0x80);
	//sprintf(i,"%d",value1);//convrets adc value to i's data type
	lcd_string("adc value1:     ");
	lcd_command(0x8d);
	lcd_number(value1);
	_delay_ms(100);

  if(value1<=512&&value1>=300)
  {	
    
    PORTC=0b00001010;
    _delay_ms(100);}

//	adc_init2();
  value2=adc_read(1);//1th pin is used 0f adc channel
   lcd_clear();
	lcd_command(0xc0);
	//sprintf(j,"%d",value2);//convrets adc value to i's data type
	lcd_string("adc value2:     ");
	lcd_command(0xcd);
	lcd_number(value2);//lcd number is used whenever the data is generated automatically 
	_delay_ms(100);

   if(value2>=512&&value2<900)
{ PORTC=0b00000101;
_delay_ms(100);	
   }
	value3=adc_read(2);
	lcd_clear();
	lcd_string("adc value3:      ");
	lcd_command(0x8d);
	lcd_number(value3);
	_delay_ms(100);

      if(value3>=0&&value3<300)
	 {  PORTC=0b00000010;
	   _delay_ms(100);
	   }

	
}
	return 0;
}

