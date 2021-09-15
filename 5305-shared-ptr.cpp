#include <cstddef>

struct Expression;
struct Number;
struct BinaryOperation;

/* Реализуйте класс SharedPtr как описано ранее.
 * Задание немного сложнее, чем кажется на первый взгляд.
 * Уделите особое внимание "граничным случаям" —
 * нулевой указатель,
 * присваивание самому себе,
 * вызов reset на нулевом SharedPtr и прочее.
 *
 * Подсказка:
 * возможно, вам понадобится завести вспомогательную структуру.
 * Требования к реализации:
 * ваш код не должен вводить или вводить что-либо,
 * реализовывать функцию main не нужно.
 */

struct CounterPointer {
    CounterPointer(Expression *pointer = NULL) {
        this->pointer = pointer;
        counter = 1;
    }

    ~CounterPointer() {
        delete pointer;
    }

    Expression *pointer;
    mutable int counter;
};

struct SharedPtr {
    explicit SharedPtr(Expression *pointer = 0) {
        if (pointer != 0)
            counterPointer = new CounterPointer(pointer);
        else
            counterPointer = NULL;
    }

    SharedPtr(const SharedPtr &other) {
        this->counterPointer = other.counterPointer;

        if (this->counterPointer != NULL && this->counterPointer->counter)
            ++(this->counterPointer->counter);
    }

    ~SharedPtr() {
        if (counterPointer != NULL) {
            --(counterPointer->counter);
            if (counterPointer->counter == 0)
                delete counterPointer;
        }
    }

    SharedPtr &operator=(const SharedPtr &other) {
        if (this != &other) {
            this->~SharedPtr();

            this->counterPointer = other.counterPointer;
            if (this->counterPointer != NULL)
                ++(this->counterPointer->counter);
        }
    }

    Expression *get() const {
        if (this->counterPointer != NULL)
            return this->counterPointer->pointer;
        else
            return NULL;
    }

    void reset(Expression *pointer = 0) {
        this->~SharedPtr();

        if (pointer != 0)
            counterPointer = new CounterPointer(pointer);
        else
            counterPointer = NULL;
    }

    Expression &operator*() const {
        if (this->counterPointer != NULL)
            return *(this->counterPointer->pointer);
        else
            return *(Expression *) NULL;
    }

    Expression *operator->() const {
        if (this->counterPointer != NULL)
            return this->counterPointer->pointer;
        else
            return NULL;
    }

private:
    CounterPointer *counterPointer = NULL;
};
