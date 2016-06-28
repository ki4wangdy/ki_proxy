
#include "platform.h"

int main(int argc, char** argv){

	int32_t optchar;

	int8_t* router_ip = NULL;
	int8_t* dealer_ip = NULL;

	while ((optchar = getopt(argc, argv, "br:d:?")) > 0){
		switch (optchar){
			case 'b':
				break;
			case 'r':
				router_ip = (int8_t*)optarg;
				break;
			case 'd':
				dealer_ip = (int8_t*)optarg;
				break;
			case '?':
				fputs("Usage: ki_proxy <options>\n"
					  "options are:\n"
					  "-d daemon fork process to run\n"
					  "-r router bind ip address\n"
					  "-d dealer bind ip address\n"
					  "?  for help\n",
					  stdout);
				return 0;
		}
	}

	// check the router ip and dealer ip
	if (!router_ip || !dealer_ip || strlen(router_ip) == 0 || strlen(dealer_ip) == 0){
		fprintf(stdout, "the router ip or dealer ip is error!, please input it again\n");
		return 0;
	}


}