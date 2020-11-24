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
    ~element();
  };

  element *head = nullptr;

  element* quicksort(element* elem, std::function<bool(K, K)> lessThan);

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
list<K, V>::element::element(const std::tuple<K, V> tuple, list::element *element1)
    : key(std::get<0>(tuple)),value(std::get<1>(tuple)), next(element1) { }


/**
 * Destructor for class list.
 * @tparam K
 * @tparam V
 */
template <typename K, typename V>
list<K, V>::~list() {
  delete head;
}

/**
 * Destructor for struct element
 * @tparam K
 * @tparam V
 */
template <typename K, typename V>
list<K, V>::element::~element() {
  delete next;
}


/**
 *
 * @tparam K
 * @tparam V
 * @param key key to search
 * @return value of element with this key
 */
template <typename K, typename V>
const V *list<K, V>::search(const K) const {
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
  return head == nullptr;
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
  auto *nextElement = head;
  if (nextElement == nullptr) {
    return false; /* or true müssen wir evtl. auch in einem eigenen Google Test festlegen */
  }
  while (nextElement->next != nullptr) {
    if (lessThan(nextElement->key, nextElement->next->key)) {
      nextElement = nextElement->next;
    } else {
      return false;
    }
  }
  return true;
}


/**
 * Removes head from list
 * @tparam K
 * @tparam V
 * @return tuple of element head
 */
template <typename K, typename V>
std::tuple<K, V> list<K, V>::popHead() {
  if (!isEmpty()) {
    auto popElem = head;
    head = head->next;
    std::tuple<K, V> tuple (popElem->key, popElem->value);
    delete popElem;
    return tuple;
  }
  return std::tuple<K, V>();
}


/**
 * Sorts list.
 * @tparam K
 * @tparam V
 * @param lessThan function which compares two values
 */
template <typename K, typename V>
void list<K, V>::sort(std::function<bool(K, K)> lessThan) {
  element *sorted = quicksort(head, lessThan);
  head = sorted;
}


/**
 * Sorts list with quicksort.
 * @tparam K
 * @tparam V
 * @param elem
 * @param lessThan
 * @return
 */
template<typename K, typename V>
struct list<K, V>::element* list<K, V>::quicksort(list::element *elem, std::function<bool(K, K)> lessThan) {

  if (elem == nullptr || elem->next == nullptr) {
    return elem;
  }

  element *current = elem->next;
  element *next;
  element *pivot = elem;
  pivot->next = nullptr;
  element *lh = nullptr;
  element *rh = nullptr;

  while (current != nullptr) {
    if (lessThan(current->key, pivot->key)) {
      if (lh == nullptr) {
        lh = current;
        current = current->next;
        lh->next = nullptr;
      } else {
        next = current->next;
        current->next = lh;
        lh = current;
        current = next;
      }
    } else {
      if (rh == nullptr) {
        rh = current;
        current = current->next;
        rh->next = nullptr;
      } else {
        next = current->next;
        current->next = rh;
        rh = current;
        current = next;
      }
    }
  }

  lh = quicksort(lh, lessThan);
  rh = quicksort(rh, lessThan);

  if (lh == nullptr) {
    pivot->next = rh;
    return pivot;
  } else {
    element *lh_end = lh;
    while (lh_end->next != nullptr) {
      lh_end = lh_end->next;
    }
    lh_end->next = pivot;
    pivot->next = rh;
    return lh;
  }
}


/**
 * Adds element at end of list or if key is already in list, replaces it
 * @tparam K
 * @tparam V
 * @param tuple
 * @return
 */
template<typename K, typename V>
list<K, V> &list<K, V>::operator+=(const std::tuple<K, V> el) {
  auto elem = new typename list<K, V>::element(el, nullptr);
  K key = std::get<0>(el);
  if (head == nullptr || head->key == key) {
    head = elem;
    return *this;
  }
  element *current = head;
  element *next = head->next;
  while (next != nullptr) {
    if (next->key == key) {
      elem->next = next->next;
      current->next = elem;
      next->next = nullptr;
      return *this;
    }
    current = current->next;
    next = current->next;
  }
  current->next = elem;
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
list<K, V> &list<K, V>::operator-=(const K) {
  return *this;
}


/**
 * Prints list
 * @tparam K
 * @tparam V
 * @param ostr
 */
template <typename K, typename V>
void list<K, V>::printTo(std::ostream &ostr) const {
  ostr.clear();
}


template <typename K, typename V>
std::ostream &operator<<(std::ostream &ostr, const list<K, V> &list) {
  list.printTo(ostr);
  return ostr;
}

#endif  // LINKEDLIST_LIST_H
