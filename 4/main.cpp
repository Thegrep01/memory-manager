#include "mem_manager.h"


int main() {

    srand(time(0));
    int buffer[SIZE] {};


    thread t1(input, ref(buffer), SIZE);
    thread t2(output, ref(buffer), SIZE, RANDOM);
    thread t3(defrag, ref(buffer), SIZE);
    thread t4(print_buffer, ref(buffer), SIZE);

    t1.join();
    t2.join();
    t3.join();
    t4.join();


    return 0;

}