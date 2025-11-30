#include "memory_resource.hpp"

#include <stdexcept> 
#include <cstdint>   
#include <cstring>

FixedBlockMemory::FixedBlockMemory(size_t total_size) : m_memory_chunk(nullptr), m_chunk_size(total_size) {
    if (total_size == 0) {
        throw std::invalid_argument("Total size must be greater than zero");
    }

    m_memory_chunk = std::malloc(total_size);

    if (m_memory_chunk == nullptr) {
        throw std::bad_alloc(); 
    }

    m_blocks_info.push_back({
        m_memory_chunk,
        m_chunk_size,
        false
    });
}

FixedBlockMemory::~FixedBlockMemory() {
    std::free(m_memory_chunk);
}

void* FixedBlockMemory::do_allocate(size_t bytes, size_t alignment) {
    for (auto it = m_blocks_info.begin(); it != m_blocks_info.end(); ++it) {
        if (it->is_used) {
            continue;
        }
        uintptr_t base = reinterpret_cast<uintptr_t>(it->addr);
        uintptr_t aligned = (base + alignment - 1) & ~(alignment - 1);
        size_t padding = aligned - base;
        size_t required = bytes + padding;

        if (it->size < required) { 
            continue;
        }

        if (it->size > required) {
            m_blocks_info.insert(std::next(it), {
                reinterpret_cast<char*>(aligned) + bytes,
                it->size - required,
                false
            });
        }

        it->addr = reinterpret_cast<void*>(aligned);
        it->size = bytes;
        it->is_used = true;

        return reinterpret_cast<void*>(aligned);
    }

    throw std::bad_alloc(); 
}

void FixedBlockMemory::do_deallocate(void* p, size_t bytes, size_t alignment) {
    for (auto& block : m_blocks_info) {
        if (block.addr == p && block.is_used) {
            block.is_used = false;
            break;
        }
    }
}

bool FixedBlockMemory::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}