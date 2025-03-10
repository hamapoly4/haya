mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	LineTracer.o \
	CalcPID.o \
	Runner.o \
	ColorDetect.o \
	RunDistDetect.o 

	

SRCLANG := c++



ifdef CONFIG_EV3RT_APPLICATION


# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_LIBS += -I/usr/include/opencv4
APPL_LIBS += `pkg-config --cflags --libs opencv4`

PYTHON_INCLUDE = /usr/include/python3.9
PYTHON_LIB = /usr/lib/x86_64-linux-gnu

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit



INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit \
	-I/usr/include/opencv4 \
	-I/usr/include/python3.9 \
