#include <vector>
#include <thread>


int SimCurrentlyAvailable;

int RunMultiply(function FunctionToRun, struct ParametersToUse, struct StoragePointer, int NumberOfRuns)
{
    unsigned int NumberOfThreadsAvailable = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    SimCurrentlyAvailable=0;

    //Load the cores with simulations
    for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
        threads.push_back(std::thread(PrintMe));
    }

    //Clean up after itself
    for(auto& thread : threads) {
        thread.join();
    }

    return 0;
};


int LoadCore(function FunctionToRun, struct ParametersToUse, struct StoragePointer, int NumberOfRuns)
{
    while SimCurrentlyAvailable<NumberOfRuns
    {
        ThisSimNum=SimCurrentlyAvailable;
        SimCurrentlyAvailable++;

    }
    return 0;
};
