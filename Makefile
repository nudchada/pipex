# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 10:06:03 by nusamank          #+#    #+#              #
#    Updated: 2024/05/01 12:12:45 by nusamank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
HEAD = includes
SRCDIR = srcs
BINDIR = bin

SRCS = $(SRCDIR)/pipex.c $(SRCDIR)/pipex_utils.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))

BONUS_DIR = srcs_bonus
BONUS_SRCS = $(BONUS_DIR)/pipex_bonus.c $(BONUS_DIR)/pipex_utils_bonus.c \
			$(BONUS_DIR)/here_doc_bonus.c $(BONUS_DIR)/print_error_bonus.c
BONUS_OBJS = $(patsubst $(BONUS_DIR)/%.c, $(BINDIR)/%.o, $(BONUS_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(HEAD) $(OBJS) $(LIBFT) -o $@

bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(BONUS_DIR) $(BONUS_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEAD) | $(BINDIR)
	$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@

$(BINDIR)/%.o: $(BONUS_DIR)/%.c $(BONUS_DIR) | $(BINDIR)
	$(CC) $(CFLAGS) -c -I $(BONUS_DIR) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)
	
clean:
	rm -rf $(BINDIR)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus