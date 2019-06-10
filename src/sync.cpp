#include "sync.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <cerrno>

Sync::Sync(const char *name, sem_t *sem):
  ISync(),
  name(name) {
    this->sem = sem;
  }

Sync::~Sync() {
}

ISync* Sync::create(const char *name, int value) {
    sem_t *sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR  | S_IRGRP | S_IWGRP, value);
    Sync* sync = new Sync(name, sem);
    return sync;
}

ISync* Sync::create(const char *name) {
    sem_t *sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR  | S_IRGRP | S_IWGRP, 0);
    Sync* sync = new Sync(name, sem);
    return sync;
}

ISync* Sync::open(const char* name) {
    sem_t *sem = sem_open(name, 0);
    Sync* sync = new Sync(name, sem);
    return sync;
}

void Sync::destroy(const char* name) {
  sem_unlink(name);
}

void Sync::wait() {
  sem_wait(sem);
}

void Sync::signal() {
  sem_post(sem); 
}

void Sync::close() {
  sem_close(sem);
}