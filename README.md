# TP Sistemas Operativos 2024 - Primer Cuatrimestre
Este repositorio contiene el trabajo práctico correspondiente a la asignatura Sistemas Operativos de la carrera de Ingeniería en Sistemas de Información. El trabajo fue desarrollado durante un periodo de cuatro meses. La consigna del trabajo práctico puede encontrarse en el siguiente [enlace](https://docs.google.com/document/d/1-AqFTroovEMcA1BfC2rriB5jsLE6SUa4mbcAox1rPec/edit).

## Integrantes del grupo
- Facundo Gauna Somá
- Nehuen Balian Amaros
- Rocio Ochoa Charlín
- Eitan Wajsberg
- Yerilin Villarreal

## Descripción del Proyecto
El objetivo del trabajo práctico consiste en desarrollar una solución que permita la simulación de un sistema distribuido, capaz de planificar procesos, resolver peticiones al sistema y administrar de manera adecuada una memoria y un sistema de archivos bajo los esquemas explicados en sus correspondientes módulos.

## Dependencias

Para poder compilar y ejecutar el proyecto, es necesario tener instalada la
biblioteca [so-commons-library] de la cátedra:

```bash
git clone https://github.com/sisoputnfrba/so-commons-library
cd so-commons-library
make debug
make install
```

## Compilación

Cada módulo del proyecto se compila de forma independiente a través de un
archivo `makefile`. Para compilar un módulo, es necesario ejecutar el comando
`make` desde la carpeta correspondiente.

El ejecutable resultante se guardará en la carpeta `bin` del módulo.

## Importar desde Visual Studio Code

Para importar el workspace, debemos abrir el archivo `tp.code-workspace` desde
la interfaz o ejecutando el siguiente comando desde la carpeta raíz del
repositorio:

```bash
code tp.code-workspace
```

## Despliegue

Para desplegar el proyecto en una máquina Ubuntu Server, podemos utilizar el
script [so-deploy] de la cátedra:

```bash
git clone https://github.com/sisoputnfrba/so-deploy.git
cd so-deploy
./deploy.sh -r=release -p=utils -p=kernel -p=cpu -p=memoria -p=entradasalida "tp-{año}-{cuatri}-{grupo}"
```

El mismo se encargará de instalar las Commons, clonar el repositorio del grupo
y compilar el proyecto en la máquina remota.

Ante cualquier duda, podés consultar la documentación en el repositorio de
[so-deploy], o utilizar el comando `./deploy.sh -h`.

[so-commons-library]: https://github.com/sisoputnfrba/so-commons-library
[so-deploy]: https://github.com/sisoputnfrba/so-deploy
