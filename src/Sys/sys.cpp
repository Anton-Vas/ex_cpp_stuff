
#include <Sys/sys.hpp>



Sys::Sys(){};
Sys::~Sys(){};


//> input array fill
void Sys::fill_arr          (vector<int>& _arr, const int _opt){
    
    switch(_opt){
    case 1:
        for(auto& i : _arr){
            i = rand()%_arr.size();
        }
        break;
    case 2:
        for(int i = 0; i < _arr.size(); i++){
            _arr.at(i) = i + 1;
        }
        break;
    default:
        break;
    }
    
}

//> separate thread
void Sys::th_start          (void (*_func)(const std::vector<int>&), const vector<int>& _vec){
    log(LOG_DONE) << "thread alive";
    th = new thread(_func, _vec);
}

void Sys::th_start          (void (*_func)()){
    log(LOG_DONE) << "thread alive";
    th = new thread(_func);
}

void Sys::th_stop           (){
    if (th->joinable()) {
		th->join();
        delete th;
        log(LOG_DONE) << "thread dead";
	}
}

    



