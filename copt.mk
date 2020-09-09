################################################################################
# Application defines.
TARGET    	=test_term.out
CC  		=gcc
LINK     	=gcc
OBJ_COPY 	=objcopy
SIZE     	=size
CPP_CHECK	=cppcheck

LIB_PATHS=-L./

################################################################################
# Compiler tools.
BIN_DIR     =$(CPP_DIR)
SHASUM    	="shell shasum -a256 $(TARGET).bin"

################################################################################
# Compiler options.
COPTS+=-DSW_VER=0x100
COMPILER_OPTS=$(COPTS)

################################################################################
# Linker options.
LINKER_OPTS+=-static 
LINKER_OPTS+=$(LIB_PATHS)
