OBJ_FILES := $(patsubst %.c, $(BUILD_DIR)/%.o, $(CFILES)) $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPPFILES))

# Default target
all: $(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/%.o: %.c
	@printf "  CC\t$<\n"
	@mkdir -p $(dir $@)
	@$(Q)$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: %.cpp
	@printf "  CXX\t$<\n"
	@mkdir -p $(dir $@)
	@$(Q)$(CXX) $(CXXFLAGS) -o $@ -c $<

# Linking the final executable
$(BUILD_DIR)/$(PROJECT_NAME): $(OBJ_FILES)
	@printf "  LD\t$@\n"
	@mkdir -p $(BUILD_DIR)
	@$(Q)$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

run: $(BUILD_DIR)/$(PROJECT_NAME)
	@printf "Running $(PROJECT_NAME)...\n"
	sudo $(BUILD_DIR)/$(PROJECT_NAME)

# Clean up build directory
clean:
	@printf "Cleaning up build directory...\n"
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
