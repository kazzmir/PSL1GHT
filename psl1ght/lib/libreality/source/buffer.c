#include <rsx/buffer.h>
#include <assert.h>

int checkCommandBufferLength(gcmContextData *context, uint32_t len) {
	if (context->current + len > context->end) {
		int retval; // It's a bit messy, but it works.
		int tocval = ((uint32_t *)(uint64_t) context->callback)[1];
		int procaddr = ((uint32_t *)(uint64_t) context->callback)[0];
		asm("mr 3,%3; mr 31,2; mr 2,%1; mtctr %2; bctrl; mr 2,31; mr %0,3;" : "=r"(retval) : "r"(tocval), "r"(procaddr), "r"(context) : "r31", "r3");
		return retval;
	}
	return 0;
}

void commandBufferPut(gcmContextData* context, uint32_t value) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	 *buffer++ = value;
	context->current = (uint32_t)(uint64_t) buffer;
}

