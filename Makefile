
INCLUDE = include
MODULES = modules
ARGS = tst
# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = src/test.o $(MODULES)/hash_table.o  $(MODULES)/inverted_index.o  $(MODULES)/linked_list.o $(MODULES)/common_functions.o 

# Το εκτελέσιμο πρόγραμμα
EXEC = test


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

input1: $(EXEC)
	./$(EXEC)  $(ARGS)/input1.txt

input2: $(EXEC)
	./$(EXEC)  $(ARGS)/input2.txt

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)