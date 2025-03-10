mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	LineTracer.o \
	CalcPID.o \
	Runner.o \
	ColorDetect.o \
	RunDistDetect.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

SRC_DIR = /RasPike/sdk/workspace/run02_R
SRCS = $(SRC_DIR)/main.cpp

# Python インクルードディレクトリへのパスを指定
PYTHON_INCLUDE = /usr/include/python3.9

# Boost インクルードディレクトリ
BOOST_INCLUDE = /usr/include/boost

# コンパイラ
CXX = g++

# コンパイルフラグ
CXXFLAGS = -I$(PYTHON_INCLUDE) -I$(BOOST_INCLUDE) -fPIC -shared

# 出力ファイル
TARGET = main

# ソースファイル
SRCS = $(SRC_DIR)/main.cpp

# ライブラリリンクフラグ
LDFLAGS = -L$(SRC_DIR) -lboost_python39 -lpython3.9 -lrun02_R

# デフォルトターゲット
all: $(TARGET)

# ターゲットのビルドルール
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)


# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit
	

