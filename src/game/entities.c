#include "common.h"

#include "defs.h"
#include "draw.h"
#include "structs.h"
#include "entities.h"
#include "util.h"
#include <stdlib.h>

inline void draw_entity_of_type(Entity_Type TYPE, char DEBUG);
inline void draw_debug_rect(Entity *e);

inline Entity* get_bullet_inactive(void);
inline void set_bullet_inactive(Entity *BULLET);
inline void fire_pistol(Entity E);

inline void spawn_enemy(Entity *E);
inline void set_enemy_inactive(Entity *ENEMY);
inline Entity* get_enemy_inactive(void);

Entity player;
char player_facing_right = true;
float player_reload = .10;
float current_reload = 0;

float enemy_spawn_interval = 1;
float enemy_spawn_timer = 0;

void init_entities(void)
{
    Entity e;

    { // Player
        player.type = ENT_PLAYER;
        player.active = true;
        player.hp = 3;
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
    { // Tiles hitbox
        e.type = ENT_TILE_HITBOX;
        e.active = true;
        e.rect.x = 10;
        e.rect.y = get_scr_height_scaled() / 2 + 100;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 320;
        e.sprite.src.h = 180;

        e.rect.w = 25;
        e.rect.h = 50;

        e.sprite.tex = load_texture("assets/tiles.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;

        e.type = ENT_TILE_HITBOX;
        e.active = true;
        e.rect.x = get_scr_width_scaled() - 10;
        e.rect.y = get_scr_height_scaled() / 2 + 100;

        e.sprite.src.x = 0;
        e.sprite.src.y = 0;
        e.sprite.src.w = 320;
        e.sprite.src.h = 180;

        e.rect.w = 25;
        e.rect.h = 50;

        e.sprite.tex = load_texture("assets/tiles.png");

        e.hitbox = e.rect;

        stage.entities_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    { // Enemies 
        int i = 0;
        for(i = 0; i < 48; i++)
        {
            e.type =  ENT_ENEMY;
            e.active = false;
            e.hp = 1;
            e.dmg = 1;
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
    { // Player bullets
        int i = 0;
        for(i = 0; i < 32; i++)
        {
            e.id = rand();
            e.type = ENT_P_BULLET,
            e.active = false;
            e.dmg = 1;
            e.rect.x = get_scr_width_scaled() / 2;
            e.rect.y = get_scr_height_scaled() / 2;

            e.sprite.src.x = 0;
            e.sprite.src.y = 1;
            e.sprite.src.w = 9;
            e.sprite.src.h = 4;

            e.rect.w = e.sprite.src.w;
            e.rect.h = e.sprite.src.h;

            e.sprite.tex = load_texture("assets/bullets.png");

            e.hitbox = e.rect;

            stage.entities_pool[stage.entity_count] = e;
            stage.entity_count++;
        }
    }
}

void update_entities(void)
{
    Entity *e;
    Entity *player = &stage.entities_pool[0];
    
    current_reload += (game.dt / 1000.f);
    enemy_spawn_timer += (game.dt / 1000.f);
    SDL_Log("Enemy spawn timer: %f", enemy_spawn_timer);

    // Update entities by type
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entities_pool[i];

        switch(e->type)
        {
            case ENT_PLAYER:
                {
                    if(e->active == true)
                    {
                        e->vel.x = e->vel.y = 0;

                        if(game.keyboard[SDL_SCANCODE_A])
                        {
                            e->vel.x = -PLAYER_VELOCITY;
                        }
                        if(game.keyboard[SDL_SCANCODE_D])
                        {
                            e->vel.x = PLAYER_VELOCITY;
                        }

                
                        e->rect.x += e->vel.x * game.dt;
                        e->rect.y += e->vel.y * game.dt;
                        //SDL_Log("Player x: %i, Player y: %i", e->rect.x, e->rect.y);
                    }
                    break;
                }
            case ENT_P_PISTOL:
                {
                    if(e->active == true)
                    {
                        e->rect.x = player->rect.x + 15;
                        e->rect.y = player->rect.y + 20;

                        if(game.keyboard[SDL_SCANCODE_SPACE])
                        {
                            if(current_reload > player_reload)
                            {
                                fire_pistol(*e);

                                current_reload = 0;
                            }
                        }
                    }

                    break;
                }
            case ENT_P_SHOTGUN:
                {
                    if(e->active == true)
                    {
                        e->rect.x = player->rect.x + 15;
                        e->rect.y = player->rect.y + 20;
                    }
                    break;
                }
            case ENT_P_MACHINEGUN:
                {
                    if(e->active == true)
                    {
                        e->rect.x = player->rect.x + 15;
                        e->rect.y = player->rect.y + 20;
                    }
                    break;
                }
            case ENT_P_BULLET:
                {
                    if(e->active == true)
                    {
                        e->rect.x += BULLET_VELOCITY * game.dt;
                        //e->rect.y += e->vel.y * game.dt;

                        if(e->rect.x > get_scr_width_scaled() + 100)
                        {
                            set_bullet_inactive(e);
                        }
                        /*
                        if(e->rect.x >= get_scr_width_scaled() + 100)
                        {
                            e->active = false;
                        }
                        if(e->rect.x <= get_scr_width_scaled() - 100)
                        {
                            e->active = false;
                        }
                        */
                    }
                    break;
                }
            case ENT_UI_P_HEALTH:
                {
                    break;
                }
            case ENT_UI_P_BULLETS:
                {
                    break;
                }
            case ENT_UI_P_SCORE:
                {
                    break;
                }
            case ENT_BACKGROUND:
                {
                    break;
                }
            case ENT_TILE:
                {
                    break;
                }
            case ENT_TILE_HITBOX:
                {
                    if(e->active)
                    {
                        SDL_Rect p_r, t_r;
                        p_r = player->rect;
                        p_r.w *= SCREEN_SCALE;
                        p_r.h *= SCREEN_SCALE;
                        p_r.x -= (p_r.w / 2);
                        p_r.y -= (p_r.h / 2);

                        t_r = e->rect;
                        t_r.w *= SCREEN_SCALE;
                        t_r.h *= SCREEN_SCALE;
                        t_r.x -= (t_r.w / 2);
                        t_r.y -= (t_r.h / 2);

                        if(SDL_HasIntersection(&p_r, &t_r))
                        {
                            if(p_r.x > t_r.x)
                            {
                                player->rect.x = 100;
                            }
                            if(p_r.x < t_r.x)
                            {
                                player->rect.x = t_r.x - 48;
                            }
                        };
                    }
                    break;
                }
            case ENT_BARREL:
                {
                    break;
                }
            case ENT_PICKUP_HP:
                {
                    break;
                }
            case ENT_PICKUP_POWERUP:
                {
                    break;
                }
            case ENT_ENEMY:
                {
                    if(e->active == false AND enemy_spawn_timer > enemy_spawn_interval)
                    {
                        spawn_enemy(e);
                        SDL_Log("Spawn enemy");
                        enemy_spawn_timer = 0;
                    }

                    if(e->active == true)
                    {
                        e->vel.x = e->vel.y = 0;
                            
                        if(e->rect.x < player->rect.x)
                        {
                            e->vel.x = ENEMY_VELOCITY;
                        }
                        if(e->rect.x > player->rect.x)
                        {
                            e->vel.x = -ENEMY_VELOCITY;
                        }

                        e->rect.x += e->vel.x * game.dt;
                        e->rect.y += e->vel.y * game.dt;
                    }
                    break;
                }
            case NUM_ENTITIES:
                {
                    break;
                }
            default:
                break;
        }
    }    
}

void draw_entities(void)
{
    draw_entity_of_type(ENT_BACKGROUND, false);
    draw_entity_of_type(ENT_TILE, false);

    draw_entity_of_type(ENT_TILE_HITBOX, true);

    draw_entity_of_type(ENT_BARREL, true);

    draw_entity_of_type(ENT_ENEMY, true);

    draw_entity_of_type(ENT_PLAYER, true);
    draw_entity_of_type(ENT_P_PISTOL, true);

    draw_entity_of_type(ENT_PICKUP_HP, true);
    draw_entity_of_type(ENT_PICKUP_POWERUP, true);

    draw_entity_of_type(ENT_P_BULLET, true);

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
            if(TYPE == ENT_TILE_HITBOX)
            {
                draw_debug_rect(e);
            }
            else
            {
                blit_from_sheet(e->sprite.tex, e->rect, e->sprite.src, 0, SCREEN_SCALE, 1);
            }


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

inline void fire_pistol(Entity E)
{
    Entity *b = get_bullet_inactive();
    
    b->rect.x = E.rect.x + 25;
    b->rect.y = E.rect.y;

    b->active = true;
    b->vel.x = BULLET_VELOCITY;
}

inline Entity* get_bullet_inactive(void)
{
    Entity *b = NULL;
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        b = &stage.entities_pool[i];
        if(b->type == ENT_P_BULLET AND b->active == false)
        {
            return(b);
        }
    }

    SDL_Log("Could not find an inactive bullet");
    return(b);
}

inline void set_bullet_inactive(Entity *BULLET)
{
    BULLET->active = false;
}


inline void spawn_enemy(Entity *E)
{
    //Entity *e = get_enemy_inactive();
    
    E->rect.x = get_scr_width_scaled() / 2 + 475;
    E->rect.y = get_scr_height_scaled() / 2 + 150;

    E->active = true;
}

inline Entity* get_enemy_inactive(void)
{
    Entity *e = NULL;
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entities_pool[i];
        if(e->type == ENT_ENEMY AND e->active == false)
        {
            return(e);
        }
    }

    SDL_Log("Could not find an inactive bullet");
    return(e);
}

inline void set_enemy_inactive(Entity *ENEMY)
{
    ENEMY->active = false;
}
