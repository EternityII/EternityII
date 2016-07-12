CC=g++
FLAGS=-Wall -std=c++14
SOURCES=$(wildcard *.cpp) $(wildcard */*.h) $(wildcard */*.cpp) $(wildcard */*/*.h) $(wildcard */*/*.cpp) $(wildcard */*/*/*.h) $(wildcard */*/*/*.cpp)
OBJECTS=$(subst .h,.o,$(subst .cpp,.o,$(SOURCES)))

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