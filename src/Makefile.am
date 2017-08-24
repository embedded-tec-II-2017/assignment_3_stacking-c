bin_PROGRAMS = stacking_c

stacking_c_CFLAGS = -g -Wall -Werror -O2

stacking_c_SOURCES = test_main.c stacking_c.c utils.c

include_HEADERS = stacking_c.h utils.h

stacking_c_CFLAGS += $(LIBTIFF_CFLAGS)

stacking_c_LDADD   = $(LIBTIFF_LIBS)
