#include <iostream>
#include <memory>
#include <vector>
#include "Cuenta.cpp"

int main()
{
    // Crear cuentas utilizando el Builder
    CuentaBuilder builder;
    auto cuentaAhorro = builder.setSaldo(10000)
                            .setTipo("Ahorro")
                            .setMoneda("Euros")
                            .addClienteID(101) // ID del Cliente 1
                            .addClienteID(102) // ID del Cliente 2
                            .build();

    // Mostrar detalles de la cuenta
    cuentaAhorro->mostrarDetalles();
    std::cout << "\n";

    // Realizar operaciones
    cuentaAhorro->depositar(2000);
    cuentaAhorro->retirar(500);
    cuentaAhorro->retirar(200);
    cuentaAhorro->retirar(100);
    // Solicitar un préstamo
    cuentaAhorro->solicitarPrestamo(5000, 9.5);  // Monto: 5000, Tasa de interés: 9.5%
    cuentaAhorro->mostrarEstadoDeCuenta();

    std::cout << "\n";

    // Liquidar deuda
    if (cuentaAhorro->liquidarDeuda(1500))
    {
        std::cout << "Deuda liquidada\n";
    }
        std::cout << "\n";


    // Mostrar detalles de nuevo
    cuentaAhorro->mostrarDetalles();
    cout << "\n";
    cuentaAhorro->mostrarEstadoDeCuenta();

    // Cntrl k + } (debajo de borrar)

    auto cuenta1 = builder.setSaldo(5000).setTipo("Ahorro").setMoneda("Soles").build();
    auto cuenta2 = builder.setSaldo(3000).setTipo("Pluss").setMoneda("Dolares").build();

    // Mostrar estado inicial
    std::cout << "Estado inicial de las cuentas:\n";
    cuenta1->mostrarDetalles();
    cuenta2->mostrarDetalles();

    // Realizar transferencia
    cuenta1->transferir(*cuenta2, 1000);

    // // Mostrar }
    std::cout << "Estado final de las cuentas:\n";
    cuenta1->mostrarEstadoDeCuenta();
    cout<<endl;
    cuenta2->mostrarDetalles();

    return 0;
}