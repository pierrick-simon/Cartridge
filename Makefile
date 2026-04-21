##
## EPITECH PROJECT, 2026
## cartridge
## File description:
## Makefile for Game Boy ROM
##

NAME        =   game.gb

GBDK        ?=  /opt/gbdk
LCC         =   $(GBDK)/bin/lcgit gi

# -Wl-yt0x1B : MBC5 + RAM + BATTERY
# -Wl-yoA : 512 KB ROM
# -Wl-ya1 : 8 KB SRAM
CFLAGS      =   -Wa-l -Wl-m -Wl-j
LFLAGS      =   -Wl-yt0x1B -Wl-yoA -Wl-ya1

# Pass include path to the SDCC frontend only (-Wf) not to lcc itself
# Dont add GBDK's include path
# lcc adds it
INCLUDE     =   -Wf-I./include

SRC_DIR     =   src
OBJ_DIR     =   obj

SRCS        =   $(wildcard $(SRC_DIR)/*.c)
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
