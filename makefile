main: main2.cpp
	g++ main2.cpp data_generator.cpp -Wall -Wextra -o build/main
	./build/main
