# Modèle de fichier Makefile, à adapter pour le TP
# Faire une copie de ce fichier, changer le nom pour "makefile" (sans extension .txt!!!) et l'adapter pour votre projet
# >cp makefile_model.txt makefile
# 
# Maintenant pour compiler il suffit d'écrire 
# >make




# options de compilation
CC = g++ 
CCFLAGS = -Wall //
LIBS = 	-lm			# par exemple, -lm rajoute le libm standard
LIBSDIR = 

# fichiers du projet
SRC = util.cpp main.cpp lagrange.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = run.out


# règle initiale
all: $(EXEC)

# dépendance des .h

util.o: util.hpp lagrange.hpp
main.o: util.hpp lagrange.hpp main.cpp
lagrange.o: lagrange.hpp

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	rm -f *.o
mproper:
	rm -f $(EXEC) *.o