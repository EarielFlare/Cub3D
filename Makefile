NAME			=	cub3D
LIBFT_NAME		=	libft.a
MLX_NAME		=	libmlx.a
SRCS_DIR		=	./src_main/
MLX_DIR			=	./mlx/
LIBFT_DIR		=	./libft/
SRCS			=	main.c			messages.c\
					aux_funcs.c		hooks.c\
					draw_funcs.c	init.c\
					libft.c			parser_utils.c\
					map_check.c		border_check.c\
					init_structs.c	player_checker.c\
					hv_arrays.c		ray_checks.c\
					../gnl/get_next_line.c
FRACTOL_H		=	cub3d.h
HEADERS			=	./inc/
OBJ				=	$(addprefix $(SRCS_DIR), $(SRCS:%.c=%.o))
CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
MAKEFLAGS		=	--no-print-directory
RM				=	rm -rf

.PHONY			:	all clean fclean re bonus

all				:	$(NAME)

$(NAME)			:	$(LIBFT_DIR)$(LIBFT_NAME) $(MLX_DIR)$(MLX_NAME) $(OBJ) $(HEADERS)$(FRACTOL_H)
					@$(RM) -rf $(OBJ_BONUS)
					@$(CC) $(OBJ)\
					$(LIBFT_DIR)$(LIBFT_NAME) $(MLX_DIR)$(MLX_NAME) -framework OpenGL -framework AppKit -o $(NAME)
					@echo "$(BLUE)$(NAME): program created$(DEFAULT)"

#$(NAME)			:	libft/libft.a mlx/libmlx.a $(OBJ) $(HEADERS)$(FRACTOL_H)
#					@$(RM) -rf $(OBJ_BONUS)
#					@$(CC) $(OBJ)\
#					-Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
#					@echo "$(BLUE)$(NAME): program created$(DEFAULT)"

$(LIBFT_DIR)$(LIBFT_NAME)	:
					@make -s -w all bonus -C $(LIBFT_DIR)

$(MLX_DIR)$(MLX_NAME)	:
					@make -s -w -C $(MLX_DIR)

%.o:				%.c $(HEADERS)$(FRACTOL_H) $(HEADERS)$(BONUS_H)
					@$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR)\
					-I/usr/include -Imlx -O3 -c $< -o $@

clean			:	
					@$(RM) $(OBJ)
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(MLX_DIR)
					@echo "$(YELLOW)$(NAME): obj files deleted$(DEFAULT)"

fclean			:	clean
					@$(RM) $(NAME)
					@make fclean -C $(LIBFT_DIR)
					@make clean -C $(MLX_DIR)
					@echo "$(RED)$(NAME): all files deleted$(DEFAULT)"

re				:	fclean all

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
DEFAULT = \033[0m
