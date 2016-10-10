#include <hpx/include/thread_executors.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/server/locking_hook.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>

#include <cstdio>
#include <vector>
#include <string>

#if defined(BOOST_MSVC)
#ifdef _WIN64
typedef __int64    ssize_t;
#else
typedef _W64 int   ssize_t;
#endif
#endif

namespace hpx { namespace io { namespace server
{
	class base_file
    	: public components::locking_hook<
            components::managed_component_base<base_file> >
    {
    	base_file()
        {
            fp_ = NULL;
            file_name_.clear();
        }

        ~base_file()
        {
            close();
        }

        virtual void open(std::string const& name, std::string const& mode);
        void open_novirtual(std::string const& name, std::string const& mode)
        {
        	open(name, mode);
        }

        virtual void close();
        void close_novirtual()
        {
        	close();
        }

        virtual std::std::vector<char> read(size_t const count);
        std::std::vector<char> read_novirtual(size_t const count)
        {
        	return read(count);
        }

        virtual std::vector<char> pread(size_t const count, off_t const offset);
        std::std::vector<char> pread_novirtual(size_t const count, off_t const offset)
        {
        	return pread(count, offset);
        }

        virtual ssize_t write(std::vector<char> const& buf);
        ssize_t write_novirtual(std::vector<char> const& buf)
        {
        	return write(buf);
        }

        virtual ssize_t pwrite(std::vector<char> const& buf, off_t const offset);
        ssize_t pwrite_novirtual(std::vector<char> const& buf, off_t const offset)
        {
        	return pwrite(buf, offset);
        }

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into a action
        // type, allowing to generate all require boilerplate code for threads,
        // serialization, etc.
        HPX_DEFINE_COMPONENT_ACTION(base_file, open_novirtual, open_action);
        HPX_DEFINE_COMPONENT_ACTION(base_file, close_novirtual, close_action);
        HPX_DEFINE_COMPONENT_ACTION(base_file, read_novirtual, read_action);
        HPX_DEFINE_COMPONENT_ACTION(base_file, pread_novirtual, pread_action);
        HPX_DEFINE_COMPONENT_ACTION(base_file, write_novirtual, write_action);
        HPX_DEFINE_COMPONENT_ACTION(base_file, pwrite_novirtual, pwrite_action);

		private:
        typedef components::managed_component_base<base_file> base_type;

        std::FILE *fp_;
        std::string file_name_;
    };

}}}  // hpx::io::server

///////////////////////////////////////////////////////////////////////////////
// Declaration of serialization support for the local_file actions
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::open_action,
        base_file_open_action)
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::close_action,
        base_file_close_action)
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::read_action,
        base_file_read_action)
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::pread_action,
        base_file_pread_action)
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::write_action,
        base_file_write_action)
HPX_REGISTER_ACTION_DECLARATION(hpx::io::server::base_file::write_action,
        base_file_pwrite_action)
