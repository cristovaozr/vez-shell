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

/** VEZ Shell entry prototype */
struct vez_shell_entry {
    const char *cmd;
    int (*fp)(int, char **);
    const char *help_str;
};

/**
 * @brief Displays greeter message
 *
 * @param msg Custom greeter message
 */
extern void vez_shell_greeter(const char *msg);

/**
 * @brief Runs the shell iteration routine
 *
 * @param cmd_list The list of commands to process
 * @param cmd_len The number of command entries in the list
 */
extern void vez_shell_iterate(const struct vez_shell_entry *cmd_list, uint32_t cmd_len);

/** Symbol defined during linking time */
extern const struct vez_shell_entry __start_shell_commands;

/** Symbom defnied during linking time */
extern const struct vez_shell_entry __end_shell_commands;

/** Command array size in entries */
#define SHELL_COMMAND_SIZE (((uint32_t)&__end_shell_commands - (uint32_t)&__start_shell_commands) / sizeof(struct vez_shell_entry))

/** Command array start address */
#define SHELL_COMMAND_ARRAY_ADDR (&__start_shell_commands)

/** Declare a set of shell commands as an array */
#define SHELL_DECLARE_COMMAND_ARRAY(cmd_array) \
    const struct vez_shell_entry cmd_array \
    __attribute__((__section__(".shell_commands"))) __attribute__((__used__))

/** Decleare a shell command  */
#define SHELL_DECLARE_COMMAND(cmd_name, cmd_callback, cmd_desc) \
    const struct vez_shell_entry cmd_callback ## _entry \
    __attribute__((__section__(".shell_commands"))) __attribute__((__used__)) \
    = {cmd_name, cmd_callback, cmd_desc}

#endif // INCLUDE_VEZ_SHELL_H_