#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class IBuilder
{
public:
    virtual ~IBuilder() {}
    virtual void ProducirParteA() const = 0;
    virtual void ProducirParteB() const = 0;
    virtual void ProducirParteC() const = 0;
};
class Producto1
{
public:
    vector<string> componentes;
    void ListaComp() const
    {
        cout << "Compenentes: ";
        for (size_t i = 0; i < componentes.size(); i++)
        {
            if (componentes[i] == componentes.back())
            {
                cout << componentes[i];
            }
            else
            {
                cout << componentes[i] << ", ";
            }
        }
        cout << endl;
    }
};
class BuilerEspecifico : public IBuilder
{
private:
    Producto1 *producto;

public:
    BuilerEspecifico()
    {
        this->Reset();
    }
    ~BuilerEspecifico()
    {
        delete producto;
    }
    void Reset()
    {
        this->producto = new Producto1();
    }
    void ProducirParteA() const override
    {
        this->producto->componentes.push_back("ParteA1");
    }
    void ProducirParteB() const override
    {
        this->producto->componentes.push_back("ParteB1");
    }
    void ProducirParteC() const override
    {
        this->producto->componentes.push_back("ParteC1");
    }
    Producto1 *GetProducto()
    {
        Producto1 *resultado = this->producto;
        this->Reset();
        return resultado;
    }
};

class Director
{
private:
    IBuilder *builder;

public:
    void set_builder(IBuilder *builder)
    {
        this->builder = builder;
    }
    void BuildProductoMin()
    {
        this->builder->ProducirParteA();
    }
    void BuildProductoCompleto()
    {
        this->builder->ProducirParteA();
        this->builder->ProducirParteB();
        this->builder->ProducirParteC();
    }
};
void ClienteCode(Director &director)
{
    BuilerEspecifico *builder = new BuilerEspecifico();
    director.set_builder(builder);
    cout << "ProductoBasico:\n";
    director.BuildProductoMin();
    Producto1 *p = builder->GetProducto();
    p->ListaComp();
    delete p;
    std::cout << "ProductoCompleto:\n";
    director.BuildProductoCompleto();
    p = builder->GetProducto();
    p->ListaComp();
    delete p;
    cout << "Productobasico:\n";
    builder->ProducirParteA();
    builder->ProducirParteC();
    p = builder->GetProducto();
    p->ListaComp();
    delete p;
    delete builder;
};
int main()
{
    Director *director = new Director();
    ClienteCode(*director);
    delete director;
    return 0;
}