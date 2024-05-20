{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    cs-flake = {
      url = "github:Sigmapitech/cs";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-utils.follows = "flake-utils";
      };
    };

    pre-commit-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-utils.follows = "flake-utils";
      };
    };
  };

  outputs = { self, pre-commit-hooks, nixpkgs, flake-utils, cs-flake }:
    flake-utils.lib.eachSystem [ "x86_64-linux" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        cs = cs-flake.packages.${system}.report;
        cs-wrapped = (pkgs.writeShellScriptBin "cs" ''
          ${cs}/bin/cs .
        '');

      in
      {
        formatter = pkgs.nixpkgs-fmt;

        checks =
          let
            hooks = {
              nixpkgs-fmt = {
                enable = true;
                name = pkgs.lib.mkForce "Nix files format";
              };

              cs-check = {
                enable = true;
                name = "Coding style";
                entry = "${cs-wrapped}/bin/cs";
                files = "\\.*";
              };
            };
          in
          {
            pre-commit-check = pre-commit-hooks.lib.${system}.run {
              inherit hooks;
              src = ./.;
            };
          };

        devShells.default = pkgs.mkShell {
          hardeningDisable = [ "format" "fortify" ];
          packages = with pkgs; [
            criterion
            gcc13
            libuuid
            gnumake
            # compile_commands.json
            python3Packages.compiledb
            # colors in makefile
            ncurses
            # coding style
            cs-wrapped

            # python compilation, AI
            python311Packages.cython_3
          ];

          shellHook = ''
            ${self.checks.${system}.pre-commit-check.shellHook}
          '';
        };

        packages =
          let
            build-zappy = { name, bins }:
              pkgs.stdenv.mkDerivation {
                inherit name;
                src = self;

                buildInputs = with pkgs; [
                  libuuid
                  gnumake
                ];

                enableParralelBuilding = true;
                buildPhase = ''
                  make $name
                '';

                installPhase = ''
                  mkdir -p $out/bin
                  cp ${pkgs.lib.strings.concatStringsSep " " bins} $out/bin
                '';

                meta.mainProgram = builtins.head bins;
              };
          in
          {
            default = build-zappy {
              name = "all";
              bins = [ "zappy_ai" "zappy_server" "zappy_gui" ];
            };

            zappy_server = build-zappy rec {
              name = "zappy_server";
              bins = [ name ];
            };

            zappy_gui = build-zappy rec {
              name = "zappy_gui";
              bins = [ name ];
            };

            zappy_ai = build-zappy rec {
              name = "zappy_ai";
              bins = [ name ];
            };
          };
      });
}
