#ifndef MEMORIA_LECTURA_H
#define MEMORIA_LECTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuraciones.h"
#include <utils/estructuras_compartidas/instrucciones.h>

extern t_log *logger_obligatorio;
extern t_log *logger_propio;

// INDICE DE INSTRUCCIONES
t_dictionary *crear_indice_de_instrucciones();
void agregar_instrucciones_al_indice(t_dictionary *indice_de_instrucciones, uint32_t PID, int *tabla_de_paginas);
void quitar_instrucciones_al_indice(t_dictionary *indice_de_instrucciones, uint32_t PID);
void destruir_indice_de_instrucciones(t_dictionary *indice_de_instrucciones);

t_instruccion_cadena *leer_instruccion(int desplazamiento);

#endif