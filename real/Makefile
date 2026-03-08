CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++20
TARGET = rational

SRCS = main.cpp rational.cpp rational_calc.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)