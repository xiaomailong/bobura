/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_ITEM_H)
#define BOBURA_VIEW_DIAGRAM_ITEM_H

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view item.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class item : private boost::noncopyable
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;


        // constructors and destructor

        /*!
            \brief Creates an item.
        */
        item()
        {}

        /*!
            \brief Destroys the item.
        */
        virtual ~item()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

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
            Otherwise, this function returns NULL;

            \return A pointer to the item.
        */
        item* p_item_by_position(const position_type& position)
        {
            return p_item_by_position_impl(position);
        }

        /*!
            \brief Returns a ponter to the item by the position.

            When position is in the region of this item or its child, this function returns a pointer to the item.
            Otherwise, this function returns NULL;

            \return A pointer to the item.
        */
        const item* p_item_by_position(const position_type& position)
        const
        {
            return const_cast<item*>(this)->p_item_by_position_impl(position);
        }


    private:
        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const = 0;

        virtual item* p_item_by_position_impl(const position_type& position)
        = 0;


    };


}}}


#endif
