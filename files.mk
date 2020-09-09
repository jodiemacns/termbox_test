################################################################################
# Source files and includes

################################################################################
# Include directories 
INC_APP+=-I./termbox/src/

################################################################################
# Library paths
LIB_PATHS+=./termbox/src/

################################################################################
# Build Application Specfics
C_APP_SRC=./test.c

C_APP_SRC+=./termbox/src/termbox.c
C_APP_SRC+=./termbox/src/utf8.c

###############################################################################
# Sum up all the options.
INCLUDES+=$(INC_APP)
C_SRCS+=$(C_APP_SRC)
