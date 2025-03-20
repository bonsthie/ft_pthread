{
  description = "A Nix Flake that compiles and installs a custom debug-friendly glibc";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs }: 
  let
    supportedSystems = [ "x86_64-linux" ];
    forEachSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
      pkgs = import nixpkgs { inherit system; };
    });
  in {
    packages = forEachSystem ({ pkgs }: {
      glibc-debug = pkgs.stdenv.mkDerivation {
        pname = "glibc-debug";
        version = "2.39";  # Adjust version as needed

        src = pkgs.fetchurl {
          url = "http://ftp.gnu.org/gnu/libc/glibc-2.39.tar.gz";
          sha256 = "0bclvk3vgsp3l9ilkmq8jzcp07m8q6q8jqvg784m9kc8flxlzy4p";
        };

        nativeBuildInputs = with pkgs; [ bison python3Minimal perl texinfo ];  # Required dependencies
        buildInputs = with pkgs; [ gcc binutils ];
        enableParallelBuilding = true;

        # Use these CFLAGS to ensure proper debugging symbols
        CFLAGS = "-Wno-error -O1 -g3";

        configurePhase = ''
          mkdir -p build
          cd build
          ../configure \
            --prefix=$out \
            --disable-sanity-checks \
            --disable-werror \
            --enable-shared \
            --disable-default-pie \
            --disable-static-nss \
            --disable-stack-protector \
            --disable-fortify-source
        '';

        buildPhase = ''
          make -j$(nproc)
        '';

        installPhase = ''
          make install
          # Fix RUNPATH in the dynamic linker
          patchelf --set-rpath "$out/lib" $out/lib/ld-linux-x86-64.so.2

		  # Auto-configure GDB for this glibc
          mkdir -p $out/etc
          echo "add-auto-load-safe-path $out/lib/libthread_db.so.1" > $out/etc/gdbinit
          echo "set libthread-db $out/lib/libthread_db.so.1" >> $out/etc/gdbinit
        '';

        meta = {
          description = "Debug-friendly dynamically compiled glibc";
          license = pkgs.lib.licenses.lgpl2;
        };
      };
    });

devShells = forEachSystem ({ pkgs }: {
      default = pkgs.mkShell {
        buildInputs = [ self.packages.${pkgs.system}.glibc-debug pkgs.gdb ];

        shellHook = ''
          echo "[INFO] Setting up GDB for glibc-debug..."

          # Detect the glibc-debug output path dynamically
          GLIBC_OUT=$(dirname $(realpath $(which gcc)))/..

          if [ -d "$GLIBC_OUT" ]; then
			echo 'set debuginfod enabled on' >> ~/.gdbinit
            echo "[INFO] Found glibc-debug at $GLIBC_OUT"

            # Ensure GDB recognizes the entire glibc output path
            GDBINIT_FILE="$HOME/.gdbinit"

            if ! grep -q "add-auto-load-safe-path $GLIBC_OUT" "$GDBINIT_FILE" 2>/dev/null; then
              echo "add-auto-load-safe-path $GLIBC_OUT" >> "$GDBINIT_FILE"
              echo "set libthread-db $GLIBC_OUT/lib/libthread_db.so.1" >> "$GDBINIT_FILE"
              echo "[INFO] Updated ~/.gdbinit to trust entire $GLIBC_OUT"
            fi
          else
            echo "[ERROR] Could not detect glibc-debug output path!"
          fi
        '';
      };
});
  };
}
