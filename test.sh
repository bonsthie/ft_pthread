echo "compiling libft_pthread"
make || { echo "libft_pthread compilation failed"; exit 1; }

if [ -z "$LIBC_DIR_ABS" ]; then
    echo "Error: LIBC_DIR_ABS is empty. Check the LIBC_DIR path."
    exit 1
fi

echo "compiling test"
clang -nostdlib -static -g \
  -I"$LIBC_DIR_ABS/include" \
  -Iinclude \
  "$LIBC_DIR_ABS/lib/crt1.o" \
  "$LIBC_DIR_ABS/lib/crti.o" \
  test.c \
  libft_pthread.a \
  "$LIBC_DIR_ABS/lib/crtn.o" \
  -L"$LIBC_DIR_ABS/lib" \
  -Wl,--rpath="$LIBC_DIR_ABS/lib" \
  -Wl,--dynamic-linker="$LIBC_DIR_ABS/lib/ld-linux-x86-64.so.2" \
  -lpthread -lc -lquadmath -lgcc_eh -lgcc -ldl \
  -o test.out
