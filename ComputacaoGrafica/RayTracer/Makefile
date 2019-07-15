CC	:=	g++
SRCDIR := src
OBJDIR := build
INCDIR := include
PROGDIR := program
EXECNAME := raytracer

MAIN := $(PROGDIR)/main.cpp

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -g -Wall -O3 -std=c++11
INC :=  -I $(INCDIR)/

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INC) -c -o $@ $<

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(MAIN) $^ -o $(EXECNAME)

run:
	./$(EXECNAME)

clean:
	$(RM) -r $(OBJDIR)/* $(OBJDIR)
