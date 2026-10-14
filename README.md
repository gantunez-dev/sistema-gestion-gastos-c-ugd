# 📊 Sistema de Gestión de Gastos Personales y Familiares

Trabajo Práctico Integrador para la asignatura **Programación Estructurada I (2025)** — *Universidad Gastón Dachary (UGD)*.

## 👥 Integrantes - Grupo N° 2
- **Antúnez, Gonzalo Sebastián** (Matrícula: 68013)
- **Closs Irrazábal, Agustín** (Matrícula: 67971)
- **Falk, Lucas Germán** (Matrícula: 67993)

**Cátedra:**
- **Titular:** Mg. Ing. Karina B. Ecker
- **Adjuntos:** Ing. Fernando Arias, Lic. Prof. D. Gabriela Barros
- **JTP:** Ing. Lucas M. Rodoni

---

## 📌 Descripción del Proyecto
Aplicación desarrollada en **C++ (Programación Estructurada)** para la gestión organizada de ingresos, gastos mensuales (fijos, ocasionales, temporales/cuotas y anuales) y pagos por diversos medios. Incluye algoritmos de cálculo de saldo disponible, proyección financiera futura y exportación de reportes mensuales.

## 🛠️ Tecnologías y Conceptos Aplicados
- **Lenguaje:** C++ / C
- **Estructuras de Datos:** `typedef struct` para modelado de datos.
- **Persistencia en Archivos Binarios:** Manejo de datos estructurados (`.dat`).
- **Exportación de Reportes:** Generación automática de resúmenes en texto plano (`.txt`).
- **Punteros y Modularización:** Pasaje de parámetros por referencia y algoritmos de consulta.

## 📁 Estructura del Repositorio
- `/src`: Código fuente del sistema (`main.cpp`).
- `/data`: Archivos binarios pre-cargados para pruebas (`gastos.dat`, `ingresos.dat`, `pagos.dat`).
- `/docs`: Consignas académicas y carátula oficial de presentación en PDF.

## 💻 Compilación y Ejecución
```bash
g++ src/main.cpp -o gestion_gastos.exe
./gestion_gastos.exe