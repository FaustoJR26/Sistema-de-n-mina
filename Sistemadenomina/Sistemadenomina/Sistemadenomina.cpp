using System;
using System.Collections.Generic;

namespace SistemaNomina
{
    // ===== CLASE BASE =====
    abstract class Empleado
    {
        public string PrimerNombre{ get; set; }
        public string ApellidoPaterno{ get; set; }
        public string NumeroSeguroSocial{ get; set; }

        public abstract decimal CalcularPagoSemanal();
    }

    // ===== EMPLEADO ASALARIADO =====
    class EmpleadoAsalariado : Empleado
    {
        public decimal SalarioSemanal{ get; set; }

            public override decimal CalcularPagoSemanal()
        {
            return SalarioSemanal;
        }
    }

    // ===== EMPLEADO POR HORAS =====
    class EmpleadoPorHoras : Empleado
    {
        public decimal SueldoPorHora{ get; set; }
        public int HorasTrabajadas{ get; set; }

            public override decimal CalcularPagoSemanal()
        {
            if (HorasTrabajadas <= 40)
                return SueldoPorHora * HorasTrabajadas;
            else
                return (SueldoPorHora * 40) +
                (SueldoPorHora * 1.5m * (HorasTrabajadas - 40));
        }
    }

    // ===== EMPLEADO POR COMISION =====
    class EmpleadoPorComision : Empleado
    {
        public decimal VentasBrutas{ get; set; }
        public decimal TarifaComision{ get; set; }

            public override decimal CalcularPagoSemanal()
        {
            return VentasBrutas * TarifaComision;
        }
    }

    // ===== EMPLEADO ASALARIADO POR COMISION =====
    class EmpleadoAsalariadoPorComision : Empleado
    {
        public decimal VentasBrutas{ get; set; }
        public decimal TarifaComision{ get; set; }
        public decimal SalarioBase{ get; set; }

            public override decimal CalcularPagoSemanal()
        {
            return (VentasBrutas * TarifaComision) +
                SalarioBase +
                (SalarioBase * 0.10m);
        }
    }

    // ===== PROGRAMA PRINCIPAL =====
    class Program
    {
        static List<Empleado> empleados = new List<Empleado>();

        static void Main(string[] args)
        {
            int opcion;

            do
            {
                Console.Clear();
                Console.WriteLine("=== SISTEMA DE NOMINA ===");
                Console.WriteLine("1. Agregar empleado");
                Console.WriteLine("2. Mostrar reporte semanal");
                Console.WriteLine("3. Salir");
                Console.Write("Seleccione una opcion: ");
                opcion = int.Parse(Console.ReadLine());

                switch (opcion)
                {
                case 1:
                    AgregarEmpleado();
                    break;
                case 2:
                    MostrarReporte();
                    break;
                }

                Console.WriteLine("\nPresione una tecla para continuar...");
                Console.ReadKey();

            } while (opcion != 3);
        }

        static void AgregarEmpleado()
        {
            Console.Clear();
            Console.WriteLine("TIPOS DE EMPLEADO");
            Console.WriteLine("1. Asalariado");
            Console.WriteLine("2. Por Horas");
            Console.WriteLine("3. Por Comision");
            Console.WriteLine("4. Asalariado por Comision");
            Console.Write("Seleccione el tipo: ");
            int tipo = int.Parse(Console.ReadLine());

            Console.Write("Apellido: ");
            string apellido = Console.ReadLine();

            Console.Write("Numero de Seguro Social: ");
            string nss = Console.ReadLine();

            Console.Write("Primer Nombre: ");
            string nombre = Console.ReadLine();

            switch (tipo)
            {
            case 1:
                Console.Write("Salario semanal: ");
                decimal salario = decimal.Parse(Console.ReadLine());

                empleados.Add(new EmpleadoAsalariado
                    {
                        PrimerNombre = nombre,
                        ApellidoPaterno = apellido,
                        NumeroSeguroSocial = nss,
                        SalarioSemanal = salario
                    });
                break;

            case 2:
                Console.Write("Sueldo por hora: ");
                decimal sueldoHora = decimal.Parse(Console.ReadLine());

                Console.Write("Horas trabajadas: ");
                int horas = int.Parse(Console.ReadLine());

                empleados.Add(new EmpleadoPorHoras
                    {
                        PrimerNombre = nombre,
                        ApellidoPaterno = apellido,
                        NumeroSeguroSocial = nss,
                        SueldoPorHora = sueldoHora,
                        HorasTrabajadas = horas
                    });
                break;

            case 3:
                Console.Write("Ventas brutas: ");
                decimal ventas = decimal.Parse(Console.ReadLine());

                Console.Write("Tarifa de comision: ");
                decimal tarifa = decimal.Parse(Console.ReadLine());

                empleados.Add(new EmpleadoPorComision
                    {
                        PrimerNombre = nombre,
                        ApellidoPaterno = apellido,
                        NumeroSeguroSocial = nss,
                        VentasBrutas = ventas,
                        TarifaComision = tarifa
                    });
                break;

            case 4:
                Console.Write("Ventas brutas: ");
                decimal ventas2 = decimal.Parse(Console.ReadLine());

                Console.Write("Tarifa de comision: ");
                decimal tarifa2 = decimal.Parse(Console.ReadLine());

                Console.Write("Salario base: ");
                decimal salarioBase = decimal.Parse(Console.ReadLine());

                empleados.Add(new EmpleadoAsalariadoPorComision
                    {
                        PrimerNombre = nombre,
                        ApellidoPaterno = apellido,
                        NumeroSeguroSocial = nss,
                        VentasBrutas = ventas2,
                        TarifaComision = tarifa2,
                        SalarioBase = salarioBase
                    });
                break;
            }

            Console.WriteLine("\nEmpleado agregado correctamente.");
        }

        static void MostrarReporte()
        {
            Console.Clear();
            Console.WriteLine("=== REPORTE SEMANAL DE PAGOS ===\n");

            foreach(var emp in empleados)
            {
                Console.WriteLine($"Empleado: {emp.PrimerNombre} {emp.ApellidoPaterno}");
                Console.WriteLine($"NSS: {emp.NumeroSeguroSocial}");
                Console.WriteLine($"Pago semanal: ${emp.CalcularPagoSemanal():0.00}");
                Console.WriteLine("--------------------------------");
            }
        }
    }
}

