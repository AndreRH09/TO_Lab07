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
    virtual string GetMarca() { return ""; };
    virtual string GetColor() { return ""; }; // Agregar color
};

// Procesador
class Processor : public item
{
    virtual string GetName() { return ""; };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    virtual string GetMarca() { return ""; };
    virtual string GetColor() { return ""; };
};

class Intel5 : public Processor
{
    string GetName() { return "Intel I5"; };
    string GetMarca() { return "Intel"; };
    float GetPrice() { return 3000.0; };
    void GetConfiguration()
    {
        cout << "1.5Gz up to 2.0 Ghz, 2 cores, 4 threads, 8MB cache. RAM 4 GB / 8GB " << endl;
    };
};

class Intel7 : public Processor
{
    string GetName() { return "Intel I7"; };
    string GetMarca() { return "Intel"; };
    float GetPrice() { return 4700.0; };
    void GetConfiguration()
    {
        cout << "1.6Gz up to 1.99 Ghz, 9na Gen, 4 cores, 8 threads, 16MB cache, RAM 16 GB " << endl;
    };
};

// Almacenamiento
class Drive : public item
{
    virtual string GetName() { return ""; };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    virtual string GetMarca() { return ""; };
    virtual string GetColor() { return ""; };
};

class HDD : public Drive
{
    string GetName() { return "Hard Disk Drive"; };
    string GetMarca() { return "Kingston"; };
    float GetPrice() { return 150.0; };
    string GetColor() { return "Gray"; }; // Ejemplo de color
    void GetConfiguration()
    {
        cout << "Capacity 1TB, data transfer 1050 mbits/s" << endl;
    };
};

class SDD : public Drive
{
    string GetName() { return "Solid State Drive"; };
    string GetMarca() { return "DeepBlue"; };
    float GetPrice() { return 195.0; };
    string GetColor() { return "Blue"; }; // Ejemplo de color
    void GetConfiguration()
    {
        cout << "Capacity 250GB, data transfer 1800 mbits/s" << endl;
    };
};

// Pantalla
class DisplayType : public item
{
    virtual string GetName() { return ""; };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    virtual string GetMarca() { return ""; };
    virtual string GetColor() { return ""; };
};

class NonTouchScreen : public DisplayType
{
    string GetName() { return "Non-Touch Screen"; };
    string GetMarca() { return "FlexValley"; };
    float GetPrice() { return 195.0; };
    string GetColor() { return "Black"; }; // Ejemplo de color
    void GetConfiguration()
    {
        cout << "15.6 inch FHD (1980 x 1080), plane, etc." << endl;
    };
};

class Plasma : public DisplayType
{
    string GetName() { return "Plasma Display"; };
    string GetMarca() { return "PlasmaCorp"; };
    float GetPrice() { return 1200.0; };
    string GetColor() { return "Silver"; }; // Ejemplo de color
    void GetConfiguration()
    {
        cout << "40 inch, 4K resolution, 120Hz refresh rate." << endl;
    };
};

// Impresora
class Printer : public item
{
    
    virtual string GetName() { return ""; };
    virtual float GetPrice() { return 0.0; };
    virtual void GetConfiguration() {};
    virtual string GetMarca() { return ""; };
    virtual string GetColor() { return ""; };
};

class InkjetPrinter : public Printer
{
    string GetName() { return "Inkjet Printer"; };
    string GetMarca() { return "HP"; };
    float GetPrice() { return 250.0; };
    string GetColor() { return "White"; }; // Ejemplo de color
    void GetConfiguration()
    {
        cout << "Prints up to A4, 20 ppm, wireless, color printing." << endl;
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
            cout << "Marca: " << mLaptopParts[i]->GetMarca() << ", ";
            cout << "Color: " << mLaptopParts[i]->GetColor() << endl;
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
        lap->addParts(new NonTouchScreen());
        lap->addParts(new HDD());
        return lap;
    }

    laptop *opcion2()
    {
        laptop *lap = new laptop();
        lap->addParts(new Intel7());
        lap->addParts(new Plasma());
        lap->addParts(new SDD());
        lap->addParts(new InkjetPrinter());
        return lap;
    }
};

int main()
{
    laptopBuilder cotizar;

    cout << "Laptop Lenovo" << endl;
    laptop *lenovo = cotizar.opcion1();
    lenovo->getConfiguration();
    cout << "Precio: " << lenovo->getCost() << endl;

    cout << "\nLaptop HP" << endl;
    laptop *hp = cotizar.opcion2();
    hp->getConfiguration();
    cout << "Precio: " << hp->getCost() << endl;


    return 0;
}
