// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef RETURN_FROM_PYTHON_DWA200265_HPP
# define RETURN_FROM_PYTHON_DWA200265_HPP

# include <boost/python/converter/callback_from_python_base.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>
# include <boost/python/detail/void_ptr.hpp>
# include <boost/call_traits.hpp>
# include <boost/python/detail/void_return.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T>
  struct return_pointer_from_python
  {
      typedef T result_type;
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_reference_from_python
  {
      typedef T result_type;
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_rvalue_from_python
  {
      typedef typename call_traits<T>::param_type result_type;
      return_rvalue_from_python();
      result_type operator()(PyObject*);
   private:
      rvalue_from_python_data<T> m_data;
  };
  
  template <class T>
  struct select_return_from_python
  {
      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
    
      BOOST_STATIC_CONSTANT(
          bool, ref = is_reference<T>::value);

      typedef typename mpl::select_type<
          ptr
          , return_pointer_from_python<T>
          , typename mpl::select_type<
              ref
              , return_reference_from_python<T>
              , return_rvalue_from_python<T>
            >::type
          >::type type;
  };
}

template <class T>
struct return_from_python
    : detail::select_return_from_python<T>::type
{
};

// Specialization as a convenience for call and call_method
template <>
struct return_from_python<void>
{
    typedef python::detail::returnable<void>::type result_type;
    
    result_type operator()(PyObject* x) const
    {
        converter::detail::absorb_result(x);
# ifdef BOOST_NO_VOID_RETURNS
        return result_type();
# endif 
    }
};

//
// Implementations
//
namespace detail
{
  template <class T>
  inline return_rvalue_from_python<T>::return_rvalue_from_python()
      : m_data(
          const_cast<registration*>(&registered<T>::converters)
          )
  {
  }
  
  template <class T>
  inline typename return_rvalue_from_python<T>::result_type
  return_rvalue_from_python<T>::operator()(PyObject* obj)
  {
      return *(T*)convert_rvalue(obj, m_data.stage1, m_data.storage.bytes);
  }

  template <class T>
  inline T return_reference_from_python<T>::operator()(PyObject* obj) const
  {
      return python::detail::void_ptr_to_reference(
          callback_convert_reference(obj, registered<T>::converters)
          , (T(*)())0);
  }

  template <class T>
  inline T return_pointer_from_python<T>::operator()(PyObject* obj) const
  {
      return T(callback_convert_pointer(obj, registered_pointee<T>::converters));
  }
}
  
}}} // namespace boost::python::converter

#endif // RETURN_FROM_PYTHON_DWA200265_HPP
