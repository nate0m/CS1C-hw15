// hw15.cpp
// to illustrate stl containers & iterators

/*************************************************************************
 * AUTHOR     : First Last
 * HW15       : stl containers & iterators
 * CLASS      : CS 1C
 * SECTION    : Date & Time
*************************************************************************/

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

using std::vector;

// function & class definitions go into hw15.cpp:

// hw15.cpp

namespace hw15 {

//
// list conainter, iterator example code adapted from Chapter 20.4
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

//------------------------------------------------------------------------------

template<typename Elem>
struct Link
{
    Link* prev;    // previous link
    Link* succ;    // successor (next) link
    Elem  val;     // the value
    Link(const Elem& v = Elem(), Link* p = 0, Link* s = 0) : val{v}, prev{p}, succ{s} { }
};

//--Q#3-------------------------------------------------------------------------

template<typename Elem>
class list
{
    // representation and implementation details
public:
    class iterator;         // forward declaration of member type: class iterator
    class const_iterator;   // forward declaration of member type: class const_iterator

    list() : first(new Link<Elem>()), last{first} { }
    ~list()
    {
        while (first != last)
        {
            Link<Elem> *next = first->succ;
            delete first;
            first = next;
        }
        delete last;
    }

    iterator begin();   // iterator to first element
    iterator end();     // iterator to one beyond last element
                    
    // add missing const iterators begin, end here

    const_iterator begin() const; // constant iterator to first element
    const_iterator end()   const;  // constant iterator to one beyond last element

    iterator insert(iterator p, const Elem& v); // insert v into list after p
    iterator erase(iterator p);                 // remove p from the list

    void push_back(const Elem& v);  // insert v at end
    void push_front(const Elem& v); // insert v at front
    void pop_front();   // remove the first element
    void pop_back();    // remove the last element

    Elem& front();      // the first element
    Elem& back();       // the last element

    Link<Elem>* first;
    Link<Elem>* last;   // one-beyond-the-last link
};

//--Q#4-------------------------------------------------------------------------

template<typename Elem>
class list<Elem>::iterator // definition for class iterator
{
    Link<Elem>* curr;   // current node
public:
    iterator(Link<Elem>* p) : curr{p} { }
    iterator& operator++() // forward
    {
        return curr->succ; // included so that incomplete lab code will compile
    }
    iterator& operator--() // backwards
    {
        return curr->prev; // included so that incomplete lab code will compile
    }
    Elem& operator*()  // get value (dereference)
    {
        return curr->val; // included so that incomplete lab code will compile
    }

    bool operator==(const iterator& rhs) const // lhs, rhs iterators point to the same node (equal)
    {
        return  curr == rhs.curr; // included so that incomplete lab code will compile
    }
    bool operator!=(const iterator& rhs) const // lhs, rhs iterators do not point to the same node (not equal)
    {
        return curr != rhs.curr; // included so that incomplete lab code will compile
    }
};

//--Q#4-------------------------------------------------------------------------

template<typename Elem>
class list<Elem>::const_iterator // definition for class const_iterator
{
    const Link<Elem>* curr;   // current node
                              // node pointed to by curr is immutable (i.e. can't be changed)
                              // fine to modify curr pointer itself (i.e. pointer value stored in curr)
                              // refer to const correctness reading
public:
    const_iterator(const Link<Elem>* p) : curr{p} {}
    // add missing constructor, overloaded ++, --, *, ==, != operators here
    const_iterator& operator++() const // forward
    {
        return curr->succ; // included so that incomplete lab code will compile
    }
    const_iterator& operator--() const // backwards
    {
        return curr->prev; // included so that incomplete lab code will compile
    }
    Elem& operator*() const // get value (dereference)
    {
        return *curr; // included so that incomplete lab code will compile
    }
    bool operator==(const const_iterator& rhs) const // lhs, rhs iterators point to the same node (equal)
    {
        return  curr == rhs.curr; // included so that incomplete lab code will compile
    }
    bool operator!=(const const_iterator& rhs) const // lhs, rhs iterators do not point to the same node (not equal)
    {
        return curr != rhs.curr; // included so that incomplete lab code will compile
    }
};

//------------------------------------------------------------------------------

template<typename Elem> 
typename list<Elem>::iterator list<Elem>::begin()  // iterator to first element
{ 
    return iterator(first); 
}

//--Q#3-------------------------------------------------------------------------

// constant iterator to first element
template<typename Elem> 
typename list<Elem>::const_iterator list<Elem>::begin() const // iterator to first element
{ 
    return const_iterator(first); 
}

//------------------------------------------------------------------------------

template<typename Elem> 
typename list<Elem>::iterator list<Elem>::end() // iterator to one beyond last element
{ 
    return iterator(last); 
}

//--Q#3-------------------------------------------------------------------------

// constant iterator to last element
template<typename Elem> 
typename list<Elem>::const_iterator list<Elem>::end() const // iterator to one beyond last element
{ 
    return const_iterator(last); 
}


//------------------------------------------------------------------------------

template<typename Elem> 
void list<Elem>::push_front(const Elem& v) // insert v at front
{
    first = new Link<Elem>(v,0,first);
}

//
// low algorithms adapted from Chapter 20.1, 20.4
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

//--Q#5-------------------------------------------------------------------------

double* low_doubles(double* first, double* last)
    // return a pointer to the element in [first,last) that has the lowest value
{
    double l = -1;
    double* low;
    for(double* p = first; p!=last; ++p)
        if (*p < l) { low = p; l = *p; }
    return low;
}

//--Q#5-------------------------------------------------------------------------

// implement templated low algorithm here
template<typename T>
T* low(T* first, T* last) 
{ 
    T l = -1;
    T* low;
    for(T* p = first; p != last; ++p)
        if (*p < l) { low = p; l = *p; }
    return low;
}

//------------------------------------------------------------------------------

} // hw15

//------------------------------------------------------------------------------

using namespace hw15;

//
// list conainter, iterator example code adapted from Chapter 20.4
// low algorithms adapted from Chapter 20.1, 20.4
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

int main()
{
    // console header
	cout << endl;
	cout << "************************************** " << endl;
	cout << "*           Running HW15             * " << endl;
	cout << "*      Programmed by First Last      * " << endl;
	cout << "*         CS1C Date & Time           * " << endl;
	cout << "************************************** " << endl;
	cout << endl;

	// Q#3,4 - containters & iterators

    list<int> myList;
    int x;
    while (cin >> x) myList.push_front(x);

	// Q#5 - low_doubles algorithm

    double d[] = {1,2,3,4,5,-99.25,100,10,500.123,5};       // init array of doubles
    vector<double> v = {1,2,3,4,5,-99.25,100,10,500.123,5}; // init identical vector of doubles

    double* lowa = low_doubles(&d[0], &d[9]); // min of array
    cout << endl << "low_doubles alg: double array min value is " << *lowa << endl << endl;

    double* middle = &v[0] + v.size()/2;
    double* lowv1 = low_doubles(&v[0], middle);          // min of vector first half
    double* lowv2 = low_doubles(middle, &v[0]+v.size()); // min of vector second half
    cout << "low_doubles alg: double vector min value first half is " << *lowv1 << endl;
    cout << "low_doubles alg: double vector min value second half is " << *lowv2 << endl << endl;

	// Q#5 - low algorithm

    // NOTE: uncomment code below once low algorithm definition is complete

    lowa = low(&d[0], &d[9]); // min of array
    cout << "low alg: double array min value is " << *lowa << endl << endl;

    lowv1 = low(&v[0], middle);          // min of vector first half
    lowv2 = low(middle, &v[0]+v.size()); // min of vector second half
    cout << "low alg: double vector min value first half is " << *lowv1 << endl;
    cout << "low alg: double vector min value second half is " << *lowv2 << endl << endl;

    list<int>::iterator p = low(myList.begin(), myList.end()); // min of list
    if (p==myList.end())    // did we reach the end?
         cout << "low alg: the list is empty";
     else
         cout << "low alg: the lowest value in the list is " << *p << endl;


    return 0;
}

//------------------------------------------------------------------------------

// WRITTEN ANSWERS

// Q#1
// An stl cotainer is a data structure. A templated data stucture within the stl 
// that can hold different single types of data values. An stl container an be 
// structured in different ways. Some sort data some keep data unsorted and other 
// store elements in a specific order.

// Q#2
// An stl iterator is a pointer used to access the elements of a container. The 
// poiter is used to iterate and traverse throught the container flexibly. The
// iterator only loosely coples to the container allowing the iterator to 
// easily detatch from the container.

// Q#5
// An stl algorithm is what is used by an iterator pointer to sort a container of data. 
// Algorithms sort containers using iterators. Algorithms are templated meaning they 
// can sort any one data type. 

