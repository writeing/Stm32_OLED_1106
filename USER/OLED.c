#include "OLED.h"
#include "oled_font.h"  	 
#include "spi.h"
void Delay_ms( uint32_t nCount)
{                         
  uint16_t a;
  while(nCount)
  {
    a=1800;
    while(a--);
    nCount--;
   }
}

void OLED_WriteByte(uint8_t dat,uint8_t cmd)
{
  uint8_t i;
  OLED_DC(cmd);
  OLED_CS(0);
	//OLED_WB(dat);
  for(i=0;i<8;i++)
  {
    OLED_SCLK(0);
    if(dat&0x80)
      OLED_MOSI(1);
    else
      OLED_MOSI(0);
    OLED_SCLK(1);
    dat<<=1;
  }
  OLED_CS(1);
  OLED_DC(1);
}

void OLED_SetPos(uint8_t x, uint8_t y)
{
  OLED_WriteByte(0xB0+y,isCMD);
  OLED_WriteByte(((x&0xF0)>>4)|0x10,isCMD);
  OLED_WriteByte((x&0x0F)|0x02,isCMD);
}

void OLED_Clear(void)
{
  uint8_t i,n;
  for(i=0;i<8;i++)
  {
    OLED_WriteByte (0xB0+i,isCMD);
    OLED_WriteByte (0x02,isCMD);
    OLED_WriteByte (0x10,isCMD);
    for(n=0;n<128;n++)
      OLED_WriteByte(0,isDATA);
  }
}


void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{
  uint8_t c=0,i=0;
  c=chr-' ';
  if(x>Max_Column-1)
  {
    x=0;
    y=y+2;
  }
 
  if(SIZE ==16)
  {
    OLED_SetPos(x,y);
    for(i=0;i<8;i++)
      OLED_WriteByte(F8X16[c*16+i],isDATA);
    OLED_SetPos(x,y+1);
    for(i=0;i<8;i++)
      OLED_WriteByte(F8X16[c*16+i+8],isDATA);
  }
  else
  {
    OLED_SetPos(x,y+1);
    for(i=0;i<6;i++)
    OLED_WriteByte(F6x8[c][i],isDATA);
  }
}

uint32_t oled_pow(uint8_t m,uint8_t n)
{
  uint32_t result=1;
  while(n--)
    result*=m;
  return result;
}

void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2)
{
  uint8_t t,temp;
  uint8_t enshow=0;
  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
      {
        if(temp==0)
          {
            OLED_ShowChar(x+(size2/2)*t,y,' ');
            continue;
          }
        else
          enshow=1;
      }
    OLED_ShowChar(x+(size2/2)*t,y,temp+'0');
  }
}

void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
  uint8_t j=0;
  while (chr[j]!='\0')
  {
    OLED_ShowChar(x,y,chr[j]);
    x=x+8;
    if(x>120)
    {
      x=0;
      y=y+2;
    }
    j++;
  }
}
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no)
{
  uint8_t t,adder=0;
	x=x*8;
	OLED_SetPos(x,y);
	for(t=0;t<16;t++)
	{
		OLED_WriteByte(bigHzk[2*no][t],isDATA);
		adder++;
	 }
	OLED_SetPos(x,y+1);
	for(t=0;t<16;t++)
	{
		OLED_WriteByte(bigHzk[2*no+1][t],isDATA);
		adder+=1;
	}

}
void OLED_ShowBigChinese(uint8_t x,uint8_t y,uint8_t no)
{
  uint8_t t,adder=0 , k = 0;
	x=x*8;
	for(int j = 0; j < 4 ; j ++ )
	{
		OLED_SetPos(x,y + j);
		for(t=0;t<16;t++)
		{
			OLED_WriteByte(bigHzk[8*no + k][t],isDATA);
			adder++;
		}
		k++;
		OLED_SetPos(x+16,y + j);
		for(t=0;t<16;t++)
		{
			OLED_WriteByte(bigHzk[8*no + k][t],isDATA);
			adder+=1;
		}
		k++;
	}
}

void OLED_DrawBMP(uint8_t x, uint8_t y , int no)
{ 	
	uint16_t j=0; 
	x = x*8;
	OLED_SetPos(x,y);
	for( j = 0; j < 16 ; j ++)
	{      
		OLED_WriteByte(bmp[2*no][j],isDATA);	    	
	}
	OLED_SetPos(x,y+1);
	for( j = 0; j < 16 ; j ++)
	{      
		OLED_WriteByte(bmp[2*no+1][j],isDATA);	    	
	}
}
void OLED_sDrawBMP(uint8_t x, uint8_t y , int no)
{ 	
	uint16_t j=0; 
	x = x*8;
	OLED_SetPos(x,y);
	for( j = 0; j < 8 ; j ++)
	{      
		OLED_WriteByte(sBmp[no][j],isDATA);	    	
	}
	OLED_SetPos(x,y+1);
	for( j = 0; j < 8 ; j ++)
	{
		OLED_WriteByte(sBmp[2*no+1][j],isDATA);	    	
	}
}
void OLED_InitGPIO(void)
{
	GPIO_InitTypeDef OLEDIO;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	OLEDIO.GPIO_Pin= (OLED_SCLK_Pin|OLED_MOSI_Pin |OLED_RES_Pin|OLED_DC_Pin|OLED_CS_Pin);	// 
	OLEDIO.GPIO_Mode= GPIO_Mode_Out_PP;
	OLEDIO.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_Init(GPIOA, &OLEDIO);
}

void OLED_Init(void)
{

  OLED_InitGPIO();
  OLED_RES(1);
  Delay_ms(100);
  OLED_RES(0);
  Delay_ms(100);
  OLED_RES(1); 

	OLED_WriteByte(0xAE,isCMD);//--turn off oled panel
	OLED_WriteByte(0x02,isCMD);//---set low column address
	OLED_WriteByte(0x10,isCMD);//---set high column address
	OLED_WriteByte(0x40,isCMD);//-- set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteByte(0x81,isCMD);//-- set contrast control register
	OLED_WriteByte(Brightness,isCMD);//-- Set SEG Output Current Brightness
	OLED_WriteByte(0xA1,isCMD);//-- Set SEG/Column Mapping     0xa0??
	OLED_WriteByte(0xC8,isCMD);//-- Set COM/Row Scan Direction   0xc0??
	OLED_WriteByte(0xA6,isCMD);//-- set normal display
	OLED_WriteByte(0xA8,isCMD);//-- set multiplex ratio(1 to 64)
	OLED_WriteByte(0x3f,isCMD);//--1/64 duty
	OLED_WriteByte(0xD3,isCMD);//-- set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteByte(0x00,isCMD);//-- not offset
	OLED_WriteByte(0xd5,isCMD);//--set display clock divide ratio/oscillator frequency
	OLED_WriteByte(0x80,isCMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteByte(0xD9,isCMD);//--set pre-charge period
	OLED_WriteByte(0xF1,isCMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteByte(0xDA,isCMD);//--set com pins hardware configuration
	OLED_WriteByte(0x12,isCMD);
	OLED_WriteByte(0xDB,isCMD);//--set vcomh
	OLED_WriteByte(0x40,isCMD);//Set VCOM Deselect Level
	OLED_WriteByte(0x20,isCMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteByte(0x02,isCMD);//
	OLED_WriteByte(0x8D,isCMD);//--set Charge Pump enable/disable
	OLED_WriteByte(0x14,isCMD);//--set(0x10) disable
	OLED_WriteByte(0xA4,isCMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WriteByte(0xA6,isCMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WriteByte(0xAF,isCMD);//--turn on oled panel
	
  OLED_WriteByte(0xAF,isCMD); /*display ON*/ 
  OLED_Clear();
  OLED_SetPos(0,0); 
}
