#include "mem_manager.h"

int processes[SIZE][3]; /*
 * 0 - proc number
 * 1 - begin index
 * 2 - data size
 */
int proc_count = 0;

mutex mutex1;

int find_place(int *buff, int bs){
    int i = bs - 1;
    while(buff[i] == 0){
        if (i == 0)
            return 0;
        i--;
    }
    return i+1;
}
void delete_process(int p){
    int i = 0;
    while(processes[i++][PROC_NUMBER] != p)
        continue;

    int zero_index = i-1;
    processes[zero_index][PROC_NUMBER] = 0;
    processes[zero_index][BEGIN_INDEX] = 0;
    processes[zero_index][DATA_SIZE] = 0;
    while(processes[i++][PROC_NUMBER] != 0)
        continue;

    processes[zero_index][PROC_NUMBER] = processes[i-2][PROC_NUMBER];
    processes[zero_index][BEGIN_INDEX] = processes[i-2][BEGIN_INDEX];
    processes[zero_index][DATA_SIZE] = processes[i-2][DATA_SIZE];
    processes[i-2][PROC_NUMBER] = 0;
    processes[i-2][BEGIN_INDEX] = 0;
    processes[i-2][DATA_SIZE] = 0;
    proc_count--;
}

bool is_the_same(int p){
    for (int i = 0; i < proc_count; ++i) {
        if (processes[i][PROC_NUMBER] == p)
            return true;
    }
    return false;
}

void input(int *buff, int bs){
    int data_size;
    int process_number;

    for (;;) {


        mutex1.lock();
        data_size = rand() % 20 + 1;
        process_number = rand() % 150 + 1;

        while(is_the_same(process_number))
            process_number = rand()% 150 +1;


        int index = find_place(buff, bs);
        if (bs - index - 1 < data_size)
            cout << "Not enough free space" << endl;
        else {
            //buff[index] = -1;
            for (int i = 0; i < data_size; ++i) {
                buff[index + i] = process_number;
            }
            //buff[index + data_size + 1] = -1;

            processes[proc_count][PROC_NUMBER] = process_number;
            processes[proc_count][BEGIN_INDEX] = index;
            processes[proc_count][DATA_SIZE] = data_size;
            proc_count++;
        }


        mutex1.unlock();
        sleep(1);
    }
    //cout << "Data size: " << data_size << endl;
    //cout << "Process number: " << process_number << endl;
}

void output(int *buff, int bs, Strategy strategy){
    for (;;) {
        float c = 150;
        //this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(10));
        mutex1.lock();
        if(!proc_count) {
            mutex1.unlock();
            continue;
        }
        int a = proc_count;
        int pc;
        pc = rand() % proc_count;

        int process_number = processes[pc][PROC_NUMBER];
        int ds = processes[pc][DATA_SIZE];


        for (int i = processes[pc][BEGIN_INDEX];
             i < processes[pc][BEGIN_INDEX] + ds; ++i) {
            buff[i] = 0;
        }

        delete_process(process_number);
        cout << "Process number to be remove: " << process_number << endl;
        mutex1.unlock();
        //this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds((int)(c * (float)ds)));

        sleep(1);

    }

}

void defrag(int *buff, int bs){
    while(1) {

        mutex1.lock();
        for (int i = 0; i < bs; ++i) {
            while (buff[i] == 0) {
                int j = i;

                while (buff[j] == 0 && j != bs)
                    j++;
                if (j == bs)
                    break;
                while (buff[j] != 0) {
                    buff[i] = buff[j];
                    buff[j] = 0;
                    j++;
                    i++;
                }
            }
        }
        mutex1.unlock();

    }
}

void print_buffer(int *buff, int bs){
    for (;;) {
        mutex1.lock();

        system("clear");
        cout << "Processes: -----> " << proc_count << endl;
        cout << "**********************************************************************************\n" << endl;


        for (int i = 0; i < bs; ++i) {
            if(buff[i] < 0 || (buff[i] > 9 && buff[i] < 100))
                cout << " " << buff[i] << " ";
            else if (buff[i] == 0)
                cout << "*.";
            else if(buff[i] > 99)
                cout << buff[i] << " ";
            else
                cout << "  " << buff[i] << " ";
        }
        cout << "<-----END" << endl;
        cout << "**********************************************************************************\n" << endl;

        print_processes();
        mutex1.unlock();
       // this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(3));
        sleep(1);
    }
}

void print_processes(){
    cout << "Processes: ";
    for (int i = 0; i < proc_count; ++i) {
        cout << processes[i][PROC_NUMBER] << " ";
    }
    cout << endl;
}