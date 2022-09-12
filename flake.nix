{

  description = "omnet++ setup that works?";
  inputs.nixpkgs.url = github:NixOS/nixpkgs/nixos-22.05;
  inputs.flake-utils.url = github:numtide/flake-utils;
  inputs.nurpkgs.url = github:pschuprikov/nur-packages;
  inputs.nurpkgs.inputs.nixpkgs.follows = "nixpkgs";

  outputs = { self, nixpkgs, flake-utils, nurpkgs }:
    flake-utils.lib.eachDefaultSystem (system:
      let 
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShell = pkgs.mkShell {
          buildInputs = [
            nurpkgs.packages.${system}.omnetpp_5_7
            pkgs.openscenegraph
            pkgs.libGL
            pkgs.clang_12
          ];
        };
      });
}
