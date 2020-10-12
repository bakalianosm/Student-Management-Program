
INCLUDE = include
MODULES = modules
ARGS = -i input1.txt -c configfile.txt
# compiler
CC = gcc 


# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = src/mnstd.o $(MODULES)/hash_table.o  $(MODULES)/inverted_index.o  $(MODULES)/linked_list.o $(MODULES)/common_functions.o 

# Το εκτελέσιμο πρόγραμμα
EXEC = mnstd


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)


valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)