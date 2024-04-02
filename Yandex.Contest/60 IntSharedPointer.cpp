#include <iostream>

class IntSharedPointer {
private:
    int* ptr;
    int* count;

public:
    IntSharedPointer(int* p = nullptr) : ptr(p), count(new int(1)) {}

    ~IntSharedPointer() {
        if (ptr && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    IntSharedPointer(const IntSharedPointer& other) : ptr(other.ptr), count(other.count) {
        if (ptr) {
            ++(*count);
        }
    }

    IntSharedPointer& operator=(IntSharedPointer other) {
        swap(*this, other);
        return *this;
    }

    int& operator*() const {
        return *ptr;
    }

    friend void swap(IntSharedPointer& lhs, IntSharedPointer& rhs) noexcept {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.count, rhs.count);
    }
};

void print(IntSharedPointer p) {
    std::cout << *p << std::endl;
}

void print_with_exception(IntSharedPointer p) {
    std::cout << *p << std::endl;
    if (*p % 2) throw std::string("error");
}

int main() {
    IntSharedPointer p(new int);
    std::cin >> *p;
    p = p;
    print(p);

    IntSharedPointer p2(p);
    std::cin >> *p2;
    print(p);
    print(p2);

    {
        int value;
        std::cin >> value;
        IntSharedPointer p3(new int(value));
        p2 = p3;
    }
    print(p2);

    p = p2;
    try {
        print_with_exception(p);
    }
    catch (const std::string& e) {
        std::cout << e << std::endl;
    }
}