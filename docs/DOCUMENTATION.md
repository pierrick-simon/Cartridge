# How to make a game

To make add a game in this project there are multiple step to folow.

## STEP 1 - Understand the code

This Project is separate in multiple parts, whith the main parts the **cors** that combine them all.

The **cors** is here to handle which game run and which game to init.

This is made by the **init_table[]** and **update_table** in the **core.h**.
It contains the functions to execute for each game.

## STEP 2 - Game structure

The new implement game must contain struct that will persist between is init and update functions:
```
typedef struct {
    // score;
    // sprites;
    // vram state;
    // player pos;
} game_state;
```
It contains all the information that need to be init or save to make your game work.

## STEP 3 - Init function

The init function is here to create a the object needed during the game, like load the data of the main sprites in the vram. \
It take the game structure in parameter and return a void:

```
void game_init(game_state *game);
```

## STEP 4 - Update function

The update function is here to update the state of the loaded game each tick. \
It take the game structure and the input_state structure in parameter and return a game_state_t typedef:

```
game_state_t game_update(game_state *game, const input_state *input)
```

The input can be used to know if the user push on any of the available button:

```
uint8_t pressed = get_just_pressed(input);
if (pressed & J_START)
    printf("Start button as been push");
```

With GBDK there is 8 buttons that can be used:

```
#define	J_UP         0x04U
#define	J_DOWN       0x08U
#define	J_LEFT       0x02U
#define	J_RIGHT      0x01U
#define	J_A          0x10U
#define	J_B          0x20U
#define	J_SELECT     0x40U
#define	J_START      0x80U
```

And the return value of the game update function is the enum to make the core know what will be lauded next.

## STEP 5 - Add the game

The final step is to change multiple define and enum to make the core know that your game exist and launch it if the criteria are right.

Also modified the menu to be able to launch it from it.

## STEP 6 - More

There is a lot of main methode that you can use to implement your game:
- **Sprite** : methode that handle the sprites inside the vram.
- **Sound Manager**: methode that handle the sounds play on the gameboy.