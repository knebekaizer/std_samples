//
// Created by Vladimir on 21.12.2021.
//

#include "fancy_ptr.h"

#include <vector>
#include <memory>
#include <iostream>
using namespace std;

using all = std::allocator;

namespace my {

    template<class Tp_>
    class _LIBCPP_TEMPLATE_VIS allocator {
    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Tp_ *pointer;
        typedef const Tp_ *const_pointer;
        typedef Tp_ &reference;
        typedef const Tp_ &const_reference;
        typedef Tp_ value_type;

        typedef true_type propagate_on_container_move_assignment;
        typedef true_type is_always_equal;

        template<class Up_>
        struct rebind {
            typedef allocator<Up_> other;
        };

        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
        allocator() _NOEXCEPT {}

        template<class _Up>
        _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX17
        allocator(const allocator<_Up> &) _NOEXCEPT {}

        _LIBCPP_INLINE_VISIBILITY pointer address(reference __x) const _NOEXCEPT { return _VSTD::addressof(__x); }

        _LIBCPP_INLINE_VISIBILITY const_pointer address(const_reference __x) const _NOEXCEPT {
            return _VSTD::addressof(__x);
        }

        _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY
        pointer allocate(size_type __n, allocator<void>::const_pointer = 0) {
            if (__n > max_size())
                __throw_length_error("allocator<T>::allocate(size_t n)"
                                     " 'n' exceeds maximum supported size");
            return static_cast<pointer>(_VSTD::__libcpp_allocate(__n * sizeof(Tp_), _LIBCPP_ALIGNOF(Tp_)));
        }

        _LIBCPP_INLINE_VISIBILITY void deallocate(pointer __p, size_type __n) _NOEXCEPT {
            _VSTD::__libcpp_deallocate((void *) __p, __n * sizeof(Tp_), _LIBCPP_ALIGNOF(Tp_));
        }

        _LIBCPP_INLINE_VISIBILITY size_type max_size() const _NOEXCEPT { return size_type(~0) / sizeof(Tp_); }

#if !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)

        template<class _Up, class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        void
        construct(_Up *__p, _Args &&... __args) {
            ::new((void *) __p) _Up(_VSTD::forward<_Args>(__args)...);
        }

#else  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)
        _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p)
            {
                ::new((void*)__p) Tp_();
            }
# if defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)

        template <class _A0>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, _A0& __a0)
            {
                ::new((void*)__p) Tp_(__a0);
            }
        template <class _A0>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, const _A0& __a0)
            {
                ::new((void*)__p) Tp_(__a0);
            }
# endif  // defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES)
        template <class _A0, class _A1>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, _A0& __a0, _A1& __a1)
            {
                ::new((void*)__p) Tp_(__a0, __a1);
            }
        template <class _A0, class _A1>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, const _A0& __a0, _A1& __a1)
            {
                ::new((void*)__p) Tp_(__a0, __a1);
            }
        template <class _A0, class _A1>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, _A0& __a0, const _A1& __a1)
            {
                ::new((void*)__p) Tp_(__a0, __a1);
            }
        template <class _A0, class _A1>
            _LIBCPP_INLINE_VISIBILITY
            void
            construct(pointer __p, const _A0& __a0, const _A1& __a1)
            {
                ::new((void*)__p) Tp_(__a0, __a1);
            }
#endif  // !defined(_LIBCPP_HAS_NO_RVALUE_REFERENCES) && !defined(_LIBCPP_HAS_NO_VARIADICS)

        _LIBCPP_INLINE_VISIBILITY void destroy(pointer __p) { __p->~_Tp(); }
    };
}

int main() {
    vector<int> v(10);
    auto sz = v.size();
    cout << "size = " << sz << endl;
    return 0;
}