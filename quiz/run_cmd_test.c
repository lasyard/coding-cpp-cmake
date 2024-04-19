#include <stdbool.h>
#include <unistd.h>

#include <sys/wait.h>

#include "run_cmd.h"

int main(int argc, char *argv[])
{
    run_cmd(argc - 1, &argv[1]);
}
