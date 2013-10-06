
GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS = -lm
SOURCES = answer06.c pa06.c
TARGET = pa06
TESTN := $(shell seq 1 5)
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
	@echo ' testing #$* .......'
	@echo '========================================================================='
	./$(TARGET) inputs/0$*-unnormalized.ee264  outputs/0$*-normalized.ppm
#	cat outputs/01-unnormalized.ppm | sort | diff -w expected(copy)/01-normalized.ppm - 
	diff -w outputs/0$*-normalized.ppm expected/0$*-normalized.ppm
	$(VALGRIND) --log-file=outputs/memoutput1 ./$(TARGET) inputs/01-unnormalized.ee264 > /dev/null
	@echo
	@bin/valrgind-checker.sh outputs/memoutput1
	@echo
	@make clean
