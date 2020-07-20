//
// Created by Dmitry on 16.02.2019.
//

#ifndef LINKED_PTR_LINKED_PTR_HPP
#define LINKED_PTR_LINKED_PTR_HPP
#include <utility>

namespace smart_ptr {
    namespace details {
        struct linked_ptr_base {
            mutable linked_ptr_base *prev;
            mutable linked_ptr_base *next;
        };
    }

    template<typename T>
    class linked_ptr : public smart_ptr::details::linked_ptr_base {
    protected:
        template <typename U> friend
        class linked_ptr;

        T *value;

        template<typename U>
        void make_link(linked_ptr<U> const &other) {
            next = other.next;
            next->prev = this;
            prev = const_cast<linked_ptr<U> *>(&other);
            other.next = this;
        }

    public:
        linked_ptr() : value(nullptr) {
            prev = next = this;
        }

        template<typename U>
        explicit linked_ptr(U *obj) : value(obj) {
            prev = next = this;
        }

        linked_ptr(linked_ptr const &other) : value(other.value) {
            if (value) {
                make_link(other);
            }
            else {
                prev = next = this;
            }
        }


        template<typename U>
        linked_ptr(linked_ptr<U> const &other) : value(other.value) {
            if (value)
                make_link(other);
            else {
                prev = next = this;
            }
        }


        ~linked_ptr() {
            reset();
        }

        template<typename U>
        linked_ptr &operator=(U *pValue) {
            reset(pValue);
            return *this;
        }

        linked_ptr &operator=(linked_ptr const &linkedPtr) {
            if (linkedPtr.value != value) {
                reset(linkedPtr.value);
                if (linkedPtr.value) {
                    make_link(linkedPtr);
                }
            }
            return *this;
        }

        template<typename U>
        linked_ptr &operator=(linked_ptr<U> const &linkedPtr) {
            if (linkedPtr.value != value) {
                reset(linkedPtr.value);
                if (linkedPtr.value)
                    make_link(linkedPtr);
            }
            return *this;
        }

        template<typename U>
        void reset(U *pValue) {
            if (pValue != value) {
                if (unique()) {
                    delete value;
                } else {
                    prev->next = next;
                    next->prev = prev;
                    prev = next = this;
                }
                value = pValue;
            }
        }

        void reset() {
            reset((T *) nullptr);
        }

        bool unique() const {
            return (next == static_cast<linked_ptr_base const *>(this));
        }

        template<typename U>
        void swap(linked_ptr<U> &other) {
            if (value != other.value) {
                std::swap(value, other.value);
                if (unique() && !other.unique()) {
                    other.next->prev = other.prev->next = this;
                    next = other.next;
                    prev = other.prev;
                    other.next = other.prev = &other;
                } else if (!unique() && other.unique()) {
                    next->prev = prev->next = &other;
                    other.next = next;
                    other.prev = prev;
                    next = prev = this;

                } else if (!unique() && !other.unique()) {
                    std::swap(next->prev, other.next->prev);
                    std::swap(prev->next, other.prev->next);
                    std::swap(next, other.next);
                    std::swap(prev, other.prev);
                }
            }
        }


        T &operator*() const {
            return *value;
        }

        T *operator->() const {
            return value;
        }


        T *get() const {
            return value;
        }


        int use_count() const {
            int counter = 1;
            for (auto *current = static_cast<linked_ptr_base const *>(this);
                 current->next != static_cast<linked_ptr_base const *>(this); current = current->next)
                ++counter;
            return counter;
        }



        operator bool() const {
            return static_cast<bool>(value);
        }

        bool operator!() {
            return value == nullptr;
        }
    };

    template<typename T, typename U>
    inline bool operator==(linked_ptr<T> const &a, linked_ptr<U> const &b) {
        return (a.get() == b.get());
    }

    template<typename T, typename U>
    inline bool operator!=(linked_ptr<T> const &a, linked_ptr<U> const &b) {
        return (a.get() != b.get());
    }

    template<typename T, typename U>
    inline bool operator<(linked_ptr<T> const &a, linked_ptr<U> const &b) {
        return (a.get() < b.get());
    }

    template<typename T, typename U>
    inline bool operator<=(linked_ptr<T> const &a, linked_ptr<U> const &b) {
        return (a.get() <= b.get());
    }

    template<typename T, typename U>
    inline bool operator>(linked_ptr<T> const &a, linked_ptr<U> const &b) {
        return (a.get() > b.get());
    }

    template<typename T, typename U>
    inline bool operator>=(linked_ptr<T> &a, linked_ptr<U> &b) {
        return (a.get() >= b.get());
    }

    template<typename U>
    linked_ptr<U> make_linked(U *ptr) {
        return linked_ptr<U>(ptr);
    }
}

#endif //LINKED_PTR_LINKED_PTR_HPP
