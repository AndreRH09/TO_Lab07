#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// Clase base para los componentes del automóvil
class Componente {
public:
    virtual string GetNombre() const = 0; // Método virtual puro
    virtual float GetPrecio() const = 0;
    virtual void MostrarCaracteristicas() const = 0;
    virtual string GetColor() const = 0;

    virtual ~Componente() {}
};

// Subclase para la puerta
class Puerta : public Componente {
private:
    string color;
    float precio;
public:
    Puerta(string color, float precio) : color(color), precio(precio) {}

    string GetNombre() const override { return "Puerta"; }
    float GetPrecio() const override { return precio; }
    void MostrarCaracteristicas() const override { 
        cout << "Puerta: Color " << color << ", Precio: $" << precio << endl; 
    }
    string GetColor() const override { return color; }
};

// Subclase para la llanta
class Llanta : public Componente {
private:
    string color;
    float precio;
public:
    Llanta(string color, float precio) : color(color), precio(precio) {}

    string GetNombre() const override { return "Llanta"; }
    float GetPrecio() const override { return precio; }
    void MostrarCaracteristicas() const override { 
        cout << "Llanta: Color " << color << ", Precio: $" << precio << endl; 
    }
    string GetColor() const override { return color; }
};

// Subclase para el motor
class Motor : public Componente {
private:
    string tipo;
    float precio;
public:
    Motor(string tipo, float precio) : tipo(tipo), precio(precio) {}

    string GetNombre() const override { return "Motor"; }
    float GetPrecio() const override { return precio; }
    void MostrarCaracteristicas() const override { 
        cout << "Motor: Tipo " << tipo << ", Precio: $" << precio << endl; 
    }
    string GetColor() const override { return "N/A"; } // Motor no tiene color
};

// Clase para el automóvil
class Automovil {
private:
    vector<Componente*> componentes;
    float precioTotal;

public:
    Automovil() : precioTotal(0) {}

    void AgregarComponente(Componente* componente) {
        componentes.push_back(componente);
        precioTotal += componente->GetPrecio();
    }

    void MostrarAutomovil() const {
        cout << "Características del Automóvil:" << endl;
        for (auto& comp : componentes) {
            comp->MostrarCaracteristicas();
        }
        cout << "Precio total: $" << precioTotal << endl;
    }

    // Método de template para aplicar un descuento sobre los componentes seleccionados
    template <typename T>
    void AplicarDescuento(T porcentajeDescuento) {
        for (auto& comp : componentes) {
            float precio = comp->GetPrecio();
            precio -= precio * porcentajeDescuento / 100;
            cout << comp->GetNombre() << " con descuento: $" << precio << endl;
        }
    }

    ~Automovil() {
        for (auto comp : componentes) {
            delete comp;
        }
    }
};

int main() {
    // Crear componentes
    Componente* puerta = new Puerta("Rojo", 500);
    Componente* llanta = new Llanta("Negra", 150);
    Componente* motor = new Motor("V8", 3000);

    // Crear el automóvil y agregar componentes
    Automovil* autoCliente = new Automovil();
    autoCliente->AgregarComponente(puerta);
    autoCliente->AgregarComponente(llanta);
    autoCliente->AgregarComponente(motor);

    // Mostrar características del automóvil
    autoCliente->MostrarAutomovil();

    // Aplicar un descuento del 10%
    cout << "\nAplicando descuento del 10%" << endl;
    autoCliente->AplicarDescuento(10);

    delete autoCliente;
    return 0;
}
