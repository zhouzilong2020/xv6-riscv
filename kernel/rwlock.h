// Mutual exclusion lock.
struct rwlock {
  struct spinlock global, read;
  uint reader;  // the number of readers
};
