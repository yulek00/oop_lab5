#pragma once

#include "stack.hpp"
#include <memory_resource> 
#include <stdexcept>

template <typename T>
Stack<T>::Stack(std::size_t cap, std::pmr::memory_resource* mr)
    : alloc(mr), data_(nullptr), sz_(0), cap_(cap) {
    if (cap_ == 0) { 
        cap_ = 4;
    }

    data_ = alloc.allocate(cap_); 
}

template <typename T>
Stack<T>::~Stack() noexcept {
    clear();
    if (data_) {
        alloc.deallocate(data_, cap_);
    }
}

template <typename T>
template <typename... Args>
void Stack<T>::push(Args&&... args) {
    if (sz_ >= cap_) {
        std::size_t new_cap = cap_ * 2;
        T* new_data = alloc.allocate(new_cap); 
        for (std::size_t i = 0; i < sz_; ++i) {
            alloc.construct(&new_data[i], std::move(data_[i]));
            alloc.destroy(&data_[i]); 
        }
        
        alloc.deallocate(data_, cap_);
        data_ = new_data;
        cap_ = new_cap;
    }
    
    alloc.construct(&data_[sz_], std::forward<Args>(args)...);
    ++sz_;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::underflow_error("Stack is empty");
    }
    alloc.destroy(&data_[sz_]); 
    --sz_;          
}

template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data_[sz_ - 1];
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data_[sz_ - 1];
}

template <typename T>
bool Stack<T>::empty() const noexcept {
    return sz_ == 0;
}

template <typename T>
std::size_t Stack<T>::size() const noexcept {
    return sz_;
}

template <typename T>
std::size_t Stack<T>::capacity() const noexcept {
    return cap_;
}

template <typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}
