#include "common.h"

#include "defs.h"
#include "draw.h"
#include "structs.h"
#include "entities.h"
#include "util.h"

inline void draw_entity_of_type(Entity_Type TYPE, char DEBUG);
inline void draw_debug_rect(Entity *e);

Entity player;

void init_entities(void)
{
    Entity e;

    player.type = ENT_PLAYER;
    player.active = true;
    player.rect.x = get_scr_width_scaled() / 2;
    player.rect.y = get_scr_height_scaled() / 2;

    player.sprite.src.x = 0;
    player.sprite.src.y = 0;
    player.sprite.src.w = 21;
    player.sprite.src.h = 28;

    player.rect.w = player.sprite.src.w;
    player.rect.h = player.sprite.src.h;

    player.sprite.tex = load_texture("assets/player.png");

    player.hitbox = player.rect;

    stage.entities_pool[0] = player;
    stage.entity_count++;

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

    e.sprite.tex = load_texture("assets/background.png");

    e.hitbox = e.rect;

    stage.entities_pool[stage.entity_count] = e;
    stage.entity_count++;

    e.type = ENT_TILE;
    e.active = true;
    e.rect.x = get_scr_width_scaled() / 2;
    e.rect.y = get_scr_height_scaled() / 2;

    e.sprite.src.x = 0;
    e.sprite.src.y = 0;
    e.sprite.src.w = 320;
    e.sprite.src.h = 180;

    e.rect.w = e.sprite.src.w;
    e.rect.h = e.sprite.src.h;

    e.sprite.tex = load_texture("assets/tiles.png");

    e.hitbox = e.rect;

    stage.entities_pool[stage.entity_count] = e;
    stage.entity_count++;
}

void update_entities(void)
{
    
}

void draw_entities(void)
{
    draw_entity_of_type(ENT_BACKGROUND, false);
    draw_entity_of_type(ENT_TILE, false);
    draw_entity_of_type(ENT_PLAYER, true);
}

inline void draw_entity_of_type(Entity_Type TYPE, char DEBUG)
{
    Entity *e;
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entities_pool[i];
        
        if(e->type == TYPE)
        {
            blit_from_sheet(e->sprite.tex, e->rect, e->sprite.src, 0, 4.f, 1);

            if(DEBUG == true)
            {
                draw_debug_rect(e);
            }
        }
    }
}

inline void draw_debug_rect(Entity *e)
{
    SDL_Rect drect;
    drect = e->rect;
    drect.w *= SCREEN_SCALE;
    drect.h *= SCREEN_SCALE;
    drect.x -= (drect.w / 2);
    drect.y -= (drect.h / 2);
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &drect);
}
