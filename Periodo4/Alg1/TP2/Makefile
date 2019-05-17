CC	:=	gcc
CFLAGS := -g -Wall

TARGET := tp2
SRCEXT := c

SRCDIR := src
OBJDIR := build
INCDIR := include
PROGDIR := program

INC := -I $(INCDIR)/
MAIN := $(PROGDIR)/main.c

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(MAIN) $^ -o $(TARGET) -lm
	$(RM) -r $(OBJDIR)

run_tst_1:
	./$(TARGET) arquivos/dataset_tp2/cidades1.txt
	