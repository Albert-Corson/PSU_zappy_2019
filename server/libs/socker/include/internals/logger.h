/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** logger
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#ifndef LOG_FD
#define LOG_FD 2
#endif

#define LOG_LEVEL_NONE (0)
#define LOG_LEVEL_INFO (1 << 0)
#define LOG_LEVEL_WARN (1 << 2)
#define LOG_LEVEL_ERROR (1 << 3)
#define LOG_LEVEL_ALL (LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR)

#define LOG_INFO(fmt, ...)
#define LOG_WARN(fmt, ...)
#define LOG_ERROR(fmt, ...)

#ifdef SOCKER_LOG_LEVEL

    #include <stdio.h>

    #if (SOCKER_LOG_LEVEL & LOG_LEVEL_INFO)
        #undef LOG_INFO
        #define LOG_INFO(fmt, ...) \
            dprintf(LOG_FD, fmt "\n", __VA_ARGS__);
    #endif
    #if (SOCKER_LOG_LEVEL & LOG_LEVEL_WARN)
        #undef LOG_WARN
        #define LOG_WARN(fmt, ...) \
            dprintf(LOG_FD, "[?] " fmt "\n", __VA_ARGS__);
    #endif
    #if (SOCKER_LOG_LEVEL & LOG_LEVEL_ERROR)
        #undef LOG_ERROR
        #define LOG_ERROR(fmt, ...) \
            dprintf(LOG_FD, "[!] " fmt "\n", __VA_ARGS__);
    #endif
#endif

#endif /* !LOGGER_H_ */
