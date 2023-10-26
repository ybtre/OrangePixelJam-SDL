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

    { // Player
        player.type = ENT_PLAYER;
        player.active = true;
        player.rect.x = get_scr_width_scaled() / 2;
        player.rect.y = get_scr_height_scaled() / 2 + 115;

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
    }
    { // Background
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
    }
    { // Tiles
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
    { // Enemy 1
        e.type =  ENT_ENEMY;
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 + 350;
        e.rect.y = get_scr_height_scaled() / 2 + 150;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 10;
        e.sprite.src.h = 10;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/enemy_robot.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // Player Pistol
        e.type = ENT_P_PISTOL,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 + 20;
        e.rect.y = get_scr_height_scaled() / 2 + 135;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 15;
        e.sprite.src.h = 9;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/player_pistol.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // Barrel
        e.type = ENT_BARREL,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 + 120;
        e.rect.y = get_scr_height_scaled() / 2 + 130;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 15;
        e.sprite.src.h = 15;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/barrels.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // UI Player HP
        e.type = ENT_UI_P_HEALTH,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 - 20;
        e.rect.y = get_scr_height_scaled() / 2 + 270;

        e.sprite.src.x = 45;
        e.sprite.src.y = 13;
        e.sprite.src.w = 33;
        e.sprite.src.h = 13;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/ui_elements.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // UI Player Ammo
        e.type = ENT_UI_P_BULLETS,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 + 140;
        e.rect.y = get_scr_height_scaled() / 2 + 270;

        e.sprite.src.x = 12;
        e.sprite.src.y = 0;
        e.sprite.src.w = 33;
        e.sprite.src.h = 13;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/ui_elements.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // UI Player Score
        e.type = ENT_UI_P_SCORE,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 - 70;
        e.rect.y = get_scr_height_scaled() / 2 - 300;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 8;
        e.sprite.src.h = 8;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/coin.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // Pickup HP
        e.type = ENT_PICKUP_HP,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 - 140;
        e.rect.y = get_scr_height_scaled() / 2 + 140;

        e.sprite.src.x = 0;
        e.sprite.src.y = 13;
        e.sprite.src.w = 12;
        e.sprite.src.h = 13;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/ui_elements.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // Pickup Power Up
        e.type = ENT_PICKUP_POWERUP,
        e.active = true;
        e.rect.x = get_scr_width_scaled() / 2 - 200;
        e.rect.y = get_scr_height_scaled() / 2 + 140;

        e.sprite.src.x = 2;
        e.sprite.src.y = 0;
        e.sprite.src.w = 9;
        e.sprite.src.h = 13;

        e.rect.w = e.sprite.src.w;
        e.rect.h = e.sprite.src.h;

        e.sprite.tex = load_texture("assets/ui_elements.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
}

void update_entities(void)
{
    
}

void draw_entities(void)
{
    draw_entity_of_type(ENT_BACKGROUND, false);
    draw_entity_of_type(ENT_TILE, false);

    draw_entity_of_type(ENT_BARREL, true);

    draw_entity_of_type(ENT_ENEMY, true);

    draw_entity_of_type(ENT_PLAYER, true);
    draw_entity_of_type(ENT_P_PISTOL, true);

    draw_entity_of_type(ENT_PICKUP_HP, true);
    draw_entity_of_type(ENT_PICKUP_POWERUP, true);

    draw_entity_of_type(ENT_UI_P_HEALTH, false);
    draw_entity_of_type(ENT_UI_P_BULLETS, false);
    draw_entity_of_type(ENT_UI_P_SCORE, false);
}

inline void draw_entity_of_type(Entity_Type TYPE, char DEBUG)
{
    Entity *e;
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entities_pool[i];
       
        if(e->active == false)
            continue;

        if(e->type == TYPE)
        {
            blit_from_sheet(e->sprite.tex, e->rect, e->sprite.src, 0, SCREEN_SCALE, 1);

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
