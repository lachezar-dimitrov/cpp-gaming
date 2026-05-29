# cpp-gaming

Small SFML C++ movement/collision prototype.

## Build with CMake

```sh
cmake -S . -B build
cmake --build build
```

## Build Manually

```
clang++ -o sfml_test src/main.cpp -std=c++17 -I/opt/homebrew/Cellar/sfml/3.0.0/include -L/opt/homebrew/Cellar/sfml/3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system
```

## Run

```
./sfml_test
```
