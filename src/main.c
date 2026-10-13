#include <genesis.h>
#include "title.h"

int main(bool hardReset)
{
    JOY_init();

    title_init();

    while (TRUE)
    {
        title_update();

        SYS_doVBlankProcess();
    }

    return 0;
}
