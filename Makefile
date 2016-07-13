CC=g++
FLAGS=-Wall -std=c++14 -O3
SOURCES=$(shell find . -type f -regex ".*cpp" | tac)
HEADERS=$(shell find * -type f -regex ".*h" | tac)
OBJECTS=$(subst .cpp,.o,$(SOURCES))

main : $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^ $(HEADERS)

make_optimized : $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^ $(HEADERS)

%.o : %.cpp
	$(CC) $(FLAGS) -o $@ -c $<

clean :
	find * -regex ".*\.o" -exec rm {} \;
	rm -f main