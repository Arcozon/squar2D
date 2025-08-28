NAME = cub3d

S_SRC_HOOKS =	key_hook.c  loop.c  setup_hook.c  move_player.c
D_SRC_HOOKS =	hooks/
SRC_HOOKS   =	$(addprefix $(D_SRC_HOOKS), $(S_SRC_HOOKS))

S_SRC_RENDER =	set_floor_ceiling.c  draw_frame.c  draw_projected_wall.c  antialiasing.c
S_SRC_RENDER+=	antialiasing_top.c  antialiasing_bot.c  minimap.c
D_SRC_RENDER =	render/
SRC_RENDER   =	$(addprefix $(D_SRC_RENDER), $(S_SRC_RENDER))	

S_SRC_INIT =	init.c  pars_data.c  pars_data_color.c  pars_map.c  pars_player.c
S_SRC_INIT+=	parsing.c  parsing_utils.c  read.c  flood_fill.c  fill_game.c
D_SRC_INIT =	init/
SRC_INIT   =	$(addprefix $(D_SRC_INIT), $(S_SRC_INIT))

S_SRC_UTILS =	utils.c  errors.c free.c s_vector.c
D_SRC_UTILS =	utils/
SRC_UTILS   =	$(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

S_SRC =	$(SRC_UTILS)  $(SRC_INIT)  $(SRC_HOOKS)  $(SRC_RENDER)  main.c
D_SRC =	src/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(S_SRC:.c=.o))

MAKE += --no-print-directory
LINK_MLX = https://cdn.intra.42.fr/document/document/34997/minilibx-linux.tgz
TAR_MLX = $(D_MLX).tgz
MK_MLX = $(MAKE) --silent -C$(D_MLX) 2>/dev/null
D_MLX = minilibx-linux
D_INCS = inc/ inc/utils/ $(D_MLX)  

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g
IFLAGS = $(addprefix -I, $(D_INCS))
LFLAGS = -L$(D_MLX) -lmlx -lXext -lX11 -lm

RM =  rm -rf

RANDOM_CLR = echo -n '[3;38;5;'$(shell shuf -i 0-255 -n 1)m
RESET_CLR = echo -n '[0m'

all:	cp_mlx
	@$(MAKE) $(NAME)

$(NAME):	$(OBJ)
	$(MK_MLX)
	@$(RANDOM_CLR)
	$(CC) -o$@ $^ $(LFLAGS)
	@$(RESET_CLR)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	@$(RANDOM_CLR)
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@
	@$(RESET_CLR)

cp_mlx:
	@test -d $(D_MLX) || $(MAKE) $(TAR_MLX)

$(TAR_MLX):
	@curl --output $@ $(LINK_MLX)
	@tar -xf $@
	@$(RM) $@

clean:
	@$(MK_MLX) clean || true
	$(RM) $(D_BUILD)

# La mlx est telechargee et untar automatiquement, le fclean rm -rf la mlx ducoup (Si pour ton pc c est dur enleve le $(D_MLX de la ligne en dessous))
fclean: clean
	$(RM) $(NAME) $(D_MLX)

re: fclean
	make all

DEPS = DEPS = $(OBJ:.o=.d)
-include $(DEPS)

.PHONY: re fclean clean all cp_mlx


