.PHONY: all
all:
	@gcc -c main.cpp AlphaBlending.cpp -mavx2 -O3
	@g++ main.o AlphaBlending.o -o AlphaBlending -lsfml-graphics -lsfml-window -lsfml-system

nosimd:
	@gcc -c main.cpp AlphaBlendingNoSIMD.cpp -mno-sse2 -O3
	@g++ main.o AlphaBlendingNoSIMD.o -o AlphaBlending -lsfml-graphics -lsfml-window -lsfml-system