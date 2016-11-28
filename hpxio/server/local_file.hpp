//  Copyright (c) 2016 Hartmut Kaiser
//  Copyright (c) 2016 Alireza Kheirkhahan
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_IO_SERVER_LOCAL_FILE_HPP)
#define HPX_IO_SERVER_LOCAL_FILE_HPP

#include <hpxio/server/base_file.hpp>

/* ------------------------  POSIX headears --------------------- */

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
} //extern "C" {
#endif

/* -------------------------  end POSIX headears  --------------- */

///////////////////////////
namespace hpx { namespace io { namespace server
{
    class HPX_COMPONENT_EXPORT local_file
      : public base_file,
        public components::locking_hook<components::component_base<local_file> >
    {
    public:
        local_file() : fd_(-1)
        {
        }

        ~local_file()
        {
            close();
        }

        void open(std::string const& name, int const flag)
        {
            // Get a reference to one of the IO specific HPX io_service objects ...
            hpx::threads::executors::io_pool_executor scheduler;

            // ... and schedule the handler to run on one of its OS-threads.
            scheduler.add(hpx::util::bind(&local_file::open_work, this,
                        boost::ref(name), flag));

            // Note that the destructor of the scheduler object will wait for
            // the scheduled task to finish executing.
        }

        void open_work(std::string const& name, int const flag)
        {
            if (fd_ >= 0)
            {
                close();
            }
            if (flag & O_CREAT)
            {
                fd_ = ::open(name.c_str(), flag, 0644);
            } else
            {
                fd_ = ::open(name.c_str(), flag);
            }
            file_name_ = name;
        }

        bool is_open() 
        {
            return fd_ >= 0;
        }

        void close()
        {
            hpx::threads::executors::io_pool_executor scheduler;
            scheduler.add(hpx::util::bind(&local_file::close_work, this));
        }

        void close_work()
        {
            if (fd_ >= 0)
            {
                ::close(fd_);
                fd_ = -1;
            }
            file_name_.clear();
        }

        int remove_file(std::string const& file_name)
        {
            int result;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::remove_file_work,
                            this, boost::ref(file_name), boost::ref(result)));
            }
            return result;
        }

        void remove_file_work(std::string const& file_name, int &result)
        {
            result = ::unlink(file_name.c_str());
        }

        std::vector<char> read(size_t const count)
        {
            std::vector<char> result;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::read_work,
                            this, count, boost::ref(result)));
            }
            return result;
        }

        void read_work(size_t const count, std::vector<char>& result)
        {
            if (fd_ < 0 || count <= 0)
            {
                return;
            }

            std::unique_ptr<char> sp(new char[count]);
            ssize_t len = ::read(fd_, sp.get(), count);

            if (len == 0)
            {
                return;
            }

            result.assign(sp.get(), sp.get() + len);
        }

        std::vector<char> pread(size_t const count, off_t const offset)
        {
            std::vector<char> result;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::pread_work,
                            this, count, offset, boost::ref(result)));
            }
            return result;
        }

        void pread_work(size_t const count, off_t const offset,
                std::vector<char>& result)
        {
            if (fd_ < 0 || count <= 0 || offset < 0)
            {
                return;
            }

            std::unique_ptr<char[]> sp(new char[count]);
            ssize_t len = ::pread(fd_, sp.get(), count, offset);

            if (len == 0)
            {
                return;
            }

            result.assign(sp.get(), sp.get() + len);
        }

        ssize_t write(std::vector<char> const& buf)
        {
            ssize_t result = 0;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::write_work,
                            this, boost::ref(buf), boost::ref(result)));
            }
            return result;
        }

        void write_work(std::vector<char> const& buf, ssize_t& result)
        {
            if (fd_ < 0|| buf.empty())
            {
                return;
            }
            result = ::write(fd_, buf.data(), buf.size());
        }

        ssize_t pwrite(std::vector<char> const& buf, off_t const offset)
        {
            ssize_t result = 0;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::pwrite_work,
                    this, boost::ref(buf), offset, boost::ref(result)));
            }
            return result;
        }

        void pwrite_work(std::vector<char> const& buf,
                off_t const offset, ssize_t& result)
        {
            if (fd_ < 0 || buf.empty() || offset < 0)
            {
                return;
            }

            result = ::pwrite(fd_, buf.data(), buf.size(), offset);
        }

        int lseek(off_t const offset, int const whence)
        {
            int result;
            {
                hpx::threads::executors::io_pool_executor scheduler;
                scheduler.add(hpx::util::bind(&local_file::lseek_work,
                    this, offset, whence, boost::ref(result)));
            }
            return result;
        }

        void lseek_work(off_t const offset, int const whence, int& result)
        {
            if (fd_ < 0)
            {
                result = -1;
                return;
            }

            result = ::lseek(fd_, offset, whence);
        }

    private:

        int fd_;
        std::string file_name_;
    };

}}} // hpx::io::server

#endif
