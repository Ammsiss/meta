BINARY = meta
CODEDIRS = . ./src
INCDIRS = . ./include

CC = g++-14
OPT = -O0
DEPFLAGS = -MP -MD
LDFLAGS = -lncurses

CXXFLAGS = -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -pedantic-errors -ggdb -std=c++20 \
$(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CXXFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.cpp))
OBJECTS = $(patsubst %.cpp, ./build/%.o, $(CXXFILES))
DEPFILES = $(patsubst %.cpp, ./build/%.d, $(CXXFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

./build/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) build

-include $(DEPFILES)






