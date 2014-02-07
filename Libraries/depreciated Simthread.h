#include <vector>
#include <thread>


int ThreadSimCurrentlyAvailable;


//int ThreadSim(int FunctionToRun, struct ParametersToUse, struct StoragePointer, int NumberOfRuns)// section 2.6 http://www.newty.de/fpt/fpt.html
template<typename _Callable, int , typename ParameterStructVec, typename StorageStructVec, typename... _Args>
void ThreadSim(_Callable&& __FunctionToRun, int NumberOfRuns, ParameterStructVec ParaVec, StorageStructVec StorageVec  , _Args&&... __args)// section 2.6 http://www.newty.de/fpt/fpt.html
{
    unsigned int NumberOfThreadsAvailable = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    ThreadSimCurrentlyAvailable=0;

    //Load the cores with simulations
    //for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
    //    threads.push_back(std::thread(LoadCore(__FunctionToRun, ParametersToUse, StoragePointer, NumberOfRuns)));//http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-api-4.6/a01086_source.html
    //}

    for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
        threads.push_back(std::thread( std::bind<void>( std::forward<_Callable>(__FunctionToRun), NumberOfRuns, ParaVec, StorageVec, std::forward<_Args>(__args)...)));
    }


    for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
        threads.push_back(std::thread(LoadCore(__FunctionToRun, NumberOfRuns, ParaVec, StorageVec, __args)));//http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-api-4.6/a01086_source.html
    }

    //http://en.wikipedia.org/wiki/Varargs#Variadic%5Ffunctions%5Fin%5FC.2C%5FObjective-C.2C%5FC.2B.2B.2C%5Fand%5FD
    //templates http://en.wikipedia.org/wiki/Template_(C%2B%2B)
    //binding http://en.cppreference.com/w/cpp/utility/functional/bind
    //forwarding http://stackoverflow.com/questions/7257144/when-to-use-stdforward-to-forward-arguments

    //Clean up after itself
    for(auto& thread : threads) {
        thread.join();
    }
};

template<typename _Callable, int , typename ParameterStructVec, typename StorageStructVec, typename... _Args>
void LoadCore(_Callable&& __FunctionToRun, int NumberOfRuns, ParameterStructVec ParaVec, StorageStructVec StorageVec  , _Args&&... __args)
{
    while ThreadSimCurrentlyAvailable<NumberOfRuns
    {
        N=ThreadSimCurrentlyAvailable;
        ThreadSimCurrentlyAvailable++;
        std::bind<void>(std::forward<_Callable>(__FunctionToRun), ParaVec[N], StorageVec[N], std::forward<_Args>(__args)...);

        //(*__FunctionToRun)( struct ParametersToUse, struct StoragePointer, int NumberOfRuns);
    }
};
