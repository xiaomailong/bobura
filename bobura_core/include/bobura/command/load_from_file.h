/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <memory>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class load_from_file : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The file loading type.
        using load_from_file_type = boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type;

        //! The parameter type.
        class parameter_type : public parameter_base
        {
        public:
            /*!
                \brief Creates a parameter.

                \param path A path.
            */
            explicit parameter_type(boost::filesystem::path path);

            /*!
                \brief Destroys the parameter.
            */
            virtual ~parameter_type()
            TETENGO2_STDALT_NOEXCEPT;

            /*!
                \brief Returns the path.

                \return The path.
            */
            const boost::filesystem::path& path()
            const;

        private:
            boost::filesystem::path m_path;

        };


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
        */
        explicit load_from_file(const load_from_file_type& load_from_file);

        /*!
            \brief Destroys the load-from-file command.
        */
        virtual ~load_from_file()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const override;

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;

        virtual void execute_impl(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
        const;


    };


}}


#endif
