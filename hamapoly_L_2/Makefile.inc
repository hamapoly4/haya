mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += app_Line.o app_Slalom.o app_Block.o Distance.o Direction.o Grid.o Run.o

APPL_CXXOBJS += \
	util.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

# COPTS += -fno-use-cxa-atexit


