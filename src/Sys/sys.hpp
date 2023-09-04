#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <string>

#include <Sys/Logger.hpp>

using namespace std;

class Sys{
public:
    ///> system interface
    Sys();
    Sys(Sys& _src)                  = delete;                           ///> Copy semantics
    Sys& operator=(Sys const&)      = delete;
    Sys(Sys&& _src)                 = delete;                           ///> Move semantics
    Sys& operator=(Sys const&&)     = delete;
    ~Sys();

    //> input array fill
    void            fill_arr        (vector<int>& _arr, const int _opt);

    //> separate thread
    void            th_start        (void (*_func)(const std::vector<int>&), const vector<int>& _vec);
    void            th_start        (void (*_func)());
    void            th_stop         ();


private:
    //>separate thread
    thread*         th              = nullptr;  
    LOG_INIT_COUT();
};