#pragma once

#include <iostream>

#include <Logger.hpp>

using namespace std;

namespace stl_containers{

    /*
    *   STL containers ONLY!
    */

    //> Example: list, deque, forward list
    void     sequence_containers                    (const vector<int>& _inp_arr);

    //> Example: queue, stack
    void     adaptors_containers                    (const vector<int>& _inp_arr);

    //> Example: set, multiset, map, multimap
    void     associative_containers                 (const vector<int>& _inp_arr);

    //> Example: unordered_set, .._map, .._multi..
    void     unordered_associative_containers       (const vector<int>& _inp_arr);
   
}

namespace patterns{

    /*
    *   SOURCE:
    *       - https://medium.com/must-know-computer-science/basic-design-patterns-in-c-39bd3d477a5c
    *       - https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Builder
    */
    namespace creational{
        void    builder                             ();
        void    factory                             ();
        void    factory_method                      ();
        void    abstract_factory                    ();
        void    prototype                           ();
    }
    namespace structural{
        void    adapter                             ();
        void    bridge                              ();
        void    composite                           ();
        void    decoration                          ();
        void    facade                              ();
        void    flyweight                           ();
        void    proxy                               ();
        void    curiously_recurring_tmplt           ();
        void    interface_base_progr                ();
    }
    namespace behavioral{
        void    chain_of_responsibility             ();
        void    command                             ();
        void    interpreter                         ();
        void    iterator                            ();
        void    mediator                            ();
        void    memento                             ();
        void    observer                            ();
        void    state                               ();
        void    strategy                            ();
        void    tmplt_method                        ();
        void    visitor                             ();
        void    behavioral_model_view_controller    ();
    }

}