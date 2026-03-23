{
  description = "Embedded MCU development environment with Nix";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          vscode
          cmake
          ninja
          gcc-arm-embedded
          openocd
          clang-tools
          gnumake
          git
          pkg-config
        ];

        shellHook = ''
          echo "Embedded dev shell is ready."
          echo "Tools:"
          echo "  code      -> $(command -v code || echo not-found)"
          echo "  cmake     -> $(command -v cmake || echo not-found)"
          echo "  ninja     -> $(command -v ninja || echo not-found)"
          echo "  arm-none-eabi-gcc -> $(command -v arm-none-eabi-gcc || echo not-found)"
          echo "  openocd   -> $(command -v openocd || echo not-found)"
          echo "  clangd    -> $(command -v clangd || echo not-found)"
        '';
      };
    };
}
