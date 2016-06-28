
#include "item.h"

item_t item_init(int8_t* router, int8_t* dealer,void* zmq_ctx){
	item_t t = calloc(1,sizeof(item_st));
	t->router = router;
	t->dealer = dealer;
	t->zmq_ctx = zmq_ctx;
	return t;
}

void item_destory(item_t t){
	free(t);
}

int8_t* item_router(item_t t){
	assert(t);
	return t->router;
}

int8_t* item_dealer(item_t t){
	assert(t);
	return t->dealer;
}

int8_t* item_zmq_ctx(item_t t){
	assert(t);
	return t->zmq_ctx;
}

