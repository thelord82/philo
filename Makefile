# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malord <malord@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 10:07:57 by malord            #+#    #+#              #
#    Updated: 2022/11/11 12:45:58 by malord           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc
CFLAGS		=	-g -Wall -Werror -Wextra
INCLUDE		=	-pthread
RM			=	rm -f
OBJDIR		=	bin/
SRCDIR		=	src/

SRCS_FILES	=	philo.c				\
				inits.c				\
				utils.c				\
				time.c				\
				singletons.c		\
				routine_sim.c		\
				errors.c			\
				main.c

VPATH		= $(SRCDIR)
SRC_OBJ		= $(SRCS_FILES:.c=.o)
SRCS		= $(addprefix $(SRCDIR), $(SRCS_FILES))
OBJS		= $(addprefix $(OBJDIR), $(SRC_OBJ))

# Targets

# .c.o:
#				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): 		$(OBJS)
				@echo "Compiling $(NAME) sources"
				@$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo "Done !"

all: 			 $(NAME)

$(OBJDIR)%.o:%.c | $(OBJDIR)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
				@mkdir -p $(OBJDIR)
	
# Removes objects
clean:
				@echo "Removing $(NAME) objects..."
				@$(RM) $(OBJS)
				@echo "$(NAME) objects successfully deleted."

# Removes objects and executable
fclean: 		clean
				@echo "Removing $(NAME) program..."
				@$(RM) $(NAME)
				@echo "Executable(s) and archive(s) successfully deleted."

valgrind:		all
				valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
			
norm:		
				@norminette include/
				@norminette src/

segfault:		
				@$(CC) $(CFLAGS) -fsanitize=address -o $(NAME) $(OBJS)

# Removes objects and executable then remakes all
re: 			fclean all
				
.PHONY:			all clean fclean bonus re
