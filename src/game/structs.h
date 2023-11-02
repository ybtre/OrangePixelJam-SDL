#ifndef STRUCTS_H
#define STRUCTS_H

#include "../Include/SDL2/SDL.h"
#include "../Include/SDL2/SDL_ttf.h"
#include "defs.h"
#include "util.h"

typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct Texture
{
    char            active;

    char            name[MAX_NAME_LENGTH];
    SDL_Texture*    texture;
} Texture;

typedef struct
{
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
} Mouse;

#define TEXTURE_CACHE_MAX   16
typedef struct
{
	SDL_Renderer*   renderer;
	SDL_Window*     window;
    Delegate        delegate;

    Mouse           mouse;

    float           dt;

    int             keyboard[MAX_KEYBOARD_KEYS];

    TTF_Font        *font;

    SDL_Texture     *spritesheet;

    Texture         texture_cache[TEXTURE_CACHE_MAX];
} Game;
extern Game game;

typedef enum Game_State
{
    MAIN_MENU,
    PLAYING,
    GAME_OVER,
} Game_State;
extern Game_State game_state;

enum Flags 
{
    GAME_PAUSED         = 1 << 0,
};

// |= flag      : set flag
// &= !()flag   : unset flag
// ^= flag      : flip flag
typedef struct Game_Flags
{
    uint64_t flags;

} Game_Flags;
extern Game_Flags game_flags;

typedef enum Entity_Type
{
    ENT_PLAYER,
    ENT_P_PISTOL,
    ENT_P_SHOTGUN,
    ENT_P_MACHINEGUN,
    ENT_P_BULLET,

    ENT_UI_P_HEALTH_BG,
    ENT_UI_P_HEALTH_FG,
    ENT_UI_P_BULLETS,
    ENT_UI_P_SCORE,

    ENT_BACKGROUND,
    ENT_TILE,
    ENT_TILE_HITBOX,
    ENT_BARREL,
    ENT_EXPLOSION,
    ENT_MUZZLE_FLASH,

    ENT_PICKUP_HP,
    ENT_PICKUP_POWERUP,
    ENT_PICKUP_COIN,

    ENT_ENEMY,

    NUM_ENTITIES,
} Entity_Type;

typedef enum
{
    L_BACKGROUND,
    L_GAMEPLAY,
    L_FOREGROUND,
    L_UI,

    NUM_LAYERS,
} Layers;

typedef struct
{
    SDL_Rect        src;

    SDL_Texture     *tex;
} Sprite;

typedef struct 
{
    char            loop;
    int             num_frames;
    int             cur_frame;
    float           frame_rate;
    float           frame_timer;
} AnimData;

typedef struct
{
    int             id;
    char            active;
    Entity_Type     type;
    int             hp;
    int             base_hp;
    int             dmg;
    int             base_dmg;

    char            facing_right;
    char            hit_this_frame;
    int             hit_frame_timer;
    int             hit_frame_length;

    SDL_Rect        rect; //x, y for position, w, h for constructing dest rect
    Vec2            vel;

    SDL_Rect        hitbox;

    Sprite          sprite;
    AnimData        anim;
    //Layers          layer;
} Entity;

typedef struct
{
    char            is_moving;

    float           reload_rate;
    float           reload_timer;

    int             score;

    char            take_dmg;
    float           take_dmg_rate;
    float           take_dmg_timer;
} PlayerData;

typedef struct
{
    //Entity 0 is always player
    int             entity_count;
    Entity          entities_pool[ENTITIES_MAX];
}Stage;
extern Stage stage;


#endif
