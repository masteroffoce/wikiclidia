{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gnumake
	pkgs.ncurses
	pkgs.gcc
  ];
}
