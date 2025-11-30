#include "stack.hpp"
#include "memory_resource.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "Введите размер памяти (в байтах)";
    std::size_t pool_size;
    std::cin >> pool_size;

    FixedBlockMemory pool(pool_size);
    Stack<std::string> stack(2, &pool);

    std::cout << "\nСтек создан. Добавим несколько элементов...\n";

    stack.push("Hello");
    stack.push("Artem");
    stack.push("Yadroff");
    
    std::cout << "Добавлено 3 элемента\n";
    std::cout << "Размер стека: " << stack.size() << "\n";
    std::cout << "Вместимость: " << stack.capacity() << "\n";
    std::cout << "Верхний элемент: " << stack.top() << "\n\n";

    std::cout << "Удаляем 2 элемента...\n";
    stack.pop();
    stack.pop();

    std::cout << "После удаления:\n";
    std::cout << "Размер стека: " << stack.size() << "\n";
    std::cout << "Верхний элемент: " << stack.top() << "\n\n";

    if (stack.empty()) {
        std::cout << "Стек пуст!\n";
    } else {
        std::cout << "Стек содержит " << stack.size() << " элемент(а/ов)\n";
    }
    
    std::cout << "\nОчищаем стек...\n";
    stack.clear();
    std::cout << "Стек очищен\n";
    std::cout << "Размер: " << stack.size() << "\n";
    std::cout << "Пустой: " << std::boolalpha << stack.empty() << "\n";
    
    std::cout << "\nПрограмма завершена успешно!\n";
    return 0;
}