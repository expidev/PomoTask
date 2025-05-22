CXX = g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
NAME = pomotask

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CXX) -Wextra -Werror -Wall -I./src -o $@ $^

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all