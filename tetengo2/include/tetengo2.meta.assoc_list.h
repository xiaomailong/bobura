/*! \file
    \brief The definition of tetengo2::meta::assoc_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_META_ASSOCLIST_H)
#define TETENGO2_META_ASSOCLIST_H

#include <cstddef>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/void.hpp>


namespace tetengo2 { namespace meta
{
    /*!
        \brief The metaclass for a node of an associative list.

        \tparam Value A value.
        \tparam Next  A next node.
    */
    template <typename Value, typename Next>
    struct assoc_list
    {
        // types

        //! The value.
        typedef Value value;

        //! The next node.
        typedef Next next;

        //! The category.
        typedef boost::mpl::forward_iterator_tag category;


    };


#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename AssocList, std::size_t Size>
        struct assoc_list_size
        {
            typedef
                typename assoc_list_size<
                    typename AssocList::next, Size + 1
                >::type
                type;
        };

        template <std::size_t Size>
        struct assoc_list_size<boost::mpl::void_, Size>
        {
            typedef boost::mpl::size_t<Size> type;
        };


    }
#endif


}}

#if !defined(DOCUMENTATION)
namespace boost { namespace mpl
{
    // functions

    // boost::mpl::deref
    template <typename Value, typename Next>
    struct deref<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef Value type;
    };

    // boost::mpl::next
    template <typename Value, typename Next>
    struct next<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef Next type;
    };

    // boost::mpl::begin
    template <typename Value, typename Next>
    struct begin<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef tetengo2::meta::assoc_list<Value, Next> type;
    };

    // boost::mpl::end
    template <typename Value, typename Next>
    struct end<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef boost::mpl::void_ type;
    };

    // boost::mpl::size
    template <typename Value, typename Next>
    struct size<tetengo2::meta::assoc_list<Value, Next> >
    {
        typedef
            typename tetengo2::meta::detail::assoc_list_size<
                tetengo2::meta::assoc_list<Value, Next>, 0
            >::type
            type;
    };

    template <>
    struct size<boost::mpl::void_>
    {
        typedef boost::mpl::size_t<0> type;
    };

}}
#endif


#endif
