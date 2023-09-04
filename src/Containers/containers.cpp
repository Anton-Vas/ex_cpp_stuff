
#include <containers.hpp>



void stl_containers::sequence_containers                (const vector<int>& _inp_arr){
    
    //> setup
    LOG_INIT_COUT();
    log(LOG_INFO) << "loop : " << __func__;

    //> List ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // list<int> list = 


    // cout << "thread is alive!" << endl;
    // timer->start();
    // this_thread::sleep_for(chrono::seconds(1));
    // timer->stop("sequence container");

}

void stl_containers::adaptors_containers                (const vector<int>& _inp_arr){
    
    //> setup
    LOG_INIT_COUT();
    log(LOG_INFO) << "loop : " << __func__;

    //> stack ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        cout << "\n~~~ STACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        stack<int> stack;

        //> input
        log(LOG_INFO) << "1 - input";
        log.add_snapshot("stack_inp");

        cout << "array [ ";
        for(int i = 0; i < _inp_arr.size(); i++){
            // cout << _inp_arr.at(i) << " ";
            stack.push(_inp_arr.at(i));
        }
        cout << " ]" << endl;
        log.time_since_snap("stack_inp");

        //> operations
        log(LOG_INFO) << "2 - operations";
        log(LOG_DONE) << "stack size() : " << stack.size();

        //> output
        // cout << "3. Output" << endl;
        // log(LOG_INFO) << "3 - output";
        // log.add_snapshot("stack_out");
        // while(!stack.empty()){
        //     cout << "   " <<  stack.top() << " ";
        //     stack.pop();
        //     cout << "( size: " << stack.size() << ")" << endl;
        // }
        // log.time_since_snap("stack_out");
    }
    //> queue ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        cout << "\n~~~ QUEUE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        queue<int> q;

        //>input
        log(LOG_INFO) << "1 - input";
        log.add_snapshot("queue_inp");
        cout << "array [ ";
        for(int i = 0; i < _inp_arr.size(); i++){
            // cout << _inp_arr.at(i) << " ";
            q.push(_inp_arr.at(i));
        }
        cout << " ]" << endl;
        log.time_since_snap("queue_inp");

        //> operations
        log(LOG_INFO) << "2 - operations";
        log(LOG_DONE) << "queue size() : " << q.size();

        //> output
        // log(LOG_INFO) << "3 - output";
        // log.add_snapshot("queue_out");
        // while(!q.empty()){
        //     cout << "   " << q.front() << " ";
        //     q.pop();
        //     cout << "( size: " << q.size() << ")"<< endl;
        // }
        // log.time_since_snap("queue_out");
    }

}

void stl_containers::associative_containers             (const vector<int>& _inp_arr){
    
    //> setup
    LOG_INIT_COUT();
    log(LOG_INFO) << "loop : " << __func__;

    //> map ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        cout << "\n~~~ MAP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "   - (usually based on a RED-BLACK TREE)" << endl;

        map<int, string> m;                                           //> key = value from _inp_vec, val = ASCII[key]

        //> input
        log(LOG_INFO) << "1 - input";
        log.add_snapshot("map_inp");
        for(int i = 0; i < _inp_arr.size(); i++){
            m.insert({_inp_arr.at(i), to_string(_inp_arr.at(i))});
        }
        log.time_since_snap("map_inp");

        //> operations
        log(LOG_INFO) << "2 - operations";
        log(LOG_DONE) << "map size() : " << m.size();
        
        // log(LOG_INFO) << "3 - output";
        // log.add_snapshot("map_out");
        // for(int i = 0; i < m.size(); i++){
        //     cout << "   key ("<< i << ") = val (" << m[i] << ")"; 
        //     if (i == 10){cout << " ERASED";} 
        //     cout << endl;
        // }
        // log.time_since_snap("map_out");
    }
    //> set ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        //..
    }
    //> multimap ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        //..
    }
    //> multiset ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        //..
    }
}

void stl_containers::unordered_associative_containers   (const vector<int>& _inp_arr){
    
    //> setup
    LOG_INIT_COUT();
    log(LOG_INFO) << "loop : " << __func__;
}
