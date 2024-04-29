#include <utils/comunicacion.h>

int crear_conexion(t_log *logger, char *ip, char *puerto)
{
    struct addrinfo hints, *server_info;
    int s;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(ip, puerto, &hints, &server_info);
    if (s)
    {
        log_error(logger, "No se pudo obtener información para conectar al puerto %s en la IP %s: %s", puerto, ip, gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    int socket_cliente = socket(server_info->ai_family,
                                server_info->ai_socktype,
                                server_info->ai_protocol);
    if (socket_cliente == -1)
    {
        log_error(logger, "No se pudo crear el socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
    {
        close(socket_cliente);
        log_error(logger, "No se pudo conectar el socket al puerto %s en la IP %s: %s", puerto, ip, strerror(errno));
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info);

    return socket_cliente;
}

int iniciar_servidor(t_log *logger, char *puerto)
{
    struct addrinfo hints, *servinfo;
    int s;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, puerto, &hints, &servinfo);
    if (s)
    {
        log_error(logger, "No se pudo obtener información para conectar al puerto %s: %s", puerto, gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // Creamos el socket de escucha del servidor
    int socket_servidor = socket(servinfo->ai_family,
                                 servinfo->ai_socktype,
                                 servinfo->ai_protocol);
    if (socket_servidor == -1)
    {
        log_error(logger, "No se pudo crear el socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Asociamos el socket a un puerto
    if (bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen))
    {
        close(socket_servidor);
        log_error(logger, "No se pudo bindear el socket al puerto %s: %s", puerto, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Escuchamos las conexiones entrantes
    if (listen(socket_servidor, SOMAXCONN))
    {
        close(socket_servidor);
        log_error(logger, "No se pudo poner el socket en escucha: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);

    return socket_servidor;
}

int esperar_cliente(t_log *logger, int socket_servidor)
{
    // Aceptamos un nuevo cliente
    int socket_cliente = accept(socket_servidor, NULL, NULL);
    if (socket_cliente == -1)
    {
        close(socket_servidor);
        log_error(logger, "No se pudo aceptar socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return socket_cliente;
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
    close(conexion);
    log_destroy(logger);
    config_destroy(config);
}

int handshake_cliente(t_log *logger, int conexion, int32_t handshake)
{
    size_t bytes;
    int32_t result;

    bytes = send(conexion, &handshake, sizeof(int32_t), 0);
    bytes = recv(conexion, &result, sizeof(int32_t), MSG_WAITALL);

    if (result == 0)
    {
        log_info(logger, "Handshake realizado correctamente");
        return 1;
    }
    else
    {
        log_error(logger, "Ocurrio un error en el Handshake");
        return 0;
    }
}

int handshake_servidor(t_log *logger, int conexion, int32_t handshake_esperado)
{
    size_t bytes;

    int32_t handshake;
    int32_t resultOk = 0;
    int32_t resultError = -1;

    bytes = recv(conexion, &handshake, sizeof(int32_t), MSG_WAITALL);
    if (handshake == handshake_esperado)
    {
        bytes = send(conexion, &resultOk, sizeof(int32_t), 0);
        return 1;
    }
    else
    {
        bytes = send(conexion, &resultError, sizeof(int32_t), 0);
        return 0;
    }
}