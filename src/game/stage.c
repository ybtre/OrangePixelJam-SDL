#include "common.h"

#include "defs.h"
#include "structs.h"
#include "draw.h"
#include "stage.h"
#include "entities.h"
#include "util.h"

inline void update(void);
inline void render(void);

inline SDL_Texture *cursor_texture;
inline SDL_Texture *spritesheet;

inline void reset_game(void);
inline void render_main_menu();
inline void render_game_over();

void init_stage(void)
{
    game.delegate.logic = update;
    game.delegate.draw = render;

    memset(&stage, 0, sizeof(Stage));

    cursor_texture = load_texture("assets/cursor.png");

    game_state = MAIN_MENU;

    //TODO: init level
    init_entities();
}

inline void update(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
             {
                 if(game.keyboard[SDL_SCANCODE_SPACE])
                 {
                     reset_game();
                     game_state = PLAYING;
                 }
             }
             break;
        
        case PLAYING:
            {
                //TODO: update lvl
                update_entities();
            }
            break;

        case GAME_OVER:
            {
                if(game.keyboard[SDL_SCANCODE_SPACE])
                {
                    reset_game();
                    //reset key state to up
                    game.keyboard[SDL_SCANCODE_SPACE] = 0;
                    game_state = MAIN_MENU;
                }
            }
            break;

    }
    if(game.keyboard[SDL_SCANCODE_ESCAPE])
    {
        exit(1);
    }
}

inline void render(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
            {
                render_main_menu();

                char buff[32];
                sprintf(buff, "PRESS SPACE TO PLAY!");

                SDL_Rect dest = {get_scr_width_scaled() / 4 - 50, get_scr_height_scaled() / 2 - 80, 0, 0};
                render_text(buff, dest, 3.f);

                sprintf(buff, "Mockup Jam!");
                dest.x = get_scr_width_scaled() / 4 + 50;
                dest.y = get_scr_height_scaled() / 2 - 310;
                render_text(buff, dest, 4.f);
            }
            break;
        
        case PLAYING:
            {
                //TODO:draw level
                draw_entities();
            }
            break;

        case GAME_OVER:
            {
                render_game_over();

                char buff[48];
                sprintf(buff, "PRESS SPACE TO GO BACK TO MAIN MENU!");

                SDL_Rect dest = {get_scr_width_scaled() / 4 - 200, get_scr_height_scaled() / 2 - 80, 0, 0};
                render_text(buff, dest, 2.f);

                sprintf(buff, "GAME OVER!");
                dest.x = get_scr_width_scaled() / 4 + 50;
                dest.y = get_scr_height_scaled() / 2 - 310;
                render_text(buff, dest, 4.f);

            }
            break;
    }

    blit(cursor_texture, game.mouse.x, game.mouse.y, 1.f, 1);
}


inline void reset_game(void)
{
    init_entities();
}

inline void render_game_over()
{
    Entity e;
    e.type = ENT_BACKGROUND;
    e.active = true;
    e.rect.x = get_scr_width_scaled() / 2;
    e.rect.y = get_scr_height_scaled() / 2;

    e.sprite.src.x = 0;
    e.sprite.src.y = 0;
    e.sprite.src.w = 320;
    e.sprite.src.h = 180;

    e.rect.w = e.sprite.src.w;
    e.rect.h = e.sprite.src.h;

    e.sprite.tex = load_texture("assets/game_over_bg.png");

    e.hitbox = e.rect;

    blit_from_sheet(e.sprite.tex, e.rect, e.sprite.src, 0, SCREEN_SCALE, 1);

}

inline void render_main_menu()
{
    Entity e;
    e.type = ENT_BACKGROUND;
    e.active = true;
    e.rect.x = get_scr_width_scaled() / 2;
    e.rect.y = get_scr_height_scaled() / 2;

    e.sprite.src.x = 0;
    e.sprite.src.y = 0;
    e.sprite.src.w = 320;
    e.sprite.src.h = 180;

    e.rect.w = e.sprite.src.w;
    e.rect.h = e.sprite.src.h;

    e.sprite.tex = load_texture("assets/main_menu_bg.png");

    e.hitbox = e.rect;

    blit_from_sheet(e.sprite.tex, e.rect, e.sprite.src, 0, SCREEN_SCALE, 1);
}
