#ifndef _HELPER_H_20160105_
#define _HELPER_H_20160105_

#include <pthread.h>

//
// thread helper micro
//
#define THREAD_OBJECT(pt)				pthread_t pt = 0;
#define THREAD_PROC(proc,context)		void* proc(void* context)
#define THREAD_CREATE(pt,proc,context)	(0 == pthread_create(&pt, NULL, proc, (void*)context))
#define THREAD_CLOSE(pt)				if(0!=pt) {void* pt_rtn = NULL; pthread_join(pt, &pt_rtn); pthread_detach(pt);}


#endif // _HELPER_H_20160105_

