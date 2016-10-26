//  Copyright (c) 2016 Hartmut Kaiser
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

        hpx::future<void> open(std::string const& name, std::string const& mode)
        {
            typedef hpx::io::server::base_file::open_action open_action;
            return hpx::async(open_action(), this->get_id(), name, mode);
        }
        void open(hpx::launch::sync_policy, std::string const& name,
            std::string const& mode)
        {
            typedef hpx::io::server::base_file::open_action open_action;
            open_action()(this->get_id(), name, mode);
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

        hpx::future<ssize_t> write(std::vector<char> const& buf)
        {
            typedef hpx::io::server::base_file::write_action write_action;
            return hpx::async(write_action(), this->get_id(), buf);
        }
        ssize_t write(hpx::launch::sync_policy, std::vector<char> const& buf)
        {
            typedef hpx::io::server::base_file::write_action write_action;
            return write_action()(this->get_id(), buf);
        }
    };
}}

#endif

