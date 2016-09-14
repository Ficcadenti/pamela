#!/bin/tcsh

# Pamela Environment
setenv PAMELA_DIR /home/raffo/mongo-test/pamela
setenv PAMELA_RES $PAMELA_DIR/resources

if ! $?LD_LIBRARY_PATH then
    setenv LD_LIBRARY_PATH $PAMELA_DIR/lib
else if $?LD_LIBRARY_PATH then
    setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH\:$PAMELA_DIR/lib
endif
