#!/bin/bash


BASE_DIR=glibc_base
PATCH_DIR=glibc_patch
PATCH_FILE=glibc_patch.diff

# List of files to diff (relative to BASE_DIR and PATCH_DIR)
FILES=$(cat file_list.txt)

# Start empty patch file
> "$PATCH_FILE"

# Diff only those files
for f in $FILES; do
    if [ -f "$BASE_DIR/$f" ] && [ -f "$PATCH_DIR/$f" ]; then
        diff -u "$BASE_DIR/$f" "$PATCH_DIR/$f" >> "$PATCH_FILE"
    fi
done

echo "✅ Patch created: $PATCH_FILE"

rm -rf $LIBC_DIR
nix-shell -p bison gcc --run "sh glibc_debug.sh" || exit 1
sh test.sh

