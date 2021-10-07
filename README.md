# vez-shell
VEZ-Shell - A tiny shell implementation

# Enabling VEZ-Shell on your project

VEZ-Shell needs modification on the Linker file to work correctly on systems. It is necessary to add the following
lines to the linker file, on the `.text` section:

```ld
.text {
    // Some stuff previously

    __start_shell_commands = .;
    KEEP(*(.shell_commands))
    KEEP(*(.shell_commands*))
    __end_shell_commands = .;

    // Some stuff after
```

The following code explains how to export a command for the VEZ-Shell:
```c
int my_new_command(int argc, char **argv)
{
    do_stuff();

    return E_SUCCESS;
}

SHELL_DECLARE_COMMAND("my_new_command", my_new_command, "Executes the new command");
```

To declare multiple commands in an array you can do:
```c
const struct vez_shell_entry cmd_list[] = {
    // List stuff here
}

SHELL_DECLARE_COMMAND_ARRAY(cmd_list);
```