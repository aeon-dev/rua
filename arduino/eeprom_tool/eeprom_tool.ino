#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;

static const uint16_t SERIAL_BAUD = 57600;
static const uint8_t OUTPUT_ENABLE = 3;
static const uint8_t WRITE_ENABLE = 4;
static const uint8_t IO_PIN_BEGIN = 5;
static const uint8_t IO_PIN_END = 12;

void select_address(uint16_t address)
{
    mcp.writeGPIOAB(address);
}

void configure_address_selection()
{
    mcp.begin();

    for (uint8_t i = 0; i < 16; ++i)
    {
        mcp.pinMode(i, OUTPUT);
    }

    select_address(0);
}

void configure_data_io()
{
    pinMode(OUTPUT_ENABLE, OUTPUT);
    pinMode(WRITE_ENABLE, OUTPUT);
}

void configure_serial()
{
    Serial.begin(SERIAL_BAUD);
}

void set_io_direction(uint8_t dir)
{
    for (auto i = IO_PIN_BEGIN; i <= IO_PIN_END; ++i)
    {
        pinMode(i, dir);
    }
}

void set_output_enable()
{
    digitalWrite(OUTPUT_ENABLE, LOW);
}

void clear_output_enable()
{
    digitalWrite(OUTPUT_ENABLE, HIGH);
}

void set_write_enable()
{
    digitalWrite(WRITE_ENABLE, LOW);
}

void clear_write_enable()
{
    digitalWrite(WRITE_ENABLE, HIGH);
}

uint8_t read_eeprom(uint16_t address)
{
    select_address(address);

    uint8_t data = 0;
    for (auto i = IO_PIN_END; i >= IO_PIN_BEGIN; --i)
    {
        data = (data << 1) + digitalRead(i);
    }

    delayMicroseconds(1000);

    return data;
}

void write_eeprom(uint16_t address, uint8_t data)
{
    select_address(address);
    delayMicroseconds(1);

    for (uint8_t i = IO_PIN_BEGIN; i <= IO_PIN_END; ++i)
    {
        digitalWrite(i, data & 1);
        data = data >> 1;
    }

    set_write_enable();
    delayMicroseconds(10);
    clear_write_enable();
    delayMicroseconds(10);
}

void serial_write_hex(uint8_t value)
{
    char buff[3];
    sprintf(buff, "%02x", value);
    Serial.print(buff);
}

void read_data_test()
{
    set_io_direction(INPUT);
    clear_write_enable();
    set_output_enable();

    for (uint8_t i = 0; i < 16; ++i)
    {
        auto data = read_eeprom(i);
        
        serial_write_hex(data);

        Serial.print(" ");

    }
    Serial.println("");
}

void write_data_test()
{
    clear_output_enable(); 
    set_io_direction(OUTPUT);

    for (uint8_t i = 0; i < 16; ++i)
    {
        write_eeprom(i, i);
    }
}

void setup()
{
    configure_data_io();
    configure_address_selection();
    clear_write_enable();
    set_output_enable();

    set_io_direction(INPUT);

    configure_serial();

    delay(50);

    write_data_test();

    read_data_test(); 
}

void loop()
{
}

