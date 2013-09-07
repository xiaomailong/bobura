/*! \file
    \brief The definition of tetengo2::gui::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ICON_H)
#define TETENGO2_GUI_ICON_H

#include <cassert>
#include <utility>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for an icon.

        \tparam Path      A path type.
        \tparam Dimension A dimension type.
        \tparam Details   A detail implementation type.
    */
    template <typename Path, typename Dimension, typename Details>
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The path type.
        typedef Path path_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The detail implementation type.
        typedef Details details_type;

        //! The icon details type.
        typedef typename details_type::icon_details_type icon_details_type;

        //! The icon details pointer type.
        typedef typename details_type::icon_details_ptr_type icon_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an icon.

            The dimension is determined by the system.

            \param path A path.
        */
        explicit icon(path_type path)
        :
        m_path(std::move(path)),
        m_dimension(details_type::template default_dimension<dimension_type>()),
        m_p_icon_details(details_type::create(m_path, m_dimension))
        {}

        /*!
            \brief Creates an icon.

            \param path      A path.
            \param dimension A dimension.
        */
        icon(path_type path, dimension_type dimension)
        :
        m_path(std::move(path)),
        m_dimension(std::move(dimension)),
        m_p_icon_details(details_type::create(m_path, m_dimension))
        {}


        // functions

        /*!
            \brief Returns the path.

            \return The path.
        */
        const path_type& path()
        const
        {
            return m_path;
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const icon_details_type& details()
        const
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        icon_details_type& details()
        {
            assert(m_p_icon_details);
            return *m_p_icon_details;
        }


    private:
        // variables

        const path_type m_path;

        const dimension_type m_dimension;

        const icon_details_ptr_type m_p_icon_details;


    };


}}

#endif