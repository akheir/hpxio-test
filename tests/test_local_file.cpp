//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>

#include <hpxio/server/local_file.hpp>
#include <hpxio/base_file.hpp>

int main(int argc, char* argv[])
{
    hpx::io::base_file f =
        hpx::new_<hpx::io::server::local_file>(hpx::find_here());

    f.open(hpx::launch::sync, "test.txt", "w+");

    std::vector<char> data = { 't', 'e', 's', 't' };
    f.write(hpx::launch::sync, data);

    return 0;
}

