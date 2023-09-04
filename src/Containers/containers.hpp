#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <thread>

#include <Sys/Logger.hpp>

using namespace std;


namespace stl_containers{

    /*
    *   STL containers ONLY!
    */

    //> Example: list, deque, forward list
    void     sequence_containers                     (const vector<int>& _inp_arr);

    //> Example: queue, stack
    void     adaptors_containers                     (const vector<int>& _inp_arr);

    //> Example: set, multiset, map, multimap
    void     associative_containers                  (const vector<int>& _inp_arr);

    //> Example: unordered_set, .._map, .._multi..
    void     unordered_associative_containers        (const vector<int>& _inp_arr);
   
}

namespace other_containers{
    /*
    *   Basic containers on which the STL is based
    */

   //> Example: hash
   //..

   //> Example: heap
   //..

}