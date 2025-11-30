#pragma once

#include <memory_resource>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack {
public:
    explicit Stack(std::size_t cap, std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    ~Stack() noexcept;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    template <typename... Args>
    void push(Args&&... args);

    void pop();
    T& top();
    const T& top() const;

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;

    void clear();


private:
    using alloc_type = std::pmr::polymorphic_allocator<T>;
    alloc_type alloc;
    T* data_;
    std::size_t sz_;
    std::size_t cap_;
};

#include "stack.ipp"