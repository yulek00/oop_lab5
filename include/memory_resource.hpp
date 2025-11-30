#pragma once

#include <cstdlib>
#include <memory_resource> 
#include <list>         
#include <cstddef>

class FixedBlockMemory : public std::pmr::memory_resource {
public:
    explicit FixedBlockMemory(size_t total_size);
    ~FixedBlockMemory() override;

    FixedBlockMemory(const FixedBlockMemory&) = delete;
    FixedBlockMemory& operator=(const FixedBlockMemory&) = delete;

private:
    struct BlockInfo {
        void* addr;         
        size_t size;        
        bool is_used;      
    };

    std::list<BlockInfo> m_blocks_info;

    void* m_memory_chunk;
    size_t m_chunk_size;

    void* do_allocate(size_t bytes, size_t alignment) override;

    void do_deallocate(void* p, size_t bytes, size_t alignment) override;

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};