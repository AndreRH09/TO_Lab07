#include "Prestamo.h"
#include <iostream>

Prestamo::Prestamo(double monto, double tasaInteres)
    : monto(monto), tasaInteres(tasaInteres) {}

double Prestamo::calcularMontoTotal() const {
    return monto * (1 + tasaInteres / 100); // Calcular monto total con intereses
}

void Prestamo::mostrarDetalles() const {
    std::cout << "Monto del préstamo: " << monto << "\n";
    std::cout << "Intereses: " << tasaInteres << "%\n";
    std::cout << "Monto total: " << calcularMontoTotal() << "\n";
}
