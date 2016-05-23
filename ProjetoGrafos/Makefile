# By: Lucas "Iron" Alexandre Soares && VVilliam Ferreira
# USP BCC 2015 23/09/2015
# 
# How to make makefile
# 
# The -c flag says to generate the object file
# $@ gets the file named on the left side of the :
# $^ gets the files named on the right side of the :
# $< is the first item in the dependencies list
# $* is used to get the name of the file (path included)
# @ before just means "DON'T PRINT THIS COMMAND IN COMMAND LINE"
# echo means "PRINT: "
# @echo means the world will explode
# 
# make should normaly be in project directory and access includes and libs relatively from there
# 
# DIRECTORIES TREE:
# 	project/
# 		include
# 		lib
# 		build
# 		src/
# 			obj
#

# Project name
NAME=ProjetoGrafos


# Directories
INCDIR=include
LIBDIR=lib
BLDDIR=build
SRCDIR=src
OBJDIR=$(SRCDIR)/.obj

# Can use any debbuger (like gdb) or overlay (like valgrind) (though gdb is an overlay too)
DEBUGGER=
DBGFLAGS=--leak-check=full --show-leak-kinds=all --read-var-info=yes --track-origins=yes


# This will search for 'anything' terminating in .c inside SRCDIR and set an object rule for each of them (make *.o)
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(foreach file, $(SRC), $(file:$(SRCDIR)/%.c=$(OBJDIR)/%.o))

# Find all .h dependencies
DEPS=$(wildcard $(INCDIR)/*.h)

# Finally something easy to read!
CC=gcc
CFLAGS=-O3 -Wall -Wextra -I./$(INCDIR)


# Library links (example: -lm for math lib)
LIBS=

# if you run make [target] debug=____ where ____ is anything (even an empty string will do)
ifdef debug
	CFLAGS+= -g
	DEBUGGER=valgrind $(DBGFLAGS) 
endif

all: $(OBJ)
	@echo Linking object files...
	@$(CC) -o $(BLDDIR)/$(NAME) $^ $(CFLAGS) $(LIBS)
	@echo Done.

# Compile directives
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@echo Building $*...
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo Done.

# Run directives
run:
	@$(DEBUGGER) ./$(BLDDIR)/$(NAME)

go: all run

zip: clean
	@echo Compressing files...
	@tar -zcvf $(NAME).tar.gz *

	@echo Done.


# Utility directives
clean:
	@echo Cleaning object files...
	@-rm -f $(OBJDIR)/*.o

	@echo Cleaning built file...
	@-rm -f $(BLDDIR)/$(NAME)

	@clear
	@clear

list:
	@ls -lhR

# Check if project has a name before creating it
create:
ifeq ($(strip $(NAME)),)
	$(error No project name provided (open this Makefile and set NAME))
endif
	
	@mkdir $(NAME) 
	@echo Project directory created.

	@mkdir $(NAME)/$(SRCDIR)
	@echo Source directory created.

	@mkdir $(NAME)/$(INCDIR)
	@echo Include directory created.

	@mkdir $(NAME)/$(LIBDIR)
	@echo Library directory created.

	@mkdir $(NAME)/$(BLDDIR)
	@echo Build folder created.

	@mkdir $(NAME)/$(OBJDIR)
	@echo Object folder created.

	@mv ./Makefile ./$(NAME)
	@echo Done.
