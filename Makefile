NAME =  cub3d

S_SRC_UTILS =  utils.c  errors.c free.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_UTILS)  main.c  parsing.c
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

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MK_MLX)
	$(CC) -o$@ $^ $(LFLAGS)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@ 

cp_mlx: $(TAR_MLX)

$(TAR_MLX):
	curl --output $@ $(LINK_MLX)
	tar -xf $@
	$(RM) $@

clean:
	$(MK_MLX) clean || true
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all cp_mlx


