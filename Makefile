##
## EPITECH PROJECT, 2026
## cartridge
## File description:
## Makefile for Game Boy ROM
##

NAME        =   game.gb

GBDK        ?=  /opt/gbdk
LCC         =   $(GBDK)/bin/lcc

# -Wl-yt0x1B : MBC5 + RAM + BATTERY
# -Wl-yoA : 512 KB ROM
# -Wl-ya1 : 8 KB SRAM
CFLAGS      =   -Wa-l -Wl-m -Wl-j
LFLAGS      =   -Wl-yt0x1B -Wl-yoA -Wl-ya1

# Pass include path to the SDCC frontend only (-Wf) not to lcc itself
# Dont add GBDK's include path
# lcc adds it
INCLUDE     =   -Wf-I./include -Wf-I./assets/backgrounds/ \
				-Wf-I./assets/maps/ -Wf-I./assets/sprites/ \
				-Wf-I./assets/musics/

SRC_DIR     =   src
ASSETS_DIR  =   assets
OBJ_DIR     =   obj

SRCS		=   $(addprefix $(SRC_DIR)/, 			\
					game1.c							\
					game1_init.c					\
					game1_handle.c					\
					game1_move_player.c				\
					game1_attacks.c					\
					game2.c							\
					game2_init.c					\
					game2_handle.c					\
					game2_enemy.c					\
					game3.c							\
					input.c							\
					main.c 							\
					menu.c 							\
					cursor.c						\
					sound_manager.c 				\
					sprite.c 						\
					save.c 							\
				)									\
				$(addprefix $(ASSETS_DIR)/, 		\
					$(addprefix backgrounds/, 		\
						moontile.c					\
						spacetile.c 				\
					)								\
					$(addprefix sprites/, 			\
						platformtile.c				\
						playertile.c				\
						flash.c 					\
						asteroid.c 					\
						spaceship1.c 				\
						spaceship2.c 				\
						spaceship3.c 				\
						spaceship4.c 				\
						explosion.c 				\
						hearttile.c					\
						number.c					\
						power_up.c 					\
						star.c 						\
					)								\
					$(addprefix	 musics/, 			\
						sound_note.c 				\
						starwars.c					\
						game2_theme.c 				\
						power.c 					\
					)								\
				)									\

OBJS        =   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

obj/save_data.o: src/save_data.c
	$(LCC) $(LCCFLAGS) -Wf-ba0 -c -o obj/save_data.o src/save_data.c

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# $@ = target of the rule
# $< = first dependency
# $^ = all dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(LCC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME): $(OBJS) obj/save_data.o
	$(LCC) $(CFLAGS) $(LFLAGS) -o $@ $^ obj/save_data.o

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

CORE    =   $(HOME)/.var/app/org.libretro.RetroArch/config/retroarch/cores/gambatte_libretro.so
run: all
	flatpak run org.libretro.RetroArch -L $(CORE) $(NAME)

.PHONY: all clean fclean re run
