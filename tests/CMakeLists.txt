# Copyright (c) 2016 Hartmut Kaiser
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_hpx_executable(test_local_file
  FOLDER "Core/IO"
  SOURCES test_local_file.cpp
  COMPONENT_DEPENDENCIES base_file)

