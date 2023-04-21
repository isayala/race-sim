/*
 *  Israel Ayala
 *  CS302
 *  Race header file will use a node class to create a doubly linked list.
 *  Will also use template's for the node class and the DLL class.
*/
#include "vehicle.h"

// Node for a DLL
template <typename T>
class node {
    public:
        // Constructors
        node<T>();
        node<T>(T * data);
        node<T>(T * data, node<T> * next, node<T> * prev);

        // Set the next pointer
        void set_next(node<T> * next);
        // Get the next pointer
        node<T> *& get_next();
        // Set the prev pointer
        void set_prev(node<T> * prev);
        // Get the prev pointer
        node<T> *& get_prev();
        // Set the data
        void set_data(T * data);
        // Get the data
        T *& get_data();

    private:
        T * data;
        node<T>* next;
        node<T>* prev;
};

// Doubly Linked list for a race of various cars
template <typename T>
class dlist {
    public:
        // Constructor
        dlist();
        // Copy Constructor
        dlist(const dlist & source);
        // Destructor
        ~dlist();
        // Assignment Operator
        dlist & operator = (const dlist & source);

        // Add to the list
        dlist & operator += (T * to_add);

        // Output
        template<typename U>
        friend std::ostream & operator << (std::ostream & out, const dlist<U> & source);

        // Add at the end of the list
        int add(T * to_add);
        // Display the list
        void display() const;
        // Remove the last node
        int remove();
        // Remove the list
        int remove_all();
        // Copy the list
        int copy(const dlist & source);
        // Declare winner by best lap time
        int winner();

    private:
        node<T> * head;
        node<T> * tail;
        // For constructors, destructors
        int destroy(node<T> *& head, node<T> *& tail);
        int copy(node<T> *& head, node<T> *& tail);
        // Recursive functions
        int add(node<T> *& head, T * to_add);
        void display(node<T> * head) const;
        int remove(node<T> *& head);
        int winner(node<T> * head, float & fastest);
};
#include "race.tpp"
