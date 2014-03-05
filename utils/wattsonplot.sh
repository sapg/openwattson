#!/bin/sh
# Shell script that takes NROWS last values from logwattson log file and 
# creates a PNG file with a date-time vs. power plot. 
# Parameters
# - Name of log file (compulsory)
# - Name of PNG file to create (compulsory)
# - Number of rows to include from the end of the file (optional; default is 5000)
# The 'ploticus' package is required for this script to work 
# (do 'sudo apt-get ploticus' or similar if needed). 
#
# Author: Kary Främling, 2010
#

# Verify that we have at least two command line parameters.
if [ $# -lt 2 ]; then
	echo "Usage: ./wattsonplot logfile pngfile [rows to include]"
	exit 0
fi

# Set variable accordingly
logfile=$1
pngfile=$2
if [ $# -eq 3 ]; then
	nrows=$3
else
	nrows=5000
fi

# Do the job
tail -n $nrows $logfile | awk '{ split($0, arr);print arr[2] "." arr[3] " " arr[4];}' > /tmp/wattsonplot.tmp
ploticus -maxrows $nrows -png -o $pngfile -prefab chron data=/tmp/wattsonplot.tmp x=1 y=2 datefmt=yyyy-mmm-dd mode=line unittype=datetime


