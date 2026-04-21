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
CFLAGS      =   -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
CFLAGS      +=  -Wf--noinduction -Wf--nolospre
LFLAGS      =   -Wl-yt0x1B -Wl-yoA -Wl-ya1

INCLUDE     =   -I include

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
	$(LCC) $(CFLAGS) $(LFLAGS) $(INCLUDE) -o $@ $^

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
