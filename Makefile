CPP = g++
SRC = src/main.cpp \
	  src/task.cpp \
	  src/project.cpp \
	  src/timer.cpp \
	  src/menu.cpp

OBJ = $(SRC:.cpp=.o)
NAME = pomotask

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) -std=c++17 -Wextra -Werror -Wall -I./src -o $@ $^

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all