#DevLog - ~12:30h
Game 4, side 2d arena shooter part of OrangePascal game jam

[![Image from Gyazo](https://i.gyazo.com/56f3a8aac61c4980e7b47ff8f43967a9.gif)](https://gyazo.com/56f3a8aac61c4980e7b47ff8f43967a9)

## Game 4/10 in the 10 games in 10 weeks challenge
////////////////////////////////////
              NOTE:
Part of OrangePixel game jam: https://itch.io/jam/orangepixels-mockup-game-jam
need to use provided sprites

////////////////////////////////////
#### Goals:
- spend min ~12h per game
- aim for 10 games by week 10 
- have a small scope finished game by the end of the week
- even if not finished - still release it

////////////////////////////////////
              TODO:
////////////////////////////////////

#### FINAL:
- permanence (bullet shells on ground?

#### WIP: Game Feel
- screen shake?
- gun delay (moves slightly slower than player)


##### TBD
- polish/game feel
- think of ammo powerup
- ammo/reload system?
- connect ammo/reload system to UI?
- telepathic gun
- tweens (ray easings?)

////////////////////////////////////
              DONE:
////////////////////////////////////

//03.11.2023 -
- enemy knockup on hit - 0:10h
- fix pickups spawning in the air
- freeze frame/sleep - 0:10h
- add graphics to main menu - 0:15h
- add graphics to game over - 0;05
- game over leads to main menu - 0:05 
- - reset spacebar down state when transitioning to game over - 0:05h

//02.11.2023 - ~1:20h
- slight draw_ent_of_type refactor - 0:25h
- bigger muzzle flash - 0:05h
- bigger bullets - 0:05h
- faster bullets - 0:05h
- higher RoF - 0:05h
- less accuracy - 0:10h
- enemy hit animation (white flash) - 0:15h
- enemy knowback on hit - 0:05h
- player knockback on fire - 0;05h
- increase enemy spawn rate with time - 0:10h

//01.11.2023 - ~2:15h
- create muzzle flash sprite and anim
- basic animations
- - enemy anim
- - coin anim
- - UI coin anim
- - player anim
- lower enemy hp -> 3hp 
- explosion on enemy hit
- explosion anim
- bullet impact effect on walls
- muzzle flash

// 31.10.2023 - ~2:00h 
- implementing basic game loop
- - enemy drop ammo pack on death(chance)
- - collision detection recognises ammo powerups
- slight refactor
- - unity entity hp/dmg to be easier to change/configure
- - PlayerData struct
- flipping enemy and bullet sprites based on direction
- fix flipping issues
- connect HP UI to player HP

// 30.10.2023 - ~2:15h
- implementing basic game loop
- - player shooting both ways
- - enemy choose rand spawn point
- - enemy deal dmg to player
- - player collision w/HP pack
- - player death
- - implement game reset
- - enemy drop hp pack on death(chance)
- - hp pickup refactor to supprot pooling and multiple spawns
- - enemy drop coin on death(chance)
- - score connect to coin

//27.10.2023 - ~3:15h
- debugging random movement code issue

- start implementing basic game loop
- - player collision with walls
- - player shooting
- - player reload
- - player bullets pool
- - player hp
- - enemy spawning
- - enemy pool
- - bullet collide w/ enemy
- - bullet kill enemy
- - player flip
- - gun flip

//26.10.2023 - 3:15h
- mockup
- project skeleton
- start implementing basic game loop
- - player movement
- - enemy move towards player
- start implementing static mockup sprites
- - player
- - player pistol
- - background
- - tiles
- - barrels
- - enemies
- - UI player hp
- - UI player ammo
- - UI player scoer
- - Pickup HP
- - Picktup Power Up
