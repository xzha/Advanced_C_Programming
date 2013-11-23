GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer10.o pa10.o tree.o
HDRS = pa10.h
TARGET = pa10
TESTN := $(shell seq 1 9)
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

TESTS := $(addprefix test,${TESTN})

.PHONY : all test clean environment help testall $(TESTS)

pa10: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

testall:  | $(TESTS)

${TESTS}: test%: $(TARGET) | environment
	@echo '***************************************'
	@echo 'Shapes:'
	@echo "test$*"
	@echo '***************************************'
	./$(TARGET) shapes $* > debug_files/debug_shape$*
	diff debug_files/debug_shape$* expected/shapes-$*
	$(VALGRIND) --log-file=outputs/memoutput-shape$* ./$(TARGET) shapes $* > /dev/null
	@echo
	@bin/valgrind-checker.sh outputs/memoutput-shape$*
	@echo 
	@echo '***************************************'
	@echo 'Sortable:'
	@echo "test$*"
	@echo '***************************************'
	./$(TARGET) sortable expected/stack-sortable-$* > debug_files/debug_sortable$*
	diff debug_files/debug_sortable$* expected/sort
	$(VALGRIND) --log-file=outputs/memoutput-sortable$* ./$(TARGET) sortable expected/stack-sortable-$* > /dev/null
	@echo
	@bin/valgrind-checker.sh outputs/memoutput-sortable$*
	@echo 
	@echo 
	@echo '***************************************'
	@echo 'Sort:'
	@echo "test$*"
	@echo '***************************************'
	./$(TARGET) sort expected/stack-sortable-$* > debug_files/debug_sort$*
	$(VALGRIND) --log-file=outputs/memoutput-sort$* ./$(TARGET) sort expected/stack-sortable-$* > /dev/null
	@echo
	@bin/valgrind-checker.sh outputs/memoutput-sort$*
	@echo 
	@echo 
	@echo '***************************************'
	@echo 'Unsortable:'
	@echo "test$*"
	@echo '***************************************'
	./$(TARGET) sort expected/stack-unsortable-$* > debug_files/debug_unsortable$*
	diff debug_files/debug_unsortable$* expected/stack-unsortable-$*
	$(VALGRIND) --log-file=outputs/memoutput-unsortable$* ./$(TARGET) sort expected/stack-unsortable-$* > /dev/null
	@echo
	@bin/valgrind-checker.sh outputs/memoutput-unsortable$*
	@echo 

environment:
	@mkdir -p outputs
	@mkdir -p debug_files

.c.o: 
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(TARGET) $(OBJS) outputs/output* outputs/memoutput* debug_files/* 
