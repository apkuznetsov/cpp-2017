#include <cstddef>

struct Expression;
struct Number;
struct BinaryOperation;

/* Помните иерархию Expression, которую мы разрабатывали на четвёртой неделе?
 * Реализуйте ScopedPtr, который будет работать с указателями на базовый класс Expression.
 * В этом задании вам требуется реализовать методы get, release и reset, операторы * и -> так,
 * как это было описано в предыдущем степе. А также реализуйте конструктор ScopedPtr от указателя на Expression.
 * 
 * Подсказка:
 * в качестве признака того, что ScopedPtr не хранит никакого указателя (после вызова release),
 * используйте нулевой указатель, при этом вы можете явно проверить указатель в деструкторе,
 * но делать это не обязательно, так как delete от нулевого указателя ничего не делает.
 *
 * Требования к реализации:
 * ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно.
 */

struct ScopedPtr {

    explicit ScopedPtr(Expression *ptr = 0) {
        this->ptr = ptr;
    }

    ~ScopedPtr() {
        delete ptr;
    }

    Expression *get() const {
        return ptr;
    }

    Expression *release() {
        Expression *ptr = this->ptr;
        this->ptr = NULL;

        return ptr;
    }

    void reset(Expression *ptr = 0) {
        delete this->ptr;

        this->ptr = ptr;
    }

    Expression &operator*() const {
        return *ptr;
    }

    Expression *operator->() const {
        return ptr;
    }

private:
    ScopedPtr &operator=(const ScopedPtr &other) {}
    ScopedPtr(const ScopedPtr &other) {}
    Expression *ptr;
};
