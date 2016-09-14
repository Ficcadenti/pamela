#!/bin/tcsh

# check if dispatcher is running
set counter=`pgrep -c dispatcher`;


if ( $counter == 0 ) then
    echo "Dispatcher Server not running...";
else
    echo "Dispatcher Server stopped...";
    set pid_dispa=`/bin/ps -edaf | grep "dispa" | awk '{print $2}' | head -1`
    kill -9 $pid_dispa
endif


# end


