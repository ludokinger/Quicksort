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
  element *tmp;
  while (head != nullptr) {
    tmp = head->next;
    delete head;
    head = tmp;
  }
}


/**
 *
 * @tparam K
 * @tparam V
 * @param key key to search
 * @return value of element with this key
 */
template <typename K, typename V>
const V *list<K, V>::search(const K key) const {
  auto elem = head;
  while (elem != nullptr) {
    if (elem->key == key)
      return &elem->value;
    elem = elem-> next;
  }
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
    popElem->next = nullptr;
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
 * @return a element according to which only sorted elements are
 */
template<typename K, typename V>
struct list<K, V>::element* list<K, V>::quicksort(list::element *elem, std::function<bool(K, K)> lessThan) {

  if (elem == nullptr || elem->next == nullptr) {        // 1  (a)
    return elem;
  }

  element *current = elem->next;                        // 1   (a)
  element *next;                                        // 1   (a)
  element *pivot = elem;                                // 1   (a)
  pivot->next = nullptr;                                // 1   (a)
  element *lh = nullptr;                                // 1   (a)
  element *rh = nullptr;                                // 1   (a)
                                                        // Therefore part (a) is O(1)

  while (current != nullptr) {                          // n        (b)
    if (lessThan(current->key, pivot->key)) {           // n        (b)
      if (lh == nullptr) {                              // max. 1   (b)(b1)
        lh = current;                                   // 1        (b)(b1)
        current = current->next;                        // 1        (b)(b1)
        lh->next = nullptr;                             // 1        (b)(b1)   -> (b1) max. 3
      } else {                                          // max. n-1 (b)(b2)
        next = current->next;                           // 1        (b)(b2)
        current->next = lh;                             // 1        (b)(b2)
        lh = current;                                   // 1        (b)(b2)
        current = next;                                 // 1        (b)(b2)   -> (b2) max 4(n-1)
      }
    } else {                                            // max. n   (b)(b3)
      if (rh == nullptr) {                              // max. 1   (b)(b3)
        rh = current;                                   // 1        (b)(b3)
        current = current->next;                        // 1        (b)(b3)
        rh->next = nullptr;                             // 1        (b)(b3)   -> (b3) max. 3
      } else {                                          // max. n-1 (b)(b4)
        next = current->next;                           // 1        (b)(b4)
        current->next = rh;                             // 1        (b)(b4)
        rh = current;                                   // 1        (b)(b4)
        current = next;                                 // 1        (b)(b4)   -> (b4) max. 4(n-1)
      }
    }
  }                                                     // Therefore part (b) is:
                                                        // Worst-Case: T(n) = n + n + 3 + 4(n-1) + 3 + 4(n-1) = 10n - 2, T(n) is O(n)
                                                        // Best-Case: T(n) = n + n = 2n, T(n) is O(n)
                                                        // => O(n)

  lh = quicksort(lh, lessThan);                         // ((a) + (b) + (d))/2 = T(n/2)                                                 (c)
  rh = quicksort(rh, lessThan);                         // both calls together: 2*T(n/2) = n + 2 * (n/2) + 4 * (n/4) + ... = nlogn      (c)
                                                        // Therefore recursive part (c): T(n) = nlogn, T(n) is O(nlogn)    (in average case, if pivot is "bad" it's worst case which is O(n^2))

  if (lh == nullptr) {                                  // 1         (d)(d1)
    pivot->next = rh;                                   // max. 1    (d)(d1)
    return pivot;                                       // max. 1    (d)(d1)   -> (d1) max 3 operations, min. 1
  } else {                                              // max. 1    (d)(d2)
    element *lh_end = lh;                               // max. 1    (d)(d2)
    while (lh_end->next != nullptr) {                   // max. n    (d)(d2)
      lh_end = lh_end->next;                            // max. n    (d)(d2)
    }
    lh_end->next = pivot;                               // 1         (d)(d2)
    pivot->next = rh;                                   // 1         (d)(d2)
    return lh;                                          // 1         (d)(d2)   -> (d2) max. 2n + 5, min
  }                                                     // Therefore part (d) is:
                                                        // Worst-Case: T(n) = 3 + 2n + 5 = 2n + 8, T(n) is O(n)
                                                        // Best-Case:  T(n) = 1, T(n) is O(1)
                                                        // => O(n)

                                                        // Therefore (a) + (b) + (c) + (d) = O(1) + O(n) + O(nlogn) + O(n) = O(nlogn)
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
  auto *elem = new typename list<K, V>::element(el, nullptr);
  K key = std::get<0>(el);
  if (head == nullptr) {
    head = elem;
    return *this;
  } else if (head->key == key) {
    head->next = nullptr;
    delete head;
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
 * Removes element by key
 * @tparam K
 * @tparam V
 * @param key
 * @return list
 */
template <typename K, typename V>
list<K, V> &list<K, V>::operator-=(const K newKey) {
  if (head == nullptr) {
    return *this;
  }

  element *current = head;
  element *prev = nullptr;

  while (current != nullptr) {
    if (current->key == newKey) {
      element *t = current->next;
      if (prev == nullptr) {
        head->next = nullptr;
        delete head;
        head = t;
        return *this;
      }
      current->next = nullptr;
      prev->next = t;
      delete current;
      current = t;
      return *this;
    }
    prev = current;
    current = current->next;
  }
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
