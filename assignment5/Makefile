CXX = g++
CXXFLAGS = -g -std=c++11

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

all: test-rot13cipher test-caesarcipher test-datecipher

ROT13_OBJECTS = test-rot13cipher.o rot13cipher.o ioutils.o
test-rot13cipher: $(ROT13_OBJECTS)
	$(CXX) -o $@ $(ROT13_OBJECTS)

CAESAR_OBJECTS = test-caesarcipher.o caesarcipher.o ioutils.o
test-caesarcipher: $(CAESAR_OBJECTS)
	$(CXX) -o $@ $(CAESAR_OBJECTS)
	
DATE_OBJECTS = test-datecipher.o datecipher.o ioutils.o
test-datecipher: $(DATE_OBJECTS)
	$(CXX) -o $@ $(DATE_OBJECTS)

# Remove all objects and test- programs (TODO: add your own executables)
clean: 
	$(RM) *.o test-rot13cipher test-caesarcipher test-datecipher