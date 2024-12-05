#include "Cuenta.h"
#include <iostream>
#include <stdexcept>

// Implementación de la clase base Cuenta

Cuenta::Cuenta(double saldoInicial, const std::string &monedaCuenta)
    : saldo(saldoInicial), moneda(monedaCuenta) {}

std::string Cuenta::getTipoCuenta() const {
    return tipoCuenta;
}

double Cuenta::getSaldo() const {
    return saldo;
}

std::string Cuenta::getMoneda() const {
    return moneda;
}

std::vector<int> Cuenta::getClientesIDs() const {
    return clientesIDs;
}

void Cuenta::depositar(double monto) {
    saldo += monto;
    registrarOperacion("Depósito", monto);
}

bool Cuenta::retirar(double monto) {
    if (saldo >= monto) {
        saldo -= monto;
        registrarOperacion("Retiro", monto);
        return true;
    }
    return false;
}

void Cuenta::registrarOperacion(const std::string &descripcion, double monto) {
    operaciones.push_back(Operacion(descripcion, monto));
}

void Cuenta::mostrarDetalles() const {
    std::cout << "Tipo de Cuenta: " << tipoCuenta << "\n";
    std::cout << "Moneda: " << moneda << "\n";
    std::cout << "Saldo: " << saldo << "\n";
    std::cout << "Clientes asociados (por ID): ";
    for (const auto &id : clientesIDs) {
        std::cout << id << " ";
    }
    std::cout << "\n";
}

void Cuenta::mostrarEstadoDeCuenta() const {
    std::cout << "Estado de Cuenta:\n";
    for (const auto &op : operaciones) {
        std::cout << op.getDescripcion() << ": " << op.getMonto() << "\n";
    }
    std::cout << "Saldo Final en " << moneda << " : " << saldo << std::endl;
}

bool Cuenta::liquidarDeuda(double monto) {
    if (monto <= saldo) {
        saldo -= monto;
        registrarOperacion("Liquidación de deuda", monto);
        return true;
    }
    return false;
}

void Cuenta::transferir(Cuenta &cuentaDestino, double monto) {
    double tasa = (moneda == "Soles") ? 0.02 : 0.003; // Ejemplo de tasas
    double costoTransferencia = monto * tasa;

    if (saldo >= (monto + costoTransferencia)) {
        saldo -= (monto + costoTransferencia);
        cuentaDestino.depositar(monto);
        registrarOperacion("Transferencia enviada", monto + costoTransferencia);
        cuentaDestino.registrarOperacion("Transferencia recibida", monto);
        std::cout << "Transferencia realizada con éxito.\n";
    } else {
        std::cout << "Saldo insuficiente para realizar la transferencia.\n";
    }
}

void Cuenta::solicitarPrestamo(double monto, double tasaInteres) {
    prestamoActivo = std::make_shared<Prestamo>(monto, tasaInteres);
    saldo += monto;  // Aumenta el saldo con el monto del préstamo
    registrarOperacion("Préstamo solicitado", monto);
}

void Cuenta::mostrarPrestamo() const {
    if (prestamoActivo) {
        prestamoActivo->mostrarDetalles();
    } else {
        std::cout << "No hay préstamo activo.\n";
    }
}

// Subclases de Cuenta

CuentaAhorro::CuentaAhorro(double saldoInicial, const std::string &monedaCuenta)
    : Cuenta(saldoInicial, monedaCuenta) {
    tipoCuenta = "Ahorro";
}

double CuentaAhorro::calcularIntereses() const {
    return saldo * 0.0045; // 0.45% de interés
}

CuentaJoven::CuentaJoven(double saldoInicial, const std::string &monedaCuenta)
    : Cuenta(saldoInicial, monedaCuenta) {
    tipoCuenta = "Joven";
}

double CuentaJoven::calcularIntereses() const {
    return saldo * 0.0265; // 2.65% de interés
}

CuentaPluss::CuentaPluss(double saldoInicial, const std::string &monedaCuenta)
    : Cuenta(saldoInicial, monedaCuenta) {
    tipoCuenta = "Pluss";
}

double CuentaPluss::calcularIntereses() const {
    return saldo * 0.015; // 1.5% de interés
}

CuentaEmpresarial::CuentaEmpresarial(double saldoInicial, const std::string &monedaCuenta)
    : Cuenta(saldoInicial, monedaCuenta) {
    tipoCuenta = "Empresarial";
}

double CuentaEmpresarial::calcularIntereses() const {
    return saldo * 0.02; // 2% de interés
}

TarjetaCredito::TarjetaCredito(double saldoInicial, const std::string &monedaCuenta)
    : Cuenta(saldoInicial, monedaCuenta) {
    tipoCuenta = "Tarjeta de Crédito";
}

double TarjetaCredito::calcularIntereses() const {
    return saldo * 0.25; // 25% de interés
}

void TarjetaCredito::realizarCompra(double monto) {
    saldo += monto;
    registrarOperacion("Compra con tarjeta", monto);
}

// Implementación del Builder

CuentaBuilder &CuentaBuilder::setSaldo(double saldoInicial) {
    saldo = saldoInicial;
    return *this;
}

CuentaBuilder &CuentaBuilder::setTipo(const std::string &tipoCuenta) {
    tipo = tipoCuenta;
    return *this;
}

CuentaBuilder &CuentaBuilder::setMoneda(const std::string &monedaCuenta) {
    moneda = monedaCuenta;
    return *this;
}

CuentaBuilder &CuentaBuilder::addClienteID(int clienteID) {
    clientesIDs.push_back(clienteID);
    return *this;
}

std::shared_ptr<Cuenta> CuentaBuilder::build() const {
    std::shared_ptr<Cuenta> cuenta;
    if (tipo == "Ahorro") {
        cuenta = std::make_shared<CuentaAhorro>(saldo, moneda);
    } else if (tipo == "Joven") {
        cuenta = std::make_shared<CuentaJoven>(saldo, moneda);
    } else if (tipo == "Pluss") {
        cuenta = std::make_shared<CuentaPluss>(saldo, moneda);
    } else if (tipo == "Empresarial") {
        cuenta = std::make_shared<CuentaEmpresarial>(saldo, moneda);
    } else if (tipo == "Tarjeta de Crédito") {
        cuenta = std::make_shared<TarjetaCredito>(saldo, moneda);
    } else {
        throw std::invalid_argument("Tipo de cuenta no válido: " + tipo);
    }

    // Asignar clientes (por ID)
    for (const auto &id : clientesIDs) {
        cuenta->clientesIDs.push_back(id);
    }

    return cuenta;
}
