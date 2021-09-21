# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 20:46:01 by lvirgini          #+#    #+#              #
#    Updated: 2021/09/21 17:16:24 by lvirgini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ----------------- #
#	 VARIABLES		#
# ----------------- #

NAME =		pipex

OBJ_DIR =	obj/
INC_DIR = 	includes/
SRC_DIR = 	srcs srcs/utils srcs/formating_argv srcs/exec_command

OBJ		= $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))

LIB		=	

HEADERS =	pipex.h

SRCS	=	main.c \
			ft_strlen.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_strchr_len.c \
			ft_strcmp.c \
			ft_split.c \
			get_argv_for_execve.c \
			exec_command.c \

vpath %.c $(foreach dir, $(SRC_DIR)/, $(dir):)
vpath %.h $(foreach dir, $(INC_DIR), $(dir):)

# ----------------- #
#	 COMPILATION	#
# ----------------- #

CC = 			gcc
CFLAG =			-Wall  -Wextra -g
IFLAG = 		$(foreach dir, $(INC_DIR), -I $(dir))
LFLAG =			$(foreach lib, $(LIB), -l $(lib) )

# ----------------- #
#	  FONCTIONS		#
# ----------------- #

all		:	${NAME}

$(OBJ_DIR):
			@mkdir -p $@


$(OBJ_DIR)%.o: %.c $(HEADERS) | $(OBJ_DIR)
			@echo "\033[32mCompilation de ... $(foreach file, $< , $(notdir $<))\033[0m"
			@$(CC) $(CFLAG) $(IFLAG) -o $@ -c $<
			
$(NAME)	:	$(OBJ) $(INC_DIR)
			@$(CC) $(CFLAG) $(IFLAG) $(OBJ) -o $@ $(LFLAG)
			@echo "\n\t\033[36;1m*.............................*"
			@echo "\n\t*     Compilation $(NAME)       *\t   \033[32;1m--------->>> \033[4;5mComplete\033[0m"
			@echo "\n\t\033[036;1m*.............................*\033[0m\n"
	

show	:
			@echo "SRC_DIR : $(SRC_DIR)\n"
			@echo "LIB_DIR : $(LIB_DIR)\n"
			@echo "INC_DIR : $(INC_DIR)\n"
			@echo "CFLAG : $(CFLAG)\n"
			@echo "IFLAG : $(IFLAG)\n"
			@echo "LFLAG : $(LFLAG)\n"
			@echo "HEADERS : $(foreach file, $(HEADERS),\n\t$(file))\n"
			@echo "SRC : $(foreach file, $(SRCS),\n\t$(file))\n"
			@echo "OBJ : $(foreach file, $(OBJ),\n\t$(file))\n"


# ----------------- #
# 		CLEAN		#
# ----------------- #

clean:
			@rm -rf $(OBJ_DIR) outfile
			@echo "\033[36;1m ------>>  clean\033[0m"

fclean:		clean
			@rm -f $(NAME) a.out outfile
			@echo "\033[36;1m ------>> fclean\033[0m"

re:			fclean all

.PHONY: 	all clean fclean re