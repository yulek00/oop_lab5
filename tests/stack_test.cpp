#include <gtest/gtest.h>
#include "stack.hpp"
#include "memory_resource.hpp"

TEST(StackTest, BasicOperations) {
    FixedBlockMemory pool(512);
    Stack<int> stack(2, &pool);
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(10);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);
    
    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);
    
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);
}

TEST(StackTest, AutoResize) {
    FixedBlockMemory pool(256);
    Stack<int> stack(2, &pool); 
    
    stack.push(1);
    stack.push(2);
    EXPECT_EQ(stack.capacity(), 2);
    
    stack.push(3); 
    EXPECT_EQ(stack.capacity(), 4);
    EXPECT_EQ(stack.size(), 3);
}

TEST(StackTest, EmptyStackErrors) {
    FixedBlockMemory pool(128);
    Stack<int> stack(1, &pool);
    
    EXPECT_THROW(stack.pop(), std::underflow_error);
    

    EXPECT_THROW(stack.top(), std::underflow_error);
}


TEST(StackTest, UsesCustomAllocator) {
    FixedBlockMemory pool(100);
    Stack<std::string> stack(1, &pool);
    
    stack.push("Hello");
    stack.push("World");
    
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), "World");
}