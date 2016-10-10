#include <hpx/hpx.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/serialization.hpp>

#include <hpxio/base_file.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

///////////////////////////////////////////////////////////////////////////////
// Add factory registration functionality
HPX_REGISTER_COMPONENT_MODULE()

///////////////////////////////////////////////////////////////////////////////
typedef hpx::io::server::base_file base_file_type;

HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    hpx::components::managed_component<base_file_type>,
    base_file, hpx::components::factory_enabled)
HPX_DEFINE_GET_COMPONENT_TYPE(base_file_type)

///////////////////////////////////////////////////////////////////////////////
// Serialization support for the base_file actions
HPX_REGISTER_ACTION(
    base_file_type::open_action,
    base_file_open_action)
HPX_REGISTER_ACTION(
    base_file_type::close_action,
    base_file_close_action)
HPX_REGISTER_ACTION(
    base_file_type::read_action,
    base_file_read_action)
HPX_REGISTER_ACTION(
    base_file_type::pread_action,
    base_file_pread_action)
HPX_REGISTER_ACTION(
    base_file_type::write_action,
    base_file_write_action)
HPX_REGISTER_ACTION(
    base_file_type::pwrite_action,
    base_file_pwrite_action)