/*! \file
    \brief The definition of bobura::view::scale_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_SCALELIST_H)
#define BOBURA_VIEW_SCALELIST_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>


namespace bobura { namespace view
{
    /*!
        \brief The class template for a view scale list.

        \tparam Scale  A scale type.
        \tparam Size   A size type.
        \tparam String A string type.
    */
    template <typename Scale, typename Size, typename String>
    class scale_list : boost::noncopyable
    {
    public:
        // types

        //! The scale type.
        using scale_type = Scale;

        //! The size type.
        using size_type = Size;

        //! The string type.
        using string_type = String;


        // functions

        /*!
            \brief Returns the scale count.

            \return The scale count.
        */
        size_type size()
        const
        {
            assert(scales().size() == labels().size());
            return scales().size();
        }

        /*!
            \brief Returns the scale at the specified index.

            \param index An index.

            \return The scale.

            \throw std::out_of_range When index is out of range.
        */
        const scale_type& at(const size_type index)
        const
        {
            if (index >= scales().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return scales()[index];
        }

        /*!
            \brief Returns the scale label at the specified index.

            \param index An index.

            \return The scale label.

            \throw std::out_of_range When index is out of range.
        */
        const string_type& label_at(const size_type index)
        const
        {
            if (index >= labels().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return labels()[index];
        }

        /*!
            \brief Returns the same scale index.

            \param scale A scale.

            \return The same scale index.
        */
        boost::optional<size_type> index_of(const scale_type& scale)
        const
        {
            for (size_type i = 0; i < scales().size(); ++i)
            {
                if (scales()[i] == scale)
                    return boost::make_optional(i);
            }
            return boost::none;
        }

        /*!
            \brief Returns the nearest larger scale.
        
            \param scale A scale.

            \return The nearest larger scale.
        */
        const scale_type& larger(const scale_type& scale)
        const
        {
            const auto found =
                std::find_if(
                    scales().begin(),
                    scales().end(),
                    [&scale](const scale_type& candidate) { return candidate > scale; }
                );
            return found != scales().end() ? *found : scales().back();
        }

        /*!
            \brief Returns the nearest smaller scale.
        
            \param scale A scale.

            \return The nearest smaller scale.
        */
        const scale_type& smaller(const scale_type& scale)
        const
        {
            const auto found =
                std::find_if(
                    scales().rbegin(),
                    scales().rend(),
                    [&scale](const scale_type& candidate) { return candidate < scale; }
                );
            return found != scales().rend() ? *found : scales().front();
        }


    private:
        // static functions

        static const std::vector<scale_type>& scales()
        {
            static const std::vector<scale_type> singleton(make_scales());
            return singleton;
        }

        static const std::vector<string_type>& labels()
        {
            static const std::vector<string_type> singleton(make_labels());
            return singleton;
        }

        static std::vector<scale_type> make_scales()
        {
            std::vector<scale_type> scales;

            scales.emplace_back(1, 10);
            scales.emplace_back(1, 4);
            scales.emplace_back(1, 2);
            scales.emplace_back(3, 4);
            scales.emplace_back(1);
            scales.emplace_back(3, 2);
            scales.emplace_back(2);
            scales.emplace_back(4);

            assert(std::is_sorted(scales.begin(), scales.end(), std::less<scale_type>()));
            return scales;
        }

        static std::vector<string_type> make_labels()
        {
            std::vector<string_type> labels;

            labels.emplace_back(TETENGO2_TEXT("10%"));
            labels.emplace_back(TETENGO2_TEXT("25%"));
            labels.emplace_back(TETENGO2_TEXT("50%"));
            labels.emplace_back(TETENGO2_TEXT("75%"));
            labels.emplace_back(TETENGO2_TEXT("100%"));
            labels.emplace_back(TETENGO2_TEXT("150%"));
            labels.emplace_back(TETENGO2_TEXT("200%"));
            labels.emplace_back(TETENGO2_TEXT("400%"));

            assert(labels.size() == scales().size());
            return labels;
        }


    };


}}


#endif
