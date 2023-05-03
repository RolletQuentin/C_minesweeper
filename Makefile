CC=gcc
srcdir=./src/
bindir=./bin/
docdir=./doc/
savedir=./save/
PROG=main
FLAGS= -Wall
CFLAGS=
LDFLAGS=
SRC=$(wildcard $(srcdir)*.c)
HEAD=$(wildcard *.h)
OBJ=$(subst $(srcdir), $(bindir), $(SRC:.c=.o))
CURRENT_FOLDER=$(basename $(pwd))
LANGUAGE = English
PROJECT_NAME = TP8-9
CSS = doxygen-awesome.css

# Compilation
all : $(PROG)

$(PROG) : $(OBJ)
	$(CC) $^ -o $(bindir)$@ $(LDFLAGS)

$(bindir)%.o : $(srcdir)%.c $(srcdir)%.h 
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

$(bindir)main.o : $(srcdir)main.c
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

# to use this function even if you have the same filename
.PHONY : clean
.PHONY : all_clean
.PHONY : clean_doc
.PHONY : clean_save
.PHONY : clean_exe
.PHONY : save
.PHONY : restore
.PHONY : give
.PHONY : run
.PHONY : Doxyfile
.PHONY : doc

# clean
all_clean : clean_doc clean clean_save clean_exe

clean :
	rm -f $(bindir)*.o

clean_exe :
	rm -f $(bindir)$(PROG)

clean_save :
	rm -f $(savedir)*

clean_doc :
	rm -rf $(docdir)*

# save & restore
save :
	cp -r $(srcdir)* $(savedir)

restore :
	cp -r $(savedir)* $(srcdir)

# run
run :
	$(bindir)$(PROG)

# documentation

all_doc : Doxyfile doc

Doxyfile :
	doxygen -g
	( echo 'PROJECT_NAME=$(PROJECT_NAME)' ; echo 'HTML_EXTRA_STYLESHEET=$(CSS)' ; echo 'OUTPUT8LANGUAGE=$(LANGUAGE)' ; echo 'OUTPUT_DIRECTORY=$(docdir)' ; echo 'INPUT=$(srcdir)') >> Doxyfile

doc :
	doxygen Doxyfile


give : all_clean
	mkdir $(CURRENT_FOLDER)
	cp Doxyfile ./$(CURRENT_FOLDER)
	cp README.md ./$(CURRENT_FOLDER)
	cp ./doc ./$(CURRENT_FOLDER)
	cp ./src ./$(CURRENT_FOLDER)
	cp ./bin ./$(CURRENT_FOLDER)
	tar -czvf $(CURRENT_FOLDER).tgz $(CURRENT_FOLDER)

