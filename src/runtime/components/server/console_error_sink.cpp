//  Copyright (c) 2007-2010 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <iostream>

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/ini.hpp>
#include <hpx/util/util.hpp>
#include <hpx/runtime/components/server/console_error_sink.hpp>
#include <hpx/runtime/components/server/console_error_sink_singleton.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

#include <hpx/util/serialize_exception.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components { namespace server
{
    ///////////////////////////////////////////////////////////////////////////
    // implementation of this console error sink
    void console_error_sink(boost::uint32_t src, boost::exception_ptr const& e)
    {
        try {
            boost::rethrow_exception(e);
        }
        catch (boost::exception const& be) {
            // extract error information
            HPX_OSSTREAM strm;
            strm << boost::diagnostic_information(be);

            // dispatch this error to registered functions
            get_error_dispatcher()(src, HPX_OSSTREAM_GETSTRING(strm));
        }
    }
}}}

// This must be in global namespace
HPX_REGISTER_ACTION_EX(hpx::components::server::console_error_sink_action,
    console_error_sink_action);

