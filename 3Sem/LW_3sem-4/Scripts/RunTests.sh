cd ..
rm -rf build/
mkdir build/
cd build
cmake ..
clear
make
cd Tests
make
./Tests
