#include <boost/asio.hpp>
#include <iostream>
#include <thread>

int main() {
    boost::asio::io_service is;
    std::thread th1(
        [&] {
            boost::asio::io_service::work is_work(is);
            while(1) {
                sleep(3);
                std::cout << "in\n" ;
                is.post([]{
                    std::cerr << "NO!\n";
                });
            }
        }
    );
    std::thread th2(
        [&] {
            is.run();
        }
    );
    th1.join(); th2.join();
    return 0;
}