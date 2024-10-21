# Makefile

NAME = ft_ping

CC = gcc
CFLAGS = #-Wall -Wextra -Werror

SRCS =  srcs/ft_ping.c \
		srcs/ft_split.c \
		srcs/signals.c \
		srcs/utils.c \

OBJECT_FILES = $(SRCS:.c=.o)
HEADER = -I./includes

all: $(NAME)
.c.o:
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
	@printf "$(YELLOW)Compiling $(NAME): << $< >>\033[K\r$(DEFAULT)"

$(NAME): $(OBJECT_FILES)
	@echo "\n"
	$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(SRCS)
	@echo "$(GREEN)<<<<< $(NAME) exec file created >>>>>$(DEFAULT)"
#------------------------------------------------------------------------------
clean:
	@echo "$(RED)<<<<< deleting $(NAME) obj. files >>>>>$(DEFAULT)"
	@rm -rf $(OBJECT_FILES)
	@echo "$(GREEN)<<<<< clean from $(NAME) done >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
fclean: clean
	@echo "$(RED)<<<<< deleting $(NAME) exec >>>>>$(DEFAULT)"
	@rm -rf $(NAME)

	@echo "$(GREEN)<<<<< fclean from $(NAME) done >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
re: fclean all
	@echo "$(GREEN)\n<<<<< $(NAME) make re done >>>>>$(DEFAULT)"
#------------------------------------------------------------------------------
#COLORS
RED = \033[3;31m
GREEN = \033[3;32m
YELLOW = \033[3;33m
DEFAULT = \033[0m
#------------------------------------------------------------------------------
#DEBUG
# -fsanitize=address
# valgrind --leak-check=full