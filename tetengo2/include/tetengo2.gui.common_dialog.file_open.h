/*! \file
    \brief The definition of tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H)
#define TETENGO2_GUI_COMMONDIALOG_FILEOPEN_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a file open dialog.

        \tparam Widget              A widget type.
        \tparam String              A string type.
        \tparam Path                A path type.
        \tparam CommonDialogDetails A detail implementation type of common
                                    dialogs.
    */
    template <
        typename Widget,
        typename String,
        typename Path,
        typename CommonDialogDetails
    >
    class file_open : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef
            typename common_dialog_details_type::file_open_dialog_details_type
            details_type;

        //! The detail implementaiton pointer type;

        typedef
            typename common_dialog_details_type::file_open_dialog_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a file open dialog.

            \param parent A parent widget.
        */
        file_open(widget_type& parent)
        :
        m_p_details(
            common_dialog_details_type::create_file_open_dialog(parent)
        ),
        m_result()
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const path_type& result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.
        */
        void do_modal()
        {

        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // variables

        details_ptr_type m_p_details;

        path_type m_result;


    };


}}}


#endif
