
CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++
MV = mv -f
RM = rm -rf
LN = ln -sf

DEBUG = 
#WALL=-Wall -Waggregate-return -Wmissing-declarations  -Wmissing-prototypes -Wredundant-decls -Wshadow -Wstrict-prototypes -Winline 
#CFLAGS = $(DEBUG) -Wall -c
CFLAGS = $(DEBUG) 
#SVN_REVISION = $(shell svn info |grep Revision|awk '{print $$2}') 
REVISION = $(shell git rev-parse HEAD)
CFLAGS  += -DREVISION="\"$(REVISION)"\"

TARGET = json.cgi
 
TOP_PATH = $(shell pwd)
SRC_PATH = $(TOP_PATH)

#LIBS_DIR = $(subst cgi,libs,$(TOP_PATH))

LIB_PATH = $(TOP_PATH)/libs/cJSON
LIB_INC_PATH = $(TOP_PATH)/libs/cJSON
LIB_FLAG=-static -lcjson
#find -maxdepth 3 -mindepth 1 -type d | grep -v .git |grep -v .
DIRS = $(shell find $(SRC_PATH) -maxdepth 0 -mindepth 0 -type d | grep -v .git )
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))


##########################################################
# srcs
##########################################################
#SRCS_CPP += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
#SRCS_CC += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cc))
SRCS_C += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
 
##########################################################
# objs
##########################################################
#OBJS_CPP = $(patsubst %.cpp, %.o, $(SRCS_CPP))
#OBJS_CC = $(patsubst %.cc, %.o, $(SRCS_CC))
OBJS_C = $(patsubst %.c, %.o, $(SRCS_C))
 
##########################################################
# paths
##########################################################
INC_PATH += -I$(LIB_INC_PATH)
INC_PATH += -I$(SRC_PATH)

LD_LIB += -L$(LIB_PATH)

##########################################################
# libs
##########################################################
# libs:
# 	@echo "making libs"
# 	make -C $(LIB_PATH)
##########################################################
# building
##########################################################
all :$(TARGET)

$(TARGET) : $(OBJS_C)
	@ $(CC) $^ -o $@ $(LD_LIB) $(LIB_FLAG)
#	@ echo libs_dir: $(LIBS_DIR)
	@ echo Create $(TARGET) ok...

$(OBJS_C):%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INC_PATH)

.PHONY : clean
clean:
	@ $(RM) $(TARGET) $(OBJS_C)

libs_clean:
# 	make -C $(LIB_PATH) clean