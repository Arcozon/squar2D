NAME = cub3d

S_SRC_UTILS =  utils.c  errors.c free.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_UTILS)  main.c  parsing.c  init.c  read.c
D_SRC = src/

D_INC = inc/  

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

LINK_MLX = https://cdn.intra.42.fr/document/document/34997/minilibx-linux.tgz
TAR_MLX = $(D_MLX).tgz
MK_MLX = $(MAKE) --silent -C$(D_MLX) 2>/dev/null
D_MLX = minilibx-linux

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g
IFLAGS = -I$(D_INC) -I$(D_MLX)
LFLAGS = -L$(D_MLX) -lmlx -lXext -lX11 -lm
RM =  rm -rf

all:	cp_mlx
	@$(MAKE) $(NAME)

$(NAME):	$(OBJ)
	$(MK_MLX)
	$(CC) -o$@ $^ $(LFLAGS)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@ 

cp_mlx:
	@test -d $(D_MLX) || $(MAKE) $(TAR_MLX)

$(TAR_MLX):
	@curl --output $@ $(LINK_MLX)
	@tar -xf $@
	@$(RM) $@

clean:
	@$(MK_MLX) clean || true
	$(RM) $(D_BUILD)

# La mlx est telechargee et detar automatiquement, le fclean rm -rf la mlx ducoup (Si pour ton pc c est dur enleve le $(D_MLX de la ligne en dessous))
fclean: clean
	$(RM) $(NAME) $(D_MLX)

re: fclean
	make all

DEPS = DEPS = $(OBJ:.o=.d)
-include $(DEPS)

.PHONY: re fclean clean all cp_mlx


