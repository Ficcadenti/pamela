#----------------------------------------------------------------
#
#  Makefile for dispatcher
#
#  Author: Raffaele Ficcadenti
#
#----------------------------------------------------------------



#----------------------------------------------------------------
# Definitions:
#

PRG       = $(BN)/dispatcher
MOBJS     = $(LB)/apidb_dispatcher.o
LOBJS     = $(LB)/dispatcher.o	
SOBJ      = $(LB)/libdispatcher.$(DLL)

QTDIR = /usr/local/Qt-5.5.1

LIBS += -lshared -lQt5Core -lQt5Gui -lQt5Sql 
INCPATH += -I$(QTDIR)/include
LIBPATH += -L$(QTDIR)/lib
CFLAGS += 
LDFLAGS +=

#----------------------------------------------------------------
# Commands:
#

all: $(PRG)

lib: $(SOBJ)

link:
	@$(LINK) $(shell pwd)/inc/*.h $(IN)
	@rm -f $(IN)/LinkDef.h

clean:
	@rm -f src/*~
	@rm -f src/\#*
	@rm -f inc/*~
	@rm -f inc/\#*
	@rm -f *~
	@rm -f \#*
	@rm -f $(PRG)
	@rm -f $(MOBJS) $(LOBJS) $(SOBJ) $(PRG)

#----------------------------------------------------------------
# Dependencies:
#


$(SOBJ): $(LOBJS)
	@echo "Linking $(subst $(LB)/,,$@) ..."
	@$(LD) $(LDFLAGS) $(SOFLAGS) $(LIBPATH) $(LOBJS) $(LIBS) -o $(SOBJ)


$(MOBJS): $(LB)/%.o: src/%.cpp inc/%.h
	@echo "Compiling $(subst src/,,$<) ..."
	@$(CC) $(CFLAGS) $(LIBPATH) $(INCPATH) -c $< -o $@

$(LOBJS): $(LB)/%.o: src/%.cpp inc/%.h
	@echo "Compiling $(subst src/,,$<) ..."
	@$(CC) $(CFLAGS) $(LIBPATH) $(INCPATH) -c $< -o $@

$(PRG): $(SOBJ) $(MOBJS)
	@echo "Linking $(subst $(BN)/,,$@) ..."
	@$(LD) $(LDFLAGS) $(MOBJS) $(LIBPATH) -ldispatcher $(LIBS) -o $(PRG)


#
#----------------------------------------------------------------



