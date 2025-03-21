#!/bin/bash

set -x

LIBC_DIR_DEFAULT="glibc_debug"
LIBC_DIR="${LIBC_DIR:-$LIBC_DIR_DEFAULT}"

if [ -f .env ]; then
    source .env
fi

LIBC_DIR_ABS="$(realpath "${LIBC_DIR/#\~/$HOME}" 2>/dev/null)"

SCRIPT_PATH=$(pwd)

compile_glibc() {
    if [ -f .env ]; then
        source .env
    fi

    LIBC_DIR_ABS="$(realpath "${LIBC_DIR/#\~/$HOME}" 2>/dev/null)"

    echo "test : $LIBC_DIR_ABS"
    if [ -d "$LIBC_DIR_ABS" ]; then
        echo "libc found at $LIBC_DIR"
        return 0
    fi

    echo "libc will be installed to: $LIBC_DIR"

	if [ ! -d /tmp/glibc_tmp ]; then
		git clone --depth 1 --single-branch --branch master "https://sourceware.org/git/glibc.git" /tmp/glibc_tmp
	fi

	mkdir -p "$LIBC_DIR_ABS"

	patch -p1 -R -d /tmp/glibc_tmp < glibc_patch.diff

    cd /tmp/glibc_tmp || { echo "Failed to enter glibc source directory"; exit 1; }

    mkdir -p build

	cd build

    export CFLAGS="-Wno-error -O0 -g3 -fcf-protection=none"
	export CFLAGS+=" -U_FORTIFY_SOURCE"
    ../configure --prefix="$LIBC_DIR_ABS" \
      --disable-sanity-checks \
      --disable-werror \
      --enable-shared \
      --disable-default-pie \
      --disable-static-nss \
      --disable-stack-protector \
      --disable-fortify-source || { echo "Glibc configure failed"; exit 1; }

    make || { echo "Compilation of glibc failed"; exit 1; }
    make install -j"$(nproc)" || { echo "Installation of glibc failed"; exit 1; }

    cd "$SCRIPT_PATH" || { echo "Failed to return to script directory"; exit 1; }

    rm -rf /tmp/glibc_tmp
}

ask_glibc_path() {
    if [ -d "$LIBC_DIR" ]; then
        echo "Libc Found at $LIBC_DIR"
        return
    fi
    echo "No debug version of libc found."
    echo "Would you like to:"
    echo "1) Change the path to an existing libc"
    echo "2) Set the environment variable LIBC_DIR (current: $LIBC_DIR) to specify where it will be placed?"
    echo -n "Please enter your choice (1 or 2): "
    read -r choice

    case $choice in
        1) 
            echo "Please enter the new path for libc: " 
            read -r new_path
            echo "LIBC_DIR=\"$new_path\"" > .env  # Overwrite and properly quote
            source .env  # Reload changes
            compile_glibc
            ;;
        2) 
            compile_glibc
            ;;
        *) 
            echo "Invalid choice. Please enter 1 or 2."
            ;;
    esac
}

ask_glibc_path
