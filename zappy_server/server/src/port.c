/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** port
*/

#include "serrorh.h"
#include <stdlib.h>

// return -1 if port is invalid else the port as an int (with strtol)
signed int get_port(const char *port)
{
    char *endptr = NULL;
    long port_int = strtol(port, &endptr, 10);

    if (port_int < 0 || port_int > 65535 || (*endptr) != '\0') {
        LOG_ERROR("Invalid port: \"%s\"", port);
        return -1;
    }
    return port_int;
}
