#include "lcd.h"

static uint8_t transmission_buffer[BUFFER_SIZE], transmission_buffer_index = 0;

//---------------------------------------------------
// Private functions
//---------------------------------------------------

static void begin_transmission(uint8_t address)
{
	transmission_buffer[0] = address;
	transmission_buffer_index = 1;
}

static void write(uint8_t data)
{
	transmission_buffer[transmission_buffer_index++] = data;
}

static void end_transmission()
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
	I2C_Send7bitAddress(I2C1, transmission_buffer[0] << 1, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	for (int i = 1; i < transmission_buffer_index; i++)
	{
		I2C_SendData(I2C1, transmission_buffer[i]);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
	transmission_buffer_index = 0;
}

static void LCD_send_data(uint8_t data)
{
	begin_transmission(LCD_ADDRESS);
	write(LCD_DATA);
	write(data);
	end_transmission();
}

static void LCD_send_command(uint8_t command)
{
	begin_transmission(LCD_ADDRESS);
	write(LCD_COMMAND);
	write(command);
	end_transmission();
}

static void LCD_send_command_data(uint8_t command, uint8_t data)
{
	begin_transmission(LCD_ADDRESS);
	write(LCD_COMMAND);
	write(command);
	write(LCD_COMMAND);
	write(data);
	end_transmission();
}

static void I2C1_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    
	I2C_InitTypeDef i2citd;
	i2citd.I2C_ClockSpeed = 50000;
	i2citd.I2C_Mode = I2C_Mode_I2C;
	i2citd.I2C_DutyCycle = I2C_DutyCycle_2;
	i2citd.I2C_OwnAddress1 = 0;
	i2citd.I2C_Ack = I2C_Ack_Enable;
	i2citd.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &i2citd);
	
	I2C_Cmd(I2C1, ENABLE);
}


//---------------------------------------------------
// Public functions
//---------------------------------------------------

void LCD_init()
{
	I2C1_init();
	for(int i = 0; i < 1000; i++);
    
	LCD_send_command(0xAE);
	LCD_send_command_data(0xD5, 128);
	LCD_send_command_data(0xA8, 0x3F);
	LCD_send_command_data(0xd3, 0x00);
	LCD_send_command_data(0x8d, 0x14);
	LCD_send_command(0x40);
	LCD_send_command(0xa6);
	LCD_send_command(0xa4);
	LCD_send_command(0xa1);
	LCD_send_command(0xc8);
	// Horizontal mode
	LCD_send_command(0x20);
	LCD_send_command(0x00);

	LCD_send_command_data(0xda, 0x12);
	LCD_send_command_data(0x81, 0x8F);
	LCD_send_command_data(0xd9, 0xf1);
	LCD_send_command_data(0xdb, 0x40);
	LCD_send_command(0xaf);
}

void LCD_send_text(uint8_t *data)
{
	uint16_t count = 0, buffer_char_space = BUFFER_SIZE / 6;
	
	begin_transmission(LCD_ADDRESS);
	write(LCD_DATA);
	while(*data)
	{
		if (count % buffer_char_space == 0)
		{
			end_transmission();
			begin_transmission(LCD_ADDRESS);
			write(LCD_DATA);
		}
		
		for (int i = 0; i < 5; i++)
		{
			write(font_6x8[(int) *data - 32][i]);
			count++;
		}
		
		write(0); // 1 empty column between letters
		count++;
		data++;
	}
	
	end_transmission();	
}

// todo - make start adres in pixels
void LCD_set_page_address(uint8_t start)  
{
	//  Page start Address, range : 0-7d
	LCD_send_command(0x22);
	LCD_send_command(start);
	LCD_send_command(7);
}

// todo - make start adres in pixels
void LCD_set_column_address(uint8_t start) 
{
	// Column start address, range : 0-127d
	LCD_send_command(0x21);
	LCD_send_command(start);
	LCD_send_command(127);
}

void LCD_clear_screen()
{
	LCD_set_page_address(0);
	LCD_set_column_address(0);
	for (int i = 0; i < 8; i++)
	{
		begin_transmission(LCD_ADDRESS);
		write(LCD_DATA);
		for (int j = 0; j < 128; j++)
		{
			write(0);
		}
		
		end_transmission();
	}
}

void LCD_draw_line(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y)
{
	// todo
}