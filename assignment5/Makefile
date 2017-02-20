CXX = g++
CXXFLAGS = -g -std=c++11

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

all: test-rot13cipher test-caesarcipher

ROT13_OBJECTS = test-rot13cipher.o rot13cipher.o ioutils.o
test-rot13cipher: $(ROT13_OBJECTS)
	$(CXX) -o $@ $(ROT13_OBJECTS)

## Define your own test-* targets here and then add them to the all: target
## For example, if you implement a Caesar cipher, define test-caesar as follows
## and then change the all: target above to "all: test-rot13cipher test-caesar"
## Do the same for test-date.
CAESAR_OBJECTS = test-caesarcipher.o caesarcipher.o ioutils.o
test-caesarcipher: $(CAESAR_OBJECTS)
	$(CXX) -o $@ $(CAESAR_OBJECTS)

# Remove all objects and test- programs (TODO: add your own executables)
clean: 
	$(RM) *.o test-rot13cipher test-caesarcipher