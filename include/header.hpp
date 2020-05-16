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

void create_child(const std::string& command, const time_t& period);

void create_child(const std::string& command, const time_t& period, int& res);

void check_time(child& process, const time_t& period);

int Prob(std::string command1, int& res, time_t& timeout, time_t& time_spent);

time_t time_now();

#endif // INCLUDE_HEADER_HPP_
