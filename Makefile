EXE := bouncy-ball

SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./obj
BINDIR = ./bin

CXX := g++
CXXFlags := -Wall -I$(INCDIR)
LDLFlags := -L$(SDL_ROOT)/lib -lSDL2

SRC = $(wildcard $(SRCDIR)/*.cpp)
INC = $(wildcard $(INCDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all
all: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(OBJ)
	$(CXX) $(CXXFlags) -o $@ $(OBJ) $(LDLFlags)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFlags) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(BINDIR)/* $(OBJDIR)/*.o
