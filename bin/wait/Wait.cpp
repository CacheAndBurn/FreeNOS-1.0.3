#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "sys/wait.h"
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for process to change state");
    parser().registerPositional("PID", "Wait for process to change state when given process ID");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    pid_t pid = atoi(arguments().get("PID"));
    int status;

    // Wait now
    if (waitpid(pid, &status, 0) != pid)
    {
        ERROR("failed to wait: " << strerror(errno));
        return IOError;
    }

    // Done
    return Success;
}
