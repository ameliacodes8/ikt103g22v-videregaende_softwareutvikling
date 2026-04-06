#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// Allows us to specify time as 1s etc.
using namespace std::chrono_literals;

// Data structure used by all threads.
// Contains variables and a mutex to lock access to them.
struct Data
{
    int number = 0;
    std::mutex mutex;
};

// Thread function that adds 1 to number every second
void add_one(Data &data)
{
    std::this_thread::sleep_for(1s);

    for (int i = 0; i < 10; i++)
    {
        // Lock mutex to gain exclusive access to the data.
        // Any other thread trying to lock the mutex will wait.
        //data.mutex.lock();

        // Access to std::cout must also be locked as it is not *thread safe*
        std::cout << "Adding 1..." << std::endl;
        data.number++;

        // Unlock the mutex before sleeping, otherwise no other threads will be able to lock it.
        //data.mutex.unlock();

        std::this_thread::sleep_for(1s);
    }
}

// Thread function that adds 10 to number every 10 seconds
void add_ten(Data &data)
{
    std::this_thread::sleep_for(1s);

    for (int i = 0; i < 10; i++)
    {
        // Lock mutex to gain exclusive access to the data.
        // Any other thread trying to lock the mutex will wait.
        //data.mutex.lock();

        // Access to std::cout must also be locked as it is not *thread safe*
        std::cout << "Adding 10..." << std::endl;
        data.number += 10;

        // Unlock the mutex before sleeping, otherwise no other threads will be able to lock it.
        //data.mutex.unlock();

        std::this_thread::sleep_for(10s);
    }
}

int main()
{
    // Data used by threads
    Data data;

    // Spawn threads. Send a reference to the data object as the first and only parameter
    std::thread thread1 (add_one, std::ref(data));
    std::thread thread2 (add_ten, std::ref(data));

    std::cout << "Threads now execute concurrently" << std::endl;

    // Wait for threads to finish by calling join()
    thread1.join();
    thread2.join();

    std::cout << "Threads have completed." << std::endl;

    return 0;
}
