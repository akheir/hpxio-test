//  Copyright (c) 2016 Hartmut Kaiser
//  Copyright (c) 2016 Alireza Kheirkhahan
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_IO_BASE_FILE_HPP)
#define HPX_IO_BASE_FILE_HPP

#include <hpx/include/async.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/lcos.hpp>

#include <hpxio/server/base_file.hpp>

#include <utility>
#include <vector>
#include <string>

namespace hpx { namespace io
{
    class base_file
      : public hpx::components::client_base<base_file, server::base_file>
    {
        typedef hpx::components::client_base<base_file, server::base_file>
            base_type;

    public:
        base_file() {}

        base_file(hpx::future<hpx::id_type> && f)
          : base_type(std::move(f))
        {}

        ~base_file()
        {
            close(hpx::launch::sync);
        }

        hpx::future<void> open(std::string const& name, int const flag)
        {
            typedef hpx::io::server::base_file::open_action open_action;
            return hpx::async(open_action(), this->get_id(), name, flag);
        }
        void open(hpx::launch::sync_policy, std::string const& name,
            int const flag)
        {
            typedef hpx::io::server::base_file::open_action open_action;
            open_action()(this->get_id(), name, flag);
        }

        hpx::future<bool> is_open()
        {
            typedef hpx::io::server::base_file::is_open_action is_open_action;
            return hpx::async(is_open_action(), this->get_id());
        }
        bool is_open(hpx::launch::sync_policy)
        {
            typedef hpx::io::server::base_file::is_open_action is_open_action;
            return is_open_action()(this->get_id());
        }

        hpx::future<void> close()
        {
            typedef hpx::io::server::base_file::close_action close_action;
            return hpx::async(close_action(), this->get_id());
        }
        void close(hpx::launch::sync_policy)
        {
            typedef hpx::io::server::base_file::close_action close_action;
            return close_action()(this->get_id());
        }

        hpx::future<int> remove_file(std::string const& file_name)
        {
            typedef hpx::io::server::base_file::remove_file_action remove_file_action;
            return hpx::async(remove_file_action(), this->get_id(), file_name);
        }
        int remove_file(hpx::launch::sync_policy, std::string const& file_name)
        {
            typedef hpx::io::server::base_file::remove_file_action remove_file_action;
            return remove_file_action()(this->get_id(), file_name);
        }

        hpx::future<hpx::serialization::serialize_buffer<char> > read(size_t const count)
        {
            typedef hpx::io::server::base_file::read_action read_action;
            return hpx::async(read_action(), this->get_id(), count);
        }
        hpx::serialization::serialize_buffer<char> read(hpx::launch::sync_policy,
            size_t const count)
        {
            typedef hpx::io::server::base_file::read_action read_action;
            return read_action()(this->get_id(), count);
        }

        hpx::future<hpx::serialization::serialize_buffer<char> > pread(size_t const count,
            off_t const offset)
        {
            typedef hpx::io::server::base_file::pread_action pread_action;
            return hpx::async(pread_action(), this->get_id(), count, offset);
        }
        hpx::serialization::serialize_buffer<char> pread(hpx::launch::sync_policy,
            size_t const count, off_t const offset)
        {
            typedef hpx::io::server::base_file::pread_action pread_action;
            return pread_action()(this->get_id(), count, offset);
        }

        hpx::future<ssize_t> write(hpx::serialization::serialize_buffer<char> const& buf)
        {
            typedef hpx::io::server::base_file::write_action write_action;
            return hpx::async(write_action(), this->get_id(), buf);
        }
        ssize_t write(hpx::launch::sync_policy,
            hpx::serialization::serialize_buffer<char> const& buf)
        {
            typedef hpx::io::server::base_file::write_action write_action;
            return write_action()(this->get_id(), buf);
        }

        hpx::future<ssize_t> pwrite(hpx::serialization::serialize_buffer<char> const& buf,
            off_t const offset)
        {
            typedef hpx::io::server::base_file::pwrite_action pwrite_action;
            return hpx::async(pwrite_action(), this->get_id(), buf, offset);
        }
        ssize_t pwrite(hpx::launch::sync_policy,
            hpx::serialization::serialize_buffer<char> const& buf, off_t const offset)
        {
            typedef hpx::io::server::base_file::pwrite_action pwrite_action;
            return pwrite_action()(this->get_id(), buf, offset);
        }

        hpx::future<off_t> lseek(off_t const offset, int const whence)
        {
            typedef hpx::io::server::base_file::lseek_action lseek_action;
            return hpx::async(lseek_action(), this->get_id(), offset, whence);
        }
        off_t lseek(hpx::launch::sync_policy, off_t const offset, int const whence)
        {
            typedef hpx::io::server::base_file::lseek_action lseek_action;
            return lseek_action()(this->get_id(), offset, whence);
        }
    };
}}

#endif

