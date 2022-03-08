/// @file Container.hpp
/// @author MILKIAS GHILOM
/// @date 02/27/2022
/// @brief This program is combined with interface header and implemnetation
/// file in order to be a template class. This program will store any data
/// type the user used. keep in mind if data type double all you input should
/// be double. it took me about 5 hours to change it to template and debug it.

#ifndef  CONTAINER_HPP
#define  CONTAINER_HPP


#include <iostream>
#include <cassert>
#include <initializer_list>

/// A Container stores a set of values The storage of the Container is handled automatically,
/// being expanded as needed.

template <class T>
class Container {
public:
    /// Member types.
    using value_type    = T;
    using size_type     = std::size_t;
    using pointer       = value_type*;
    using const_pointer = const value_type*;

    /// Default ctor.
    Container(size_type count = 0);

    /// Copy ctor.
    Container(const Container& other);

    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// move ctor
    Container(Container&& other);

    /// Destructor.
    ~Container();

    /// Checks if the container has no elements, e.g begin() == end()
    /// @returns true if the container is empty, false otherwise.
    bool empty() const {
        return begin() == end();
    }

    /// Returns the number of elements in the container.
    size_type size() const {
        return used;
    }

    /// Returns a pointer to the first element.
    pointer begin() {
        return data;
    }

    const_pointer begin() const {
        return data;
    }


    /// Returns a pointer to the end (the element following the last element).
    pointer end() {
        return begin() + size();
    }

    const_pointer end() const {
        return begin() + size();
    }


    /// Adds an element to the end.
    void push_back(const value_type& value);

    /// Removes a single item from the container.
    void erase(pointer pos);

    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() {
        used = 0;
    }

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);

    /// Finds the first element equal to the given target. Search begins at pos.
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type& target, pointer pos = nullptr);

    /// Replaces the contents of the container with a copy of the contents
    /// of rhs
    Container& operator=(const Container& rhs);

    /// Returns ther appended to this
    /// @returns this
    Container& operator+=(const Container& other);

private:
    size_type capacity;  ///< Physical capacity of container.
    size_type used;      ///< Number of items in container.
    pointer   data;      ///< Array of items.
};

// related non-member functions

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
template <class T>
bool equal(const Container<T>& lhs, const Container<T>& rhs);

/// Performs stream output on Containers, using "{1,2,3}" format.
template <class T>
void write(std::ostream& output, const Container<T>& container);

/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false


template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);


/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);


//=======================================================================



/// Copies the elements in the range defined by [first,last) to another
/// range beginning at d_first. The elements are copied in forward order.
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer       d_first);

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2);


/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
template <class T>
static typename Container<T>::pointer find(typename Container<T>::pointer first,
                                  typename Container<T>::pointer last,
                                const typename Container<T>::value_type& value);

/// Swapps any data type is given and return it  by reference.
template<class T>
static void swap( T& first , T& second);

template<class T>
Container<T>::Container(size_type count) {
    data = new value_type [count];
    used = 0;
    capacity = count;
}

template<class T>
Container<T>::Container(const Container<T>& other) {
    data = new value_type[other.used];
    used = other.size();
    capacity = other.capacity;
    ::copy<T>(other.begin(),other.end(),begin());
}

template <class T>
Container<T>::Container(Container<T>&& other)
:   capacity(other.capacity),used(other.used), data(other.data){
    other.data = nullptr;
    other.capacity = other.used = 0;
}

template<class T>
Container<T>::~Container() {
    delete [] data;
    data = nullptr;
    used = capacity = 0;
}

template<class T>
Container<T>::Container(const std::initializer_list<value_type>& init) {
    data = new value_type[init.size()];
    used = init.size();
    capacity = init.size();
    ::copy<T>(init.begin(),init.end(),begin());
}

template<class T>
void Container<T>::push_back(const value_type& value) {

    if (size() == capacity) {
        pointer temp = new value_type[capacity += 8];
        ::copy<T>(begin(),end(),temp);
        delete [] data;
        data = temp;
    }

    *(data + used++) = value;
}

template<class T>
void Container<T>::erase(pointer pos) {
    if (pos != nullptr) {
        assert(begin() <= pos);
        assert(pos < end());

        ::copy<T>(pos + 1,end(),pos);  // copying pos + 1 to pos
        --used;
    }
}

template<class T>
typename Container<T>::pointer Container<T>::find(
                                   const Container<T>::value_type& target,
                                   Container<T>::pointer pos) {
    pointer first = pos == nullptr ? begin() : pos;
    pointer location = end();

    return ::find<T>(first,location,target);
}

template<class T>
void Container<T>::swap(Container<T>& other) {

    // swapping two Container
    ::swap(capacity, other.capacity);
    ::swap(used, other.used);
    ::swap(data, other.data);

}

template <class T>
bool equal(const Container<T>& lhs, const Container<T>& rhs) {
    bool is_equal = false;

    typename Container<T>::const_pointer first1 = rhs.begin();
    typename Container<T>::const_pointer first2 = lhs.begin();
    typename Container<T>::const_pointer last = rhs.end();

    if (lhs.size() == rhs.size()) {
        is_equal = true;

        while (is_equal && first1 != last) {
            is_equal = *first1++ == *first2++;
        }
    }

    return is_equal;
}

template <class T>
void write(std::ostream& output, const Container<T>& container) {
    typename Container<T>::size_type count = 0;
    typename Container<T>::const_pointer first1 = container.begin();

    //limits to print until size() - 1
    typename Container<T>::size_type size = container.size() - 1;

    output << "{";

    if (container.size() != 0) {
        for (; (first1 + count) != (first1 + size); count++) {
            output << *(first1 + count) << ",";
        }

        output << *(first1 + size);
    }

    output << "}";;
}

template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    if (this != &rhs) {
        delete [] data;
        used = rhs.size();
        pointer temp = new value_type[used];
        ::copy<T>(rhs.begin(), rhs.end(), temp);
        data = temp;
    }

    return *this;
}

template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& other) {

    const auto new_size = size() + other.size();
    auto temp = new value_type[new_size];
    ::copy<T>(begin(), end(), temp);
    ::copy<T>(other.begin(), other.end(), temp + size());

    delete [] data;
    data = temp;
    used = new_size;
    capacity = new_size;

    return *this;
}

template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    return ::equal<T>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    return !(::equal<T>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) {
    return   Container<T>(lhs) += rhs;
}

template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {

    typename Container<T>::size_type count = 0;
    typename Container<T>::const_pointer first1 = oset.begin();
    //limits to print until size() - 1
    typename Container<T>::size_type size = oset.size() - 1;

    // first it will print the {
    output << "{";

    // if the container is not empty it will print all number except
    // the last number
    if (oset.size() != 0) {
        for (; (first1 + count) != (first1 + size); count++) {
            output << *(first1 + count) << "," ;
        }
        // The last number will be printed here
        output << *(first1 + size);
    }
    // Finally it will print the last }
    output << "}";

    return output;

}

template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer       d_first){

    while (first != last) {
        *d_first++ = *first++;
    }

}

template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2) {

    bool is_equal = (first1 - last1) == (first2 - last2);

        while (is_equal && first1 != last1) {
            is_equal = *first1++ == *first2++;
        }

    return is_equal;
}

template <class T>
static typename Container<T>::pointer find(
                            typename Container<T>::pointer first,
                            typename Container<T>::pointer last,
                            const typename Container<T>::value_type& value){

    auto address = last;
    while (first != address) {
        if (*first == value) {
            address = first;
        } else {
            ++first;
        }
    }

    return address;
}

template<class T>
static void swap(T& first, T& second){

    T temp;        // declaring temporary
    temp = first;
    first = second;
    second = temp;

}

#endif /* CONTAINER_HPP */

/* EOF */
