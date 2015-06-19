#!/bin/sh
#
# Append date info to specified output file (default: "/tmp/output"),
# and display its content.
#


OUTPUT=${1:-/tmp/output}

# create output file, if not exist...
if [ ! -f "$OUTPUT" ]; then
    touch $OUTPUT
fi


# append date info
date >> $OUTPUT


# display the content of output file
cat $OUTPUT
