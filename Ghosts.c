#include <allegro.h>
#include <stdio.h>
#include <define.h>
#include <variables.h>
#include <functions.h>

int main()
{
    SetupAll();
    setupi();
    initall();
    startscreen();
    while (!key[KEY_ESC] && game == 1)
    {
        stretch_sprite(activepage, House_Background, 0, 0, SCREEN_W, SCREEN_H);
        for (i = 0; i < maxa; i++)
        {
            drawghost();
            hitwall();
            collide();
            noangry();
            checkdead();
            movecir();
        }
        checkghosts();
        checkback();
        checkscore();
        drawmouse();
        flip();
    }
    exitscreen();
    unload_datafile(Load_Datafile);
    allegro_exit();
    return 0;
}
END_OF_MAIN()
