{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          name = "math-dsp";

          packages = with pkgs; [
            (python3.withPackages (
              ps: with ps; [
                numpy
                sympy
                scipy
                matplotlib
              ]
            ))
            basedpyright
            ruff

            gcc
            clang-tools
            lldb

            cmake
            neocmakelsp

            texliveFull
            texlab
          ];
        };
      }
    );
}
