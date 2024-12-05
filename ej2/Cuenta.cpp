#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Clase base abstracta para Cuentas Bancarias
class Cuenta {
protected:
    string tipoCuenta;
    double saldo;

public:
    Cuenta(double saldoInicial) : saldo(saldoInicial) {}
    virtual ~Cuenta() {}

    string getTipoCuenta() const { return tipoCuenta; }
    double getSaldo() const { return saldo; }

    virtual double calcularIntereses() const = 0;

    void depositar(double monto) {
        saldo += monto;
        cout << "Se han depositado " << monto << " en su cuenta " << tipoCuenta << ". Saldo actual: " << saldo << endl;
    }

    bool retirar(double monto) {
        if (monto > saldo) {
            cout << "Fondos insuficientes en la cuenta " << tipoCuenta << "." << endl;
            return false;
        }
        saldo -= monto;
        cout << "Se han retirado " << monto << " de su cuenta " << tipoCuenta << ". Saldo actual: " << saldo << endl;
        return true;
    }

    virtual void mostrarDetalles() const {
        cout << tipoCuenta << " - Saldo: " << fixed << setprecision(2) << saldo << endl;
    }
};

// Tipos de Cuentas Específicas
class CuentaAhorro : public Cuenta {
public:
    CuentaAhorro(double saldoInicial) : Cuenta(saldoInicial) {
        tipoCuenta = "Ahorro";
    }

    double calcularIntereses() const override {
        return saldo * 0.0045; // Interés del 0.45%
    }
};

class CuentaJoven : public Cuenta {
public:
    CuentaJoven(double saldoInicial) : Cuenta(saldoInicial) {
        tipoCuenta = "Joven";
    }

    double calcularIntereses() const override {
        return saldo * 0.050; // Interés del 5.00%
    }
};

class CuentaPluss : public Cuenta {
public:
    CuentaPluss(double saldoInicial) : Cuenta(saldoInicial) {
        tipoCuenta = "Pluss";
    }

    double calcularIntereses() const override {
        return saldo * 7.5; // Interés del 7.5%
    }
};

class CuentaEmpresarial : public Cuenta {
public:
    CuentaEmpresarial(double saldoInicial) : Cuenta(saldoInicial) {
        tipoCuenta = "Empresarial";
    }

    double calcularIntereses() const override {
        return saldo * 0.100; // Interés del 10.00%
    }
};

class TarjetaCredito : public Cuenta {
public:
    TarjetaCredito(double saldoInicial) : Cuenta(saldoInicial) {
        tipoCuenta = "Tarjeta de Credito";
    }

    double calcularIntereses() const override {
        return saldo * 0.2650; // Interés del 26.50%
    }
};
