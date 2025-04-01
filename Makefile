TARGET = libft_pthread.so

CC = clang
CFLAGS = -Wall -Wextra -Werror -fPIC -g

ifeq ($(VERBOSE), true)
	CFLAGS	+=	-D VERBOSE
endif

SRCDIR = src
OBJDIR = obj
INCDIR = -I include

# Find all .c and .s source files and generate corresponding .o object files
SRCS = $(shell find $(SRCDIR) -name '*.c')
SRCS_ASM = $(shell find $(SRCDIR) -name '*.S')
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%.o, $(SRCS_ASM))

OBJDIRS = $(sort $(dir $(OBJS)))

# Default rule: Build the library
all: $(OBJDIRS) $(TARGET)

# Rule to build shared library
$(TARGET): $(OBJS)
	$(CC) -shared -o $@ $(OBJS)

# Compile C source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# Compile ASM source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(CC) -c $< -o $@

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
