/*  openwattson - getpower.c
 *  
 *  Version 0.1
 *  
 *  Just read current power consumption and write it out to stdout
 *  
 *  Copyright 2010, Kary Främling, Jan Nyman
 *  This program is published under the GNU General Public license
 */

#include "rwwattson.h"
 
/********** MAIN PROGRAM ************************************************
 *
 * It takes one parameter which is the config file name with path
 * If this parameter is omitted the program will look at the default paths
 * See the openwattson.conf-dist file for info
 *
 ***********************************************************************/
int main(int argc, char *argv[])
{
	WATTSON wattson;
	struct config_type config;
	int current_generated_power;

	get_configuration(&config, argv[1]);

	wattson = open_wattson(config.serial_device_name);

	/* READ GENERATED CURRENT POWER CONSUMPTION */
	
	current_generated_power = get_current_generated_power_with_retry(wattson);

	// Print out followed by newline and leave

	printf("%d\n", current_generated_power);

	close_wattson(wattson);

	return(0);
}

