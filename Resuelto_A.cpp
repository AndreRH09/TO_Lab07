#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class item
{
public:
    virtual string GetName() { return ""; };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    
};

// Procesador
class Processor : public item
{

    virtual string GetName() { return string(""); };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    
};

class Intel5 : public Processor
{
    string GetName() { return "Intel I5"; };

    float GetPrice() { return 3000.0; };
    void GetConfiguration()
    {
        cout << "1.5Gz up to 2.0 Ghz, 2 cores , 4 threads, 8MB cache. RAM 4 GB / 8GB " << endl;
    };
};

class Intel7 : public Processor
{
    string GetName() { return "Intel I7"; };

    float GetPrice() { return 4700.0; };
    void GetConfiguration()
    {
        cout << "1.6Gz up to 1.99 Ghz, 9na Gen, 4 cores , 8 threads.16MB cache. RAM 16 GB " << endl;
    };
};

// Almacenamiento
class Drive : public item
{
    virtual string GetName() { return string(""); };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
};

class HDD : public Drive
{
    string GetName() { return "Hard disk drive"; };
    float GetPrice() { return 150.0; };
    void GetConfiguration()
    {
        cout << "capacity 1TB, data transfer 1050 mbits/s" << endl;
    };
};

class SDD : public Drive
{
    string GetName() { return "Solid State drive"; };
    float GetPrice() { return 195.0; };
    void GetConfiguration()
    {
        cout << "capacity 250GB, data transfer 1800 mbits/s" << endl;
    };
};

// Display
class DisplayType : public item
{
    virtual string GetName() { return string(""); };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
};

class NonTouchScreen : public DisplayType
{
    string GetName() { return "Non Touch Screen"; };
    float GetPrice() { return 195.0; };
    void GetConfiguration()
    {
        cout << "15.6 inch FHD (1980 x 1080),plane, ..., etc" << endl;
    };
};

class Normal : public DisplayType
{
    string GetName() { return "Non Touch Screen"; };
    float GetPrice() { return 195.0; };
    void GetConfiguration()
    {
        cout << "15.6 inch FHD (1980 x 1080),plane, ..., etc" << endl;
    };
};

class laptop
{
private:
    vector<item *> mLaptopParts;

public:
    void addParts(item *item)
    {
        mLaptopParts.push_back(item);
    }

    float getCost()
    {
        float cost = 0.0;
        for (auto item : mLaptopParts)
        {
            cost += item->GetPrice();
        }
        return cost;
    }

    void getConfiguration()
    {
        for (auto i = 0; i < mLaptopParts.size(); i++)
        {
            cout << mLaptopParts[i]->GetName() + " : ";
            mLaptopParts[i]->GetConfiguration();
        }
    }
};

class laptopBuilder
{
private:
    /* data */
public:
    laptop *opcion1()
    {
        laptop *lap = new laptop();
        lap->addParts(new Intel5());
        lap->addParts(new Normal());
        lap->addParts(new HDD());
        return lap;
    }
    laptop *opcion2()
    {
        laptop *lap = new laptop();
        lap->addParts(new Intel7());
        lap->addParts(new Normal());
        lap->addParts(new SDD());
        return lap;
    }
};

int main()
{
    laptopBuilder cotizar;

    cout << "Laptop Lenovo" <<endl;

    laptop *lenovo = cotizar.opcion1();
    
    lenovo->getConfiguration();
    cout<< "Precio "<< lenovo->getCost()<<endl;

}
