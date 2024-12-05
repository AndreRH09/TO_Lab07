#ifndef OPERACION_H
#define OPERACION_H

#include <string>

class Operacion {
protected:
    std::string descripcion;
    double monto;

public:
    Operacion(const std::string &descripcion, double monto);
    std::string getDescripcion() const;
    double getMonto() const;
};

#endif
