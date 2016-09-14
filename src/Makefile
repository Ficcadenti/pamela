#----------------------------------------------------------------
#
#  Makefile
#
#  Switches into the subdirectories of the source path
#
#  Author: Raffaele Ficcadenti
#
#----------------------------------------------------------------


#----------------------------------------------------------------
# Commands:
#


shared:
	@$(MAKE) -C shared

dispatcher:
	@$(MAKE) -C dispatcher

pamelaroot:
	@$(MAKE) -C pamelaroot


#------------------------------------------------------------------------------
# All

link:
	$(MAKE) link -C shared
	$(MAKE) link -C dispatcher
	$(MAKE) link -C pamelaroot


all:
	$(MAKE) -C shared
	$(MAKE) -C dispatcher
	$(MAKE) -C pamelaroot


clean:
	$(MAKE) clean -C shared
	$(MAKE) clean -C dispatcher
	$(MAKE) clean -C pamelaroot

	$(RM) -f *~
	$(RM) -f \#*



#
#----------------------------------------------------------------



