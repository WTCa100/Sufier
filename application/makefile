CC = gcc
CFLAGS = -Wall -Werror
INCLUDES = -I./entry, -I./utilities

# Source files
SRCS = ./main.c \
	   ./entry/list.c 
#	   ./entry/contact.c
HDRS = ./entry/list.h \
	   ./entry/contact.h \
	   ./utilities/error_messages.h \
	   ./utilities/logger.h

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: Sufier.out

# Compile rules
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

# Linking rule
Sufier.out: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) Sufier.out