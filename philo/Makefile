# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 11:29:48 by OrioPrisc         #+#    #+#              #
#    Updated: 2023/04/25 16:49:50 by OrioPrisc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

SRC				=	main.c\
					parse.c\
					debug.c\
					philos_init.c\
					time.c\
					philos_utils.c\
					philos_actions.c\
					printer.c\
					monitor.c\
					vector.c\
					vector2.c\
					vector3.c\
					vector4.c\

NAME			=	philo

OBJ_FOLDER		=	objs/

CFLAGS			=	-Wall -Wextra -Werror -g

SRC_FOLDER		=	srcs/

HEADERS_FOLDER	=	includes/\
					libft/includes/\

LIBS			=	libft/libft.a\

#here to ensure things get pull properly
SUBMODULES		=	libft/.git\

LFLAGS			=	-Llibft -lft

DEPENDS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC))
OBJS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
COMMANDS	:=	$(patsubst %.c,$(OBJ_FOLDER)%.cc,$(SRC))

all: $(NAME) compile_commands.json

-include $(DEPENDS)

$(SUBMODULES) :
	git submodule update --init libft

%.a: $(SUBMODULES)
	make -C $(@D) LIBS=

$(NAME): $(LIBS) $(OBJS) $(SUBMODULES)
	cc $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

COMP_COMMAND = $(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@
CONCAT = awk 'FNR==1 && NR!=1 {print ","}{print}'

$(OBJ_FOLDER)%.o $(OBJ_FOLDER)%.cc: $(SRC_FOLDER)%.c Makefile $(SUBMODULES)
	$(COMP_COMMAND)
	@printf '{\n\t"directory" : "$(shell pwd)",\n\t"command" : "$(COMP_COMMAND)",\n\t"file" : "$<"\n}' > $(OBJ_FOLDER)$*.cc

compile_commands.json : $(COMMANDS) Makefile
	@echo "Making compile_commands.json"
	@echo "[" > compile_commands.json
	@$(CONCAT) $(COMMANDS) >> compile_commands.json
	@echo "]" >> compile_commands.json

clean: $(SUBMODULES)
	rm -f $(OBJS) $(DEPENDS) $(COMMANDS)
	make -C libft clean LIBS=

fclean: clean $(SUBMODULES)
	rm -f $(NAME) compile_commands.json
	make -C libft fclean LIBS=

re: fclean all

.PHONY: all clean fclean re bonus
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
