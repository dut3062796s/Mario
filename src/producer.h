#ifndef __MARIO_PRODUCER_H_
#define __MARIO_PRODUCER_H_

#include "env.h"
#include "mario_item.h"
#include "status.h"
#include "version.h"

namespace mario {

class Version;

class Producer 
{
public:
#if defined(MARIO_MEMORY)
    Producer(char* pool, int64_t pool_len);
#endif

#if defined(MARIO_MMAP)
    explicit Producer(WritableFile *queue, Version *version);
#endif
    ~Producer();
    Status Produce(const Slice &item);

private:
#if defined(MARIO_MEMORY)
    Status EmitMemoryRecord(RecordType t, const char *ptr, size_t n);
    inline void MovePoint(const char *src, const int64_t distance);
    char* pool_;
    char* origin_;
    int64_t pool_len_;
#endif

#if defined(MARIO_MMAP)
    WritableFile *queue_;
    Status EmitPhysicalRecord(RecordType t, const char *ptr, size_t n);
    Version *version_;
#endif
    int block_offset_;

    // No copying allowed
    Producer(const Producer&);
    void operator=(const Producer&);
};

}

#endif
