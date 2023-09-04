#include <patterns.hpp>

LOG_INIT_COUT();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Pizza{
public:
    void setDough(const std::string& dough) { log(LOG_DONE) << "Pizza -> setDough()"; m_dough = dough; }
    void setSauce(const std::string& sauce) { log(LOG_DONE) << "Pizza -> setSauce()"; m_sauce = sauce; }
    void setTopping(const std::string& topping) { log(LOG_DONE) << "Pizza -> setTopping()"; m_topping = topping; }
    void open() const                       { log(LOG_DONE)<<"Pizza -> open() : have "<< m_dough<<" dough, "<< m_sauce<<" sauce, "<< m_topping<<" topping."; }
private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

class PizzaBuilder{
public:
    PizzaBuilder()                          { log(LOG_DONE) << "PizzaBuilder -> CONST";}
    virtual ~PizzaBuilder()                 = default;
    void createNewPizza()                   { log(LOG_DONE) << "PizzaBuilder -> createNewPizza()"; m_pizza = std::make_unique<Pizza>(); }
    Pizza* getPizza()                       { log(LOG_DONE) << "PizzaBuilder -> getPizza()"; return m_pizza.release(); }
    virtual void buildDough()               = 0;
    virtual void buildSauce()               = 0;
    virtual void buildTopping()             = 0;
protected:
    std::unique_ptr<Pizza> m_pizza;
};

class HawaiianPizzaBuilder : public PizzaBuilder{
public:
    HawaiianPizzaBuilder()                  { log(LOG_DONE) << "HawaiianPizzaBuilder -> CONST";}
    ~HawaiianPizzaBuilder() override        = default;
    void buildDough() override              { log(LOG_DONE) << "HawaiianPizzaBuilder -> buildDough()"; m_pizza->setDough("Hawaiian dough"); }
    void buildSauce() override              { log(LOG_DONE) << "HawaiianPizzaBuilder -> buildSauce()"; m_pizza->setSauce("Hawaiian sauce"); }
    void buildTopping() override            { log(LOG_DONE) << "HawaiianPizzaBuilder -> buildTopping()"; m_pizza->setTopping("Hawaiian topping"); }
};

class SpicyPizzaBuilder : public PizzaBuilder{
public:
    SpicyPizzaBuilder()                     { log(LOG_DONE) << "SpicyPizzaBuilder -> CONST";}
    ~SpicyPizzaBuilder() override = default;
    void buildDough() override              { log(LOG_DONE) << "SpicyPizzaBuilder -> buildDough()"; m_pizza->setDough("Spicy dough"); }
    void buildSauce() override              { log(LOG_DONE) << "SpicyPizzaBuilder -> buildSauce()"; m_pizza->setSauce("Spicy sauce"); }
    void buildTopping() override            { log(LOG_DONE) << "SpicyPizzaBuilder -> buildTopping()"; m_pizza->setTopping("Spicy topping"); }
};

class Cook{
public:
    Cook() : m_pizzaBuilder(nullptr)        { log(LOG_DONE) << "Cook -> CONST";}
    void openPizza() const                  { log(LOG_DONE) << "Cook -> openPizza()"; m_pizzaBuilder->getPizza()->open(); }
    void createPizza(PizzaBuilder* pizzaBuilder){
        log(LOG_DONE) << "Cook -> createPizza()";
        m_pizzaBuilder = pizzaBuilder;
        m_pizzaBuilder->createNewPizza();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTopping();
    }
private:
    PizzaBuilder* m_pizzaBuilder;
};

void patterns::creational::builder                  (){

    //LOG_INIT_COUT();
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";

    log(LOG_INFO) << "cook hawaiian pizza";
    Cook cook{};
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    cook.createPizza(&hawaiianPizzaBuilder);
    cook.openPizza();

    log(LOG_INFO) << "cook spicy pizza";
    SpicyPizzaBuilder spicyPizzaBuilder;
    cook.createPizza(&spicyPizzaBuilder);
    cook.openPizza();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::creational::factory                  (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::creational::factory_method           (){

    //LOG_INIT_COUT();
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::creational::abstract_factory         (){

    //LOG_INIT_COUT();
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::creational::prototype                (){

    //LOG_INIT_COUT();
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    
    //..
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::adapter                  (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::bridge                   (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::composite                (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::decoration               (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::facade                   (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::flyweight                (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::proxy                    (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::curiously_recurring_tmplt();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::structural::interface_base_progr     (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::chain_of_responsibility             (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::command                             (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::interpreter                         (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::iterator                            (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::mediator                            (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::memento                             (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::observer                            (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::state                               (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::strategy                            (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::tmplt_method                        (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::visitor                             (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::behavioral_model_view_controller    (){

    //LOG_INIT_COUT();
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    
    //..
}