{
  description = "MLX42 Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      ...
    }@inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            cmake
            gcc
            gnumake
            valgrind
            norminette
            mlx42
            glfw
          ];

          shellHook = ''
            printf "MLX42 development environment loaded!\n"
            trap 'make fclean' EXIT
          '';
        };
      }
    );
}
