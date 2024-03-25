LIB_ROOT = ../pacs-examples/Examples

CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I${LIB_ROOT}/include

EXEC = main
LDFLAGS ?= -L${LIB_ROOT}/lib

all: $(EXEC)

%.o: %.cpp 
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC): %: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

clean:
	$(RM) *.o $(EXEC)

distclean: clean
	$(RM) *~