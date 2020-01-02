// Hossein Moein
// October 24, 2018
// Copyright (C) 2018-2019 Hossein Moein
// Distributed under the BSD Software License (see file License)

#include <DataFrame/Vectors/HeteroVector.h>

#include <algorithm>

// ----------------------------------------------------------------------------

namespace hmdf
{

template<typename T>
HeteroView::HeteroView(T *begin_ptr, T *end_ptr)
    : clear_function_([](HeteroView &hv) { views_<T>.erase(&hv); }),
      copy_function_([](const HeteroView &from, HeteroView &to)  {
              views_<T>[&to] = views_<T>[&from]; }),
      move_function_([](HeteroView &from, HeteroView &to)  {
              views_<T>[&to] = std::move(views_<T>[&from]); })  {

    views_<T>.emplace(this, VectorView<T>(begin_ptr, end_ptr));
}

// ----------------------------------------------------------------------------

template<typename T>
VectorView<T> &HeteroView::get_vector()  {

    auto    iter = views_<T>.find (this);

    if (iter == views_<T>.end())
        throw std::runtime_error("HeteroView::get_vector(): ERROR: "
                                 "Cannot find view");

    return (iter->second);
}

// ----------------------------------------------------------------------------

template<typename T>
const VectorView<T> &HeteroView::get_vector() const  {

    return (const_cast<HeteroView *>(this)->get_vector<T>());
}

// ----------------------------------------------------------------------------

template<typename T, typename U>
void HeteroView::visit_impl_help_ (T &visitor)  {

    auto    iter = views_<U>.find (this);

    if (iter != views_<U>.end())
        for (auto &&element : iter->second)
            visitor(element);
}

// ----------------------------------------------------------------------------

template<typename T, typename U>
void HeteroView::visit_impl_help_ (T &visitor) const  {

    const auto  citer = views_<U>.find (this);

    if (citer != views_<U>.end())
        for (auto &&element : citer->second)
            visitor(element);
}

// ----------------------------------------------------------------------------

template<typename T, typename U>
void HeteroView::sort_impl_help_ (T &functor)  {

    auto    iter = views_<U>.find (this);

    if (iter != views_<U>.end())
        std::sort (iter->second.begin(), iter->second.end(), functor);
}

// ----------------------------------------------------------------------------

template<typename T, typename U>
void HeteroView::change_impl_help_ (T &functor)  {

    auto    iter = views_<U>.find (this);

    if (iter != views_<U>.end())
        functor(iter->second);
}

// ----------------------------------------------------------------------------

template<typename T, typename U>
void HeteroView::change_impl_help_ (T &functor) const  {

    const auto  citer = views_<U>.find (this);

    if (citer != views_<U>.end())
        functor(citer->second);
}

// ----------------------------------------------------------------------------

template<class T, template<class...> class TLIST, class... TYPES>
void HeteroView::visit_impl_ (T &&visitor, TLIST<TYPES...>)  {

    // (..., visit_impl_help_<std::decay_t<T>, TYPES>(visitor)); // C++17
    using expander = int[];
    (void) expander { 0, (visit_impl_help_<T, TYPES>(visitor), 0) ... };
}

// ----------------------------------------------------------------------------

template<class T, template<class...> class TLIST, class... TYPES>
void HeteroView::visit_impl_ (T &&visitor, TLIST<TYPES...>) const  {

    // (..., visit_impl_help_<std::decay_t<T>, TYPES>(visitor)); // C++17
    using expander = int[];
    (void) expander { 0, (visit_impl_help_<T, TYPES>(visitor), 0) ... };
}

// ----------------------------------------------------------------------------

template<class T, template<class...> class TLIST, class... TYPES>
void HeteroView::sort_impl_ (T &&functor, TLIST<TYPES...>)  {

    using expander = int[];
    (void) expander { 0, (sort_impl_help_<T, TYPES>(functor), 0) ... };
}

// ----------------------------------------------------------------------------

template<class T, template<class...> class TLIST, class... TYPES>
void HeteroView::change_impl_ (T &&functor, TLIST<TYPES...>)  {

    using expander = int[];
    (void) expander { 0, (change_impl_help_<T, TYPES>(functor), 0) ... };
}

// ----------------------------------------------------------------------------

template<class T, template<class...> class TLIST, class... TYPES>
void HeteroView::change_impl_ (T &&functor, TLIST<TYPES...>) const  {

    using expander = int[];
    (void) expander { 0, (change_impl_help_<T, TYPES>(functor), 0) ... };
}

// ----------------------------------------------------------------------------

template<typename T>
bool HeteroView::empty() const noexcept  {

    return (get_vector<T>().empty ());
}

// ----------------------------------------------------------------------------

template<typename T>
T &HeteroView::at(size_type idx)  {

    return (get_vector<T>()[idx]);
}

// ----------------------------------------------------------------------------

template<typename T>
const T &HeteroView::at(size_type idx) const  {

    return (get_vector<T>()[idx]);
}

// ----------------------------------------------------------------------------

template<typename T>
T &HeteroView::back()  { return (get_vector<T>().back ()); }

// ----------------------------------------------------------------------------

template<typename T>
const T &HeteroView::back() const  { return (get_vector<T>().back ()); }

// ----------------------------------------------------------------------------

template<typename T>
T &HeteroView::front()  { return (get_vector<T>().front ()); }

// ----------------------------------------------------------------------------

template<typename T>
const T &HeteroView::front() const  { return (get_vector<T>().front ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::iterator<T>
HeteroView::begin()  { return (get_vector<T>().begin ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::const_iterator<T>
HeteroView::begin() const  { return (get_vector<T>().begin ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::iterator<T>
HeteroView::end()  { return (get_vector<T>().end ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::const_iterator<T>
HeteroView::end() const  { return (get_vector<T>().end ()); }


// ----------------------------------------------------------------------------

template<typename T>
HeteroView::reverse_iterator<T>
HeteroView::rbegin()  { return (get_vector<T>().rbegin ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::const_reverse_iterator<T>
HeteroView::rbegin() const  { return (get_vector<T>().rbegin ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::reverse_iterator<T>
HeteroView::rend()  { return (get_vector<T>().rend ()); }

// ----------------------------------------------------------------------------

template<typename T>
HeteroView::const_reverse_iterator<T>
HeteroView::rend() const  { return (get_vector<T>().rend ()); }

} // namespace hmdf

// ----------------------------------------------------------------------------

// Local Variables:
// mode:C++
// tab-width:4
// c-basic-offset:4
// End:
