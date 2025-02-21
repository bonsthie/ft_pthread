echo "compiling libft_pthread"
make

echo "compiling test"
clang -nostdlib -static -g \
  -Iglibc_debug/include \
  -Iinclude \
  glibc_debug/lib/crt1.o \
  glibc_debug/lib/crti.o \
  test.c \
  libft_pthread.a \
  glibc_debug/lib/crtn.o \
  -Lglibc_debug/lib \
  -Wl,--rpath=glibc_debug/lib \
  -Wl,--dynamic-linker=glibc_debug/lib/ld-linux-x86-64.so.2 \
  -lc -lquadmath -lgcc_eh -lgcc -ldl \
  -o test.out
