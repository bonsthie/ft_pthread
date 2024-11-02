# Define the target static library
TARGET = libft_pthread.a

CC = clang
CFLAGS = -fPIC -g 

SRCDIR = src
OBJDIR = obj
INCDIR = -I include

# Find all .c source files and generate corresponding .o object files
SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

OBJDIRS = $(sort $(dir $(OBJS)))

# Default rule: Build the library
all: $(OBJDIRS) $(TARGET)

# Build the static library using ar
$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# Create necessary object directories
$(OBJDIRS):
	mkdir -p $(OBJDIRS)

# Clean object files
clean:
	rm -rf $(OBJDIR)

# Clean object files and the library
fclean: clean
	rm -f $(TARGET)

# Rebuild the library
re: fclean all

.PHONY: all clean fclean re
