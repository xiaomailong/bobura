/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if defined(_MSC_VER)

// The standard library headers

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <exception>
#include <functional>
#include <ios>
#include <iterator>
#include <limits>
#include <locale>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


// Boost library headers

#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/concept_check.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/mem_fn.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/program_options.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scope_exit.hpp>
#include <boost/scoped_array.hpp>
#include <boost/signal.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/utility.hpp>


// Windows headers

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#endif
