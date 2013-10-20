
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS = -lm
SOURCES = answer07.c pa07.c
TARGET = pa07
TESTN := $(shell seq 0 12)
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

#-----------------------------------------------------------------
TESTS := $(addprefix test,${TESTN})

.PHONY : all build clean environment help testall $(TESTS)
.DEFAULT_GOAL := build

OBJF = obj
OBJS = $(patsubst %.c,$(OBJF)/%.o,$(SOURCES))

-include $(SOURCES:%=$(OBJF)/%.P)

all: | build testall
testall: | $(TESTS)
build: $(TARGET)
clean:
	@cd $(CURDIR)
	rm -rf $(TARGET) $(OBJF) outputs
environment:
	@cd $(CURDIR)
	@mkdir -p outputs
	@mkdir -p $(OBJF)

$(TARGET): $(OBJS) | environment
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJF)/%.o: %.c | environment
	@$(GCC) -MM $(CFLAGS) $< | sed 's,^\([^ ]\),$(OBJF)\/\1,g' | sed '$$ s,$$, \\,' > $(OBJF)/$<.P
	$(GCC) $(CFLAGS) -c -o $@ $<

${TESTS}: test%: $(TARGET) | environment
	@echo '========================================================================='
	@echo ' test #$*'
	@echo '========================================================================='
	@echo
	./$(TARGET) inputs/input$*_A inputs/input$*_B > outputs/output$*
	diff -w outputs/output$* expected/expected$* 
	$(VALGRIND) --log-file=outputs/memoutput$* ./$(TARGET) inputs/input$*_A inputs/input$*_B
	@echo
	@bin/valgrind-checker.sh outputs/memoutput$*
	@echo
