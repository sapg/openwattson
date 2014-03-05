#!/bin/sh
# Shell script that gets the current power reading from the Wattson energy
# meter and creates a simple HTML file for showing it. The name of the file 
# to create is given as the first command line parameter. 
# If the name of an image file (e.g.one produced by 'wattsonplot') is given as 
# the second parameter, then that image is included in the page (if it exists). 
#
# Author: Kary Främling, 2010
#

# Verify that we have a command line parameter; should be name of file to
# create.
if [ $# -lt 1 ]; then
	echo "No output file name given"
	exit 0
fi

# Get power value into variable
pow=`getpower`

# Write everything into file.
echo "<html>

<head>
<title>Kary's Wattson energy meter, Borg&aring;, Finland</title>
<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\">
<META HTTP-EQUIV=\"Expires\" CONTENT=\"Tue, 01 Jan 1980 1:00:00 GMT\">  
<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">  
<META HTTP-EQUIV=\"Refresh\" CONTENT=\"60\">  
</head>

<body bgcolor=\"white\" text=\"black\" link=\"blue\" vlink=\"purple\" alink=\"red\">

<h1 align=\"center\">Kary's Wattson energy meter, Borg&aring;, Finland</h1>
<table border=\"1\" width=\"20%\" align=\"center\">
  <tr>

<td width=\"100%\" height=\"70\" valign=\"top\">
  <center>" > $1

# See if we have image file to include
if [ $# -ge 2 ]; then
	echo "<img src=\"$2\">" >> $1
fi

# Continue with rest
echo "<b>`date`</b>
<br>
Current Power reading: $pow 
			   </center>
</td>
</tr>
</table>
<p align=\"center\">Power readings are updated once per minute</p>

</body>

</html>" >> $1


