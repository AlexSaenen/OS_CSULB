NAME = MemoryManagement

CLASSES = Classes/

SRC = main.cpp \
			$(CLASSES)Application.cpp \
			$(CLASSES)Menu.cpp \
			$(CLASSES)Handler.cpp \
			$(CLASSES)Interrupts.cpp \
			$(CLASSES)ProcessManager.cpp \
			$(CLASSES)Memory.cpp


OBJ = $(SRC:.cpp=.o)

CXX = g++ -std=c++11

CXXFLAGS = -Werror -W -Wextra -Wall -g3

RM = rm -f

all: compile

compile: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

build:
	docker build -t linux_program .

run:
	docker run -d --name MemoryTester -t linux_program bash

go:
	docker exec -ti MemoryTester bash
