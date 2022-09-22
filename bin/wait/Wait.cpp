#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for process to change state");
    parser().registerPositional("SECONDS", "Wait for process to change state after given number of seconds");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int sec = 0;

    // Convert input to seconds
    if ((sec = atoi(arguments().get("SECONDS"))) <= 0)
    {
        ERROR("invalid sleep time `" << arguments().get("SECONDS") << "'");
        return InvalidArgument;
    }

    // Wait now
    if (sleep(sec) != 0)
    {
        ERROR("failed to sleep: " << strerror(errno));
        return IOError;
    }

    // Done
    return Success;
}

// int main(int argc, char *argv[])
// {
//     pid_t cpid, w;
//     int wstatus;

//     cpid = fork();
//     if (cpid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (cpid == 0) {            /* Code executed by child */
//         printf("Child PID is %jd\n", (intmax_t) getpid());
//         if (argc == 1)
//             pause();                    /* Wait for signals */
//         _exit(atoi(argv[1]));

//     } else {                    /* Code executed by parent */
//         do {
//             w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
//             if (w == -1) {
//                 perror("waitpid");
//                 exit(EXIT_FAILURE);
//             }

//             if (WIFEXITED(wstatus)) {
//                 printf("exited, status=%d\n", WEXITSTATUS(wstatus));
//             } else if (WIFSIGNALED(wstatus)) {
//                 printf("killed by signal %d\n", WTERMSIG(wstatus));
//             } else if (WIFSTOPPED(wstatus)) {
//                 printf("stopped by signal %d\n", WSTOPSIG(wstatus));
//             } else if (WIFCONTINUED(wstatus)) {
//                 printf("continued\n");
//             }
//         } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
//         exit(EXIT_SUCCESS);
//     }
// }
