#include <iostream>
#include <vector>

#include <containers.hpp>
#include <patterns.hpp>
#include <sys.hpp>
#include <Logger.hpp>

using namespace std;

///> STL~~~~~~~~~~~~~~~~~~|
// #define STL_SEQ_CONT
// #define STL_ADA_CONT
// #define STL_ASS_CONT
// #define STL_UN_ASS_CONT
///> PATTERNS ~~~~~~~~~~~~|
#define PT_CREATIONAL_BUILDER
#define PT_CREATIONAL_FACTORY
#define PT_CREATIONAL_FACTORY_METHOD
#define PT_CREATIONAL_ABSTRACT_FACTORY
#define PT_CREATIONAL_PROTOTYPE
// #define PT_CREATIONAL_SINGLETON             // well known -> not implemented
// #define PT_STRUCTURAL_ADAPTER
// #define PT_STRUCTURAL_BRIDGE
// #define PT_STRUCTURAL_COMPOSITE
// #define PT_STRUCTURAL_DECORATOR
// #define PT_STRUCTURAL_FACADE
// #define PT_STRUCTURAL_FLYWEIGHT
// #define PT_STRUCTURAL_PROXY
// #define PT_STRUCTURAL_CURIOUSLY_RECURRING_TMPLT
// #define PT_STRUCTURAL_INTERFACE_BASED_PROGR
// #define PT_BEHAVIORAL_CHAIN_OF_RESPONSIBILITY
// #define PT_BEHAVIORAL_COMMAND
// #define PT_BEHAVIORAL_INTERPRETER
// #define PT_BEHAVIORAL_ITERATOR
// #define PT_BEHAVIORAL_MEDIATOR
// #define PT_BEHAVIORAL_MEMENTO
// #define PT_BEHAVIORAL_OBSERVER
// #define PT_BEHAVIORAL_STATE
// #define PT_BEHAVIORAL_STRATEGY
// #define PT_BEHAVIORAL_TMPLT_METHOD
// #define PT_BEHAVIORAL_VISITOR
// #define PT_BEHAVIORAL_MODEL_VIEW_CONTROLLER
///>~~~~~~~~~~~~~~~~~~~~~~|

int main(int, char**){

    LOG_INIT_COUT();
    log.set_log_level(LOG_DEBUG);
    log.set_log_style_time(LOG_STYLE_OFF);
    log.set_log_style_status(LOG_STYLE_ON);

    //> system
        /* options: 20 | 10000 | .. */
    const int               arr_len                 = 100000;
        /* options: 1 (rand <= size()) | 2 (index = val) */
    const int               arr_opt                 = 1;
    Sys                     sys;
    vector<int>             arr                     (arr_len, 0);

    //> run
    sys.fill_arr(arr, arr_opt);

    //> STL
    {
#if defined(STL_SEQ_CONT)
    sys.th_start(stl_containers::sequence_containers, arr);
    sys.th_stop();
#endif
#if defined(STL_ADA_CONT)
    sys.th_start(stl_containers::adaptors_containers, arr);
    sys.th_stop();
#endif
#if defined(STL_ASS_CONT)
    sys.th_start(stl_containers::associative_containers, arr);
    sys.th_stop();
#endif
#if defined(STL_UN_ASS_CONT)
    sys.th_start(stl_containers::unordered_associative_containers, arr);
    sys.th_stop();
#endif
    }

    //> PATTERNS
    {
#if defined(PT_CREATIONAL_BUILDER)
    sys.th_start(patterns::creational::builder);
    sys.th_stop();
#endif
#if defined(PT_CREATIONAL_FACTORY)
    sys.th_start(patterns::creational::factory);
    sys.th_stop();
#endif
#if defined(PT_CREATIONAL_FACTORY_METHOD)
    sys.th_start(patterns::creational::factory_method);
    sys.th_stop();
#endif
#if defined(PT_CREATIONAL_ABSTRACT_FACTORY)
    sys.th_start(patterns::creational::abstract_factory);
    sys.th_stop();
#endif
#if defined(PT_CREATIONAL_PROTOTYPE)
    sys.th_start(patterns::creational::prototype);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_ADAPTER)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_BRIDGE)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_COMPOSITE)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_DECORATOR)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_FACADE)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_FLYWEIGHT)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_PROXY)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_CURIOUSLY_RECURRING_TMPLT)
    /*~~~~~~~~*/
#endif
#if defined(PT_STRUCTURAL_INTERFACE_BASED_PROGR)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_CHAIN_OF_RESPONSIBILITY)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_COMMAND)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_INTERPRETER)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_ITERATOR)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_MEDIATOR)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_MEMENTO)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_OBSERVER)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_STATE)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_STRATEGY)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_TMPLT_METHOD)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_VISITOR)
    /*~~~~~~~~*/
#endif
#if defined(PT_BEHAVIORAL_MODEL_VIEW_CONTROLLER)
    /*~~~~~~~~*/
#endif
    }


}
