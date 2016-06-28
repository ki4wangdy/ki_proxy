
#include "platform.h"

int main(int argc, char** argv){

	int32_t optchar;

	while ((optchar = getopt(argc, argv, "br:d:?")) > 0){
		switch (optchar){
			case 'b':
				break;
			case 'r':
				break;
			case 'd':
				break;
			case '?':
				fputs("Usage: ki_proxy <options>\n"
					  "options are:\n"
					  "-d daemon fork process to run\n"
					  "-r router bind ip address\n"
					  "-d dealer bind ip address\n"
					  "?  for help\n",
					  stdout);
				break;
		}
	}
}