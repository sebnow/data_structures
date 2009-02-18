OBJ=queue.o
TEST_OBJ=queue_test.o

all: test

test: $(OBJ) $(TEST_OBJ)
	@$(LINK.cc) -o $@ $(OBJ) $(TEST_OBJ)
	@./$@ && echo "Queue tests: Succeeded" || echo "Queue tests: Failed"
	@$(RM) $@

clean:
	$(RM) $(OBJ) $(TEST_OBJ) test

include ../common.mk
