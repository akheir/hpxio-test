//  Copyright (c) 2016 Hartmut Kaiser
//  Copyright (c) 2016 Alireza Kheirkhahan
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/serialization.hpp>

#include "hpxio/server/local_file.hpp"
#if defined(HPX_HAVE_ORANGEFS)
#include "hpxio/server/orangefs_file.hpp"
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

///////////////////////////////////////////////////////////////////////////////
// Add factory registration functionality
HPX_REGISTER_COMPONENT_MODULE()

///////////////////////////////////////////////////////////////////////////////
typedef hpx::components::component<hpx::io::server::local_file> local_file_type;
HPX_REGISTER_DERIVED_COMPONENT_FACTORY(
    local_file_type, local_file_component,
    "base_file_component", hpx::components::factory_enabled)
HPX_DEFINE_GET_COMPONENT_TYPE(local_file_type::wrapped_type)

#if defined(HPX_HAVE_ORANGEFS)
typedef hpx::components::component<hpx::io::server::orangefs_file> orangefs_file_type;
HPX_REGISTER_DERIVED_COMPONENT_FACTORY(
    orangefs_file_type, orangefs_file_component,
    "base_file_component", hpx::components::factory_enabled)
HPX_DEFINE_GET_COMPONENT_TYPE(orangefs_file_type::wrapped_type)
#endif

///////////////////////////////////////////////////////////////////////////////
// Serialization support for the base_file actions
typedef hpx::io::server::base_file base_file_type;

HPX_REGISTER_ACTION(base_file_type::open_action, base_file_open_action)
HPX_REGISTER_ACTION(base_file_type::is_open_action, base_file_is_open_action)
HPX_REGISTER_ACTION(base_file_type::close_action, base_file_close_action)
HPX_REGISTER_ACTION(base_file_type::remove_file_action, base_file_remove_file_action)
HPX_REGISTER_ACTION(base_file_type::read_action, base_file_read_action)
HPX_REGISTER_ACTION(base_file_type::pread_action, base_file_pread_action)
HPX_REGISTER_ACTION(base_file_type::write_action, base_file_write_action)
HPX_REGISTER_ACTION(base_file_type::pwrite_action, base_file_pwrite_action)
HPX_REGISTER_ACTION(base_file_type::lseek_action, base_file_lseek_action)

HPX_DEFINE_GET_COMPONENT_TYPE(base_file_type)
