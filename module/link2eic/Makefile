#########################
# Part 1: LOCAL DEFINITIONS

       TOP = ../../
     EXTRA =
  WARNINGS = 
  INCLUDES =  -I$(TOP)/src -I.  $(INCLUDE_FLAGS)
       LIB = 

  DEP_LIBS = 
      LIBS = 

      DIRS = 
  MODS_FILE=

#########################
# Part 2: COMMON MAKE PARAMETERS

include $(TOP)/make.proj

#########################
# Part 3: LOCAL SOURCES 

LIB = ../../lib/libeic.a

HEADERS = link2eic.h

SRCS = link2eic.c

OBJS = link2eic.o

#########################
# Part 4: LOCAL TARGETS  

#### scripts

all:: $(OBJS)

install:: $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

clean::
	$(RM) $(OBJS)
clobber::
headers::

#########################
# Part 5: COMMON RULES and 
#     and default Targets

#########################
# Part 6: DEPENDENCIES

