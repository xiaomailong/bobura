/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINKIND_H)
#define BOBURA_MODEL_TRAINKIND_H

#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train kind.

        \tparam String A string type.
        \tparam Color  A color type.
    */
    template <typename String, typename Color>
    class train_kind : private boost::equality_comparable<train_kind<String, Color>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The color type.
        typedef Color color_type;

        //! The weight type.
        enum weight_type
        {
            weight_normal, //!< Normal.
            weight_bold,   //!< Bold.
        };

        //! The line style type.
        enum line_style_type
        {
            line_style_solid,      //!< Solid.
            line_style_dashed,     //!< Dashed.
            line_style_dotted,     //!< Dotted.
            line_style_dot_dashed, //!< Dot-Dashed.
        };


        // constructors and destructor

        /*!
            \brief Creates a train kind.

            \tparam S1 A string type #1.
            \tparam S2 A string type #2.
            \tparam C  A color type.

            \param name         A name.
            \param abbreviation An abbreviated name.
            \param color        A color.
            \param weight       A weight.
            \param line_style   A line style.
        */
        template <typename S1, typename S2, typename C>
        train_kind(
            S1&&                  name,
            S2&&                  abbreviation,
            C&&                   color,
            const weight_type     weight,
            const line_style_type line_style
        )
        :
        m_name(std::forward<S1>(name)),
        m_abbreviation(std::forward<S2>(abbreviation)),
        m_color(std::forward<C>(color)),
        m_weight(weight),
        m_line_style(line_style)
        {}


        // functions

        /*!
            \brief Checks whether one train kind is equal to another.

            \param one     One train kind.
            \param another Another train kind.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train_kind& one, const train_kind& another)
        {
            return
                one.m_name == another.m_name &&
                one.m_abbreviation == another.m_abbreviation &&
                one.m_color == another.m_color &&
                one.m_weight == another.m_weight &&
                one.m_line_style == another.m_line_style;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the abbreviated name.

            \return The abbreviated name.
        */
        const string_type& abbreviation()
        const
        {
            return m_abbreviation;
        }


    private:
        // variables

        string_type m_name;

        string_type m_abbreviation;

        color_type m_color;

        weight_type m_weight;

        line_style_type m_line_style;


    };


}}


#endif
