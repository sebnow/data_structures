%.o: %.c
	@echo "CC  $<"
	@$(CC) -c -o $@ $(CFLAGS) $<
