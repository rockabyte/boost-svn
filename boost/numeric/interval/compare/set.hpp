/* Boost interval/compare/set.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/utility.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace set {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(x, y);
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  return empty(x);
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(x, y);
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  return empty(x) || (x.lower() == y && x.upper() == y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(y, x);
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  return in(y, x) && !singleton(x);
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(y, x);
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  return in(y, x);
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return equal(y, x);
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return !equal(y, x);
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  return x.lower() != y || x.upper() != y;
}

} // namespace set
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP
