#include "mmu.h"

int calcular_direccion_fisica(uint32_t PID, int pagina, int desplazamiento)
{
    // Asumimos que hay una función llamada buscar_marco que busca el marco en la TLB o memoria
    // int marco = buscar_marco(PID, pagina); // Esta función debe ser implementada
    // return (tamanio_pagina * marco) + desplazamiento;
    return 0;
}

// TLB

t_TLB *crear_TLB()
{
    int max_entradas = obtener_cantidad_entradas_tlb();

    t_TLB *tlb = malloc(sizeof(t_TLB));
    tlb->entradas = malloc(sizeof(t_registro_TLB) * max_entradas);
    tlb->max_entradas = max_entradas;
    tlb->entradas_utilizadas = 0;
    tlb->tiempo_actual = 0;
    return tlb;
}

void destruir_TLB(t_TLB *tlb)
{
    free(tlb->entradas);
    free(tlb);
}

int buscar_en_TLB(t_TLB *tlb, uint32_t PID, int pagina)
{
    for (int i = 0; i < tlb->entradas_utilizadas; i++)
    {
        if (tlb->entradas[i].PID == PID && tlb->entradas[i].pagina == pagina)
        {
            if (obtener_algoritmo_tlb() == "LRU") // LRU
            {
                tlb->entradas[i].tiempo_utilizo = tlb->tiempo_actual++;
            }
            return tlb->entradas[i].marco;
        }
    }
    return -1; // Fallo de TLB, buscar el Memoria
}

void agregar_pagina_TLB(t_TLB *tlb, uint32_t PID, int pagina, int marco)
{
    if (tlb->entradas_utilizadas < tlb->max_entradas)
    {
        int tiempo_actual = tlb->tiempo_actual++;
        t_registro_TLB nueva_entrada = {PID, pagina, marco, tiempo_actual, tiempo_actual};
        tlb->entradas[tlb->entradas_utilizadas++] = nueva_entrada;
    }
    else
    {
        reemplazar_pagina_TLB(tlb, PID, pagina, marco);
    }
}

void reemplazar_pagina_TLB(t_TLB *tlb, uint32_t PID, int pagina, int marco)
{
    int indice = obtener_indice_para_reemplazo(tlb);
    int tiempo_actual = tlb->tiempo_actual++;
    t_registro_TLB nueva_entrada = {PID, pagina, marco, tiempo_actual, tiempo_actual};
    tlb->entradas[indice] = nueva_entrada;
}

int obtener_indice_para_reemplazo(t_TLB *tlb)
{
    if (obtener_algoritmo_tlb() == "FIFO") // FIFO
    {
        int indice_fifo = 0;
        for (int i = 1; i < tlb->entradas_utilizadas; i++)
        {
            if (tlb->entradas[i].tiempo_nacimiento < tlb->entradas[indice_fifo].tiempo_nacimiento)
            {
                indice_fifo = i;
            }
        }
        return indice_fifo;
    }
    else if (obtener_algoritmo_tlb() == "LRU") // LRU
    {
        // Encuentra la entrada con el menor valor de tiempo
        int indice_lru = 0;
        for (int i = 1; i < tlb->entradas_utilizadas; i++)
        {
            if (tlb->entradas[i].tiempo_utilizo < tlb->entradas[indice_lru].tiempo_utilizo)
            {
                indice_lru = i;
            }
        }
        return indice_lru;
    }
    return 0;
}
