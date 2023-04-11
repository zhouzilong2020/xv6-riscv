// Reader Writer locks

#include "types.h"
//
#include "riscv.h"
//
#include "defs.h"
//
#include "param.h"
//
#include "memlayout.h"
//
#include "spinlock.h"
//
#include "proc.h"
//
#include "spinlock.h"
//
#include "rwlock.h"

void initRWlock(struct rwlock *lk, char *name) {
  char buf[32];
  safestrcpy(buf, name, strlen(name));
  safestrcpy(buf + strlen(name), "-global", strlen(name));
  initlock(&lk->global, buf);

  safestrcpy(buf + strlen(name), "-read", strlen(name));
  initlock(&lk->read, name);

  lk->reader = 0;
}

void acquireRW_R(struct rwlock *lk) {
  acquire(&lk->read);
  lk->reader++;
  if (lk->reader == 1) acquire(&lk->read);
  release(&lk->read);
}

void releaseRW_R(struct rwlock *lk) {
  acquire(&lk->read);
  lk->reader--;
  if (lk->reader == 0) release(&lk->read);
  release(&lk->read);
}

void acquireRW_W(struct rwlock *lk) { acquire(&lk->global); }

void releaseRW_W(struct rwlock *lk) { release(&lk->global); }
