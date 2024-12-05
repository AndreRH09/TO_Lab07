#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <stdexcept>

using namespace std;
// Prestamo
class Prestamo
{
private:
    double monto;
    double tasaInteres;

public:
    Prestamo(double monto, double tasaInteres)
        : monto(monto), tasaInteres(tasaInteres) {}

    double calcularMontoTotal() const
    {
        return monto * (1 + tasaInteres / 100); // Calcular monto total con intereses
    }

    void mostrarDetalles() const
    {
        std::cout << "Monto del préstamo: " << monto << "\n";
        std::cout << "Intereses: " << tasaInteres << "%\n";
        std::cout << "Monto total: " << calcularMontoTotal() << "\n";
    }
};
// Clase base para operaciones

class Operacion
{
protected:
    std::string descripcion;
    double monto;

public:
    Operacion(const std::string &descripcion, double monto)
        : descripcion(descripcion), monto(monto) {}

    std::string getDescripcion() const { return descripcion; }
    double getMonto() const { return monto; }
};

// Clase base abstracta para cuentas
class Cuenta
{
protected:
    std::shared_ptr<Prestamo> prestamoActivo;
    std::string tipoCuenta;
    double saldo;
    std::vector<Operacion> operaciones;
    std::string moneda;           // Moneda de la cuenta
    std::vector<int> clientesIDs; // IDs de los clientes asociados a la cuenta

public:
    friend class CuentaBuilder; // Clase amiga Builder para acceder al vector
    Cuenta(double saldoInicial, const std::string &monedaCuenta)
        : saldo(saldoInicial), moneda(monedaCuenta) {}

    virtual ~Cuenta() = default;

    std::string getTipoCuenta() const { return tipoCuenta; }
    double getSaldo() const { return saldo; }
    std::string getMoneda() const { return moneda; }
    std::vector<int> getClientesIDs() const { return clientesIDs; }

    virtual double calcularIntereses() const = 0;

    void depositar(double monto)
    {
        saldo += monto;
        registrarOperacion("Depósito", monto);
    }

    bool retirar(double monto)
    {
        if (saldo >= monto)
        {
            saldo -= monto;
            registrarOperacion("Retiro", monto);
            return true;
        }
        return false;
    }

    void registrarOperacion(const std::string &descripcion, double monto)
    {
        operaciones.push_back(Operacion(descripcion, monto));
    }

    void mostrarDetalles() const
    {
        std::cout << "Tipo de Cuenta: " << tipoCuenta << "\n";
        std::cout << "Moneda: " << moneda << "\n";
        std::cout << "Saldo: " << saldo << "\n";
        std::cout << "Clientes asociados (por ID): ";
        for (const auto &id : clientesIDs)
        {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }

    void mostrarEstadoDeCuenta() const
    {
        std::cout << "Estado de Cuenta:\n";
        for (const auto &op : operaciones)
        {
            std::cout << op.getDescripcion() << ": " << op.getMonto() << "\n";
        }
        std::cout << "Saldo Final en " << moneda << " : " << saldo << endl;
    }

    bool liquidarDeuda(double monto)
    {
        if (monto <= saldo)
        {
            saldo -= monto;
            registrarOperacion("Liquidación de deuda", monto);
            return true;
        }
        return false;
    }

    void transferir(Cuenta &cuentaDestino, double monto)
    {
        double tasa = (moneda == "Soles") ? 0.02 : 0.003; // Ejemplo de tasas
        double costoTransferencia = monto * tasa;

        if (saldo >= (monto + costoTransferencia))
        {
            // Realizar la transferencia
            saldo -= (monto + costoTransferencia);
            cuentaDestino.depositar(monto);

            // Registrar operaciones
            registrarOperacion("Transferencia enviada", monto + costoTransferencia);
            cuentaDestino.registrarOperacion("Transferencia recibida", monto);
            std::cout << "Transferencia realizada con éxito.\n";
        }
        else
        {
            std::cout << "Saldo insuficiente para realizar la transferencia.\n";
        }
    }

    
    //Prestamo Personal

     // Agregar método para solicitar préstamo
    void solicitarPrestamo(double monto, double tasaInteres) {
    prestamoActivo = std::make_shared<Prestamo>(monto, tasaInteres);
    saldo += monto;  // Aumenta el saldo con el monto del préstamo
    registrarOperacion("Préstamo solicitado", monto);}

    // Mostrar detalles del préstamo si existe
    void mostrarPrestamo() const {
        if (prestamoActivo) {
            prestamoActivo->mostrarDetalles();
        } else {
            std::cout << "No hay préstamo activo.\n";
        }
    }
};

// Implementación de Cuentas Derivadas
class CuentaAhorro : public Cuenta
{
public:
    CuentaAhorro(double saldoInicial, const std::string &monedaCuenta)
        : Cuenta(saldoInicial, monedaCuenta)
    {
        tipoCuenta = "Ahorro";
    }

    double calcularIntereses() const override
    {
        return saldo * 0.0045; // 0.45% de interés
    }
};

class CuentaJoven : public Cuenta
{
public:
    CuentaJoven(double saldoInicial, const std::string &monedaCuenta)
        : Cuenta(saldoInicial, monedaCuenta)
    {
        tipoCuenta = "Joven";
    }

    double calcularIntereses() const override
    {
        return saldo * 0.0265; // 2.65% de interés
    }
};

class CuentaPluss : public Cuenta
{
public:
    CuentaPluss(double saldoInicial, const std::string &monedaCuenta)
        : Cuenta(saldoInicial, monedaCuenta)
    {
        tipoCuenta = "Pluss";
    }

    double calcularIntereses() const override
    {
        return saldo * 0.015; // 1.5% de interés
    }
};

class CuentaEmpresarial : public Cuenta
{
public:
    CuentaEmpresarial(double saldoInicial, const std::string &monedaCuenta)
        : Cuenta(saldoInicial, monedaCuenta)
    {
        tipoCuenta = "Empresarial";
    }

    double calcularIntereses() const override
    {
        return saldo * 0.02; // 2% de interés
    }
};

class TarjetaCredito : public Cuenta
{
public:
    TarjetaCredito(double saldoInicial, const std::string &monedaCuenta)
        : Cuenta(saldoInicial, monedaCuenta)
    {
        tipoCuenta = "Tarjeta de Crédito";
    }

    double calcularIntereses() const override
    {
        return saldo * 0.25; // 25% de interés
    }

    void realizarCompra(double monto)
    {
        saldo += monto;
        registrarOperacion("Compra con tarjeta", monto);
    }
};


// Builder para crear cuentas
class CuentaBuilder
{
private:
    double saldo;
    std::string tipo;
    std::string moneda;
    std::vector<int> clientesIDs;

public:
    CuentaBuilder &setSaldo(double saldoInicial)
    {
        saldo = saldoInicial;
        return *this;
    }

    CuentaBuilder &setTipo(const std::string &tipoCuenta)
    {
        tipo = tipoCuenta;
        return *this;
    }

    CuentaBuilder &setMoneda(const std::string &monedaCuenta)
    {
        moneda = monedaCuenta;
        return *this;
    }

    CuentaBuilder &addClienteID(int clienteID)
    {
        clientesIDs.push_back(clienteID);
        return *this;
    }

    std::shared_ptr<Cuenta> build() const
    {
        std::shared_ptr<Cuenta> cuenta;
        if (tipo == "Ahorro")
        {
            cuenta = std::make_shared<CuentaAhorro>(saldo, moneda);
        }
        else if (tipo == "Joven")
        {
            cuenta = std::make_shared<CuentaJoven>(saldo, moneda);
        }
        else if (tipo == "Pluss")
        {
            cuenta = std::make_shared<CuentaPluss>(saldo, moneda);
        }
        else if (tipo == "Empresarial")
        {
            cuenta = std::make_shared<CuentaEmpresarial>(saldo, moneda);
        }
        else if (tipo == "Tarjeta de Crédito")
        {
            cuenta = std::make_shared<TarjetaCredito>(saldo, moneda);
        }
        else
        {
            throw std::invalid_argument("Tipo de cuenta no válido: " + tipo);
        }

        // Asignar clientes (por ID)
        for (const auto &id : clientesIDs)
        {
            cuenta->clientesIDs.push_back(id);
        }

        return cuenta;
    }
};