// Copyright 2019 dimakirol <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_


#include <async++.h>
#include <boost/process.hpp>
#include <boost/process/extend.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include <iostream>
#include <signal.h>
#include <string>
#include <thread>
#include <chrono>

using namespace boost::asio;
using namespace boost::process;
using namespace boost::process::extend;
using namespace boost::program_options;

namespace
{
    const size_t error_in_command_line = 1;
    const size_t success = 0;
    const size_t error_unhandled_exeption = 2;
}

#endif // INCLUDE_HEADER_HPP_
