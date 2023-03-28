#include <iostream>
#include <utility>

class Toy
{
private:
    std::string name;
public:
    explicit Toy(std::string inName) : name(inName) {}
    Toy() : name("someToy") {}
    void setName(std::string inName)
    {
        name = (inName);
    }
};

template <class T>
class Shared_ptr_toy
{
private:
    T* pointer = nullptr;
    int* count = nullptr;

public:
    //default constructor
    Shared_ptr_toy() = default;;
    explicit Shared_ptr_toy(std::string inName)
    {
        pointer = new T(inName);
        count = new int(1);
    }

    //copy constructor
    Shared_ptr_toy(const Shared_ptr_toy &another)
    {
        pointer = another.pointer;
        count = another.count;
        ++* count;
    }

    //overload constructor
    Shared_ptr_toy& operator =  (const Shared_ptr_toy& another)
    {
        //check
        if (pointer == another.pointer){
            if (*count == 1) {
                delete pointer;
                delete count;
            } else {
                --* count;
            }
        }

        count = another.count;
        ++* count;
        pointer = another.pointer;
        return *this;
    }

    //destructor
    ~Shared_ptr_toy()
    {
        if (*count == 1) {
            delete count;
            delete pointer;
        }
        else {
            --* count;
        }
    }
    friend Shared_ptr_toy<T> make_shared_toy(std::string inName);
};

template <class T>
Shared_ptr_toy<T> make_shared_toy(std::string inName)
{
    return Shared_ptr_toy<T>(inName);
}

template <class T>
Shared_ptr_toy<T> make_shared_toy(Shared_ptr_toy<T> &another)
{
    return Shared_ptr_toy<T>(another);
}

int main()
{
    {
        Shared_ptr_toy<Toy> toy1;
        Shared_ptr_toy<Toy> toy2("Stick");
        toy1 = toy2;
        Shared_ptr_toy<Toy> toy3("Bone");
        Shared_ptr_toy<Toy> toy4(toy3);
        toy3 = toy2;
        Shared_ptr_toy<Toy> toy5(toy3);
    }

    Shared_ptr_toy<Toy> toy1 = make_shared_toy<Toy>("Bone");
    Shared_ptr_toy<Toy> toy2 = make_shared_toy<Toy>(toy1);
    Shared_ptr_toy<Toy> toy3;
    toy3 = toy1;
    Shared_ptr_toy<Toy> toy4(toy3);
    return 0;
}