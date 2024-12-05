#include "Operacion.h"

Operacion::Operacion(const std::string &descripcion, double monto)
    : descripcion(descripcion), monto(monto) {}

std::string Operacion::getDescripcion() const {
    return descripcion;
}

double Operacion::getMonto() const {
    return monto;
}
