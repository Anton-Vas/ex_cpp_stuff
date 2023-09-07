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
// #define PT_CREATIONAL_BUILDER
// #define PT_CREATIONAL_FACTORY
// #define PT_CREATIONAL_FACTORY_METHOD
// #define PT_CREATIONAL_ABSTRACT_FACTORY
// #define PT_CREATIONAL_PROTOTYPE
// #define PT_CREATIONAL_SINGLETON                 // well known -> not implemented
// #define PT_STRUCTURAL_ADAPTER
// #define PT_STRUCTURAL_BRIDGE
// #define PT_STRUCTURAL_COMPOSITE
// #define PT_STRUCTURAL_DECORATOR
// #define PT_STRUCTURAL_FACADE
// #define PT_STRUCTURAL_FLYWEIGHT
// #define PT_STRUCTURAL_PROXY
// #define PT_STRUCTURAL_CURIOUSLY_RECURRING_TMPLT
// #define PT_STRUCTURAL_INTERFACE_BASED_PROGR     // NO_CODE
// #define PT_BEHAVIORAL_CHAIN_OF_RESPONSIBILITY
// #define PT_BEHAVIORAL_COMMAND
// #define PT_BEHAVIORAL_INTERPRETER               // CODE to redo
// #define PT_BEHAVIORAL_ITERATOR                  // wel known -> basically custom iterator
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
    sys.th_start(patterns::structural::adapter);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_BRIDGE)
    sys.th_start(patterns::structural::bridge);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_COMPOSITE)
    sys.th_start(patterns::structural::composite);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_DECORATOR)
    sys.th_start(patterns::structural::decoration);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_FACADE)
    sys.th_start(patterns::structural::facade);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_FLYWEIGHT)
    sys.th_start(patterns::structural::flyweight);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_PROXY)
    sys.th_start(patterns::structural::proxy);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_CURIOUSLY_RECURRING_TMPLT)
    sys.th_start(patterns::structural::curiously_recurring_tmplt);
    sys.th_stop();
#endif
#if defined(PT_STRUCTURAL_INTERFACE_BASED_PROGR)
    sys.th_start(patterns::structural::interface_base_progr);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_CHAIN_OF_RESPONSIBILITY)
    sys.th_start(patterns::behavioral::chain_of_responsibility);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_COMMAND)
    sys.th_start(patterns::behavioral::command);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_INTERPRETER)
    sys.th_start(patterns::behavioral::interpreter);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_ITERATOR)
    sys.th_start(patterns::behavioral::iterator);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_MEDIATOR)
    sys.th_start(patterns::behavioral::mediator);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_MEMENTO)
    sys.th_start(patterns::behavioral::memento);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_OBSERVER)
    sys.th_start(patterns::behavioral::observer);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_STATE)
    sys.th_start(patterns::behavioral::state);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_STRATEGY)
    sys.th_start(patterns::behavioral::strategy);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_TMPLT_METHOD)
    sys.th_start(patterns::behavioral::tmplt_method);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_VISITOR)
    sys.th_start(patterns::behavioral::visitor);
    sys.th_stop();
#endif
#if defined(PT_BEHAVIORAL_MODEL_VIEW_CONTROLLER)
    sys.th_start(patterns::behavioral::model_view_controller);
    sys.th_stop();
#endif
    }


}
