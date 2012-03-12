#include "init.h"

void WriteLong(unsigned long addr,unsigned long val)
{
	*((volatile unsigned long *)addr) = val;
}

void WriteByte(unsigned long addr,unsigned char c)
{
	*((volatile unsigned char *)addr) = c;
}

unsigned long ReadLong(unsigned long addr)
{
	return *((volatile unsigned long *)addr);
}

unsigned char ReadByte(unsigned long addr)
{
	return *((volatile unsigned char *)addr);
}

void DisableWatchDog()
{
	unsigned long ulVal;
	ulVal = ReadLong(WTCON);
	ulVal = ulVal & (~( 1<<5 ));
	WriteLong(WTCON,ulVal);
}

void InitClock()
{
	unsigned long ulVal;

	ulVal = ReadLong(CLKCON);
	ulVal |= 1 << 13;
	WriteLong(CLKCON,ulVal);
	WriteLong(LOCKTIME,0xffffffff);
	WriteLong(MPLLCON,1|(1 << 4)|(74 << 12));
	WriteLong(CLKSLOW,0x04);
	WriteLong(CLKDIVN,0x05);
	WriteLong(CAMDIVN,0x00);
}

void Lidhted(int num)
{
	unsigned long ulVal;
	ulVal = ReadLong(GPFCON);
	ulVal = ulVal & (~0x3f00);
	if(num == 1)
		ulVal = ulVal | 0x00100;
	else if(num == 2)
		ulVal = ulVal | 0x00500;
	else if(num == 3)
		ulVal = ulVal | 0x01500;
	else if(num == 0)
		ulVal = ulVal | 0x00000;
	WriteLong(GPFCON,ulVal);
}

void sleep(int time)
{
	for(time *= 100000; time > 0; time--);
}

void horse()
{
	int j = 20,i = 0;
	while((j--) > 0)
	{
		Lidhted((++i)%4);
		sleep(1);
	}
	MainMenu();
}
/*void InitLED()
{
	unsigned long ulVal;

	ulVal = ReadLong(GPFCON);
	ulVal = ulVal & (~0x3f00);
	ulVal = ulVal | 0x01500;
	WriteLong(GPFCON,ulVal);

	ulVal = ReadLong(GPFDAT);
	ulVal = ulVal & (~0x70);
	WriteLong(GPFDAT,ulVal);

	ulVal = ReadLong(GPFUP);
	ulVal = ulVal | 0x70;
	WriteLong(GPFUP,ulVal);
}*/

void InitUart()
{
	unsigned long ulVal;
	ulVal = ReadLong(GPHCON);
	ulVal &= (~0xf0);
	ulVal |= 0xa0;
	WriteLong(GPHCON,ulVal);

	WriteLong(ULCON0,0x03);
	WriteLong(UCON0,0x05);
	WriteLong(UFCON0,0x00);
	WriteLong(UMCON0,0x00);

	WriteLong(UBRDIV0,UART_DIV);
}

void UartTransmit(unsigned char c)
{
	unsigned long alVal;
	do
	{
		alVal = ReadLong(UTRSTAT0);
	}while((alVal & 0x04) == 0);
	WriteByte(UTXH0,c);
}

unsigned char UartReceive()
{
	unsigned long alVal;
	do
	{
		alVal = ReadLong(UTRSTAT0);
	}while((alVal & 0x01) == 0);
	return ReadByte(URXH0);
}

unsigned char Getchar()
{
	return UartReceive();
}

void putchar(char ch)
{
	UartTransmit(ch);
}

void puts(char* str)
{
	while(*str)
		UartTransmit(*(str++));
}

void puthex(unsigned int unint)
{
	char a[20];
	int i = 0, tmp;

	if(unint > 0)
	{
		while(unint != 0)
		{
			tmp = unint % 16;
			if(tmp < 10)
				a[i++] = tmp + '0';
			else
				a[i++] = tmp + 'A'-10;
			unint = unint / 16;
		}

		for(; i > 0; i--)
			UartTransmit((unsigned char)a[i-1]);
	}
	else if (unint == 0)
		putchar('0');
	else
		puts("Number error!");
}

void InitSdrom()
{
	int i;
	unsigned long ulVal;
	for(i=0;gsdranRegTbl[i];i++)
		WriteLong(SDRAM_REG_BASE+4*i,gsdranRegTbl[i]);
}

void MemaryTesting()
{
	InitSdrom();
	puts("Testing...\r\n");
	unsigned long ulVal;
	int j,mark,temp = 2;

	for(j = 0;j < MEMERY_SIZE/4;j++)
	{
		mark = 0;
		WriteLong((SDRAM_BASE_ADDR+j*4),0xffffffff);
		ulVal=ReadLong((SDRAM_BASE_ADDR+j*4));
		if(ulVal == 0xffffffff)
			mark++;
		WriteLong((SDRAM_BASE_ADDR+j*4),0x00);
		ulVal=ReadLong((SDRAM_BASE_ADDR+j*4));
		if(ulVal == 0x00)
			mark++;
		if(mark != 2)
			temp = mark;
		if((j%256000) == 0)
		{
			if(temp == 2 )
			{
				putchar('.');
			}
			else
				putchar('x');
		}
	}
	if(temp == 2)
		puts("=>ok!!!\r\n");
	else
		puts("=>fail!!!\r\n");
	MainMenu();
}

void InitNanFlash()
{
	int i;
	char ulVal;
	WriteLong(NFCONF,(TWRPH0 << 8)|(TWRPH1 << 4)|(TACLS << 12));
	WriteLong(NFCONT,0x01);
	WriteLong(NFCMMD,0x90);
	WriteLong(NFADDR,0x00);
	/*for(i = 0; i < 5; i++)
	{
		ulVal = ReadByte(NFDATA);
		puthex(ulVal);
		putchar(' ');
	}
	puts("\r\n");	*/
}

unsigned long NFReadLong()
{
	return ReadLong(NFDATA);
}

void NandFlashRead()
{
	int i;
	unsigned long ulVal;

	puts("\r\nReading NandFlash ...\r\n");

	WriteLong(NFCMMD, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFCMMD, 0x30);

	do{
		ulVal = ReadLong(NFSTAT);
	}while((ulVal & 0x01) != 1);

	for(i = 0; i < 28; i++)
	{
		ulVal = NFReadLong();
		if((i%4) == 0)
			puts("\r\n");
		puthex(ulVal);
		puts("\t");
	}
	puts("\r\n");
}

void NandFlashErase()
{
	unsigned long ulVal;

	puts("\r\nErasing NandFlash ...\r\n");

	WriteLong(NFCMMD, 0x60);
	WriteLong(NFADDR, 0x00);//第1块64，0，0
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFCMMD, 0xD0);

	do{
		ulVal = NFReadLong();
	}while((ulVal & 0x01) != 1);
	puts("Erase Over!!!");
	//MainMenu();
}

void NandFlashProgram()
{
	int j;
	unsigned long ulVal;

	NandFlashRead();
	NandFlashErase();
	WriteLong(NFCMMD,0x80);

	WriteLong(NFADDR,0x00);
	WriteLong(NFADDR,0x00);
	WriteLong(NFADDR,0x00);
	WriteLong(NFADDR,0x00);
	WriteLong(NFADDR,0x00);

	for(j = 0;j < 512;j++)
	{
		ulVal = ReadLong(SDRAM_BASE_ADDR+j*4);
		WriteLong(NFDATA,ulVal);
	}
	WriteLong(NFCMMD,0x10);

	do
	{
		ulVal = NFReadLong();
	}while((ulVal & 0x01) != 1);

	WriteLong(NFCMMD, 0x80);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x01);
	WriteLong(NFADDR, 0x00);
	WriteLong(NFADDR, 0x00);
	for(j = 512; j < 1024; j++)
	{
		ulVal = ReadLong(SDRAM_BASE_ADDR+4*j);
		WriteLong(NFDATA,ulVal);
	}
	WriteLong(NFCMMD, 0x10);

	do{
		ulVal = ReadLong(NFSTAT);
	}while((ulVal & 0x01) != 1);
	WriteLong(NFCMMD, 0x70);
	puts("Read back complete!!");
}

void MainMenu()
{
	int i;
	char c,ch;

	puts("\r\nmenu: 1.input 2.output 3.horse 4.memaryTest \r\n");
	puts("5.read flash 6.Erease Flash 7.wirte back 8.exit\r\n");
	puts("Select the function to test :");

	do
	{
		c = UartReceive();
		UartTransmit(c);
		ch = UartReceive();
	}while(ch != '\r');
	puts("\r\n");

	switch(c)
	{
		case '1' :{
				while((c = UartReceive()) != '\r')
					UartTransmit(c);
				MainMenu();
			}break;
		case '2' :{
				for(i = 0; i < 26; i++)
					UartTransmit('A'+i);
				MainMenu();
			}break;
		case '3' : horse();break;
		case '4' : MemaryTesting();break;
		case '5' : NandFlashRead();MainMenu();break;
		case '6' : NandFlashErase();MainMenu();break;
		case '7' : NandFlashProgram();break;
		default : return;
	}
}

int main()
{
	DisableWatchDog();
	InitClock();
	//InitLED();
	InitUart();
	InitNanFlash();

	MainMenu();

	return 0;
}
