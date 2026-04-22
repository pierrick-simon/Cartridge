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
INCLUDE     =   -Wf-I./include -Wf-I./assets/tiles/ \
				-Wf-I./assets/maps/ -Wf-I./assets/sprites/

SRC_DIR     =   src
ASSETS_DIR  =   assets
OBJ_DIR     =   obj

SRCS		=   $(addprefix $(SRC_DIR)/, 			\
					game1.c							\
					game2.c							\
					game3.c							\
					input.c							\
					main.c 							\
					menu.c 							\
					cursor.c						\
				)									\
				$(addprefix $(ASSETS_DIR)/, 		\
					$(addprefix tiles/, 			\
						grasstile.c					\
					)								\
					$(addprefix sprites/, 			\
						playertile.c				\
					)								\
				)									\

OBJS        =   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# $@ = target of the rule
# $< = first dependency
# $^ = all dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(LCC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME): $(OBJS)
	$(LCC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

CORE    =   $(HOME)/.var/app/org.libretro.RetroArch/config/retroarch/cores/gambatte_libretro.so
run: all
	flatpak run org.libretro.RetroArch -L $(CORE) $(NAME)
	$(RM) $(NAME)

.PHONY: all clean fclean re run
