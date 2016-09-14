#----------------------------------------------------------------
#
#  Makefile for Pamela
#
#  Author: Raffaele Ficcadenti
#
#----------------------------------------------------------------

#----------------------------------------------------------------
# Definitions:
#
LOBJS = $(LB)/applogger.o \
	$(LB)/configparser.o \
	$(LB)/apidb_pamelaroot.o \
	$(LB)/datetime.o \
	$(LB)/storenode.o \


SOBJ = $(LB)/libshared.$(DLL)

QTDIR = /usr/local/Qt-5.5.1

LIBS += -lQt5Core -lQt5Gui -lQt5Sql 
INCPATH += -I$(QTDIR)/include
LIBPATH += -L$(QTDIR)/lib
CFLAGS += 
LDFLAGS +=

#----------------------------------------------------------------
# Commands:
#

all: $(SOBJ) 

link:
		$(LINK) $(shell pwd)/inc/*.h $(IN)
		$(RM) -f $(IN)/LinkDef.h

clean:
		$(RM) -f src/*~
		$(RM) -f src/\#*
		$(RM) -f inc/*~
		$(RM) -f inc/\#*
		$(RM) -f *~
		$(RM) -f \#*
		$(RM) -f $(LOBJS) $(SOBJ)


#----------------------------------------------------------------
# Dependencies:
#

$(SOBJ): $(LOBJS)
	@echo "Linking $(subst $(LB)/,,$@) ..."
	$(LD) $(LDFLAGS) $(SOFLAGS) $(LIBPATH) $(LOBJS) $(LIBS) -o $(SOBJ)

$(LOBJS): $(LB)/%.o: src/%.cpp inc/%.h
	@echo "Compiling $(subst src/,,$<) ..."
	$(CC) $(CFLAGS) $(LIBPATH) $(INCPATH) $(LIBS) -c $< -o $@


#
#----------------------------------------------------------------



