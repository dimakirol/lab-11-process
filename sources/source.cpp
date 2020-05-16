// Copyright 2019 dimakirol <your_email>

#include <header.hpp>



int main(int argc, char* argv[]) {
    options_description desc("Allowed options");
    desc.add_options()
            ("help", "выводим вспомогательное сообщение")
            ("config", value<std::string>(),
               "указываем конфигурацию сборки (по умолчанию Debug)")
            ("install",
                 "добавляем этап установки (в директорию _install)")
            ("pack",
                 "добавляем этап упаковки (в архив формата tar.gz)")
            ("timeout", value<time_t>(),
                    "указываем время ожидания (в секундах)");

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);


        if (vm.count("help") && !vm.count("config") && !vm.count("pack")
            && !vm.count("timeout") && !vm.count("install")) {
            std::cout << desc << "\n";
            return success;
        } else {
            std::string config = "Debug";
            time_t timeout = time_now();
            time_t time_spent = 0;
            if (vm.count("timeout")) {
                timeout = vm["timeout"].as<time_t>();
            }
            notify(vm);
            if (vm.count("config")) {
                config = vm["config"].as<std::string>();
            }

            std::string command_1 = "cmake -H. -B_build -DCMAKE_INSTALL_" +
                       std::string("PREFIX=_install -DCMAKE_BUILD_TYPE=");
            std::string command_2 = "cmake --build _builds";
            std::string command_3 = "cmake --build _builds --target install";
            std::string command_4 = "cmake --build _builds --target package";

            int resultat_1 = 0;
            int resultat_2 = 0;

            if (config == "Debug" || config == "Release") {
                command_1 += config;
                auto t1 = async::spawn([&resultat_1, config, timeout,
                                   &time_spent, command_1, command_2]() mutable {
                    time_t start_1 = time_now();

                    people_make_new_people(command_1, timeout);
                    time_t end_1 = time_now();

                    time_spent += end_1 - start_1;
                    resultat_1 = ya_nesu_resultat(command_2, resultat_1, 
                                                  timeout, time_spent);
                });
            }
            if (vm.count("install") && resultat_1 == 0) {
                auto t2 = async::spawn([&resultat_1, &resultat_2, command_3,
                                               timeout, &time_spent]() mutable {
                    resultat_2 = ya_nesu_resultat(command_3, resultat_1,
                                                  timeout, time_spent);
                });
                std::cout << "install" << std::endl;
            }
            if (vm.count("pack") && resultat_2 == 0) {
                auto t3 = async::spawn([&resultat_2, command_4,
                                        timeout, &time_spent]() mutable {
                    resultat_2 = ya_nesu_resultat(command_4, resultat_2,
                                                  timeout, time_spent);
                });
                std::cout << "package" << std::endl;
            }
        }
    }

    catch (boost::program_options::error & e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return error_in_command_line;
    }
    catch (std::exception & e) {
        std::cerr << "Unhandled Exception reached the top of main: "
                  << e.what() << ", application will now exit" << std::endl;
        return error_unhandled_exeption;
    }
}

void people_make_new_people(const std::string& command,
                            const time_t& period) {
    std::string line;
    ipstream out;

    child process(command, std_out > out);
    std::thread checkTime(check_time, std::ref(process), std::ref(period));

    while (out && std::getline(out, line) && !line.empty())
        std::cerr << line << std::endl;

    checkTime.join();
}


void people_make_new_people(const std::string& command, 
                        const time_t& period, int& resultat) {
    std::string line;
    ipstream out;

    child process(command, std_out > out);

    std::thread checkTime(check_time, std::ref(process), std::ref(period));

    while (out && std::getline(out, line) && !line.empty())
        std::cerr << line << std::endl;

    checkTime.join();

    resultat = process.exit_code();
}

void check_time(child& process, const time_t& period){
    time_t start = time_now();

    while (true) {
        if ((time_now() - start > period) && process.running()) {
            std::error_code ec;
            process.terminate(ec);
            std::cout << ec;
            break;
        } else if (!process.running()) {
            break;
        }
    }
}

time_t time_now() {
    return std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
}

int ya_nesu_resultat(std::string command1, int& resultat,
                     time_t& timeout, time_t& time_spent) {
    time_t period = timeout - time_spent;
    time_t start = time_now();

    privet_ya_rodilsia(command1, period, resultat);
    time_t end = time_now();
    time_spent += end - start;

    return resultat;
}
