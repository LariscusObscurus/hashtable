CC = g++
NAME = hashtable
DEBUG = -g3 -D_DEBUG
CFLAGS = -Wall -Wextra -Wconversion -std=c++0x
LFLAGS = 
VERSION = 1.0
ARCHIVE = $(NAME)-$(VERSION)

SRC = filehandling.cpp parser.cpp plotter.cpp main.cpp hashtable.cpp share.cpp
OBJ = $(SRC:.cpp=.o)

all: $(SRC) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LFLAGS)

clean:
	rm $(OBJ) $(NAME)

dist:
	cd ..; tar czf $(ARCHIVE).tar.gz $(NAME); mv $(ARCHIVE).tar.gz $(NAME)

distclean:
	rm $(ARCHIVE).tar.gz

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG)
