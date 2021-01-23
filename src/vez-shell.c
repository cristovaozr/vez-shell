/**
 * @author Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 * @version 0.1
 *
 * @copyright Copyright Cristóvão Zuppardo Rufino (c) 2021
 * Please see LICENCE file to information regarding licensing
 */

#include "include/vez-shell.h"

#include "include/errors.h"

#include "ulibc/include/ustdio.h"

#include <stdint.h>
#include <string.h>

#define MAX_ARG_SIZE    8 /** Limits VEZ-Shell argument count to 8 */

#define MAX_LINE_SIZE   80 /** Limits VEZ-Shell line size */

#define SHELL_BANNER "> "   /** Default banner for the VEZ-Shell */

/**
 * @brief Variable that stores a line to process
 */
static char line[MAX_LINE_SIZE];
static char last_line[MAX_LINE_SIZE];

/** Stores current position of the line */
static uint32_t pos = 0;

static void process_line(char *line, const struct vez_shell_entry *cmd_list)
{
    char *saveptr, *cmd, *argv[MAX_ARG_SIZE];
    int argc;
    int32_t ret;

    // Extracts command name
    cmd = strtok_r(line, " ", &saveptr);
    if (cmd == NULL) {
        return;
    }

    // Extracts arguments
    for (argc = 0; argc < MAX_ARG_SIZE; argc++) {
        char *token = strtok_r(NULL, " ", &saveptr);
        if (token == NULL) break;
        argv[argc] = token;
    }

    // Looks for a command in the command list
    for (int i = 0; cmd_list[i].cmd; i++) {
        if(strcmp(cmd, cmd_list[i].cmd) == 0) {
            ret = cmd_list[i].fp(argc, argv);
            if (ret) uprintf("Error executing command %s\r\n", cmd);
            return;
        }
    }
    uprintf("Command not found: %s\r\n", cmd);
}

void vez_shell_greeter(const char *msg)
{
    uprintf("VEZ-Shell - A tiny shell\r\n");
    uprintf("Build date: %s, %s\r\n", __DATE__ , __TIME__);
    if (msg) uprintf("%s\r\n", msg);
    uprintf("\r\n" SHELL_BANNER);
}

void vez_shell_iterate(const struct vez_shell_entry *cmd_list)
{
    int c = ugetchar();
    if (c == -1) return;

    switch (c) {
        case '\b': // Backspace
        case 0x7f:
            if (pos > 0) uputchar(c);
            pos = ((pos - 1) < 0) ? 0 : pos - 1;
            break;

        case '\n':
        case '\r':
            uprintf("\r\n");
            line[pos] = '\0'; // EOL
            // Saves last line
            if (pos > 0) strcpy(last_line, line);
            process_line(line, cmd_list);
            pos = 0;
            uprintf(SHELL_BANNER); // New line
            break;

        case 0x12: // CTRL + R
            strcpy(line, last_line);
            uprintf("%s", line);
            pos = strlen(line);
            break;

        default:
            // If line buffer is full stop printint chars
            if (pos > (sizeof(line) - 1)) break;
            uputchar(c);
            line[pos++] = c;
            break;
    }
}
