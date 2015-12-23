################################################################################
# COSC2123 - Algorithms and Analysis
# Semester 2 2015 Assignment #2
# Full Name        : Stuart Parker
# Student Number   : s3390317
# Course Code      : COSC2123 - Algorithms and Analysis
# Program Code     : BP094 - Bachelor of Computer Science
#
# Makefile
################################################################################

# The name of the applications we're trying to generate.
TARGET_SPEED = speedDateMatch
TARGET_BACH = bachDateMatch

SRC_SPEED = speed.c speedPerson.c common.c
SRC_BACH = bach.c bachPerson.c common.c

HEADER := $(SRC_SPEED:.c=.h) $(SRC_BACH:.c=.h) person.h

OBJ_SPEED := $(SRC_SPEED:.c=.o)
OBJ_BACH := $(SRC_BACH:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -g -Og -D_GNU_SOURCE


.PHONY : all clean test_speed test_bach

all : $(TARGET_SPEED) $(TARGET_BACH)

$(TARGET_SPEED) : $(OBJ_SPEED)
	$(CC) -o $@ $(OBJ_SPEED)
	
$(TARGET_BACH) : $(OBJ_BACH)
	$(CC) -o $@ $(OBJ_BACH)

# This generates the dependencies between your various .c and .h files, using
# the c compiler's -MM option.
depend : $(SRC_SPEED) $(SRC_BACH) $(HEADER)
	$(CC) $(CFLAGS) -MM $(SRC_SPEED) > depend
	$(CC) $(CFLAGS) -MM $(SRC_BACH) > depend

# This includes the dependencies made with the previous rule, and in fact forces
# them to be generated.
-include depend

clean :
	-rm -f depend
	-rm -f $(TARGET_SPEED) $(TARGET_BACH) $(OBJ_SPEED) $(OBJ_BACH)
	-rm -f *~

SPEED_EXAMPLES = examples/taskAExample*.csv
BACH_EXAMPLES = examples/taskBExample*.csv

test_speed :
	python assign2TesTScript.py -v . speed $(SPEED_EXAMPLES)

test_bach :
	python assign2TesTScript.py -v . bach $(BACH_EXAMPLES)
