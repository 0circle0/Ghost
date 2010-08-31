#define UPLEFT Ghosts[i].bminx > Ghosts[ii].bminx && Ghosts[i].bminx < Ghosts[ii].bmaxx && Ghosts[i].bminy > Ghosts[ii].bminy && Ghosts[i].bminy < Ghosts[ii].bmaxy && Ghosts[i].bounced != Ghosts[ii].bounced
#define UPRIGHT Ghosts[i].bmaxx > Ghosts[ii].bminx && Ghosts[i].bmaxx < Ghosts[ii].bmaxx && Ghosts[i].bminy > Ghosts[ii].bminy && Ghosts[i].bminy < Ghosts[ii].bmaxy && Ghosts[i].bounced != Ghosts[ii].bounced
#define DOWNLEFT Ghosts[i].bminx > Ghosts[ii].bminx && Ghosts[i].bminx < Ghosts[ii].bmaxx && Ghosts[i].bmaxy > Ghosts[ii].bminy && Ghosts[i].bmaxy < Ghosts[ii].bmaxy && Ghosts[i].bounced != Ghosts[ii].bounced
#define DOWNRIGHT Ghosts[i].bmaxx > Ghosts[ii].bminx && Ghosts[i].bmaxx < Ghosts[ii].bmaxx && Ghosts[i].bmaxy > Ghosts[ii].bminy && Ghosts[i].bmaxy < Ghosts[ii].bmaxy && Ghosts[i].bounced != Ghosts[ii].bounced

BITMAP *buffer, *buffer2, *activepage;
BITMAP *Ghost, *Flash_Light, *Mad_Ghost[10], *Dead_Ghost[10];
BITMAP *House_Background;
BITMAP *temp;
BITMAP *numbers[10];

COLOR_MAP trans_table;

PALETTE pal;

DATAFILE *Load_Datafile;

int mode = GFX_AUTODETECT_FULLSCREEN, x = 800, y = 600, bpp = 16;
int maxsize = 10, minsize = 10;
int i, maxa = 10, ii, tspeed, game = 1, n;
int score = 0, bouncecount = 0;
int lives = 10, scoreadd = 0, scoresub = 0;
int madcount = 0, ghostcount = 0;
int scoredigit, ret = 0;

char scorestring[50], temps[100];

struct cicr
{    
    int x, y;
    int colors;
    int xi, yi;
    int bminx, bminy, bmaxx, bmaxy;
    int bounced, wall;
    int size, orgsize;
    int level, dead;
}Ghosts[1000];
