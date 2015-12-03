# MAKE FILE

RM:= rm
CC:= gcc
CFLAGS := -Wall -g

OBJETOS = main.o

all : Subs_Cliente

Subs_Cliente : $(OBJETOS)
	$(CC) $(CFLAGS) $(OBJETOS) -o $@ -pthread
	@echo 'Creación exitosa'


# Reglas Generales

%.o : ../src/%.c
	$(CC) -c $(DEFS) $(CFLAGS) $< -o $@

.PHONY: all clean

clean : 
	$(RM) Subs_Cliente $(OBJETOS)

