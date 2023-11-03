
#include "common.h"

#include "defs.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "stage.h"
#include "main.h"
#include "util.h"
#include <stdint.h>
#include <stdlib.h>

Game game;
Entity grid_large[GRID_X][GRID_Y];
Stage stage;
Game_State game_state;

inline void cap_fps(long *THEN, float *REMAINDER);

int main(int argc, char *argv[])
{
    long then;
    float remainder;

    srand(42);

    memset(&game, 0, sizeof(Game));
    
    init_SDL();

    atexit(game_close);

    init_game();

    init_stage();

    then = SDL_GetTicks();
    remainder = 0;

    char running = 1;
    uint32_t total_frame_ticks = 0;
    uint32_t total_frames = 0;

    float last_tick_time = 0;
    float delta = 0;
    while(running == 1)
    {
        float tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;

        game.dt = delta;

        prepare_scene();

        handle_input();

        game.delegate.logic();
        game.delegate.draw();

        char dt_buffer[32];
        sprintf(dt_buffer, "Current dt: %f", (float)game.dt / 1000.f);
        SDL_Rect dest = { 10, 10, 0, 0};
        render_text(dt_buffer, dest, 1.f);

        render_scene();
    }
    return(0);
}


inline void cap_fps(long *THEN, float *REMAINDER)
{// fps cap logic
    long wait, frame_time;

    wait = 16 + *REMAINDER;

    *REMAINDER -= (int)*REMAINDER;

    frame_time = SDL_GetTicks() - *THEN;

    wait -= frame_time;

    if(wait < 1)
    {
        wait = 1;
    }

    SDL_Delay(wait);

    *REMAINDER += 0.667f;

    *THEN = SDL_GetTicks();
}






















