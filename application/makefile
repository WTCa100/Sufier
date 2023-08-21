CC = gcc
CFLAGS = -Wall -Werror
INCLUDES = -I./entry, -I./utilities

# Source files
SRCS = ./main.c \
	   ./entry/list.c \
	   ./utilities/input/input_handle.c \
	   ./utilities/ui/menu.c \
	   ./utilities/logger.c \
	   ./utilities/file_management/csv_handle.c
HDRS = ./entry/list.h \
	   ./entry/contact.h \
	   ./utilities/error_messages.h \
	   ./utilities/logger.h \
	   ./utilities/input/input_handle.h \
	   ./utilities/ui/menu.h \
	   ./utilities/file_management/csv_handle.h \
	   ./utilities/limits.h

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