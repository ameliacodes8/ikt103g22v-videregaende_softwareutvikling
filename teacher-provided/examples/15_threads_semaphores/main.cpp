#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

// Allows us to specify time as 1s etc.
using namespace std::chrono_literals;

// Thread function that makes a semaphore available every second
[[noreturn]] void signaling_thread(std::binary_semaphore &semaphore)
{
    std::this_thread::sleep_for(1s);

    while (true)
    {
        // Releasing the semaphore makes it available in other threads
        std::cout << "Releasing semaphore..." << std::endl;
        semaphore.release();

        std::this_thread::sleep_for(1s);
    }
}

// Thread that waits for a semaphore to become available and prints a message
[[noreturn]] void waiting_thread(std::binary_semaphore &semaphore)
{
    std::this_thread::sleep_for(1s);

    while (true)
    {
        semaphore.acquire();
        std::cout << "Got semaphore." << std::endl;
    }
}

int main()
{
    // Data used by threads. 0 means the semaphore begins as unavailable.
    std::binary_semaphore semaphore(0);

    // Spawn threads. Send a reference to the data object as the first and only parameter
    std::thread thread1 (signaling_thread, std::ref(semaphore));
    std::thread thread2 (waiting_thread, std::ref(semaphore));

    std::cout << "Threads now execute concurrently" << std::endl;

    // Wait for threads to finish by calling join().
    // Since these threads loop forever the program will only stop when the user stops it.
    thread1.join();
    thread2.join();

    // This never happens, since the threads never exit
    std::cout << "Threads have completed." << std::endl;

    return 0;
}
