TARGET = libft_pthread.so

CC = clang
CFLAGS = -Wall -Wextra -Werror -fPIC

SRCDIR = src
OBJDIR = obj
INCDIR = -I include

SRCS = $(shell find $(SRCDIR) -name '*.c')

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

OBJDIRS = $(sort $(dir $(OBJS)))

all: $(OBJDIRS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -shared -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(OBJDIRS):
	mkdir -p $(OBJDIRS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
