CXX = g++
CXXFLAGS = -Wall -I../include

SRC = lanzarProcesoPar.cpp enviarMensajeProcesoPar.cpp \
      establecerFuncionDeEscucha.cpp destruirProcesoPar.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = ../lib/libprocesopar.a

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
