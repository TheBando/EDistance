CC = g++

CFLAGS =
LFLAGS = -lsfml-system
OBJ = $(TARGET).o
DEPS =
LIBS =
TARGET = EDistance

all:$(TARGET)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) $(LFLAGS) $(CFLAGS)

$(OBJ): $(TARGET).cpp
	g++ -c $(TARGET).cpp

clean:
	rm $(OBJ)