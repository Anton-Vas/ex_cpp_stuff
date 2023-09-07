#include <patterns.hpp>
#include <cstring>
#include <string>
#include <memory>
#include <chrono>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <list>

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

    
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to create a complex OBJ without many ARGS in constructor?\n" <<
            "|SOLUTION:\n" <<
            "|   define a BUILDER and SPECIFIC-BUILDERs to automate the building process.\n" <<
            "|   We will get a complex OBJ without th need of its` interface, just an OBJ." << endl;


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

enum VehicleType {
    VT_TwoWheeler,
    VT_ThreeWheeler,
    VT_FourWheeler
};
 
// Library classes
class Vehicle {
public:
    virtual void printVehicleInfo()         = 0;
    virtual ~Vehicle()                      {}
};
 
class TwoWheeler : public Vehicle {
public:
    void printVehicleInfo()                 { log(LOG_DONE) << "TwoWheeler -> printVehicleInfo()"; }
};
 
class ThreeWheeler : public Vehicle {
public:
    void printVehicleInfo()                 { log(LOG_DONE) << "ThreeWheeler -> printVehicleInfo()"; }
};
 
class FourWheeler : public Vehicle {
public:
    void printVehicleInfo()                 { log(LOG_DONE) << "FourWheeler -> printVehicleInfo()"; }
};
 
// Class Vehicle Factory with a single responsibility to
// construct Vehicles according to the clients requests. PS:
// This class can be extended to TwoWheelerFactory,
// ThreeWheelerFactory and so on.
class VehicleFactory {
public:
    Vehicle* build(VehicleType vehicleType)
    {
        switch (vehicleType)
        {
        case VT_TwoWheeler:
            log(LOG_DONE) << "VehicleFactory -> build() : TwoWheeler";
            return new TwoWheeler();
            break;
        
        case VT_ThreeWheeler:
            log(LOG_DONE) << "VehicleFactory -> build() : ThreeWheeler";
            return new ThreeWheeler();
            break;

        case VT_FourWheeler:
            log(LOG_DONE) << "VehicleFactory -> build() : FourWheeler";
            return new FourWheeler();
            break;

        default:
            log(LOG_DONE) << "VehicleFactory -> build() : nullptr";
            return nullptr;
            break;
        }
    }
};
 
// Client class. The client object will ask the factory to
// build vehicles.
class Client {
public:
    Client()                                { log(LOG_DONE) << "Client -> CONST"; pVehicle = nullptr; }
    void BuildVehicle(VehicleType vehicleType)
    {
        log(LOG_DONE) << "Client -> BuildVehicle()";
        VehicleFactory* vf = new VehicleFactory();
        pVehicle = vf->build(vehicleType);
        delete vf;
    }
 
    ~Client()
    {
        if (pVehicle) {
            log(LOG_DONE) << "Client -> ~Client() : delete instance of a vehicle";
            delete pVehicle;
            pVehicle = NULL;
        }
    }
 
    Vehicle* getVehicle()                   { log(LOG_DONE) << "Client -> getVehicle() : gey access to vehicle"; return pVehicle; }
 
private:
    Vehicle* pVehicle;
};

void patterns::creational::factory                  (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to create a complex object without exposing the instantiation logic to the client?\n" <<
            "|SOLUTION:\n" <<
            "|   if client requires OBJ, it calls FACTORY to init NEW-OBJ.\n" <<
            "|   Client uses PREDEFINED interface instead the actual OBJs one." << endl;
    
    
    Client* pClient = new Client();
 
    pClient->BuildVehicle(VT_TwoWheeler);
    pClient->getVehicle()->printVehicleInfo();
 
    pClient->BuildVehicle(VT_ThreeWheeler);
    pClient->getVehicle()->printVehicleInfo();
 
    pClient->BuildVehicle(VT_FourWheeler);
    pClient->getVehicle()->printVehicleInfo();
 
    delete pClient;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Abstract base class declared by framework */
class Document {
public:
    Document(char *fn)                      { log(LOG_DONE) << "Document -> CONST"; strcpy(name, fn); }
    virtual void Open()                     = 0;
    virtual void Close()                    = 0;
    char *GetName()                         { log(LOG_DONE) << "Document -> GetName()"; return name; }
private:
    char name[20];
};

/* Concrete derived class defined by client */
class MyDocument: public Document {
public:
    MyDocument(char *fn): Document(fn)      { log(LOG_DONE) << "MyDocument -> CONST"; }
    void Open()                             { log(LOG_DONE) << "MyDocument -> Open()"; }
    void Close()                            { log(LOG_DONE) << "MyDocument -> Close()";  }
};

/* Framework declaration */
class Application
{
public:
    Application(): _index(0)                { log(LOG_DONE) << "Application -> CONST"; }
    /* The client will call this "entry point" of the framework */
    void NewDocument(char *name)
    {
        log(LOG_DONE) << "Application -> NewDocument()";
        /* Framework calls the "hole" reserved for client customization */
        _docs[_index] = CreateDocument(name);
        _docs[_index++]->Open();
    }
    void OpenDocument()                     { log(LOG_DONE) << "Application -> OpenDocument()"; }
    void ReportDocs()
    {
        log(LOG_DONE) << "Application -> ReportDocs()";
        for (int i = 0; i < _index; i++)
            cout << _docs[i]->GetName() << endl;
    }
    /* Framework declares a "hole" for the client to customize */
    virtual Document *CreateDocument(char*) = 0;
private:
    int _index;
    /* Framework uses Document's base class */
    Document *_docs[10];
};

/* Customization of framework defined by client */
class MyApplication : public Application
{
public:
    MyApplication()                             { log(LOG_DONE) << "MyApplication -> CONST"; }
    /* Client defines Framework's "hole" */
    Document *CreateDocument(char *fn)
    {
        log(LOG_DONE) << "MyApplication -> CreateDocument()";
        return new MyDocument(fn);
    }
};

void patterns::creational::factory_method           (){

    
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to standardize the model for application but allow to define their own domain\n" <<
            "|   OBJ and provide their own instantiation?\n" <<
            "|SOLUTION:\n" <<
            "|   concrete classes are used during the object creation, the return type of \n" <<
            "|   the factory methods is usually declared as either an abstract class or an interface.\n" << 
            "|   (lets a class defer instantiation to subclasses)" << endl;
    
    /* Client's customization of the Framework */
    MyApplication myApp;

    myApp.NewDocument("foo");
    myApp.NewDocument("bar");
    myApp.ReportDocs();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Pizza2 {
public:
	virtual int getPrice() const                = 0;
	virtual ~Pizza2()                            {};  /* without this, no destructor for derived Pizza's will be called. */
};

class HamAndMushroomPizza : public Pizza2 {
public:
	virtual int getPrice() const                { log(LOG_DONE) << "HamAndMushroomPizza -> getPrice()"; return 850; };
	virtual ~HamAndMushroomPizza()              {};
};

class DeluxePizza : public Pizza2 {
public:
	virtual int getPrice() const                { log(LOG_DONE) << "DeluxePizza -> getPrice()"; return 1050; };
	virtual ~DeluxePizza()                      {};
};

class HawaiianPizza : public Pizza2 {
public:
	virtual int getPrice() const                { log(LOG_DONE) << "HawaiianPizza -> getPrice()"; return 1150; };
	virtual ~HawaiianPizza()                    {};
};

class PizzaFactory {
public:
	enum PizzaType {
		HamMushroom,
		Deluxe,
		Hawaiian
	};

	static unique_ptr<Pizza2> createPizza(PizzaType pizzaType) {
		switch (pizzaType) {
		case HamMushroom: log(LOG_DONE) << "PizzaFactory -> createPizza() : HamMushroom ptr"; return make_unique<HamAndMushroomPizza>();
		case Deluxe:      log(LOG_DONE) << "PizzaFactory -> createPizza() : Deluxe ptr"; return make_unique<DeluxePizza>();
		case Hawaiian:    log(LOG_DONE) << "PizzaFactory -> createPizza() : Hawaiian ptr"; return make_unique<HawaiianPizza>();
		}
		throw "invalid pizza type.";
	}
};

void patterns::creational::abstract_factory         (){

    
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to decide at run time what object is to be created based on some\n" << 
            "|   configuration or application parameter?\n" <<
            "|SOLUTION:\n" <<
            "|   Define an interface for creating an object, but let subclasses decide\n" <<
            "|   which class to instantiate.\n" <<
            "|Abstraction vs Factory method:\n" <<
            "|   FM -> creates 1 PROD, AF -> creates families of related or dependent products\n" <<
            "|   FM -> is a method, AF -> is an OBJ\n" <<
            "|   FM -> abstracts the way OBJ are created, AF -> abstracts the way factories are created" << endl;
    
    unique_ptr<Pizza2> pizza = nullptr;
    
    pizza = PizzaFactory::createPizza(PizzaFactory::HamMushroom);
    log(LOG_DONE) << "Price of " << PizzaFactory::HamMushroom << " = " << pizza->getPrice();

    pizza = PizzaFactory::createPizza(PizzaFactory::Deluxe);
    log(LOG_DONE) << "Price of " << PizzaFactory::Deluxe << " = " << pizza->getPrice();

    pizza = PizzaFactory::createPizza(PizzaFactory::Hawaiian);
    log(LOG_DONE) << "Price of " << PizzaFactory::Hawaiian << " = " << pizza->getPrice();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Record
{
public:
	virtual ~Record() {}
	virtual void print() = 0;
	virtual unique_ptr<Record> clone() = 0;
};

/** CarRecord is a Concrete Prototype */
class CarRecord : public Record
{
private:
	string m_carName;
	int m_ID;

public:
	CarRecord(string carName, int ID) : m_carName(carName), m_ID(ID)
	{
        log(LOG_DONE) << "CarRecord -> CONST";
	}

	void print() override
	{
        log(LOG_DONE) << "CarRecord -> print()";
		cout << "Car Record" << endl
		     << "Name  : "   << m_carName << endl
		     << "Number: "   << m_ID << endl << endl;
	}

	unique_ptr<Record> clone() override
	{
        log(LOG_DONE) << "CarRecord -> clone() : set ptr";
		return make_unique<CarRecord>(*this);
	}
};

/** BikeRecord is the Concrete Prototype */
class BikeRecord : public Record
{
private:
	string m_bikeName;
	int m_ID;

public:
	BikeRecord(string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID)
	{
        log(LOG_DONE) << "BikeRecord -> CONST";
	}

	void print() override
	{
        log(LOG_DONE) << "BikeRecord -> print()";
		cout << "Bike Record" << endl
		     << "Name  : " << m_bikeName << endl
		     << "Number: " << m_ID << endl << endl;
	}

	unique_ptr<Record> clone() override
	{
        log(LOG_DONE) << "BikeRecord -> clone() : set ptr";
		return make_unique<BikeRecord>(*this);
	}
};

/** PersonRecord is the Concrete Prototype */
class PersonRecord : public Record
{
private:
	string m_personName;
	int m_age;

public:
	PersonRecord(string personName, int age) : m_personName(personName), m_age(age)
	{
        log(LOG_DONE) << "PersonRecord -> CONST";
	}

	void print() override
	{
        log(LOG_DONE) << "PersonRecord -> print()";
		cout << "Person Record" << endl
			<< "Name : " << m_personName << endl
			<< "Age  : " << m_age << endl << endl;
	}

	unique_ptr<Record> clone() override
	{
        log(LOG_DONE) << "PersonRecord -> clone() : set ptr";
		return make_unique<PersonRecord>(*this);
	}
};

/** Opaque record type, avoids exposing concrete implementations */
enum RecordType
{
	CAR,
	BIKE,
	PERSON
};

/** RecordFactory is the client */
class RecordFactory
{
private:
	unordered_map<RecordType, unique_ptr<Record>, hash<int> > m_records;

public:
	RecordFactory()
	{
        log(LOG_DONE) << "RecordFactory -> CONST : map of ptr-s";
		m_records[CAR]    = make_unique<CarRecord>("Ferrari", 5050);
		m_records[BIKE]   = make_unique<BikeRecord>("Yamaha", 2525);
		m_records[PERSON] = make_unique<PersonRecord>("Tom", 25);
	}

	unique_ptr<Record> createRecord(RecordType recordType)
	{
        log(LOG_DONE) << "RecordFactory -> createRecord()";
		return m_records[recordType]->clone();
	}
};

void patterns::creational::prototype                (){

    
    log(LOG_WARN) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   when the inherent cost of creating a new object in the standard way\n" <<
            "|   (e.g., using the new keyword) is prohibitively expensive for\n" <<
            "|   a given application?\n" <<
            "|SOLUTION:\n" <<
            "|   Declare an abstract base class that specifies a pure virtual clone() method.\n" <<
            "|   Any class that needs a 'polymorphic constructor' capability derives itself\n" <<
            "|   from the abstract base class and implements the clone() operation." << endl;
    
    log(LOG_INFO) << "create RecordFactory OBJ";
    RecordFactory recordFactory;

    log(LOG_INFO) << "create CAR";
	auto record = recordFactory.createRecord(CAR);
	record->print();

    log(LOG_INFO) << "create BIKE";
	record = recordFactory.createRecord(BIKE);
	record->print();

    log(LOG_INFO) << "create PERSON";
	record = recordFactory.createRecord(PERSON);
	record->print();
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Dog {  // Abstract Target
public:
	virtual ~Dog()                              = default;
	virtual void Speak() const                  = 0;
};

class DogFemale : public Dog {  // Concrete Target
public:
	virtual void Speak() const override         { log(LOG_DONE) << "DogFemale -> speak() : target action"; }
};

class Cat {  // Abstract Adaptee
public:
	virtual ~Cat()                              = default;
	virtual void Speak() const                  = 0;
};

class CatFemale : public Cat {  // Concrete Adaptee
public:
	virtual void Speak() const override         { log(LOG_DONE) << "CatFemale -> speak() : needs to be adapted"; }
};

class DogNature {
public:
	void carryOutNature(Dog* dog) {
        log(LOG_DONE) << "DogNature -> carryOutNature() : carry Dog nature";
		dog->Speak();
	}
};

class ConversionAdapter : public Dog {  // Adapter
private:
	Cat* cat;
public:
	ConversionAdapter(Cat* c) : cat(c)          { log(LOG_DONE) << "ConversationAdapter -> CONST : with Cat*"; }
	virtual void Speak() const override         { log(LOG_DONE) << "ConversationAdapter -> speak() : general func"; cat->Speak(); }
};

void patterns::structural::adapter                  (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to connect independent classes with different interfaces?\n" <<
            "|SOLUTION:\n" <<
            "|   adapter class based on multiple inheritance" << endl;
    
    log(LOG_INFO) << "create 'dogFemale' and 'catFemale'";
    DogFemale* dogFemale = new DogFemale;
	CatFemale* catFemale = new CatFemale;

    log(LOG_INFO) << "create 'dogNature'";
	DogNature dogNature;

    log(LOG_INFO) << "create 'adaptedCat' to adapt 'catFemale' to 'Dog'";
	//	dogNature.carryOutNature (catFemale);  // Will not compile of course since the parameter must be of type Dog*.
	ConversionAdapter* adaptedCat = new ConversionAdapter(catFemale);  // catFemale has adapted to become a Dog!

    log(LOG_INFO) << "adapt 'dogFemale' -> 'dogNature'";
	dogNature.carryOutNature(dogFemale);
    log(LOG_INFO) << "adapt 'adaptedCat' -> 'dogNature'";
	dogNature.carryOutNature(adaptedCat);  // So now catFemale, in the form of adaptedCat, participates in the dogNature!
				// Note that catFemale is carrying out her own type of nature in dogNature though.

	delete adaptedCat;  // adaptedCat is not needed anymore
	delete catFemale; // catFemale is not needed anymore
	delete dogFemale; // dogFemale is not needed anymore, too
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Implementor*/
class DrawingAPI {
public:
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual ~DrawingAPI()                       {}
};

/* Concrete ImplementorA*/
class DrawingAPI1 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) {
        log(LOG_DONE) << "DrawingAPI1 -> drawCircle()";
        cout << "API1.circle at " << x << ':' << y << ' ' << radius << endl;
    }
};

/* Concrete ImplementorB*/
class DrawingAPI2 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) {
        log(LOG_DONE) << "DrawingAPI2 -> drawCircle()";
        cout << "API2.circle at " << x << ':' << y << ' ' <<  radius << endl;
    }
};

/* Abstraction*/
class Shape {
public:
    virtual ~Shape()                            {}
    virtual void draw()                         = 0;
    virtual void resizeByPercentage(double pct) = 0;
};

/* Refined Abstraction*/
class CircleShape : public Shape {
public:
    CircleShape(double x, double y,double radius, DrawingAPI *drawingAPI) :
        m_x(x), m_y(y), m_radius(radius), m_drawingAPI(drawingAPI)
    {
        log(LOG_DONE) << "CircleShape -> CONST";
    }
    void draw() {
        log(LOG_DONE) << "CircleShape -> draw() : interface func";
        m_drawingAPI->drawCircle(m_x, m_y, m_radius);
    }
    void resizeByPercentage(double pct) {
        log(LOG_DONE) << "CircleShape -> resizeByPercentage() : set radius";
        m_radius *= pct;
    }
private:
    double m_x, m_y, m_radius;
    DrawingAPI *m_drawingAPI;
};

void patterns::structural::bridge                   (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to simplify 1 abstraction for future modification with >1 implementation?\n" <<
            "|SOLUTION:\n" <<
            "|   separate the interface from its implementation" << endl;
    
    log(LOG_INFO) << "create 'circle1' and 'circle2'";
    CircleShape circle1(1,2,3,new DrawingAPI1());
    CircleShape circle2(5,7,11,new DrawingAPI2());

    log(LOG_INFO) << "'circle1' and 'circle2' -> resizeByPercentage()";
    circle1.resizeByPercentage(2.5);
    circle2.resizeByPercentage(2.5);

    log(LOG_INFO) << "'circle1' and 'circle2' -> draw()";
    circle1.draw();
    circle2.draw();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Graphic
{
public:
  virtual void print() const                    = 0;
  virtual ~Graphic()                            {}
};
 
class Ellipse : public Graphic
{
public:
  void print() const                            { log(LOG_DONE) << "Ellipse -> print() : target func"; cout << "Ellipse \n"; }
};
 
class CompositeGraphic : public Graphic
{
public:
  void print() const {
    log(LOG_DONE) << "CompositeGraphic -> print() : general func";
    for(Graphic * a: graphicList_) {
      a->print();
    }
  }
 
  void add(Graphic *aGraphic)                   { log(LOG_DONE) << "CompositeGraphic -> add() : compose elems"; graphicList_.push_back(aGraphic); }
 
private:
  vector<Graphic*>  graphicList_;
};

void patterns::structural::composite                (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to treat OBJ and Composition of OBJs uniformly?\n" <<
            "|SOLUTION:\n" <<
            "|   composition..." << endl;
    
    // Initialize four ellipses
    log(LOG_INFO) << "create 'ellipse1/2/3/4' as OBJ";
    const auto_ptr<Ellipse> ellipse1(new Ellipse());
    const auto_ptr<Ellipse> ellipse2(new Ellipse());
    const auto_ptr<Ellipse> ellipse3(new Ellipse());
    const auto_ptr<Ellipse> ellipse4(new Ellipse());
    
    // Initialize three composite graphics
    log(LOG_INFO) << "create 'graphic/1/2' as COMPOSITE of OBJs";
    const auto_ptr<CompositeGraphic> graphic(new CompositeGraphic());
    const auto_ptr<CompositeGraphic> graphic1(new CompositeGraphic());
    const auto_ptr<CompositeGraphic> graphic2(new CompositeGraphic());
    
    // Composes the graphics
    log(LOG_INFO) << "add 'ellipse1/2/3' to 'graphic1'";
    graphic1->add(ellipse1.get());
    graphic1->add(ellipse2.get());
    graphic1->add(ellipse3.get());
    
    log(LOG_INFO) << "add 'ellipse4' to 'graphic2'";
    graphic2->add(ellipse4.get());
    
    log(LOG_INFO) << "add 'graphic1/2' to 'graphic'";
    graphic->add(graphic1.get());
    graphic->add(graphic2.get());
    
    // Prints the complete graphic (four times the string "Ellipse")
    log(LOG_INFO) << "'graphic' -> print()";
    graphic->print();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1. "lowest common denominator"
class Widget
{
  public:
    virtual void draw() = 0;
};

class TextField: public Widget
{
    // 3. "Core" class & "is a"
    int width, height;
  public:
    TextField(int w, int h) : width(w), height(h)   { log(LOG_DONE) << "TextField -> CONST"; }
 
    /*virtual*/
    void draw()
    {
        log(LOG_DONE) << "TextField -> draw() : target func";
        cout << "TextField: " << width << ", " << height << endl;
    }
};

// 2. 2nd level base class
class Decorator: public Widget  // 4. "is a" relationship
{
    Widget *wid; // 4. "has a" relationship
  public:
    Decorator(Widget *w) : wid(w)                   { log(LOG_DONE) << "Decorator -> CONST"; }
 
    /*virtual*/
    void draw() 
    {
        log(LOG_DONE) << "Decorator -> draw()";
        wid->draw(); // 5. Delegation
    }
};

class BorderDecorator: public Decorator
{
  public:
    // 6. Optional embellishment
    BorderDecorator(Widget *w): Decorator(w)        { log(LOG_DONE) << "BorderDecorator -> CONST"; }
 
    /*virtual*/
    void draw()
    {
        // 7. Delegate to base class and add extra stuff
        log(LOG_DONE) << "BorderDecorator -> Decorator::draw() : additional func from Decorator";
        Decorator::draw();
        cout << "   BorderDecorator" << endl;;
    }
};

class ScrollDecorator: public Decorator
{
  public:
    // 6. Optional embellishment
    ScrollDecorator(Widget *w): Decorator(w)        { log(LOG_DONE) << "ScrollDecorator -> CONST"; }
 
    /*virtual*/
    void draw()
    {
        // 7. Delegate to base class and add extra stuff
        log(LOG_DONE) << "ScrollDecorator -> Decorator::draw() : additional func from Decorator";
        Decorator::draw();
        cout << "   ScrollDecorator" << endl;
    }
};

void patterns::structural::decoration               (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to add behavior or state to individual objects at run-tim?\n" <<
            "|   Inheritance - STATIC -> not usable\n" <<
            "|SOLUTION:\n" <<
            "|   Decorate an OGJ with additional behaviour/state" << endl;
    
    log(LOG_INFO) << "create 'aWidget' = BorderDecorator <- BorderDecorator <- ScrollDecorator <- TextField(ARGS)";
    Widget *aWidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator (new TextField(80, 24))));

    log(LOG_INFO) << "'aWidget' -> draw()";
    aWidget->draw();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 */
class Subsystem1 {
public:
    std::string Operation1() const              { log(LOG_DONE) << "Subsystem1 -> Operation1() : msg returned"; return "Subsystem1: AAA\n"; }
    // ...
    std::string OperationN() const              { log(LOG_DONE) << "Subsystem1 -> OperationN() : msg returned"; return "Subsystem1: BBB\n"; }
};
/**
 * Some facades can work with multiple subsystems at the same time.
 */
class Subsystem2 {
public:
    std::string Operation1() const              { log(LOG_DONE) << "Subsystem2 -> Operation1() : msg returned"; return "Subsystem2: CCC\n"; }
    // ...
    std::string OperationZ() const              { log(LOG_DONE) << "Subsystem2 -> OperationZ() : msg returned"; return "Subsystem2: DDD\n"; }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class Facade {
protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsystem2_;
    /**
     * Depending on your application's needs, you can provide the Facade with
     * existing subsystem objects or force the Facade to create them on its own.
     */
public:
    /**
     * In this case we will delegate the memory ownership to Facade Class
     */
    Facade(
        Subsystem1 *subsystem1 = nullptr,
        Subsystem2 *subsystem2 = nullptr)
    {
        log(LOG_DONE) << "Facade -> CONST : create/return Subsystem1/N";
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    /**
     * The Facade's methods are convenient shortcuts to the sophisticated
     * functionality of the subsystems. However, clients get only to a fraction of
     * a subsystem's capabilities.
     */
    std::string Operation() {
        log(LOG_DONE) << "Facade -> Operation() : all funcs";
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void patterns::structural::facade                   (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to get a simplified interface of a complex subsystem?\n" <<
            "|SOLUTION:\n" <<
            "|   facade class and the client only needs to access this class to\n" <<
            "|   perform the operations of the subsystems (just a wrapper to subsys-methods)" << endl;
    
    log(LOG_INFO) << "create 'subsystem1/2'";
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;

    log(LOG_INFO) << "create 'facade' from 'subsystem1/2'";
    Facade *facade = new Facade(subsystem1, subsystem2);

    log(LOG_INFO) << "'facade' -> Operations()";
    cout << facade->Operation() << endl;

    delete facade;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Icon
{
  public:
    Icon(char *fileName)
    {
        log(LOG_DONE) << "Icon -> CONST : set WxH";
        strcpy(_name, fileName);
        if (!strcmp(fileName, "go"))
        {
            _width = 20;
            _height = 20;
        }
        if (!strcmp(fileName, "stop"))
        {
            _width = 40;
            _height = 40;
        }
        if (!strcmp(fileName, "select"))
        {
            _width = 60;
            _height = 60;
        }
        if (!strcmp(fileName, "undo"))
        {
            _width = 30;
            _height = 30;
        }
    }
    const char *getName()
    {
        log(LOG_DONE) << "Icon -> getName()";
        return _name;
    }
    void draw(int x, int y)
    {
        log(LOG_DONE) << "Icon -> draw()";
        cout << "   drawing " << _name << ": upper left (" << x << "," << y << 
          ") - lower right (" << x + _width << "," << y + _height << ")" <<
          endl;
    }
  private:
    char _name[20];
    int _width;
    int _height;
};

class FlyweightFactory
{
  public:
    static Icon *getIcon(char *name)
    {
        log(LOG_DONE) << "FlyweightFactory -> getIcon()";
        for (int i = 0; i < _numIcons; i++)
          if (!strcmp(name, _icons[i]->getName()))
            return _icons[i];
        _icons[_numIcons] = new Icon(name);
        return _icons[_numIcons++];
    }
    static void reportTheIcons()
    {
        log(LOG_DONE) << "FlyweightFactory -> reportTheIcons()";
        cout << "Active Flyweights: ";
        for (int i = 0; i < _numIcons; i++)
          cout << _icons[i]->getName() << " ";
        cout << endl;
    }
  private:
    enum
    {
        MAX_ICONS = 5
    };
    static int _numIcons;
    static Icon *_icons[MAX_ICONS];
};

int FlyweightFactory::_numIcons = 0;
Icon *FlyweightFactory::_icons[];

class DialogBox
{
public:
    DialogBox(int x, int y, int incr): _iconsOriginX(x), _iconsOriginY(y),
      _iconsXIncrement(incr)
    {
        log(LOG_DONE) << "DialogBox -> CONST";
    }
    virtual void draw() = 0;
protected:
    Icon *_icons[3];
    int _iconsOriginX;
    int _iconsOriginY;
    int _iconsXIncrement;
};

class FileSelection: public DialogBox
{
  public:
    FileSelection(Icon *first, Icon *second, Icon *third): DialogBox(100, 100,
      100)
    {
        log(LOG_DONE) << "FileSelection -> CONST";
        _icons[0] = first;
        _icons[1] = second;
        _icons[2] = third;
    }
    void draw()
    {
        log(LOG_DONE) << "FileSelection -> draw()";
        cout << "drawing FileSelection:" << endl;
        for (int i = 0; i < 3; i++)
          _icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
    }
};

class CommitTransaction: public DialogBox
{
  public:
    CommitTransaction(Icon *first, Icon *second, Icon *third): DialogBox(150,
      150, 150)
    {
        log(LOG_DONE) << "CommitTransaction -> CONST";
        _icons[0] = first;
        _icons[1] = second;
        _icons[2] = third;
    }
    void draw()
    {
        log(LOG_DONE) << "CommitTransaction -> draw()";
        cout << "drawing CommitTransaction:" << endl;
        for (int i = 0; i < 3; i++)
          _icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
    }
};

void patterns::structural::flyweight                (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to support a lot of entities by keeping MEM usage low?\n" <<
            "|SOLUTION:\n" <<
            "|   haring parts of object state between multiple objects. In other words,\n" <<
            "|   the Flyweight saves RAM by caching the same data used by different objects" << endl;
    
    log(LOG_INFO) << "create 'dialogs[2]'";
    DialogBox *dialogs[2];

    log(LOG_INFO) << "dialogs[0] add FileSelection OBJ";
    dialogs[0] = new FileSelection(FlyweightFactory::getIcon("go"), FlyweightFactory::getIcon("stop"), FlyweightFactory::getIcon("select"));

    log(LOG_INFO) << "dialogs[1] add CommitTransaction OBJ";
    dialogs[1] = new CommitTransaction(FlyweightFactory::getIcon("select"), FlyweightFactory::getIcon("stop"), FlyweightFactory::getIcon("undo"));

    log(LOG_INFO) << "dialogs[2] -> draw()";
    for (int i = 0; i < 2; i++)
        dialogs[i]->draw();

    log(LOG_INFO) << "FlyweightFactory::reportTheIcons";
    FlyweightFactory::reportTheIcons();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The Subject interface declares common operations for both RealSubject and the
 * Proxy. As long as the client works with RealSubject using this interface,
 * you'll be able to pass it a proxy instead of a real subject.
 */
class Subject {
public:
    virtual void Request() const = 0;
};
/**
 * The RealSubject contains some core business logic. Usually, RealSubjects are
 * capable of doing some useful work which may also be very slow or sensitive -
 * e.g. correcting input data. A Proxy can solve these issues without any
 * changes to the RealSubject's code.
 */
class RealSubject : public Subject {
public:
    void Request() const override               { log(LOG_DONE) << "RealSubject -> Request() : RealSubject handling request"; }
};
/**
 * The Proxy has an interface identical to the RealSubject.
 */
class Proxy : public Subject {
  /**
   * @var RealSubject
   */
private:
    RealSubject *real_subject_;

    bool CheckAccess() const                    { log(LOG_DONE) << "Proxy -> CheckAccess() : checking access prior to firing a real request"; return true; }
    void LogAccess() const                      { log(LOG_DONE) << "Proxy -> LogAccess() : logging the time of request"; }

  /**
   * The Proxy maintains a reference to an object of the RealSubject class. It
   * can be either lazy-loaded or passed to the Proxy by the client.
   */
public:
    Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)) { log(LOG_DONE) << "Proxy -> CONST"; }

    ~Proxy() {
        delete real_subject_;
    }
    /**
     * The most common applications of the Proxy pattern are lazy loading,
     * caching, controlling the access, logging, etc. A Proxy can perform one of
     * these things and then, depending on the result, pass the execution to the
     * same method in a linked RealSubject object.
     */
    void Request() const override {
        log(LOG_DONE) << "Proxy -> Request()";
        if (this->CheckAccess()) {
            log(LOG_DONE) << "Proxy -> Request() : access granted";
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

void patterns::structural::proxy                    (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to init resource-hungry OBJ right at the moment of need?\n" <<
            "|   how to init add additional behaviour to existing OBJ?\n" <<
            "|SOLUTION:\n" <<
            "|   create PROXY OBJ that provide an object a surrogate or placeholder\n" <<
            "|   for another object to control access to it" << endl;
    
    log(LOG_WARN) << "(1) abstraction: additional behaviour";
    log(LOG_INFO) << "create OBJ with a real subject";
    RealSubject *real_subject = new RealSubject;

    log(LOG_INFO) << "execute OBJ with a real subject";
    real_subject->Request();

    log(LOG_INFO) << "create OBJ with a PROXY (additional behaviour) subject";
    Proxy *proxy = new Proxy(real_subject);

    log(LOG_INFO) << "execute OBJ with a PROXY (additional behaviour) subject";
    proxy->Request();

    delete real_subject, proxy;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// To store dimensions of an image
class Dimension {
public:
    Dimension(int _X, int _Y) : mX(_X), mY(_Y)      { log(LOG_DONE) << "Dimensions -> CONST"; }
 
private:
    int mX, mY;
};
 
// Base class for all image types. The template
// parameter T is used to know type of derived
// class pointed by pointer.
template <class T>
class Image {
public:
    void Draw()                                     { static_cast<T*>(this)->Draw(); }
    Dimension GetDimensionInPixels()                { log(LOG_DONE) << "Image -> GetDimensionInPixels()"; static_cast<T*>(this)->GetDimensionInPixels(); }
 
protected:
    int dimensionX, dimensionY;
};
 
// For Tiff Images
class TiffImage : public Image<TiffImage> {
public:
    void Draw()                                     {}
    Dimension GetDimensionInPixels()                { log(LOG_DONE) << "TiffImage -> GetDimensionInPixels() : return Dimension CONST"; return Dimension(dimensionX, dimensionY); }
};

void patterns::structural::curiously_recurring_tmplt(){

    typedef std::chrono::high_resolution_clock Clock;

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to use virtual func-s a lot without performance speed drop?\n" <<
            "|   (each call - virtual routing with slow address resolving )\n" <<
            "|   when it’s required to access the derived class object in the base class member functions?\n" <<
            "|SOLUTION:\n" <<
            "|   create class X derives from a class template instantiation using X itself\n" <<
            "|   as template argument." << endl;
    
    log(LOG_INFO) << "create an Image type pointer pointing to Tiffimage";
    Image<TiffImage>* pImage = new TiffImage;
 
    log(LOG_INFO) << "store time before virtual function calls";
    auto then = Clock::now();
 
    log(LOG_INFO) << "call Draw 1000 times to make sure performance is visible";
    log(LOG_DONE) << "Image -> Draw() : in fact it's TiffImage -> Draw()";
    for (int i = 0; i < 1000; ++i)
        pImage->Draw();
 
    log(LOG_INFO) << "store time after virtual function calls";
    auto now = Clock::now();
 
    log(LOG_INFO) << "result";
    cout << "Time taken: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count()
         << " nanoseconds" << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void patterns::structural::interface_base_progr     (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   .?\n" <<
            "|SOLUTION:\n" <<
            "|   .\n" <<
            "|   ." << endl;
    
    //.
}








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Base
{
    Base *next; // 1. "next" pointer in the base class
public:
    Base()                                      { log(LOG_DONE) << "Base -> CONST"; next = 0; }
    void setNext(Base *n)                       { log(LOG_DONE) << "Base -> setNext()"; next = n; }
    void add(Base *n)
    {
        if (next){
            log(LOG_DONE) << "Base -> add() : next != nullptr";
            next->add(n);
        }
        else{
            log(LOG_DONE) << "Base -> add() : next == nullptr";
            next = n;
        }
    }
    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(int i)                  { log(LOG_DONE) << "Base -> handle() : delegate to next HANDLER"; next->handle(i); }
};

class Handler1: public Base
{
public:
    Handler1()                                  {  log(LOG_DONE) << "Handler1 -> CONST"; }
    void handle(int i)
    {
        if (rand() % 3) {
            log(LOG_DONE) << "Handler1 -> handle() : delegate to next HANDLER";
            // 3. Don't handle requests 3 times out of 4
            cout << "H1 passed " << i << endl;
            Base::handle(i); // 3. Delegate to the base class
        }
        else{
            log(LOG_DONE) << "Handler1 -> handle() : handle here";
            cout << "H1 handled " << i << endl;
        }
    }
};

class Handler2: public Base
{
public:
    Handler2()                                  {  log(LOG_DONE) << "Handler2 -> CONST"; }
    void handle(int i) {
        if (rand() % 3) {
            log(LOG_DONE) << "Handler2 -> handle() : delegate to next HANDLER";
            cout << "H2 passed " << i << endl;
            Base::handle(i);
        }
        else{
            log(LOG_DONE) << "Handler2 -> handle() : handle";
            cout << "H2 handled " << i << endl;
        }
    }
};

class Handler3: public Base
{
public:
    Handler3()                                  {  log(LOG_DONE) << "Handler3 -> CONST"; }
    void handle(int i)
    {
        if (rand() % 3)
        {
            log(LOG_DONE) << "Handler3 -> handle() : delegate to next HANDLER";
            cout << "H3 passed " << i << endl;
            Base::handle(i);
        }
        else{
            log(LOG_DONE) << "Handler3 -> handle() : handle";
            cout << "H3 handled " << i << endl;
        }
    }
};

void patterns::behavioral::chain_of_responsibility             (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to established automatic handler for a set of possible handlers\n" <<
            "|   without hard-wiring them?\n" <<
            "|SOLUTION:\n" <<
            "|   avoid coupling the sender of a request to its receiver by giving\n" <<
            "|   more than one object a chance to handle the request." << endl;
    
    log(LOG_INFO) << "set random time";
    srand(time(0));

    log(LOG_INFO) << "create Handler1/2/3 OBJs 'root/two/thr'";
    Handler1 root;
    Handler2 two;
    Handler3 thr;

    log(LOG_INFO) << "root -> add(two)";
    root.add(&two);

    log(LOG_INFO) << "root -> add(thr)";
    root.add(&thr);

    log(LOG_INFO) << "thr -> setNext(root)";
    thr.setNext(&root);

    log(LOG_INFO) << "loop < 10 : root -> handle()";
    for (int i = 1; i < 10; i++)
    {
        root.handle(i);
        cout << '\n';
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*the Command interface*/
class Command {
public:
	virtual void execute()                      =0;
};

/*Receiver class*/
class Light {
public:
	Light()                                     { log(LOG_DONE) << "Light -> CONST"; }
	void turnOn()                               { log(LOG_DONE) << "Light -> turnOn()"; cout << "The light is on" << endl; }
	void turnOff()                              { log(LOG_DONE) << "Light -> turnDown()"; cout << "The light is off" << endl; }
};

/*the Command for turning on the light*/
class FlipUpCommand : public Command {
public:
	FlipUpCommand(Light& light) : theLight(light) { log(LOG_DONE) << "FlipUpCommand -> CONST"; }
	virtual void execute()                      { log(LOG_DONE) << "FlipUpCommand -> execute()"; theLight.turnOn(); }
private:
	Light& theLight;
};

/*the Command for turning off the light*/
class FlipDownCommand : public Command {
public:   
	FlipDownCommand(Light& light) :theLight(light) { log(LOG_DONE) << "FlipDownCommand -> CONST"; }
	virtual void execute()                      { log(LOG_DONE) << "FlipUpCommand -> execute()"; theLight.turnOff(); }
private:
	Light& theLight;
};

class Switch {
public:
	Switch(Command& flipUpCmd, Command& flipDownCmd)
	    : flipUpCommand(flipUpCmd),flipDownCommand(flipDownCmd) { log(LOG_DONE) << "Switch -> CONST"; }
	void flipUp()                               { log(LOG_DONE) << "Switch -> flipUp()"; flipUpCommand.execute(); }
	void flipDown()                             { log(LOG_DONE) << "Switch -> flipDown()"; flipDownCommand.execute(); }

private:
	Command& flipUpCommand;
	Command& flipDownCommand;
};

void patterns::behavioral::command                             (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to decouples Sender-Receiver to control what REQ goes to what CLI?\n" <<
            "|   with possible 'undo'\n" <<
            "|SOLUTION:\n" <<
            "|   need to issue requests to objects without knowing anything about the\n" <<
            "|   operation being requested or the receiver of the request" << endl;
    
    log(LOG_INFO) << "create 'lamp'";
    Light lamp;

    log(LOG_INFO) << "create 'switchIp(lamp)'";
	FlipUpCommand switchUp(lamp);

    log(LOG_INFO) << "create 'switchDown(lamp)'";
	FlipDownCommand switchDown(lamp);

    log(LOG_INFO) << "create 'switch'";
	Switch s(switchUp, switchDown);

    log(LOG_INFO) << "execute flipIp()";
	s.flipUp();

    log(LOG_INFO) << "execute flipDown()";
	s.flipDown();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
class Thousand;
class Hundred;
class Ten;
class One;

class RNInterpreter
{
  public:
    RNInterpreter(){
        log(LOG_DONE) << "RNInterpreter -> CONST";
        thousands = new Thousand(1);
        hundreds = new Hundred(1);
        tens = new Ten(1);
        ones = new One(1);
    };
    RNInterpreter(int)                          { log(LOG_DONE) << "RNInterpreter -> CONST + ARG"; }
    int interpret(char* input){
        log(LOG_DONE) << "RNInterpreter -> interpret() : get string";
        int total;
        total = 0;
        thousands->interpret(input, total);
        hundreds->interpret(input, total);
        tens->interpret(input, total);
        ones->interpret(input, total);
        if (strcmp(input, "")) //if input was invalid, return 0
            return 0;
        return total;
    }
    virtual void interpret(char *input, int &total)
    {
        log(LOG_DONE) << "RNInterpreter -> interpret() : analyze string";
        int index;
        index = 0;
        if (!strncmp(input, nine(), 2))
        {
            total += 9 * multiplier();
            index += 2;
        }
        else if (!strncmp(input, four(), 2))
        {
            total += 4 * multiplier();
            index += 2;
        }
        else
        {
            if (input[0] == five())
            {
                total += 5 * multiplier();
                index = 1;
            }
            else
              index = 0;
            for (int end = index + 3; index < end; index++)
              if (input[index] == one())
                total += 1 * multiplier();
              else
                break;
        }
        strcpy(input, &(input[index]));
    } // remove leading chars processed
  protected:
    // cannot be pure virtual because client asks for instance
    virtual char one()                          {}
    virtual char *four()                        {}
    virtual char five()                         {}
    virtual char *nine()                        {}
    virtual int multiplier()                    {}
  private:
    RNInterpreter *thousands;
    RNInterpreter *hundreds;
    RNInterpreter *tens;
    RNInterpreter *ones;
};

class Thousand: public RNInterpreter
{
  public:
    // provide 1-arg ctor to avoid infinite loop in base class ctor
    Thousand(int): RNInterpreter(1)             { log(LOG_DONE) << "Thousand -> CONST"; }
  protected:
    char one()                                  { log(LOG_DONE) << "Thousand -> one()"; return 'M'; }
    char *four()                                { log(LOG_DONE) << "Thousand -> four()"; return ""; }
    char five()                                 { log(LOG_DONE) << "Thousand -> five()"; return '\0'; }
    char *nine()                                { log(LOG_DONE) << "Thousand -> nine()"; return ""; }
    int multiplier()                            { log(LOG_DONE) << "Thousand -> multiplier()"; return 1000; }
};

class Hundred: public RNInterpreter
{
  public:
    Hundred(int): RNInterpreter(1)              { log(LOG_DONE) << "Hundred -> CONST"; }
  protected:
    char one()                                  { log(LOG_DONE) << "Hundred -> one()"; return 'C'; }
    char *four()                                { log(LOG_DONE) << "Hundred -> four()"; return "CD"; }
    char five()                                 { log(LOG_DONE) << "Hundred -> five()"; return 'D'; }
    char *nine()                                { log(LOG_DONE) << "Hundred -> nine()"; return "CM"; }
    int multiplier()                            { log(LOG_DONE) << "Hundred -> multiplier()"; return 100; }
};

class Ten: public RNInterpreter
{
  public:
    Ten(int): RNInterpreter(1)                  { log(LOG_DONE) << "Ten -> CONST"; }
  protected:
    char one()                                  { log(LOG_DONE) << "Ten -> one()"; return 'X'; }
    char *four()                                { log(LOG_DONE) << "Ten -> four()"; return "XL"; }
    char five()                                 { log(LOG_DONE) << "Ten -> five()"; return 'L'; }
    char *nine()                                { log(LOG_DONE) << "Ten -> nine()"; return "XC"; }
    int multiplier()                            { log(LOG_DONE) << "Ten -> multiplier()"; return 10; }
};

class One: public RNInterpreter
{
  public:
    One(int): RNInterpreter(1)                  { log(LOG_DONE) << "One -> CONST"; }
  protected:
    char one()                                  { log(LOG_DONE) << "One -> one()";return 'I'; }
    char *four()                                { log(LOG_DONE) << "One -> four()";return "IV"; }
    char five()                                 { log(LOG_DONE) << "One -> five()";return 'V'; }
    char *nine()                                { log(LOG_DONE) << "One -> nine()";return "IX"; }
    int multiplier()                            { log(LOG_DONE) << "One -> multiplier()";return 1; }
};
*/

void patterns::behavioral::interpreter                         (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    /*
    cout << "|PROBLEM:\n" << 
            "|   how to represent an incoming grammar accordingly to different grammar?\n" <<
            "|SOLUTION:\n" <<
            "|   Interpreter defines the behavior while the composite defines only the structure" << endl;
    
    log(LOG_INFO) << "create 'interpreter'";
    RNInterpreter interpreter;

    log(LOG_INFO) << "result";
    char input[20] = "MCMXCVI";
    cout << "Interpretation :     " << interpreter.interpret(input) << endl;
    cout << "Enter Roman Numeral: " << input << endl;
    */

   log(LOG_ERR) << "original code is commented : to old -> has to be redone";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::iterator                            (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   .?\n" <<
            "|SOLUTION:\n" <<
            "|   .\n" <<
            "|   ." << endl;
    
    //..
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class BaseComponent;

class Mediator {
public:
    Mediator() {log(LOG_DONE) << "Mediator -> CONST";}
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */
class BaseComponent {
protected:
    Mediator *mediator_;

public:
    BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {log(LOG_DONE) << "BaseComponent -> CONST";}
    void set_mediator(Mediator *mediator) {
        log(LOG_DONE) << "BaseComponent -> set_mediator()";
        this->mediator_ = mediator;
    }
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete mediator classes.
 */
class Component1 : public BaseComponent {
public:
    void DoA() {
        log(LOG_DONE) << "Component1 -> DoA()";
        std::cout << "Component 1 does A" << endl;
        this->mediator_->Notify(this, "A");
    }
    void DoB() {
        log(LOG_DONE) << "Component1 -> DoB()";
        std::cout << "Component 1 does B" << endl;
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent {
public:
    void DoC() {
        log(LOG_DONE) << "Component2 -> DoA()";
        std::cout << "Component 2 does C" << endl;
        this->mediator_->Notify(this, "C");
    }
    void DoD() {
        log(LOG_DONE) << "Component2 -> DoB()";
        std::cout << "Component 2 does D" << endl;
        this->mediator_->Notify(this, "D");
    }
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator {
private:
    Component1 *component1_;
    Component2 *component2_;

public:
    ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
        log(LOG_DONE) << "ConcreteMediator -> CONST";
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }
    void Notify(BaseComponent *sender, std::string event) const override {
        log(LOG_DONE) << "ConcreteMediator -> Notify()";
        if (event == "A") {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D") {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

void patterns::behavioral::mediator                            (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to control OBJs interactions on run-time?\n" <<
            "|SOLUTION:\n" <<
            "|   decoupling OBJs(not aware of each other) to manage them with a mediator" << endl;
    
    log(LOG_INFO) << "create Component1";
    Component1 *c1 = new Component1;

    log(LOG_INFO) << "create Component2";
    Component2 *c2 = new Component2;

    log(LOG_INFO) << "create Mediator between components";
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);

    log(LOG_INFO) << "Component1 triggers operation A";
    c1->DoA();

    log(LOG_INFO) << "Component2 triggers operation D";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The Memento interface provides a way to retrieve the memento's metadata, such
 * as creation date or name. However, it doesn't expose the Originator's state.
 */
class Memento {
public:
    Memento(){log(LOG_DONE) << "Memento -> CONST";}
    virtual ~Memento() {}
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

/**
 * The Concrete Memento contains the infrastructure for storing the Originator's
 * state.
 */
class ConcreteMemento : public Memento {
private:
    std::string state_;
    std::string date_;

public:
    ConcreteMemento(std::string state) : state_(state) {
        log(LOG_DONE) << "ConcreteMemento -> CONST";
        this->state_ = state;
        std::time_t now = std::time(0);
        this->date_ = std::ctime(&now);
    }
    /**
     * The Originator uses this method when restoring its state.
     */
    std::string state() const override {
        log(LOG_DONE) << "ConcreteMemento -> state()";
        return this->state_;
    }
    /**
     * The rest of the methods are used by the Caretaker to display metadata.
     */
    std::string GetName() const override {
        log(LOG_DONE) << "ConcreteMemento -> GetName()";
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    std::string date() const override {
        log(LOG_DONE) << "ConcreteMemento -> date()";
        return this->date_;
    }
};

/**
 * The Originator holds some important state that may change over time. It also
 * defines a method for saving the state inside a memento and another method for
 * restoring the state from it.
 */
class Originator {
  /**
   * @var string For the sake of simplicity, the originator's state is stored
   * inside a single variable.
   */
private:
    std::string state_;

    std::string GenerateRandomString(int length = 10) {
        log(LOG_DONE) << "Originator -> GenerateRandomString()";
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++) {
        random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(std::string state) : state_(state) {
        log(LOG_DONE) << "Originator -> CONST";
        std::cout << "Originator: My initial state is: " << this->state_ << endl;
    }
    /**
     * The Originator's business logic may affect its internal state. Therefore,
     * the client should backup the state before launching methods of the business
     * logic via the save() method.
     */
    void DoSomething() {
        log(LOG_DONE) << "Originator -> DoSomething()";
        std::cout << "Originator: I'm doing something important" << endl;
        this->state_ = this->GenerateRandomString(30);
        std::cout << "Originator: and my state has changed to: " << this->state_ << endl;
    }

    /**
     * Saves the current state inside a memento.
     */
    Memento *Save() {
        log(LOG_DONE) << "Originator -> Save()";
        return new ConcreteMemento(this->state_);
    }
    /**
     * Restores the Originator's state from a memento object.
     */
    void Restore(Memento *memento) {
        log(LOG_DONE) << "Originator -> Restore()";
        this->state_ = memento->state();
        std::cout << "Originator: My state has changed to: " << this->state_ << endl;
    }
};

/**
 * The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class Caretaker {
  /**
   * @var Memento[]
   */
private:
    std::vector<Memento *> mementos_;

    /**
     * @var Originator
     */
    Originator *originator_;

public:
    Caretaker(Originator* originator) : originator_(originator) {
        log(LOG_DONE) << "Caretaker -> CONST";
    }

    ~Caretaker() {
        for (auto m : mementos_) delete m;
    }

    void Backup() {
        log(LOG_DONE) << "Caretaker -> Backup()";
        std::cout << "\nCaretaker: Saving Originator's state..." << endl;
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() {
        log(LOG_DONE) << "Caretaker -> Undo()";
        if (!this->mementos_.size()) {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->GetName() << endl;
        try {
            this->originator_->Restore(memento);
        } catch (...) {
            this->Undo();
        }
    }
    void ShowHistory() const {
        log(LOG_DONE) << "Caretaker -> ShowHistory()";
        std::cout << "Caretaker: Here's the list of mementos:" << endl;
        for (Memento *memento : this->mementos_) {
        std::cout << memento->GetName() << "\n";
        }
    }
};

void patterns::behavioral::memento                             (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to capture an OBJ to restore it's captured state in the future?\n" <<
            "|SOLUTION:\n" <<
            "|   restore an object back to its previous state like 'restore'" << endl;
    
    srand(static_cast<unsigned int>(std::time(NULL)));

    log(LOG_INFO) << "create 'originator'";
    Originator *originator = new Originator("Super-duper-super-puper-super.");

    log(LOG_INFO) << "create 'caretaker'";
    Caretaker *caretaker = new Caretaker(originator);
    
    log(LOG_INFO) << "caretaker -> BackUp()";
    caretaker->Backup();

    log(LOG_INFO) << "originator -> DoSomething()";
    originator->DoSomething();
    
    log(LOG_INFO) << "caretaker -> BackUp()";
    caretaker->Backup();

    log(LOG_INFO) << "originator -> DoSomething()";
    originator->DoSomething();
    
    log(LOG_INFO) << "caretaker -> ShowHistory()";
    caretaker->ShowHistory();

    log(LOG_WARN) << "caretaker -> Undo()";
    caretaker->Undo();
    
    delete originator;
    delete caretaker;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IObserver {
public:
    virtual ~IObserver(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};

class ISubject {
public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Subject_obs : public ISubject {
public:
    virtual ~Subject_obs() {
        cout << "Goodbye, I was the Subject" << endl;
    }

    /**
     * The subscription management methods.
     */
    void Attach(IObserver *observer) override {
        log(LOG_DONE) << "Subject_obs -> Attach()";
        list_observer_.push_back(observer);
    }
    void Detach(IObserver *observer) override {
        log(LOG_DONE) << "Subject_obs -> Detach()";
        list_observer_.remove(observer);
    }
    void Notify() override {
        log(LOG_DONE) << "Subject_obs -> Notify()";
        std::list<IObserver *>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        log(LOG_DONE) << "Subject_obs -> CreateMessage()";
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        log(LOG_DONE) << "Subject_obs -> HowManyObservers()";
        cout << "There are " << list_observer_.size() << " observers in the list" << endl;
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    void SomeBusinessLogic() {
        log(LOG_DONE) << "Subject_obs -> SomeBusinessLogic()";
        this->message_ = "change message message";
        Notify();
        cout << "Some important work .." << endl;
    }

private:
    std::list<IObserver *> list_observer_;
    std::string message_;
};

class Observer_obs : public IObserver {
public:
    Observer_obs(Subject_obs &subject) : subject_(subject) {
        log(LOG_DONE) << "Observer_obs -> CONST";
        this->subject_.Attach(this);
        cout << "Hi, I'm the Observer \"" << ++Observer_obs::static_number_ << "\"." << endl ;
        this->number_ = Observer_obs::static_number_;
    }
    virtual ~Observer_obs() {
        log(LOG_DONE) << "Observer_obs -> DEST";
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\"." << endl;
    }

    void Update(const std::string &message_from_subject) override {
        log(LOG_DONE) << "Observer_obs -> Update()";
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        log(LOG_DONE) << "Observer_obs -> RemoveFromTheList()";
        subject_.Detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list." << endl;
    }
    void PrintInfo() {
        log(LOG_DONE) << "Observer_obs -> PrintInfo()";
        cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << endl;
    }

private:
    std::string message_from_subject_;
    Subject_obs &subject_;
    static int static_number_;
    int number_;
};

int Observer_obs::static_number_ = 0;

void patterns::behavioral::observer                            (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to define One-to-Many dependency where all Childs get notify on Base change?\n" <<
            "|SOLUTION:\n" <<
            "|   After subscribing the listening objects will be notified by a way of the method call" << endl;
    
    log(LOG_INFO) << "create subject, observer1-3";
    Subject_obs *subject = new Subject_obs;
    Observer_obs *observer1 = new Observer_obs(*subject);
    Observer_obs *observer2 = new Observer_obs(*subject);
    Observer_obs *observer3 = new Observer_obs(*subject);
    Observer_obs *observer4;
    Observer_obs *observer5;

    log(LOG_INFO) << "subject -> CreateMessage( AAAAAA )";
    subject->CreateMessage("AAAAAA");

    log(LOG_INFO) << "observer3 -> RemoveMeFromTheList()";
    observer3->RemoveMeFromTheList();

    log(LOG_INFO) << "subject -> CreateMessage( BBBBBB )";
    subject->CreateMessage("BBBBBB");

    log(LOG_INFO) << "create observer4";
    observer4 = new Observer_obs(*subject);

    log(LOG_INFO) << "observer2 -> RemoveMeFromTheList()";
    observer2->RemoveMeFromTheList();

    log(LOG_INFO) << "create observer5";
    observer5 = new Observer_obs(*subject);

    log(LOG_INFO) << "subject -> CreateMessage( CCCCCC )";
    subject->CreateMessage("CCCCCC");

    log(LOG_INFO) << "observer5 -> RemoveMeFromTheList()";
    observer5->RemoveMeFromTheList();

    log(LOG_INFO) << "observer4 -> RemoveMeFromTheList()";
    observer4->RemoveMeFromTheList();

    log(LOG_INFO) << "observer1 -> RemoveMeFromTheList()";
    observer1->RemoveMeFromTheList();

    delete observer5, observer4, observer3, observer2, observer1, subject;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */
class Context;

class State {
  /**
   * @var Context
   */
protected:
    Context *context_;
public:
    virtual ~State()                            {}
    void set_context(Context *context)          { log(LOG_DONE) << "State -> set_context() : set Status"; this->context_ = context; }
    virtual void Handle1()                      = 0;
    virtual void Handle2()                      = 0;
};

/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */
class Context {
  /**
   * @var State A reference to the current state of the Context.
   */
private:
    State *state_;

public:
    Context(State *state) : state_(nullptr)     { log(LOG_DONE) << "Context -> CONST : set Status"; this->TransitionTo(state); }
    ~Context()                                  { delete state_; }
    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State *state) {
        log(LOG_DONE) << "Context -> TransitionTo() : " << typeid(*state).name();
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }
    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void Request1()                             { log(LOG_DONE) << "Context -> Request1() : call Handle1()"; this->state_->Handle1(); }
    void Request2()                             { log(LOG_DONE) << "Context -> Request1() : call Handle2()"; this->state_->Handle2(); }
};

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */
class ConcreteStateA : public State {
public:
    void Handle1() override;
    void Handle2() override                     { log(LOG_DONE) << "ConcreteStateA -> Handle2()"; }
};

class ConcreteStateB : public State {
public:
    void Handle1() override                     { log(LOG_DONE) << "ConcreteStateB -> Handle1()"; }
    void Handle2() override                     { log(LOG_DONE) << "ConcreteStateB -> Handle2() : handle and change Status"; this->context_->TransitionTo(new ConcreteStateA); }
};

void ConcreteStateA::Handle1() {
    log(LOG_DONE) << "ConcreteStateA -> Handle1() : handle and change Status";
    this->context_->TransitionTo(new ConcreteStateB);
}


void patterns::behavioral::state                               (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to allow an OBJ to alter it's behaviour on internal state change?\n" <<
            "|SOLUTION:\n" <<
            "|   monolithic OBJ changes it's behaviour based on statuses factors\n" << endl;
    
    log(LOG_INFO) << "create Context OBJ with ConcreteStateA";
    Context *context = new Context(new ConcreteStateA);

    log(LOG_INFO) << "context -> Request1()";
    context->Request1();
    log(LOG_INFO) << "context -> Request1()";
    context->Request2();
    log(LOG_INFO) << "context -> Request1()";
    context->Request1();
    delete context;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StrategyInterface{
public:
    virtual void execute() const = 0;
};

class ConcreteStrategyA: public StrategyInterface{
public:
    void execute() const override               { log(LOG_DONE) << "ConcreteStrategyA -> execute()"; }
};

class ConcreteStrategyB: public StrategyInterface{
public:
    void execute() const override               { log(LOG_DONE) << "ConcreteStrategyB -> execute()"; }
};

class ConcreteStrategyC: public StrategyInterface{
public:
    void execute() const override               { log(LOG_DONE) << "ConcreteStrategyC -> execute()"; }
};

class Context_str{
private:
    StrategyInterface * strategy_;

public:
    explicit Context_str(StrategyInterface *strategy):strategy_(strategy)   { log(LOG_DONE) << "Context -> CONST"; }
    void set_strategy(StrategyInterface *strategy)                          { log(LOG_DONE) << "Context -> set_strategy()"; strategy_ = strategy; }
    void execute() const                                                    { log(LOG_DONE) << "Context -> execute()"; strategy_->execute(); }
};

void patterns::behavioral::strategy                            (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to vary independent from CLIENTs who use it?\n" <<
            "|SOLUTION:\n" <<
            "|   define a family of algorithm, encapsulate them and make them interchangeable" << endl;
    
    log(LOG_INFO) << "create ConcreteStrategyA/B/C";
    ConcreteStrategyA concreteStrategyA;
    ConcreteStrategyB concreteStrategyB;
    ConcreteStrategyC concreteStrategyC;

    log(LOG_INFO) << "create Context_strA/B/C";
    Context_str contextA(&concreteStrategyA);
    Context_str contextB(&concreteStrategyB);
    Context_str contextC(&concreteStrategyC);

    log(LOG_INFO) << "ContextA/B/C -> execute()";
    contextA.execute(); // output: "Called ConcreteStrategyA execute method"
    contextB.execute(); // output: "Called ConcreteStrategyB execute method"
    contextC.execute(); // output: "Called ConcreteStrategyC execute method"
    
    log(LOG_INFO) << "Context_strA -> set_strategy()";
    contextA.set_strategy(&concreteStrategyB);
    log(LOG_INFO) << "Context_strA -> execute()";
    contextA.execute(); // output: "Called ConcreteStrategyB execute method"
    log(LOG_INFO) << "Context_strA -> set_strategy()";
    contextA.set_strategy(&concreteStrategyC);
    log(LOG_INFO) << "Context_strA -> execute()";
    contextA.execute(); // output: "Called ConcreteStrategyC execute method"
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::tmplt_method                        (){

    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to redefine minor funcs leaving core implementation ?\n" <<
            "|SOLUTION:\n" <<
            "|   .\n" <<
            "|   ." << endl;
    
    log(LOG_WARN) << "NO_CODE to obvious";
    cout << "| class Base{\n" <<
            "|    void         base_logic()         {...some_common_logic...}\n" <<
            "|    virtual void specific_sub_logic() = 0;\n" <<
            "| }\n" <<
            "| class Child : public Base {\n" <<
            "|    virtual void specific_sub_logic() {...some_specific_logic...};\n" <<
            "| }\n" <<
            "| int main(){\n" <<
            "|    Base b;\n" <<
            "|    Child ch;\n" <<
            "|    b = ch\n" <<
            "|    b.base_logic()\n" <<
            "| }" << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wheel;
class Engine;
class Body;
class Car;
 
// interface to all car 'parts'
struct CarElementVisitor 
{
	virtual void visit(Wheel& wheel) const                  = 0;
	virtual void visit(Engine& engine) const                = 0;
	virtual void visit(Body& body) const                    = 0;
	virtual void visitCar(Car& car) const                   = 0;
};
 
// interface to one part
struct CarElement {
	virtual void accept(const CarElementVisitor& visitor)   = 0;	
};
 
// wheel element, there are four wheels with unique names
class Wheel : public CarElement {
public:
    explicit Wheel(const string& name) : name_(name)        { log(LOG_DONE) << "Wheel -> CONST"; }
    const string& getName() const                           { return name_; }
    void accept(const CarElementVisitor& visitor)           { log(LOG_DONE) << "Wheel -> accept()"; visitor.visit(*this); }

private:
    string name_;
};
 
class Engine : public CarElement {
public:
    void accept(const CarElementVisitor& visitor)           { log(LOG_DONE) << "Engine -> accept()"; visitor.visit(*this); }
};
 
class Body : public CarElement{
public:
    void accept(const CarElementVisitor& visitor)           { log(LOG_DONE) << "Body -> accept()"; visitor.visit(*this); }
};
 
class Car {
public:
    vector<unique_ptr<CarElement>>& getElements()           { log(LOG_DONE) << "Car -> getElement()"; return elements_; }
    Car() {
        log(LOG_DONE) << "Car -> CONST"; 
        // assume that neither push_back nor Wheel(const string&) may throw
        elements_.push_back( make_unique<Wheel>("front left") );
        elements_.push_back( make_unique<Wheel>("front right") );
        elements_.push_back( make_unique<Wheel>("back left") );
        elements_.push_back( make_unique<Wheel>("back right") );
        elements_.push_back( make_unique<Body>() );
        elements_.push_back( make_unique<Engine>() );
    }

private:
    vector<unique_ptr<CarElement>> elements_;
};


// PrintVisitor and DoVisitor show by using a different implementation the Car class is unchanged even though the algorithm is different in PrintVisitor and DoVisitor.
class CarElementPrintVisitor : public CarElementVisitor {
public:
    void visit(Wheel& wheel) const                          { log(LOG_DONE) << "CarElementPrintVisitor -> visit() : wheel" << wheel.getName(); }
    void visit(Engine& engine) const                        { log(LOG_DONE) << "CarElementPrintVisitor -> visit() : engin"; }
    void visit(Body& body) const                            { log(LOG_DONE) << "CarElementPrintVisitor -> visit() : body"; }
    void visitCar(Car& car) const
    {
        log(LOG_DONE) << "CarElementPrintVisitor -> visitCar() : car _______";
        vector<unique_ptr<CarElement>>& elems = car.getElements();
        
        for(auto &it : elems)
        {
            // this issues the callback i.e. to this from the element
            it->accept(*this);	  
        }
        log(LOG_DONE) << "CarElementPrintVisitor -> visitCar() : car complite";
    }
};

class CarElementDoVisitor : public CarElementVisitor 
{
public:
    // these are specific implementations added to the original object without modifying the original struct
    void visit(Wheel& wheel) const                          { log(LOG_DONE) << "CarElementDoVisitor -> visit() : wheel " << wheel.getName(); }
    void visit(Engine& engine) const                        { log(LOG_DONE) << "CarElementDoVisitor -> visit() : "; }
    void visit(Body& body) const                            { log(LOG_DONE) << "CarElementDoVisitor -> visit() : "; }
    void visitCar(Car& car) const
    {
        log(LOG_DONE) << "CarElementDoVisitor -> visitCar() : car _______"; 
        cout << endl << "Starting my car" << endl;
        vector<unique_ptr<CarElement>>& elems = car.getElements();

        for(auto& it : elems)
        {
            it->accept(*this);	// this issues the callback i.e. to this from the element  
        }
        log(LOG_DONE) << "CarElementDoVisitor -> visitCar() : car complite";
    }
};

void patterns::behavioral::visitor                             (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   how to define additional operation without changes on class?\n" <<
            "|SOLUTION:\n" <<
            "|   create an operation on unspecified type \n" << endl;
    
    log(LOG_INFO) << "create Car";
    Car car;

    log(LOG_INFO) << "create CarElemPrintVisitor";
	CarElementPrintVisitor printVisitor;

    log(LOG_INFO) << "create CarElemDoVisitor";
	CarElementDoVisitor doVisitor;
	

    log(LOG_INFO) << "CarElemPrintVisitor -> visitCar( car )";
	printVisitor.visitCar(car);

    log(LOG_INFO) << "CarElemDoVisitor -> visitCar( car )";
	doVisitor.visitCar(car);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void patterns::behavioral::model_view_controller               (){

    
    log(LOG_INFO) << "loop : '" << __func__ << "'...................";
    cout << "|PROBLEM:\n" << 
            "|   .?\n" <<
            "|SOLUTION:\n" <<
            "|   .\n" <<
            "|   ." << endl;
    
    //..
}