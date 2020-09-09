################################################################################
#
################################################################################
TARGET    = bt

#-------------------------------------------------------------------------------
include files.mk
include copt.mk

#-------------------------------------------------------------------------------
OBJS = $(patsubst %.c,%.o,$(wildcard $(C_SRCS)))
ASM_OBJS += $(patsubst %.s,%.o,$(wildcard $(ASM_SRCS)))

#-------------------------------------------------------------------------------
all:  $(ASM_OBJS) $(USER_LIBS) $(TARGET).out secondary-outputs 
chat: all
rtos: all

# ASM Compiling
asm: $(ASM_OBJS)
	@echo $(ASM_OBJS)

# Run deep checking 
check:
	$(CPP_CHECK) $(CPPCHECK_OPTS) $(CPPCHECK_FILES) $(CPPCHECK_INCLUDES)

# Building Documents 
doc:
	doxygen $(TARGET).doxyfile

# Building librarys 
$(USER_LIBS):$(LIBS_DEPS)
	$(MAKE) -C $(dir $@) MCU=$(MCU) CC=$(CC) COMPILER_OPTS=$(COMPILER_OPTS) -f makefile

# Tool invocations
$(TARGET).out: $(OBJS)
	@echo '--------------Building target: $@'
	@echo 'Invoking: Cross ARM GNU C++ Linker'
	$(LINK) -o $(TARGET).out $(OBJS) $(ASM_OBJS) $(LINKER_OPTS) $(USER_LIBS) $(LINKER_POST_OPTS)
	@echo 'Finished building target: $@'
	@echo ' '

# Building C files. 
%.o: %.c
	@echo '-------------- Building C file: $<'
	$(CC) $(INCLUDES) $(COMPILER_OPTS) -c $< -o $@
	@echo ' '

# Each subdirectory must supply rules for building sources it contributes
%.o: %.s
	@echo 'Building asm file: $<'
	$(CC) $(COMPILER_ASM_OPTS) -c -o "$@" "$<"
	@echo ' '

$(TARGET).bin: $(TARGET).out
	$(OBJ_COPY) -O binary "$(TARGET).out"  "$(TARGET).bin"

$(TARGET).hex: $(TARGET).out
	$(OBJ_COPY) -O ihex "$(TARGET).out"  "$(TARGET).hex"



$(TARGET).siz: $(TARGET).out
	$(SIZE) --format=berkeley "$(TARGET).out"

secondary-outputs: $(TARGET).hex $(TARGET).bin $(TARGET).siz

# Cleanig files. 
clean:
	find . -name "*.[od]" -exec rm {} \;
	find . -name "*.map"  -exec rm {} \;
	find . -name "*.lss"  -exec rm {} \;
	find . -name "*.su"  -exec rm {} \;
	rm -f *.hex:
	rm -f *.out
	rm -fr html
	rm -fr latex
