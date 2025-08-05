{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gnumake
	pkgs.ncurses
	pkgs.gcc
	pkgs.curl
	pkgs.cjson
	pkgs.libxml2.dev
	pkgs.pkg-config
  ];
}
