/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if defined(_MSC_VER) && !defined(NDEBUG)

// The standard library headers

#include <algorithm>
#include <cstddef>
#include <exception>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>


// Boost library headers

#include <boost/bind.hpp>
#include <boost/concept_check.hpp>
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/program_options.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signal.hpp>


// Windows headers

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>


#endif
