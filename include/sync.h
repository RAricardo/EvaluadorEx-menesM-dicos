#pragma once
#include "isync.h"

class Sync : public ISync {

    private:
        const char *name;
        sem_t *sem;
    public:
        Sync(const char *name, sem_t *sem);
        ~Sync();
        static ISync* create(const char* name, int value);
        static ISync* create(const char* name);
        static ISync* open(const char *name);
        static void destroy(const char *name);
        void wait();
        void signal();
        void close();
};
