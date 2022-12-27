include ../makefile.include

CXX = g++
INCLUDE = $(CATCH_2_INCLUDE)
CXXFLAGS = -g -Os -Wall -Wextra -std=gnu++17 
EXEC = test

.PHONY: src clean all

src:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(EXEC) tests.c

exec:
	@$(EXEC)

clean: 
	@echo ("Initiating lemon pledge . . .");
	del *.o *.exe
	@echo ("I clean . . .");
	
all: src exec