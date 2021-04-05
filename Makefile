CC=gcc
CFLAGS=-std=c99 -O3 -march=native 
CFLAGS2=-std=c99 -O3 -march=native -lm -Wall

B_DIR=./build

OBS = $(B_DIR)/supportLib.o $(B_DIR)/pbPlots.o $(B_DIR)/plotter.o $(B_DIR)/polynomial.o $(B_DIR)/bisection.o $(B_DIR)/regulaFalsi.o  $(B_DIR)/newtonRaphson.o $(B_DIR)/main.o
OBJS = ./src/plotter.c ./src/bisection.c ./src/regulaFalsi.c ./src/polynomial.c ./src/newtonRaphson.c

$(B_DIR)/plotter: $(OBS)
	$(CC) $(OBS) $(CFLAGS2) -o $@

$(B_DIR)/main.o: main.c
	$(CC) -c main.c $(CFLAGS2) -o $@

$(B_DIR)/bisection.o: src/bisection.c src/bisection.h
	$(CC) -c ./src/bisection.c $(CFLAGS2) -o $@

$(B_DIR)/regulaFalsi.o: src/regulaFalsi.c src/regulaFalsi.h
	$(CC) -c ./src/regulaFalsi.c $(CFLAGS2) -o $@

$(B_DIR)/polynomial.o: src/polynomial.c src/polynomial.h
	$(CC) -c ./src/polynomial.c $(CFLAGS2) -o $@

$(B_DIR)/newtonRaphson.o: src/newtonRaphson.c src/newtonRaphson.h
	$(CC) -c ./src/newtonRaphson.c $(CFLAGS2) -o $@

$(B_DIR)/plotter.o: src/plotter.h src/plotter.c
	$(CC) -c ./src/plotter.c $(CFLAGS2) -o $@

# compiling the pbPlots dependency library
$(B_DIR)/supportLib.o: ./C/supportLib.c ./C/supportLib.h
	$(CC) -c ./C/supportLib.c $(CFLAGS) -o $@

$(B_DIR)/pbPlots.o: ./C/pbPlots.c ./C/pbPlots.h
	$(CC) -c ./C/pbPlots.c $(CFLAGS) -o $@

clean:
	rm $(B_DIR)/*