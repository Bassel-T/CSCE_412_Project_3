# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Executable name
EXEC = MitriToubbeh_Project3

# Source files
SRCS = MitriToubbeh_Project3.cpp LoadBalancer.cpp Request.cpp WebServer.cpp

# Header files
HEADERS = LoadBalancer.h Request.h WebServer.h

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(EXEC)

# Rule to link object files into the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)

# Dependencies
MitriToubbeh_Project3.o: MitriToubbeh_Project3.cpp LoadBalancer.h
LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h Request.h WebServer.h
Request.o: Request.cpp Request.h
WebServer.o: WebServer.cpp WebServer.h Request.h

# Phony targets
.PHONY: all clean
