#include <iostream>

using namespace std;

class Drop_off_stack {
private:
public:
    int* array;
    int itop;
    int ibottom;
    int entry_count;
    int array_capacity;

    // Constructors
    Drop_off_stack(int n = 10) : array(new int[n]), itop(-1), ibottom(0), entry_count(0), array_capacity(n) {}


    // Copy Constructor
    Drop_off_stack(const Drop_off_stack& other) : array(new int[other.array_capacity]),
        itop(other.itop),
        ibottom(other.ibottom),
        entry_count(other.entry_count),
        array_capacity(other.array_capacity) {
        copy(other.array, other.array + array_capacity, array);
    }

    // Accessors
    int getop() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return array[itop];
    }

    int size() const {
        return entry_count;
    }

    bool getEntryCount() const {
        return entry_count == 0;
    }

    // Mutators
    void swap(Drop_off_stack& other) {
        std::swap(array, other.array);
        std::swap(itop, other.itop);
        std::swap(ibottom, other.ibottom);
        std::swap(entry_count, other.entry_count);
        std::swap(array_capacity, other.array_capacity);
    }

    Drop_off_stack& operator=(Drop_off_stack other) {
        swap(other);
        return *this;
    }
    bool isEmpty() const
    {
        if (itop == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }



    void push(const int& element) {
        if (entry_count == array_capacity)
        {
            // Stack is full, drop the bottom element
            ++ibottom;
            ibottom %= array_capacity;
        }
        else
        {
            ++entry_count;
        }

        // Insert at the top
        ++itop;
        itop %= array_capacity;
        array[itop] = element;
    }

   
    int pop() {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }

        int popped_element = array[itop];
        --entry_count;
        --itop;
        itop = (itop + array_capacity) % array_capacity; // Handle wraparound
        return popped_element;
    }

    void clear() {
        itop = -1;
        ibottom = 0;
        entry_count = 0;
    }
    // Destructor

    ~Drop_off_stack()
    {
        cout << "Destructor Called!\n";
        delete[] array;
    }
    // Friend
    friend ostream& operator<<(ostream& os, const Drop_off_stack& stack);

};
ostream& operator<<(ostream& os, const Drop_off_stack& stack)
{
        if (stack.entry_count == 0) {
            os << "Stack is empty." << std::endl;
            return os;
        }
       
    
        os << "Stack: \n\n";

        if (stack.entry_count < stack.array_capacity)
        {
            for (int i = stack.entry_count-1; i >=0; i--)
            {
                os << " | " << stack.array[i] << " |\n";
            }
            os << " -----\n";
            return os;
        }

if(stack.itop!=stack.array_capacity-1)
        for (int i = stack.itop; i >= 0; i--)
            os << " | " << stack.array[i] << " |\n";
        for (int i = stack.entry_count-1; i >= stack.ibottom; i--)
            os <<" | "<< stack.array[i] << " |\n";

   
        os << " -----\n";

        return os;
}
int main()
{
    Drop_off_stack temp(5);
    temp.push(6);
    temp.push(5);
    temp.push(4);
    temp.push(3);
    temp.push(2);
    cout << "STACK 1:\n";
    cout << temp;
    temp.push(1);
    cout << "STACK 1 AFTER PUSHING '1' WHEN STACK IS FULL!\n";
    cout << temp;
    Drop_off_stack temp2=temp;
    cout << "STACK 2 AFTER GETTING COPIED BY STACK 1:\n";
    cout << temp2;
    temp2.push(9);
    cout << "STACK 2 AFTER PUSHING '9' WHEN STACK 2 IS FULL!\n";

    cout << temp2;
    temp.swap(temp2);
    cout << "STACK 1 AFTER GETTING SWAPPED BY STACK 2: \n";
    cout << temp;

    return 0;
}
