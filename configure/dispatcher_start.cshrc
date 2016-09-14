#!/bin/tcsh

# check if dispatcher is running
set counter=`pgrep -c dispatcher`;

if ( $counter == 0 ) then
    echo "Starting Dispatcher Server......";
    $PAMELA_DIR/bin/dispatcher > /tmp/null &
else
    echo "Dispatcher Server is running...";
endif


# end


