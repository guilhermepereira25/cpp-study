// exemplo de concorrência

#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <chrono>

std::mutex mtx; // mutex for critical section
std::mutex state_mtx; // mutex for thread state map
int counter = 0; // shared counter

enum ThreadState {
    RUNNING,
    WAITING,
    LOCKED
};

std::map<std::thread::id, int> threadStates;

void incrementCounter() {
    for (int i = 0; i < 100; ++i) {
        // lock the thread state map
        state_mtx.lock();
        // set the state of the current thread to LOCKED
        threadStates[std::this_thread::get_id()] = LOCKED;
        state_mtx.unlock();

        // lock and unlock para que o acesso ao contador seja feito de forma exclusiva
        // caso não haja o lock, o valor do contador pode ser alterado por outra thread
        // a thread que não conseguiu o lock fica bloqueada até que o lock seja liberado
        mtx.lock();
        ++counter;
        mtx.unlock();

        // lock the thread state map
        state_mtx.lock();
        // set the state of the current thread to RUNNING
        threadStates[std::this_thread::get_id()] = RUNNING;
        state_mtx.unlock();
    }
    // lock the thread state map
    state_mtx.lock();
    // set the state of the current thread to WAITING
    threadStates[std::this_thread::get_id()] = WAITING;
    state_mtx.unlock();
}

void listener() {
    while (true) {
        state_mtx.lock();
        for (const auto& kv : threadStates) {
            std::cout << "Thread " << kv.first << " is ";

            switch (kv.second) {
                case RUNNING:
                    std::cout << "RUNNING";
                    break;
                case WAITING:
                    std::cout << "WAITING";
                    break;
                case LOCKED:
                    std::cout << "LOCKED";
                    break;
            }

            std::cout << std::endl;
        }
        state_mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    // cria duas threads que executam a função incrementCounter
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);
    std::thread t3(listener);

    // join para que a thread principal espere as threads t1 e t2 terminarem
    t1.join();
    t2.join();

    // imprime o valor do contador
    std::cout << "Counter = " << counter << std::endl;

    return 0;
}