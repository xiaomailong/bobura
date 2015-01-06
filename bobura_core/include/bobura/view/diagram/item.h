/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_ITEM_H)
#define BOBURA_VIEW_DIAGRAM_ITEM_H

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/view/diagram/selection.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view item.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class item : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The difference type.
        using difference_type = typename traits_type::difference_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The operating distance type.
        using operating_distance_type = typename traits_type::operating_distance_type;

        //! The canvas type.
        using canvas_type = typename traits_type::canvas_type;

        //! The position type.
        using position_type = typename canvas_type::position_type;

        //! The selection type.
        using selection_type = selection<traits_type>;


        // constructors and destructor

        /*!
            \brief Creates an item.

            \param selection A selection.
        */
        explicit item(selection_type& selection)
        :
        m_p_selection(&selection)
        {}

        /*!
            \brief Destroys the item.
        */
        virtual ~item()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Assigns an item.

            \param another Another item.

            \return This item.
        */
        item& operator=(item&& another)
        {
            if (&another == this)
                return *this;

            m_p_selection = another.m_p_selection;

            return *this;
        }

        /*!
            \brief Draws this item on the canvas.

            \param canvas A canvas.
        */
        void draw_on(canvas_type& canvas)
        const
        {
            draw_on_impl(canvas);
        }

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of this item or its child, this function returns a pointer to the item.
            Otherwise, this function returns nullptr;

            \param position A position.

            \return A pointer to the item.
        */
        item* p_item_by_position(const position_type& position)
        {
            return p_item_by_position_impl(position);
        }

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of this item or its child, this function returns a pointer to the item.
            Otherwise, this function returns nullptr;

            \param position A position.

            \return A pointer to the item.
        */
        const item* p_item_by_position(const position_type& position)
        const
        {
            return const_cast<item*>(this)->p_item_by_position_impl(position);
        }

        /*!
            \brief Returns the selection.

            \return The selection.
        */
        const selection_type& get_selection()
        const
        {
            return *m_p_selection;
        }

        /*!
            \brief Returns the selection.

            \return The selection.
        */
        selection_type& get_selection()
        {
            return *m_p_selection;
        }

        /*!
            \brief Returns the selected status.

            \return The selected status.
        */
        bool selected()
        const
        {
            return selected_impl();
        }

        /*!
            \brief Selects this item.

            \param switch_selection_style Specify true to switch the selection style.
        */
        void select(const bool switch_selection_style)
        {
            select_impl(switch_selection_style);
        }


    private:
        // variables

        selection_type* m_p_selection;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            boost::ignore_unused(canvas);
        }

        virtual item* p_item_by_position_impl(const position_type& position)
        {
            boost::ignore_unused(position);

            return nullptr;
        }

        virtual bool selected_impl()
        const
        {
            return false;
        }

        virtual void select_impl(const bool switch_selection_style)
        {
            boost::ignore_unused(switch_selection_style);
        }


    };


}}}


#endif