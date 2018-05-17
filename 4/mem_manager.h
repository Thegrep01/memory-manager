#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <ctime>
#include <memory.h>

#define SIZE 1024

#define PROC_NUMBER 0
#define BEGIN_INDEX 1
#define DATA_SIZE 2


using namespace std;

enum Strategy{RANDOM};

int find_place(int *buff, int bs);
void delete_process(int p);
bool is_the_same(int p);

void input(int *buff, int bs);
void output(int *buff, int bs, Strategy strategy);
void defrag(int *buff, int bs);

void print_buffer(int *buff, int bs);
void print_processes();
