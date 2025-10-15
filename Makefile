NAME = cub3d

S_SRC_HOOKS =	key_hook.c  loop.c  setup_hook.c  hook_focus.c
S_SRC_HOOKS+=	move_player.c  colision.c  mouse_hide_fix.c  colision_door.c
D_SRC_HOOKS =	hooks/
SRC_HOOKS   =	$(addprefix $(D_SRC_HOOKS), $(S_SRC_HOOKS))

S_SRC_MMAP =	minimap.c  mmap_env.c  mmap_view.c  minimap_doors.c
D_SRC_MMAP =	minimap/
SRC_MMAP   =	$(addprefix $(D_SRC_MMAP), $(S_SRC_MMAP))

S_SRC_DOORS =	doors_utils.c  handle_door.c  open_close_door.c
D_SRC_DOORS =	doors/
SRC_DOORS   =	$(addprefix $(D_SRC_DOORS), $(S_SRC_DOORS))

S_SRC_RAY_CASTING =	ray_casting.c  ray_casting_2.c  door_front.c
D_SRC_RAY_CASTING =	ray_casting/
SRC_RAY_CASTING   =	$(addprefix $(D_SRC_RAY_CASTING), $(S_SRC_RAY_CASTING))

S_SRC_RENDER =	$(SRC_MMAP)  $(SRC_RAY_CASTING)  draw_frame.c
S_SRC_RENDER+=	antialiasing_top.c  antialiasing_bot.c  antialiasing.c
S_SRC_RENDER+=	draw_wall_col.c  set_floor_ceiling.c  cub_put_img_to_img.c  fps_counter.c
D_SRC_RENDER =	render/
SRC_RENDER   =	$(addprefix $(D_SRC_RENDER), $(S_SRC_RENDER))

S_SRC_INIT =	fill_game.c  init.c  parsing.c  init_mlx.c
S_SRC_INIT+=	pars_color.c  pars_textures.c  pars_player.c
S_SRC_INIT+=	pars_map.c  make_new_map.c  flood_fill.c
S_SRC_INIT+=	parsing_utils.c   read.c  pars_utils_space.c
S_SRC_INIT+=	pars_settings.c  pars_bonus.c  pars_map_bonus.c
D_SRC_INIT =	init/
SRC_INIT   =	$(addprefix $(D_SRC_INIT), $(S_SRC_INIT))

S_SRC_UTILS =	utils.c  utils_mem.c  utils_strchr.c  utils_strcpy.c
S_SRC_UTILS+=	errors.c  free_1.c  free_2.c  s_vector.c  s_verctor_2.c
D_SRC_UTILS =	utils/
SRC_UTILS   =	$(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

S_SRC =	$(SRC_UTILS)  $(SRC_INIT)  $(SRC_HOOKS)  $(SRC_RENDER)  $(SRC_DOORS)  main.c
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
FLAGS = -Wall -Wextra -Winline -Werror -MMD -O1
IFLAGS = $(addprefix -I, $(D_INCS))
LFLAGS = -L$(D_MLX) -lmlx -lXext -lX11 -lXfixes -lm

RM =  rm -rf

RANDOM_CLR = echo -en '\e[3;38;5;'$(shell shuf -i 0-255 -n 1)m
RESET_CLR = echo -en '\e[0m'

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

# La mlx est telechargee et un-tar automatiquement, le fclean rm -rf la mlx ducoup (Si pour ton pc c est dur enleve le $(D_MLX de la ligne en dessous))
fclean: clean
	$(RM) $(NAME) $(D_MLX)

re: fclean
	make all

DEPS = DEPS = $(OBJ:.o=.d)
-include $(DEPS)

.PHONY: re fclean clean all cp_mlx


