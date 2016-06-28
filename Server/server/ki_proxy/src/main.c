
#include "platform.h"


int main(int argc, char** argv){

	int32_t optchar;

	while ((optchar = getopt(argc, argv, "Dbc:hi:?")) >= 0)
	{
		switch (optchar){
		case 'c':
			config_file = optarg;
			break;
		case 'D':
#ifdef DEBUG
			set_debug_flag(1);
#else
			printf("WARN: Debugging not enabled.  Ignoring -D.\n");
#endif
			break;
		case 'b':
			c2s_daemon();
			break;
		case 'i':
			cli_id = optarg;
			break;
		case 'h': case '?': default:
			fputs(
				"c2s - jabberd client-to-server connector \n"
				"Usage: c2s <options>\n"
				"Options are:\n"
				"   -c <config>     config file to use [default: ./c2s.xml]\n"
				"   -i id           Override <id> config element\n"
#ifdef DEBUG
				"   -D              Show debug output\n"
#endif
				,
				stdout);
			config_free(c2s->config);
			free(c2s);
			return 1;
		}
	}

}