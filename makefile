SRCS = \
		main.cpp \
		vsh.cpp \
		winapi.cpp

OBJS = \
		main.o \
		vsh.o \
		winapi.o

SRCDIR = src
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -O2 -I include -std=c++17 -lstdc++fs

vsh: $(OBJS) 
	$(CXX) $^ -o $@

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o *.exe graph_info.json *.mak conanbuildinfo.txt conaninfo.txt

.PHONY: clean
