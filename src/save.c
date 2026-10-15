#include <genesis.h>
#include "save.h"

#define SAVE_MAGIC 0x4845

bool save_exists(void)
{
    SaveData data;

    SYS_disableInts();
    SRAM_enable();
    SRAM_readAll((u8*) &data, sizeof(SaveData), 0);
    SRAM_disable();
    SYS_enableInts();

    return data.magic == SAVE_MAGIC;
}

void save_write(SaveData* data)
{
    data->magic = SAVE_MAGIC;

    SYS_disableInts();
    SRAM_enable();
    SRAM_writeAll((u8*) data, sizeof(SaveData), 0);
    SRAM_disable();
    SYS_enableInts();
}

void save_read(SaveData* data)
{
    SYS_disableInts();
    SRAM_enable();
    SRAM_readAll((u8*) data, sizeof(SaveData), 0);
    SRAM_disable();
    SYS_enableInts();
}
