
#include "platform.h"

static void print_help(){
	fputs("Usage: ki_proxy <options>\n"
		"options are:\n"
		"-d daemon fork process to run\n"
		"-r router bind ip address\n"
		"-d dealer bind ip address\n"
		"-n n router bind ip address\n"
		"-m m dealer bind ip address\n"
		"?  for help\n",
		stdout);
}

static void* pthread_run(void* arg){
	
	item_t t = (item_t)arg;

	int8_t* router = item_router(t);
	int8_t* dealer = item_dealer(t);
	void* zmq_ctx = item_zmq_ctx(t);

	void* reouter_socket = zmq_socket (zmq_ctx,ZMQ_ROUTER);
	int s = zmq_bind(reouter_socket,router);
	assert(s == 0);
	
	void* dealer_socket = zmq_socket(zmq_ctx,ZMQ_DEALER);
	int m = zmq_bind(dealer_socket,dealer);
	assert(m == 0);

	zmq_proxy(reouter_socket,dealer_socket,NULL);

	zmq_close (reouter_socket);
	zmq_close (dealer_socket);
	item_destory(t);

	pthread_detach(pthread_self());
	return NULL;
}

int main(int argc, char** argv){

	pthread_t t;
	int32_t is_fork = false;
	int32_t optchar;

	int8_t* router_ip = NULL;
	int8_t* dealer_ip = NULL;
	int8_t* n_router_ip = NULL;
	int8_t* m_dealer_ip = NULL;

	while ((optchar = getopt(argc, argv, "br:d:n:m:?")) > 0){
		switch (optchar){
			case 'b':
				is_fork = true;
				break;
			case 'r':
				router_ip = (int8_t*)optarg;
				break;
			case 'd':
				dealer_ip = (int8_t*)optarg;
				break;
			case 'n':
				n_router_ip = (int8_t*)optarg;
				break;
			case 'm':
				m_dealer_ip = (int8_t*)optarg;
				break;
			case '?':
				print_help();
				return 0;
		}
	}

	// check the router ip and dealer ip
	if (!router_ip || !dealer_ip || strlen(router_ip) == 0 || strlen(dealer_ip) == 0){
		print_help();
		fprintf(stdout, "the router ip or dealer ip is error!, please input it again\n");
		return 0;
	}

	if (!n_router_ip || !m_dealer_ip || strlen(n_router_ip) == 0 || strlen(n_dealer_ip) == 0){
		print_help();
		fprintf(stdout, "the n router ip or m dealer ip is error!, please input it again\n");
		return 0;
	}

	// fork the process
	if (is_fork){
		int s = init_daemon();
		assert(s == 1);
	}

	void* zmq_ctx = zmq_ctx_new();

	// init the input thread to start
	item_t item = item_init(router_ip,dealer_ip,zmq_ctx);
	int8_t result = pthread_create(&t,NULL,pthread_run,item);
	assert(result == 0);

	// init the output thread to start
	item_t item = item_init(n_router_ip,m_dealer_ip,zmq_ctx);
	result = item_init(n_router_ip,m_dealer_ip,zmq_ctx);
	assert(result == 0);

	while(1);
	zmq_ctx_destroy(zmq_ctx);

	return 0;

}