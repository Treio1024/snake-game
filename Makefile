run: main.c
	$ rm -rf run
	$ clear
	$ gcc main.c -o run -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
