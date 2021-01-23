/**
 * @author Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 * @version 0.1
 *
 * @copyright Copyright Cristóvão Zuppardo Rufino (c) 2021
 * Please see LICENCE file to information regarding licensing
 */

#ifndef INCLUDE_VEZ_SHELL_H_
#define INCLUDE_VEZ_SHELL_H_

#include <stdint.h>

struct vez_shell_entry {
    const char *cmd;
    int (*fp)(int, char **);
    const char *help_str;
};

extern void vez_shell_greeter(const char *msg);

extern void vez_shell_iterate(const struct vez_shell_entry *cmd_list);

#endif // INCLUDE_VEZ_SHELL_H_