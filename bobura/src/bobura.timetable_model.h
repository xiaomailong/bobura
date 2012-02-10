/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <cassert>
#include <cstddef>
//#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.unique.h>


namespace bobura
{
   /*!
        \brief The class template for a model.

        \tparam Timetable       A timetable type.
        \tparam Path            A path type.
        \tparam ObserverSet     A observer set type.
    */
    template <typename Timetable, typename Path, typename ObserverSet>
    class timetable_model : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The observer set type.
        typedef ObserverSet observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a model.
        */
        timetable_model()
        :
        m_p_timetable(
            tetengo2::make_unique<timetable_type>(string_type())
        ),
        m_path(),
        m_changed(false),
        m_observer_set()
        {
            set_timetable_observer_set();
        }


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
            \brief Returns the timetable.

            \return The timetable.
        */
        const timetable_type& timetable()
        const
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Returns the timetable.

            \return The timetable.
        */
        timetable_type& timetable()
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        /*!
            \brief Resets a timetable.

            \tparam P A path type.

            \param p_timetable A unique pointer to a timetable.
            \param path        A path.

            \throw std::invalid_argument When p_timetable is NULL.
        */
        template <typename P>
        void reset_timetable(
            std::unique_ptr<timetable_type> p_timetable,
            P&&                             path
        )
        {
            if (!p_timetable)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Timetable is NULL.")
                );
            }

            m_p_timetable = std::move(p_timetable);
            m_path = std::forward<P>(path);
            m_changed = false;

            set_timetable_observer_set();

            m_observer_set.reset()();
        }

        /*!
            \brief Checks whether the model is changed.

            \retval true  When the model is changed.
            \retval false Otherwise.
        */
        bool changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Sets a changed status.

            \param changed A changed status.
        */
        void set_changed(const bool changed)
        {
            m_changed = changed;

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // types

        typedef typename timetable_type::string_type string_type;

        class timetable_changed
        {
        public:
            timetable_changed(timetable_model& self)
            :
            m_self(self)
            {}

            void operator()()
            {
                m_self.set_changed(true);
            }

        private:
            timetable_model& m_self;

        };


        // variables

        std::unique_ptr<timetable_type> m_p_timetable;

        path_type m_path;

        bool m_changed;

        observer_set_type m_observer_set;


        // functions

        void set_timetable_observer_set()
        {
            m_p_timetable->observer_set().changed().connect(
                timetable_changed(*this)
            );
        }


    };


}

#endif
