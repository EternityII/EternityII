CC=g++
FLAGS=-Wall -std=c++14
SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJECTS=$(subst cpp,o,$(SOURCES))

main : $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

%.o : %.cpp %.h
	$(CC) $(FLAGS) -o $@ -c $^

%.o : %.cpp
	$(CC) $(FLAGS) -o $@ -c $<

%.o : %.h
	$(CC) $(FLAGS) -o $@ -c $<

clean :
	rm -f *~ **/*.o main
	rm -f *~ *.o main