CXX = g++
CXXFLAGS = -std=c++11 -Wall $(shell fltk-config --cxxflags)
LDLIBS = $(shell fltk-config --ldflags)

OBJS = main.o Maze.o Player.o Enemy.o Game.o Block.o Grid.o GameWindow.o AIPlayer.o

mazerunner_gui: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDLIBS)

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o mazerunner_gui mazerunner_gui.exe
