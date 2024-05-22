$ROOT=:$(PWD)
git submodule update --init --recursive
cd gui/raylib/raylib/src
git pull
make clean
make PLATFORM=PLATFORM_DESKTOP
cd $ROOT