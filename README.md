# linker
##commands

gcc test.c -o test -ldl
gcc --shared -fPIC aes.c -o aes.so
export LD_LIBRARY_PATH="."
readelf ./test -a | less
sudo apt install hexedit
gcc --shared -fPIC SOL.c -o ibc.so.6 -ldl
./test
