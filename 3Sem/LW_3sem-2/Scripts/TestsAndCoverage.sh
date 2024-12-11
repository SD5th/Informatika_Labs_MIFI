cd ../build/Tests
clear
make
./Tests

cd ../..
if [ -d "coverage" ]; then
    rm -r coverage
fi

mkdir coverage

gcovr -r . -e CMakeFiles --exclude-unreachable-branches --exclude-throw-branches --html-details -o ./coverage/coverage.html