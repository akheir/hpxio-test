#include <hpxio/server/base_file.hpp>


///////////////////////////
namespace hpx { namespace io { namespace server
{
    class local_file
      : public base_file
    {
      public:

        local_file()
        {
            fp_ = NULL;
            file_name_.clear();
        }

        ~local_file()
        {
            close();
        }

        void open(std::string const& name, std::string const& mode)
        {
            // Get a reference to one of the IO specific HPX io_service objects ...
            hpx::threads::executors::io_pool_executor scheduler;

            // ... and schedule the handler to run on one of its OS-threads.
            scheduler.add(hpx::util::bind(&local_file::open_work, this,
                        boost::ref(name), boost::ref(mode)));

            // Note that the destructor of the scheduler object will wait for
            // the scheduled task to finish executing.
        }

        void open_work(std::string const& name, std::string const& mode)
        {
            if (fp_ != NULL)
            {
                close();
            }
            fp_ = fopen(name.c_str(), mode.c_str());
            file_name_ = name;
        }

		void close()
        {
            hpx::threads::executors::io_pool_executor scheduler;

            scheduler.add(hpx::util::bind(&local_file::close_work, this));

        }

        void close_work()
        {
            if (fp_ != NULL)
            {
                std::fclose(fp_);
                fp_ = NULL;
            }
            file_name_.clear();
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
            if (fp_ == NULL || count <= 0)
            {
                return;
            }

            std::unique_ptr<char> sp(new char[count]);
            ssize_t len = fread(sp.get(), 1, count, fp_);

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
            if (fp_ == NULL || count <= 0 || offset < 0)
            {
                return;
            }

            fpos_t pos;
            if (fgetpos(fp_, &pos) != 0)
            {
                return;
            }

            if (fseek(fp_, offset, SEEK_SET) != 0)
            {
                fsetpos(fp_, &pos);
                return;
            }

            read_work(count, result);
            fsetpos(fp_, &pos);
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
            if (fp_ == NULL || buf.empty())
            {
                return;
            }
            result = fwrite(buf.data(), 1, buf.size(), fp_);
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
            if (fp_ == NULL || buf.empty() || offset < 0)
            {
                return;
            }

            fpos_t pos;
            if (fgetpos(fp_, &pos) != 0)
            {
                return;
            }

            if (fseek(fp_, offset, SEEK_SET) != 0)
            {
                fsetpos(fp_, &pos);
                return;
            }

            write_work(buf, result);
            fsetpos(fp_, &pos);
        }

        private:

        std::FILE *fp_;
        std::string file_name_;
    };

}}} // hpx::io::server