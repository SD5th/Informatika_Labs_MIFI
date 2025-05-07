cd ..
rm -rf build
mkdir build
cp Source/favicon.ico build/favicon.ico
cd build
cmake ..
make 
./GET-Server