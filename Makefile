CXX = g++

CXXFLAGS = -O2 -I./nes

LIBS = nes/nes.a -lSDL

TARGET = nesemu

all:
	$(CXX) main.cpp nes_sound_mgr.cpp $(LIBS) $(CXXFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)