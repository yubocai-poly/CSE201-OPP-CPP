#ifndef TD7_HPP
#define TD7_HPP

#include "common.hpp"
#include <vector>

#define EXERCISE_1 1
#define EXERCISE_2 1
#define EXERCISE_3 1
#define EXERCISE_4 1
#define EXERCISE_5 1
#define EXERCISE_6 1

// Exercise 1 - A class template for complex numbers
template <class T>
class Complex
{
public:
    Complex(T real, T imag)
    {
        this->real = real;
        this->imag = imag;
    }
    T get_r() const { return real; }
    T get_i() const { return imag; }

private:
    T real;
    T imag;
};

// Exercise 2 - Class template to represent a generic node of a linked list
template <class T>
class ListNode
{
public:
    // it stores a generic element of type T and it has two pointers to the previous and next nodes of the list
    ListNode(T element)
    {
        this->element = element;
        this->prev = nullptr;
        this->next = nullptr;
    }

    T get_element() const { return element; }
    void set_next(ListNode *next) { this->next = next; }
    void set_prev(ListNode *prev) { this->prev = prev; }
    ListNode *get_next() const { return next; }
    ListNode *get_prev() const { return prev; }

private:
    T element;
    ListNode<T> *prev;
    ListNode<T> *next;
};

// Exercise 3 - Class template to represent a generic doubly linked list
template <class T>
class List
{
public:
    List()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~List()
    {
        for (ListNode<T> *current = head; current != nullptr;)
        {
            ListNode<T> *app;
            app = current;
            current = app->get_next();
            delete app;
        }
        head = nullptr;
        tail = nullptr;
    }

    bool is_empty() const { return head == nullptr && tail == nullptr; }

    void append(T element)
    {
        ListNode<T> *new_element = new ListNode<T>(element);
        new_element->set_next(nullptr);
        new_element->set_prev(nullptr);

        if (head == nullptr && head == tail)
        {
            // empty list
            head = new_element;
            tail = new_element;
        }
        else
        {
            // non-empty list
            tail->set_next(new_element);
            new_element->set_prev(tail);
            tail = new_element;
        }
    }

    T remove_from_head()
    {
        T p = head->get_element();

        if (head == tail)
        {
            // list with one element
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            // list with more than one element
            ListNode<T> *app = head;
            head = head->get_next();
            head->set_prev(nullptr);
            delete app;
        }
        return p;
    }

    T remove_from_tail()
    {
        T p = tail->get_element();

        if (head == tail)
        {
            // list with one element
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            // list with more than one element
            ListNode<T> *app = tail;
            tail = tail->get_prev();
            tail->set_next(nullptr);
            delete app;
        }
        return p;
    }

private:
    ListNode<T> *head;
    ListNode<T> *tail;
};

// Exercise 4 - Filter elements of a vector
#if EXERCISE_4 == 1
std::vector<int>
reverse_even(std::vector<int> input_vector);
#endif

#if EXERCISE_5 == 1
std::vector<Coordinate> same_coordinates(std::vector<double> list_of_x,
                                         std::vector<double> list_of_y);
#endif

#if EXERCISE_6 == 1
std::vector<int> filter_max(std::vector<int> max_vector,
                            std::vector<int> other_vector);
#endif

#endif // TD7_HPP
