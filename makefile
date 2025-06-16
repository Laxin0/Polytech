main: main2.cpp
	g++ main2.cpp data_generator.cpp poly_algs.cpp -Wall -Wextra -o build/main
	./build/main
