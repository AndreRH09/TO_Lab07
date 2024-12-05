#ifndef PRESTAMO_H
#define PRESTAMO_H

class Prestamo {
private:
    double monto;
    double tasaInteres;

public:
    Prestamo(double monto, double tasaInteres);
    double calcularMontoTotal() const;
    void mostrarDetalles() const;
};

#endif
