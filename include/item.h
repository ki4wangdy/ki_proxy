
#ifndef _ITEM_H_
#define _ITEM_H_

#include "platform.h"

typedef struct item_st{
	int8_t* router;
	int8_t* dealer;
	void* zmq_ctx;
}*item_t;

item_t item_init(int8_t* router, int8_t* dealer,void* zmq_ctx);
void item_destory(item_t);

int8_t* item_router(item_t);
int8_t* item_dealer(item_t);
int8_t* item_zmq_ctx(item_t);

#endif