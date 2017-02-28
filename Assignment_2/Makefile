MASTER = master
SENDER = sender
RECEIVER = receiver

.KERNEL = KernelClasses/
.SENDER = SenderClasses/
.RECEIVER = ReceiverClasses/

SRCMASTER = main.cpp \
			$(.KERNEL)Application.cpp

SRCSENDER = $(.SENDER)main.cpp \
			$(.SENDER)Application.cpp

SRCRECEIVER = $(.RECEIVER)main.cpp \
			$(.RECEIVER)Application.cpp

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
	$(RM) $(RECEIVE)

re: fclean all
