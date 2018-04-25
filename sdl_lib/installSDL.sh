export SDL_INSTALL_DIR=$PWD/SDL2-2.0.8

wget https://libsdl.org/release/SDL2-2.0.8.tar.gz
tar -xf SDL2-2.0.8.tar.gz
rm -rf SDL2-2.0.8.tar.gz
cd SDL2-2.0.8
./configure --prefix=$SDL_INSTALL_DIR
make && make install
