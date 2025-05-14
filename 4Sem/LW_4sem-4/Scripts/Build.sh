cd ..
rm -rf build
mkdir build
cd build
cmake ..
make 
rm ../HTTP-Server
cp Main ../HTTP-Server