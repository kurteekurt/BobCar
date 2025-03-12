$(BUILD_DIR)/src/waveshare/DEV_Config.o: src/waveshare/DEV_Config.c
	@printf "  CC\t$<\n"
	@mkdir -p $(dir $@)
	@$(Q)$(CC) $(filter-out -Wall -Wextra, $(CFLAGS)) -w -o $@ -c $<

LDFLAGS += -lm
CFLAGS += -D USE_DEV_LIB