NAME = "RT"
SRC_PATH = ./src/
INC_PATH = ./rt.h
OBJ_PATH = ./obj/
SRC_NAME = $(shell ls $(SRC_PATH) | grep .c)
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

LIBS = libft/libft.a SDL2.framework/SDL2

OBJ =	$(patsubst src/%.c,obj/%.o,$(SRC))

#.SILENT :

all : $(OBJ) $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[33m >>> \033[32mCOMPILING \033[36;4m\"$(NAME)\"\033[0m \033[32m...\033[33m <<<\033[0m"
	@gcc $(LIBS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
#obj/%.o: src/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo '' > /dev/null
	@mkdir -p obj
	@gcc -Wall -Wextra -Werror -ofast -c $< -o $@
	@echo "\033[35m >>> \033[32mCOMPILING \"$<\"..\033[35m <<<\033[0m"

clean :
	/bin/rm -rf obj
	@echo "\033[32m >>> [$(NAME)] >>> \033[31m Remove all .o files\033[0m"

fclean : clean
	@echo "\033[31m >>> \033[33;4m \"$(NAME)\" EXECUTABLE DELETED\033[0m"
	/bin/rm -rf $(NAME)

norme :
	@echo "\033[32m==> norminette : \033[33;4m$(INC_PATH)\033[0m \033[33;4m$(SRC_PATH)\033[0m"
	@norminette $(INC_PATH) $(SRC_PATH)

re : fclean all

.PHONY: clean fclean
