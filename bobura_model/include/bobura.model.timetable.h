/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam String          A string type.
        \tparam StationLocation A station location type.
        \tparam Train           A train type.
    */
    template <typename String, typename StationLocation, typename Train>
    class timetable :
        private boost::equality_comparable<
            timetable<String, StationLocation, Train>
        >
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.

            \tparam S A string type.

            \param title A title.
        */
        template <typename S>
        explicit timetable(S&& title)
        :
        m_title(std::forward<S>(title)),
        m_station_locations(),
        m_trains()
        {}

        /*!
            \brief Creates a timetalble.

            \tparam S   A string type.
            \tparam SLs A station locations type.

            \param title             A title.
            \param station_locations The station locations
        */
        template <typename S, typename SLs>
        timetable(S&& title, SLs&& station_locations)
        :
        m_title(std::forward<S>(title)),
        m_station_locations(std::forward<SLs>(station_locations)),
        m_trains()
        {}

        /*!
            \brief Creates a timetalble.

            \tparam S             A string type.
            \tparam InputIterator An input iterator for station locations.

            \param title                  A title.
            \param station_location_first The first iterator among station
                                          locations.
            \param station_location_last  The last iterator among station
                                          locations.
        */
        template <typename S, typename InputIterator>
        timetable(
            S&&                 title,
            const InputIterator station_location_first,
            const InputIterator station_location_last
        )
        :
        m_title(std::forward<S>(title)),
        m_station_locations(station_location_first, station_location_last),
        m_trains()
        {}


        // functions

        /*!
            \brief Checks whether this is equal to another timetable.

            \param one     One timetable.
            \param another Another timetable.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const timetable& one, const timetable& another)
        {
            return one.m_station_locations == another.m_station_locations &&
                one.m_trains == another.m_trains;
        }

        /*!
            \brief Returns the title.

            \return The title.
        */
        const string_type& title()
        const
        {
            return m_title;
        }

        /*!
            \brief Sets a title.

            \tparam S A string type.

            \param title A title.
        */
        template <typename S>
        void set_title(S&& title)
        {
            m_title = std::forward<S>(title);
        }

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations()
        const
        {
            return m_station_locations;
        }

        /*!
            \brief Inserts a station location.

            After the insertion, the station locations must be sequenced in
            ascending order.

            It also inserts a stop to the every train with uninitialized
            arrival and departure time and an empty platform, so that the
            count of the station locations coincides with the one of the every
            train stop.

            \tparam SL A station location type.

            \param position         A position where a station location is
                                    inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not
                                         sequenced in ascending order after
                                         the insertion.
        */
        template <typename SL>
        void insert_station_location(
            const typename station_locations_type::const_iterator
                 position,
            SL&& station_location
        )
        {
            if (!can_insert_to(position, station_location))
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The insertion position is invalid."
                    )
                );
            }

            const difference_type offset =
                std::distance<
                    typename station_locations_type::const_iterator
                >(m_station_locations.begin(), position);

            m_station_locations.insert(
                to_mutable(position, m_station_locations),
                std::forward<SL>(station_location)
            );

            std::for_each(
                m_trains.begin(),
                m_trains.end(),
                TETENGO2_CPP11_BIND(
                    insert_train_stop,
                    tetengo2::cpp11::placeholders_1(),
                    offset
                )
            );
        }

        /*!
            \brief Erases the station locations.

            It also erases stops from the every train, so that the count of
            the station locations coincides with the one of the every train
            stop.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator first,
            const typename station_locations_type::const_iterator last
        )
        {
            const difference_type first_offset =
                std::distance<
                    typename station_locations_type::const_iterator
                >(m_station_locations.begin(), first);
            const difference_type last_offset =
                std::distance<
                    typename station_locations_type::const_iterator
                >(m_station_locations.begin(), last);

            m_station_locations.erase(
                to_mutable(first, m_station_locations),
                to_mutable(last, m_station_locations)
            );

            std::for_each(
                m_trains.begin(),
                m_trains.end(),
                TETENGO2_CPP11_BIND(
                    erase_train_stops,
                    tetengo2::cpp11::placeholders_1(),
                    first_offset,
                    last_offset
                )
            );
        }

        /*!
            \brief Returns the trains.

            \return The trains
        */
        const trains_type& trains()
        const
        {
            return m_trains;
        }

        /*!
            \brief Inserts a train.

            The count of train stops must coincide with the one of the station
            locations.

            \tparam T A train type.

            \param position A position where a train is inserted.
            \param train    A train.

            \throw std::invalid_argument When the count of the stops of a
                                         train does not coincide with the one
                                         of the station locations.
        */
        template <typename T>
        void insert_train(
            const typename trains_type::const_iterator position,
            T&&                                        train
        )
        {
            if (train.stops().size() != m_station_locations.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The count of the train stops does not coincide with "
                        "the one of the station locations."
                    )
                );
            }

            m_trains.insert(
                to_mutable(position, m_trains), std::forward<T>(train)
            );
        }

        /*!
            \brief Erases the trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            m_trains.erase(
                to_mutable(first, m_trains), to_mutable(last, m_trains)
            );
        }


    private:
        // types

        typedef
            typename train_type::stops_type::difference_type difference_type;


        // static functions

        static void insert_train_stop(
            train_type&           train,
            const difference_type offset
        )
        {
            train.insert_stop(
                train.stops().begin() + offset,
                typename train_type::stop_type(
                    train_type::stop_type::time_type::uninitialized(),
                    train_type::stop_type::time_type::uninitialized(),
                    typename train_type::stop_type::platform_type()
                )
            );
        }

        static void erase_train_stops(
            train_type&           train,
            const difference_type first_offset,
            const difference_type last_offset
        )
        {
            train.erase_stops(
                train.stops().begin() + first_offset,
                train.stops().begin() + last_offset
            );
        }


        // variables

        string_type m_title;

        station_locations_type m_station_locations;

        trains_type m_trains;


        // functions

        bool can_insert_to(
            const typename station_locations_type::const_iterator
                                         position,
            const station_location_type& station_location
        )
        const
        {
            if (
                position != m_station_locations.begin() &&
                !boost::prior(position)->before(station_location)
            )
            {
                return false;
            }

            if (
                position != m_station_locations.end() &&
                !station_location.before(*position)
            )
            {
                return false;
            }

            return true;
        }

        template <typename Container>
        typename Container::iterator to_mutable(
            const typename Container::const_iterator const_iter,
            Container&                               container
        )
        {
            typename Container::iterator mutable_iter = container.begin();
            std::advance(
                mutable_iter,
                std::distance<typename Container::const_iterator>(
                    container.begin(), const_iter
                )
            );
            return mutable_iter;
        }


    };


}}


#endif
