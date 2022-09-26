#{ sources ? import ./nix/sources.nix }:
#with import sources.nixpkgs {
  #overlays = [
  #];
#};
with import /home/atila/Files/Codes/repos/nixpkgs {};

let
  my-python-packages = python-packages: with python-packages; [
    pytorch
    # other python packages you want
  ];
  python-with-my-packages = python3.withPackages my-python-packages;
in
mkShell {
  buildInputs = [
    python-with-my-packages
    halide
    libpng
    libjpeg
    cmake
  ];

  shellHooks = ''
    cd tutorial
  '';
}
