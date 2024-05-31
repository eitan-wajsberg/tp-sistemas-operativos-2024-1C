#ifndef KERNEL_PCB_H_
#define KERNEL_PCB_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <commons/collections/dictionary.h>
#include "../configuraciones.h"
#include <utils/estructuras_compartidas/estructuras_compartidas.h>

typedef enum estado
{
    NEW,
    READY,
    EXEC,
    BLOCKED,
    EXIT,
} estado;

typedef struct
{
    uint32_t PID;
    int quantum;
    t_dictionary *registros_cpu;
    estado estado;
} t_pcb;

extern int32_t procesos_creados;
extern char *lista_PIDS;
extern t_contexto *contexto_ejecucion;

t_pcb *crear_pcb();
void destruir_pcb(t_pcb *pcb);

t_pcb *desencolar_pcb(t_list *pcbs);
void encolar_pcb(t_list *pcbs, t_pcb *pcb);
void mostrar_PIDS(t_list *pcbs);
void agregar_PID_a_lista_PIDS(void *pcb);
t_pcb *buscar_pcb_por_PID(t_list *lista_pcbs, uint32_t PID);

// Actualizo PCB en base a contexto de ejecución global
void actualizar_pcb(t_pcb *proceso, t_contexto *contexto);

// Toma valores de un pcb y asigno a contexto de ejecucion para pasar a CPU
t_contexto *asignar_valores_pcb_a_contexto(t_pcb *proceso);

#endif