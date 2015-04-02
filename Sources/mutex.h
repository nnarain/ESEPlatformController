
#ifndef MUTEX_H
#define MUTEX_H

typedef volatile unsigned char Mutex;

#define MUTEX_LOCK  (mutex) mutex = 1
#define MUTEX_UNLOCK(mutex) mutex = 0

#pragma INLINE
void mutex_lock(Mutex* m)
{
    *m = 0;
}

#pragma INLINE
void mutex_unlock(Mutex* m)
{
    *m = 1;
}

#pragma INLINE
void mutex_wait(Mutex* m)
{
    while(!*m);
    *m = 0;
}

#pragma INLINE
void mutex_signal(Mutex* m)
{
    *m = 1;
}

#endif
