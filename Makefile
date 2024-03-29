
INCLUDE = include
MODULES = modules
TEST = tst
CONFIGURE = configs
ARGS = -i $(TEST)/input300000.txt -c $(CONFIGURE)/configfile300000.txt
# compiler
CC = gcc 


# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = src/mnstd.o $(MODULES)/hash_table.o  $(MODULES)/inverted_index.o  $(MODULES)/linked_list.o  $(MODULES)/general_functions.o 

# Το εκτελέσιμο πρόγραμμα
EXEC = mnstd

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	time ./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind ./$(EXEC) $(ARGS)

run_no_args: $(EXEC)
	time ./$(EXEC) 

valgrind_no_args: $(EXEC)
	valgrind ./$(EXEC) 
