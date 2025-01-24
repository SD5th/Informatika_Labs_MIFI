cd ..
rm -rf build/
mkdir build/
cd build
cmake ..
make
cd Tests
make
clear
./Tests

cd ../..
if [ -d "coverage" ]; then
    rm -r coverage
fi

mkdir coverage

gcovr -r . -e CMakeFiles --exclude-unreachable-branches --exclude-throw-branches --html-details -o ./coverage/coverage.html