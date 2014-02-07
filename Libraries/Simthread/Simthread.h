#include <vector>
#include <thread>


int ThreadSimCurrentlyAvailable;



//template<typename _Callable, int , typename ParameterStructVec, typename StorageStructVec, typename... _Args>
//void LoadCore(_Callable&& __FunctionToRun, int NumberOfRuns, ParameterStructVec ParaVec, StorageStructVec StorageVec  , _Args&&... __args)
template <typename _Callable, typename... _Args>
void LoadCore(_Callable __FunctionToRun(ParameterStruct, StorageStruct), int NumberOfRuns, ParameterStruct ParaVec[], StorageStruct StorageVec[])//  , _Args&&... __args)
{
    int N;
    while (ThreadSimCurrentlyAvailable<NumberOfRuns)
    {
        N=ThreadSimCurrentlyAvailable;
        ThreadSimCurrentlyAvailable++;

        __FunctionToRun(ParaVec[N], StorageVec[N]);
        //std::bind<void>(std::forward<_Callable>(__FunctionToRun), ParaVec[N], StorageVec[N], std::forward<_Args>(__args)...);

        //(*__FunctionToRun)( struct ParametersToUse, struct StoragePointer, int NumberOfRuns);
    }
};



//int ThreadSim(int FunctionToRun, struct ParametersToUse, struct StoragePointer, int NumberOfRuns)// section 2.6 http://www.newty.de/fpt/fpt.html
//template<typename _Callable ,  int N, typename ParameterStructVec, typename StorageStructVec, typename... _Args>
//void ThreadSim(_Callable&& __FunctionToRun, int NumberOfRuns, ParameterStructVec ParaVec, StorageStructVec StorageVec  , _Args&&... __args)// section 2.6 http://www.newty.de/fpt/fpt.html


//http://en.cppreference.com/w/cpp/language/function_template
//template <typename _Callable<int, int>,  int N>//, typename ParameterStructVec, typename StorageStructVec, typename... _Args>

template <typename _Callable, typename... _Args>
void ThreadSim(_Callable __FunctionToRun(ParameterStruct, StorageStruct), int NumberOfRuns, ParameterStruct ParaVec[], StorageStruct StorageVec[])
{
    ThreadSimCurrentlyAvailable=0;

    //__FunctionToRun(NumberOfRuns, NumberOfRuns);

    //unsigned int NumberOfThreadsAvailable = std::thread::hardware_concurrency();
    //std::vector<std::thread> threads;

    //Load the cores with simulations
    //for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
    //    threads.push_back(std::thread(LoadCore(__FunctionToRun, ParametersToUse, StoragePointer, NumberOfRuns)));//http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-api-4.6/a01086_source.html
    //}

    //for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
    //    threads.push_back(std::thread( std::bind<void>( std::forward<_Callable>(__FunctionToRun), NumberOfRuns, ParaVec, StorageVec, std::forward<_Args>(__args)...)));
    //}




    RunASim(ParaVec[1], StorageVec[2]);//Works

    thread Works1(RunASim, ParaVec[1], StorageVec[2]);//works
    Works1.join();

    LoadCore(__FunctionToRun, NumberOfRuns, ParaVec, StorageVec);//works

    ThreadSimCurrentlyAvailable=0;
    LoadCore(RunASim, NumberOfRuns, ParaVec, StorageVec);//works

    thread works3(__FunctionToRun, ParaVec[1], StorageVec[2]);
    works3.join();





    //thread t1(LoadCore, &RunASim, NumberOfRuns, ParaVec, StorageVec);
    //t1.join();

    thread t1(LoadCore, __FunctionToRun, NumberOfRuns, ParaVec, StorageVec);
    t1.join();



    //for(unsigned int i = 0; i < NumberOfThreadsAvailable; i++) {
    //    threads.push_back(std::thread(LoadCore, &__FunctionToRun, NumberOfRuns, ParaVec, StorageVec));//, std::forward<_Args>(__args)...)));//http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-api-4.6/a01086_source.html
    //}
/*
    //http://en.wikipedia.org/wiki/Varargs#Variadic%5Ffunctions%5Fin%5FC.2C%5FObjective-C.2C%5FC.2B.2B.2C%5Fand%5FD
    //templates http://en.wikipedia.org/wiki/Template_(C%2B%2B)
    //binding http://en.cppreference.com/w/cpp/utility/functional/bind
    //forwarding http://stackoverflow.com/questions/7257144/when-to-use-stdforward-to-forward-arguments

    //Clean up after itself
    for(auto& thread : threads) {
        thread.join();
    }
    */
};

