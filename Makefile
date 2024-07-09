# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 07:47:00 by mgayout           #+#    #+#              #
#    Updated: 2024/07/09 13:58:34 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
NAME_B		=	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -g3
MLXFLAGS	=	-lXext -lX11
MATHFLAGS	=	-lm
LIBMLX		=	./minilibx/libmlx.a
LIBFT		=	./libft/libft.a

GREEN				=\033[0;32m
BLUE				=\033[0;36m
RED					=\033[0;31m
CLEAR_PREVIOUS_LINE	= \033[2K\r
MOVE_CURSOR_UP		= \033[1A

SRCDIR		= src
SRCDIR_B	= bonus
OBJDIR		= obj

SRCS	= $(shell find $(SRCDIR) -name '*.c')
OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

SRCS_B	= $(shell find $(SRCDIR_B) -name '*.c')
OBJS_B	= $(patsubst $(SRCDIR_B)/%.c, $(OBJDIR)/%.o, $(SRCS_B))

INCLUDE	= ./includes
HEADER	= ./includes/cube3D.h ./minilibx-linux/mlx_int.h ./minilibx-linux/mlx.h
HEADER	= ./includes/cube3D_bonus.h ./minilibx-linux/mlx_int.h ./minilibx-linux/mlx.h

TOTAL_OBJS		= $(words $(OBJS))
TOTAL_OBJS_B	= $(words $(OBJS_B))
COUNTER			= 0
MSG_COUNTER		= 0

centered_echo = \
  MESSAGE="$1"; \
  TERM_WIDTH=$$(tput cols); \
  MESSAGE_LENGTH=$$(( $$(echo "$$MESSAGE" | wc -c) - 1 )); \
  PADDING=$$(( (TERM_WIDTH - MESSAGE_LENGTH) / 2 )); \
  COLOR="$2"; \
  RESET="\033[0m"; \
  printf "%b%*s%b\n" "$$COLOR" $$((PADDING + MESSAGE_LENGTH)) "$$MESSAGE" "$$RESET"

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(call centered_echo, "\|" "Updating" "libft" "\|", $(BLUE))
	@make --no-print-directory all -C ./libft/
	@$(call centered_echo, "\|" "Libft" "is" "updated" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Updating" "MLX" "\|", $(BLUE))
	@make -s --no-print-directory all -C ./minilibx-linux/
	@$(call centered_echo, "\|" "MLX" "is" "updated" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Compiling" "cube3D" "\|", $(BLUE))	
	@gcc $(OBJS) -o $(NAME) ./libft/libft.a ./minilibx-linux/libmlx.a $(CFLAG) $(MLXFLAGS) $(MATHFLAGS) -I$(INCLUDE)
	@$(call centered_echo, "\|" "Cube3D" "is" "updated" "\|", $(GREEN))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	@$(call centered_echo, "Compiling" $< ($$(($(COUNTER)))/$(TOTAL_OBJS)), $(BLUE))
	@$(eval MSG_COUNTER=$(shell echo $$(($(MSG_COUNTER)+1))))
	@if [ $$(($(MSG_COUNTER) % 5)) -eq 0 ]; then \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
    fi
	@gcc $(CFLAGS) -I$(INCLUDE) -c $< -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B) $(HEADER_B)
	@$(call centered_echo, "\|" "Updating" "libft" "\|", $(BLUE))
	@make --no-print-directory all -C ./libft/
	@$(call centered_echo, "\|" "Libft" "is" "updated" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Updating" "MLX" "\|", $(BLUE))
	@make -s --no-print-directory all -C ./minilibx-linux/
	@$(call centered_echo, "\|" "MLX" "is" "updated" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Compiling" "cube3D_bonus" "\|", $(BLUE))	
	@gcc $(OBJS_B) -o $(NAME_B) ./libft/libft.a ./minilibx-linux/libmlx.a $(CFLAG) $(MLXFLAGS) $(MATHFLAGS) -I$(INCLUDE)
	@$(call centered_echo, "\|" "Cube3D_bonus" "is" "updated" "\|", $(GREEN))

$(OBJDIR)/%.o: $(SRCDIR_B)/%.c
	@mkdir -p $(dir $@)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	@$(call centered_echo, "Compiling" $< ($$(($(COUNTER)))/$(TOTAL_OBJS_B)), $(BLUE))
	@$(eval MSG_COUNTER=$(shell echo $$(($(MSG_COUNTER)+1))))
	@if [ $$(($(MSG_COUNTER) % 5)) -eq 0 ]; then \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
    fi
	@gcc $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@$(call centered_echo, "\|" "Removing" "objects" "from" "libft" "\|", $(RED))
	@make --no-print-directory clean -C ./libft
	@$(call centered_echo, "\|" "All" "objects" "from" "libft" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "objects" "from" "MLX" "and" "MLX" "\|", $(RED))
	@make -s --no-print-directory clean -C ./minilibx-linux
	@$(call centered_echo, "\|" "All" "objects" "from" "MLX" "and" "MLX" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "objects" "\|", $(RED))
	@rm -rf $(OBJDIR)
	@$(call centered_echo, "\|" "All" "objects" "have" "been" "deleted" "\|", $(GREEN))

fclean: clean
	@$(call centered_echo, "\|" "Removing" "libft" "\|", $(RED))
	@make --no-print-directory fclean -C ./libft
	@$(call centered_echo, "\|" "Libft" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "cube3D" "\|", $(RED))
	@rm -rf $(NAME)
	@$(call centered_echo, "\|" "Cube3D" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "cube3D_bonus" "\|", $(RED))
	@rm -rf $(NAME_B)
	@$(call centered_echo, "\|" "Cube3D_bonus" "have" "been" "deleted" "\|", $(GREEN))


re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
