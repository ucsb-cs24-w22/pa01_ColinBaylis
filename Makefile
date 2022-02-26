# Makefile
CXX_FLAG = --std=c++11 -g
tests: game
	./game

game: main.o cards.o utility.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
clean: rm -f cards main utility *.o
