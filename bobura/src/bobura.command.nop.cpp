/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.nop.h"


namespace bobura { namespace command
{
    class nop::impl
    {
    public:
        // types

        typedef nop::model_type model_type;

        typedef nop::abstract_window_type abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {}


    };


    nop::nop()
    :
    m_p_impl(tetengo2::make_unique<impl>())
    {}

    nop::~nop()
    {}
    
    void nop::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}