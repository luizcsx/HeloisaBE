#ifndef _SAVE_H_
#define _SAVE_H_

#include <genesis.h>

typedef struct
{
    u16 magic;
    u16 chapter;
    u16 checkpoint;

} SaveData;

bool save_exists(void);
void save_write(SaveData* data);
void save_read(SaveData* data);

#endif
