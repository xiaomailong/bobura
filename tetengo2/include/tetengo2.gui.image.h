/*! \file
    \brief The definition of tetengo2::gui::image.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_IMAGE_H)
#define TETENGO2_GUI_IMAGE_H

//#include <stdexcept>

#include <boost/bind.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.control.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for an image.
 
        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class image :
        public control<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            control<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The picture type.
        typedef typename traits_type::picture_type picture_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates an image.

            \tparam PictureReader A picture reader type.

            \param parent         A parent widget.
            \param picture_reader A picture reader.

            \throw std::runtime_error When an image cannot be created.
        */
        template <typename PictureReader>
        image(widget_type& parent, PictureReader& picture_reader)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            message_handler_details_type::make_image_message_handler_map(
                *this, message_handler_map_type()
            ),
            widget_details_type::create_image(parent)
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_p_picture(picture_reader.read())
        {
            initialize_image(this);
        }

        /*!
            \brief Destroys the image.
        */
        virtual ~image()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Fit the dimension to the dimension of the picture.
        */
        void fit_to_content()
        {
            set_client_dimension(m_p_picture->dimension());
        }


    private:
        // types

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::position_type position_type;

        typedef
            typename message_handler_details_type::message_handler_map_type
            message_handler_map_type;


        // static functions

        static void initialize_image(image* const p_image)
        {
            initialize(p_image);

            p_image->paint_observer_set().paint().connect(
                boost::bind(&image::paint_picture, p_image, _1)
            );
        }


        // variables

        const typename cpp0x::unique_ptr<picture_type>::type m_p_picture;


        // functions

        void paint_picture(canvas_type& canvas)
        const
        {
            canvas.paint_picture(
                *m_p_picture, position_type(0, 0), this->client_dimension()
            );
        }


    };


}}


#endif