/*
 *  Israel Ayala
 *  02/14/2023
 *  Race header file will use a node class to create a doubly linked list.
 *  Will also use template's for the node class and the DLL class.
*/
#include <iostream>

// Node class
// Constructors
template <typename T>
node<T>::node() : data{nullptr}, next{nullptr}, prev{nullptr} {}

template <typename T>
node<T>::node(T * data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template <typename T>
node<T>::node(T * data, node<T> * next, node<T> * prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

// Set the next pointer
template <typename T>
void node<T>::set_next(node<T> * next) {
    this->next = next;
}

// Get the next pointer
template <typename T>
node<T> *& node<T>::get_next() {
    return next;
}

// Set the prev pointer
template <typename T>
void node<T>::set_prev(node<T> * prev) {
    this->prev = prev;
}

// Get the prev pointer
template <typename T>
node<T> *& node<T>::get_prev() {
    return prev;
}

// Set the data
template <typename T>
void node<T>::set_data(T * data) {
    this->data = data;
}

// Get the data
template <typename T>
T *& node<T>::get_data() {
    return data;
}

// DLL class
// Constructor
template <typename T>
dlist<T>::dlist() : head{nullptr}, tail{nullptr} {}

// Copy Constructor
template <typename T>
dlist<T>::dlist(const dlist & source) {
    // If there is a current head
    if (head)
        // Remove the nodes
        destroy(head, tail);
    // Then make a copy
    copy(source);
}

// Destructor
template <typename T>
dlist<T>::~dlist() {
    if (head)
        destroy(head, tail);
}

// Assignment Operator
template <typename T>
dlist<T> & dlist<T>::operator = (const dlist & source) {
    if (this->head == & source)
        return * this;

    if (head)
        destroy(head, tail);

    copy(head, tail);

    return * this;
}


// Input
template <typename T>
// Add to the list
dlist<T> & dlist<T>::operator += (T * to_add) {
    this->add(to_add);

    return * this;
}

// Output
template <typename T>
std::ostream & operator << (std::ostream & out, const dlist<T> & source) {
    source.display();
    return out;
}

// Add at the end of the list
template <typename T>
int dlist<T>::add(T * to_add) {
    return add(head, to_add);
}

template <typename T>
int dlist<T>::add(node<T> *& head, T * to_add) {
    if (!head) {
        head = new node<T>;
        head->set_data(to_add);
        head->set_next(nullptr);
        return 1;
    }
    return add(head->get_next(), to_add);
}

// Display the list
template <typename T>
void dlist<T>::display() const {
    if (!head) return;

    return display(head);     
}

template <typename T>
void dlist<T>::display(node<T> * head) const {
    if (!head) return;

    head->get_data()->display();

    return display(head->get_next());
}

// Remove the first node
template <typename T>
int dlist<T>::remove() {
    if (!head) return 0;

    node<T> * temp = head->get_next();
    delete head;
    head = temp;

    return 1;
}

// Remove the list
template <typename T>
int dlist<T>::remove_all() {
    if (!head) return 0;

    return destroy(head, tail);
}

template <typename T>
int dlist<T>::destroy(node<T> *& head, node<T> *& tail) {
    if (head) {
        destroy(head->get_next(), tail);
        delete head->get_data();
        delete head;
        delete tail;
        head = tail = nullptr;
    }
    return 0;
}

// Declare a winner by best lap time
template <typename T>
int dlist<T>::winner() {
    if (!head) return 0;

    float fastest = head->get_data()->best_time();
    return winner(head, fastest);
}

template <typename T>
int dlist<T>::winner(node<T> * head, float & fastest) {
    if (!head) return 0;

    if (head->get_data()->best_time() < fastest)
        fastest = head->get_data()->best_time();

    winner(head->get_next(), fastest);
   
    if (fastest == head->get_data()->best_time()) {
        std::cout << "**********";
        head->get_data()->display();
        std::cout << "**********";
        return 1;
    }
    return 0;
}
