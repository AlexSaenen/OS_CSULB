MASTER = master
SENDER = sender
RECEIVER = receiver

SRCMASTER = master.cpp
SRCSENDER = sender.cpp
SRCRECEIVER = receiver.cpp

OBJMASTER = $(SRCMASTER:.cpp=.o)
OBJSENDER = $(SRCSENDER:.cpp=.o)
OBJRECEIVER = $(SRCRECEIVER:.cpp=.o)

CXX = g++-4.9 -std=c++11

CXXFLAGS = -Werror -W -Wextra -Wall -g3 -IDefinitions

RM = rm -f

all: compile clean

compile: $(MASTER) $(SENDER) $(RECEIVER)

$(MASTER): $(OBJMASTER)
	$(CXX) $(OBJMASTER) -o $(MASTER)

$(SENDER): $(OBJSENDER)
	$(CXX) $(OBJSENDER) -o $(SENDER)

$(RECEIVER): $(OBJRECEIVER)
	$(CXX) $(OBJRECEIVER) -o $(RECEIVER)

clean:
	$(RM) $(OBJMASTER) $(OBJSENDER) $(OBJRECEIVER)

fclean: clean
	$(RM) $(MASTER)
	$(RM) $(SENDER)
	$(RM) $(RECEIVER)

re: fclean all
