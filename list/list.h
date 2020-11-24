#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <functional>
#include <iostream>
#include <string>
#include <tuple>

template <typename K, typename V>
class list {
 private:
  struct element {
    const K key;
    const V value;
    element *next;

    element(const std::tuple<K, V>, element *);
  };

  element *head = nullptr;

 public:
  ~list();

  const V *search(const K) const;

  bool isEmpty() const;

  bool isSorted(std::function<bool(K, K)> lessThan) const;

  std::tuple<K, V> popHead();

  void sort(std::function<bool(K, K)> lessThan);

  list<K, V> &operator+=(const std::tuple<K, V>);

  list<K, V> &operator-=(const K);

  void printTo(std::ostream &ostr) const;
};


/**
 * Constructor for struct element.
 * @tparam K
 * @tparam V
 * @param tuple
 * @param element1
 */
template<typename K, typename V>
list<K, V>::element::element(const std::tuple<K, V> tuple, list::element *element1) : key(std::get<0>(tuple)),value(std::get<1>(tuple)), next(element1) { }


/**
 * Destructor for class list.
 * @tparam K
 * @tparam V
 */
template <typename K, typename V>
list<K, V>::~list() {}


/**
 *
 * @tparam K
 * @tparam V
 * @param key key to search
 * @return value of element with this key
 */
template <typename K, typename V>
const V *list<K, V>::search(const K key) const {
  return nullptr;
}


/**
 * Checks if list is empty.
 * @tparam K
 * @tparam V
 * @return true if list is empty, false else
 */
template <typename K, typename V>
bool list<K, V>::isEmpty() const {
  return false;
}


/**
 * Checks if list is sorted
 * @tparam K
 * @tparam V
 * @param lessThan function which compares two values
 * @return true if sorted, false if not
 */
template <typename K, typename V>
bool list<K, V>::isSorted(std::function<bool(K, K)> lessThan) const {
  return false;
}


/**
 * Removes head from list
 * @tparam K
 * @tparam V
 * @return tuple of element head
 */
template <typename K, typename V>
std::tuple<K, V> list<K, V>::popHead() {
  return std::tuple<K, V>();
}


/**
 * Sorts list.
 * @tparam K
 * @tparam V
 * @param lessThan function which compares two values
 */
template <typename K, typename V>
void list<K, V>::sort(std::function<bool(K, K)> lessThan) {}


/**
 * Adds element at end of list or if key is already in list, replaces it
 * @tparam K
 * @tparam V
 * @param tuple
 * @return
 */
template <typename K, typename V>
list<K, V> &list<K, V>::operator+=(const std::tuple<K, V> tuple) {
  return *this;
}


/**
 * Removes element with key
 * @tparam K
 * @tparam V
 * @param key
 * @return
 */
template <typename K, typename V>
list<K, V> &list<K, V>::operator-=(const K key) {
  return *this;
}


/**
 * Prints list
 * @tparam K
 * @tparam V
 * @param ostr
 */
template <typename K, typename V>
void list<K, V>::printTo(std::ostream &ostr) const {}


template <typename K, typename V>
std::ostream &operator<<(std::ostream &ostr, const list<K, V> &list) {
  list.printTo(ostr);
  return ostr;
}

#endif  // LINKEDLIST_LIST_H
