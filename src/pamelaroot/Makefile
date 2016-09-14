#----------------------------------------------------------------
#
#  Makefile for Mimrec
#
#  Author: Andreas Zoglauer
#
#----------------------------------------------------------------



#----------------------------------------------------------------
# Definitions:
#

PRG       = $(BN)/pamelaroot
MOBJS     = $(LB)/mongodb_test.o
LOBJS     = $(LB)/pamelaroot.o	
SOBJ      = $(LB)/libpamelaroot.$(DLL)

QTDIR = /usr/local/Qt-5.5.1

LIBS += -lshared -lQt5Core -lQt5Gui -lQt5Sql -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_program_options -lboost_system
INCPATH += -I$(QTDIR)/include -I/usr/local/mongo-cxx-driver-v2.4/src
LIBPATH += -L$(QTDIR)/lib -L/usr/local/mongo-cxx-driver-v2.4/build
CFLAGS += `root-config --cflags` 
LDFLAGS += `root-config --glibs`

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
	@$(LD) $(LDFLAGS) $(MOBJS) $(LIBPATH) -lpamelaroot $(LIBS) -o $(PRG)


#
#----------------------------------------------------------------



