BITMAP *grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame)
{
    BITMAP *temp = create_bitmap(width, height);   
    int x = startx + (frame) * width;
    blit(source, temp, x, 0, startx, starty, width, height);
    return temp;
}

int initall()
{
    Load_Datafile = load_datafile("ghost.dat");
    Ghost = (BITMAP *)Load_Datafile[GHOSTS_BMP].dat;
    Flash_Light = (BITMAP *)Load_Datafile[FLASHLIGHT_BMP].dat;
    House_Background = (BITMAP *)Load_Datafile[HOUSE1_BMP].dat;
    temp = (BITMAP *)Load_Datafile[MADGHOSTS_BMP].dat;
    for (i = 0; i < 5; i++)
        Mad_Ghost[i] = grabframe(temp, 34, 30, 0, 0, 1, i);
    temp = (BITMAP *)Load_Datafile[GHOSTDEAD_BMP].dat;
    for (i = 0; i < 12; i++)
        Dead_Ghost[i] = grabframe(temp, 80, 80, 0, 0, 1, i); 
    temp = (BITMAP *)Load_Datafile[NUMBERS2_BMP].dat;
    for (n = 0; n < 10; n++)
        numbers[n] = grabframe(temp, 14, 17, 0, 0, 1, n);
}

int SetupAll()
{
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();
    ret = install_sound(DIGI_AUTODETECT, MIDI_NONE, "");
        if (ret != 0)
        {
            allegro_message(allegro_error);
            return 1;
        }
    set_color_depth(bpp);
    ret = set_gfx_mode(mode, x, y, 0, 0);
        if (ret != 0)
        {
            allegro_message(allegro_error);
            return 1;
        }
    set_trans_blender(128, 128, 128, 180);
    create_trans_table(&trans_table, pal, 128, 128, 128, NULL);
    buffer = create_video_bitmap(SCREEN_W, SCREEN_H);
    buffer2 = activepage = create_video_bitmap(SCREEN_W, SCREEN_H);
    get_palette(pal);
}

int stretch_trans_sprite(BITMAP *drawto, BITMAP *drawfrom, int xlocation, int ylocation, int xstretch, int ystretch)
{
    BITMAP* tmpSprite = create_bitmap(xstretch, ystretch);
    clear_to_color(tmpSprite, makecol(255, 0, 255));
    stretch_sprite(tmpSprite, drawfrom, 0, 0, xstretch, ystretch);
    draw_trans_sprite(drawto, tmpSprite, xlocation, ylocation);
    destroy_bitmap(tmpSprite);
}

int draw_trans_h_flip(BITMAP *drawto, BITMAP *drawfrom, int xlocation, int ylocation)
{
    BITMAP* tmpSprite = create_bitmap(drawfrom->w, drawfrom->h);
    clear_to_color(tmpSprite, makecol(255, 0, 255));
    draw_sprite_h_flip(tmpSprite, drawfrom, 0, 0);
    draw_trans_sprite(drawto, tmpSprite, xlocation, ylocation);
    destroy_bitmap(tmpSprite);
}

int setupi()
{
    for (i = 0; i <= 500; i++)
    {
        Ghosts[i].x = rand() % (SCREEN_W - 100) + 50;
        Ghosts[i].y = rand() % (SCREEN_H - 100) + 50;
        Ghosts[i].xi = rand() % 4 + 1;
        Ghosts[i].yi = rand() % 4 + 1;
        Ghosts[i].colors = makecol(rand() % 255, rand() % 255, rand() % 255);
        Ghosts[i].bounced = rand() % 50000;
        Ghosts[i].size = 15;
        Ghosts[i].orgsize = Ghosts[i].size;
        if (rand() % 2 + 1 == 1)
            Ghosts[i].xi = -Ghosts[i].xi;
        if (rand() % 2 + 1 == 1)
            Ghosts[i].yi = -Ghosts[i].yi;
        if (i < 10)
            Ghosts[i].level = 1;
        else
            Ghosts[i].level = 8;
        Ghosts[i].dead = 0;
    }
}

int drawghost()
{
    if (Ghosts[i].level == 1 && Ghosts[i].dead == 0)
    {
        if (Ghosts[i].xi < 0 && Ghosts[i].dead == 0)
            draw_trans_sprite(activepage, Ghost, Ghosts[i].x - Ghost->w / 2, Ghosts[i].y - Ghost->h / 2);
        else
            draw_trans_h_flip(activepage, Ghost, Ghosts[i].x - Ghost->w / 2, Ghosts[i].y - Ghost->h / 2);
    }
    if (Ghosts[i].level != 1 && Ghosts[i].dead == 0)
    {
        if (Ghosts[i].xi < 0)
            draw_sprite(activepage, Mad_Ghost[(Ghosts[i].level - 2) / 3], Ghosts[i].x - Ghost->w / 2, Ghosts[i].y - Ghost->h / 2);
        else
            draw_sprite_h_flip(activepage, Mad_Ghost[(Ghosts[i].level - 2) / 3], Ghosts[i].x - Ghost->w / 2, Ghosts[i].y - Ghost->h / 2);
    }
    if (Ghosts[i].dead != 0 && Ghosts[i].dead < 24)
    {
        stretch_trans_sprite(activepage, Dead_Ghost[Ghosts[i].dead / 2], Ghosts[i].x - Ghost->w, Ghosts[i].y - Ghost->h, Ghost->w * 2, Ghost->h * 2);
    }
}

int drawmouse()
{
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    draw_sprite(activepage, (BITMAP *)Load_Datafile[FLASHLIGHT_BMP].dat, mouse_x - Flash_Light->w / 2, mouse_y + Flash_Light->h);
    if (mouse_b & 1 && !(mouse_b & 2))
        circlefill(activepage, mouse_x, mouse_y, 45, makecol(255,255,255));
    if (mouse_b & 2 && !(mouse_b & 1))
    {
        circlefill(activepage, mouse_x, mouse_y, 45, makecol(255,255,0));
        draw_trans_sprite(activepage, (BITMAP *)Load_Datafile[CROSS_BMP].dat, mouse_x - 25, mouse_y - 35);
    }
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
}

int flip()
{
    show_video_bitmap(activepage);
    if (activepage == buffer)
        activepage = buffer2;
    else
        activepage = buffer;
    clear_to_color(activepage, makecol(0, 0, 0));
}

int startscreen()
{
    play_sample((SAMPLE *)Load_Datafile[MUSIC_WAV].dat, 15, 150, 1000, 1);
    while (!key[KEY_SPACE])
    {
        stretch_sprite(activepage, (BITMAP *)Load_Datafile[GHOSTBACK_BMP].dat, 0, 0, SCREEN_W, SCREEN_H);
        flip();
    }
}

int exitscreen()
{
    while(key[KEY_ESC]);
    while(!key[KEY_ESC])
    {
        stretch_sprite(activepage, (BITMAP *)Load_Datafile[HOUSE4_BMP].dat, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_ex(activepage, font, 0, 0, makecol(255,255,255), -1, "Press Escape to Exit.  Your score was %i.", score);
        flip();
    }
}

int collide()
{
    for (ii = 0; ii < maxa; ii++)
    {
        if (UPLEFT || UPRIGHT || DOWNLEFT || DOWNRIGHT)
        {
            if (Ghosts[i].dead == 0 && Ghosts[ii].dead == 0)
            {
                tspeed = Ghosts[i].xi;
                Ghosts[i].xi = Ghosts[ii].xi;
                Ghosts[ii].xi = tspeed;
                tspeed = Ghosts[i].yi;
                Ghosts[i].yi = Ghosts[ii].yi;
                Ghosts[ii].yi = tspeed;
                bouncecount++;
                Ghosts[i].bounced = Ghosts[ii].bounced = bouncecount;
                if (Ghosts[i].level < 6 && Ghosts[ii].level != 1)
                    Ghosts[i].level++;
                if (Ghosts[ii].level < 6 && Ghosts[i].level != 1)
                    Ghosts[ii].level++;
            }
        }
    }
}

int noangry()
{
    if (mouse_b & 1 && !(mouse_b & 2))
        if (Ghosts[i].x > mouse_x - 45 && Ghosts[i].x < mouse_x + 45 && Ghosts[i].y > mouse_y - 35 && Ghosts[i].y < mouse_y + 45)
            if (Ghosts[i].level > 1)
                Ghosts[i].level--;
    if (Ghosts[i].dead > 0)
        Ghosts[i].dead++;
}

int checkdead()
{
    if (Ghosts[i].level == 1 && mouse_b & 2 && !(mouse_b & 1))
        if (Ghosts[i].x > mouse_x - 45 && Ghosts[i].x < mouse_x + 45 && Ghosts[i].y > mouse_y - 35 && Ghosts[i].y < mouse_y + 45)
            if (Ghosts[i].dead == 0)
            {
                play_sample((SAMPLE *)Load_Datafile[HIT_WAV].dat, 25, 150, 1500, 0);
                play_sample((SAMPLE *)Load_Datafile[SMASH_WAV].dat, 15, 150, 1500, 0);
                for (n = 0; n < maxa; n++)
                {
                    if (Ghosts[n].level == 1 && Ghosts[n].dead == 0)
                        scoreadd++;
                    if (Ghosts[n].level != 1 && Ghosts[n].dead == 0)
                        scoresub++;
                }
                if (scoreadd - scoresub > 0)
                    score += (scoreadd - scoresub);
                scoreadd = 0;
                scoresub = 0;
                Ghosts[i].dead = 1;
                maxa += 2;
            }
}

int checkghosts()
{
    madcount = 0;
    ghostcount = 0;
    for (i = 0; i < maxa; i++)
    {
        if (Ghosts[i].level != 1 && Ghosts[i].dead == 0)
            madcount++;
        if (Ghosts[i].dead == 0)
            ghostcount++;
    }
    if (madcount == ghostcount)
        game = 0;
}

int checkback()
{
    if (score > 150 && score < 350 && House_Background != (BITMAP *)Load_Datafile[HOUSE2_BMP].dat)
        House_Background = (BITMAP *)Load_Datafile[HOUSE2_BMP].dat;
    if (score > 350 && score < 600 && House_Background != (BITMAP *)Load_Datafile[HOUSE3_BMP].dat)
        House_Background = (BITMAP *)Load_Datafile[HOUSE3_BMP].dat;
    if (score > 600 && score < 850 && House_Background != (BITMAP *)Load_Datafile[HOUSE4_BMP].dat)
        House_Background = (BITMAP *)Load_Datafile[HOUSE4_BMP].dat;
    if (score > 850 && House_Background != (BITMAP *)Load_Datafile[HOUSE5_BMP].dat)
        House_Background = (BITMAP *)Load_Datafile[HOUSE5_BMP].dat;
}

int checkscore()
{
    snprintf(scorestring, sizeof(scorestring), "%d", score);
    int scorelength = strlen(scorestring);
    for (scoredigit = 0; scoredigit < scorelength; scoredigit++)
        stretch_sprite(activepage, numbers[scorestring[((scorelength - 1) - scoredigit)] - 48], (scorelength*34) - scoredigit * 34, 15, 28, 34);
}

int hitwall()
{
    if (Ghosts[i].x > SCREEN_W - Ghosts[i].size || Ghosts[i].x < Ghosts[i].size)
    {
        Ghosts[i].xi = -Ghosts[i].xi;
        bouncecount++;
        Ghosts[i].bounced = bouncecount;
        if (Ghosts[i].x > SCREEN_W - Ghosts[i].size)
            Ghosts[i].x = SCREEN_W - Ghosts[i].size;
        if (Ghosts[i].x < Ghosts[i].size)
            Ghosts[i].x = Ghosts[i].size;
    }
    if (Ghosts[i].y > SCREEN_H - Ghosts[i].size || Ghosts[i].y < Ghosts[i].size)
    {
        Ghosts[i].yi = -Ghosts[i].yi;
        bouncecount++;
        Ghosts[i].bounced = bouncecount;
        if (Ghosts[i].y > SCREEN_H - Ghosts[i].size)
            Ghosts[i].y = SCREEN_H - Ghosts[i].size;
        if (Ghosts[i].y < Ghosts[i].size)
            Ghosts[i].y = Ghosts[i].size;
    }
}

int movecir()
{
    if (Ghosts[i].dead == 0)
    {
        Ghosts[i].x += Ghosts[i].xi;
        Ghosts[i].y += Ghosts[i].yi;
    }
    Ghosts[i].bminx = Ghosts[i].x - Ghosts[i].size + 4;
    Ghosts[i].bminy = Ghosts[i].y - Ghosts[i].size + 4;
    Ghosts[i].bmaxx = Ghosts[i].x + Ghosts[i].size - 4;
    Ghosts[i].bmaxy = Ghosts[i].y + Ghosts[i].size - 4;
    if (bouncecount > 50000)
        bouncecount = 0;
}

