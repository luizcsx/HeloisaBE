#include <genesis.h>
#include "save.h"

#define SAVE_MAGIC 0x4845

static void save_write_u16(u16 offset, u16 value)
{
    SRAM_writeByte(offset, (value >> 8) & 0xFF);
    SRAM_writeByte(offset + 1, value & 0xFF);
}

static u16 save_read_u16(u16 offset)
{
    u8 hi = SRAM_readByte(offset);
    u8 lo = SRAM_readByte(offset + 1);

    return (hi << 8) | lo;
}

bool save_exists(void)
{
    u16 magic;

    SYS_disableInts();
    SRAM_enable();
    magic = save_read_u16(0);
    SRAM_disable();
    SYS_enableInts();

    return magic == SAVE_MAGIC;
}

void save_write(SaveData* data)
{
    data->magic = SAVE_MAGIC;

    SYS_disableInts();
    SRAM_enable();
    save_write_u16(0, data->magic);
    save_write_u16(2, data->chapter);
    save_write_u16(4, data->checkpoint);
    SRAM_disable();
    SYS_enableInts();
}

void save_read(SaveData* data)
{
    SYS_disableInts();
    SRAM_enable();
    data->magic = save_read_u16(0);
    data->chapter = save_read_u16(2);
    data->checkpoint = save_read_u16(4);
    SRAM_disable();
    SYS_enableInts();
}
