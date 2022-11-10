# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malord <malord@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 10:07:57 by malord            #+#    #+#              #
#    Updated: 2022/11/10 13:42:16 by malord           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
#LIBFT		=	libft/libft.a

CC			=	gcc
CFLAGS		=	-g -Wall -Werror -Wextra -fsanitize=thread
INCLUDE		=	-lpthread
RM			=	rm -f
OBJDIR		=	bin/
SRCDIR		=	src/

SRCS		=	src/philo.c				\
				src/inits.c				\
				src/utils.c				\
				src/time.c				\
				src/singletons.c		\
				src/routine_sim.c		\
				src/errors.c

#OBJS		= 	${SRCS:.c=.o}
OBJS		= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

# Targets

# .c.o:
#				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): 		$(OBJS)
#				@echo "Compiling libft..."
#				@$(MAKE) -C libft
#				@echo "libft compiled successfully."
				@echo "Compiling $(NAME) sources"
#				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
				@$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo "Done !"

all: 			$(NAME)

$(OBJS) : $(OBJDIR)%.o : $(SRCDIR)%.c $(OBJDIR)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
				@mkdir -p $(OBJDIR)
	
# Removes objects
clean:
				@echo "Removing $(NAME) objects..."
				@$(RM) $(OBJS)
#				@echo "Removing libft objects..."
#				@make clean -C libft
				@echo "$(NAME) objects successfully deleted."
#				@echo "libft objects successfully deleted."

# Removes objects and executable
fclean: 		clean
				@echo "Removing $(NAME) program..."
				@$(RM) $(NAME)
#				@echo "Removing libft archive..."
#				@$(RM) $(LIBFT)
				@echo "Executable(s) and archive(s) successfully deleted."

valgrind:		all
				valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
			
norm:		
				@norminette include/
				@norminette src/
#				@norminette libft/

segfault:		
				@$(CC) $(CFLAGS) -fsanitize=address -o $(NAME) $(OBJS)

# Removes objects and executable then remakes all
re: 			fclean all
				
.PHONY:			all clean fclean bonus re				