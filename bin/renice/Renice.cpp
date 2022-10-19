/*
 * Copyright (C) 2015 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ProcessClient.h>
// #include <../bin/ps/ProcessList.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Alter the priority of running processes");
    parser().registerPositional("PRIORITY", "priority value to be used to alter scheduling");
    parser().registerPositional("PROCESS", "process ID to run at new scheduled priority");
    parser().registerFlag('n', "nice", "Schedule process with specified priority");
}

Renice::Result Renice::exec()
{
    u8 priority;
    unsigned int PID;

    if (arguments().get("nice")) {
        priority = atoi(arguments().get("PRIORITY"));
        PID = atoi(arguments().get("PROCESS"));
    }
    
    ProcessClient process;

    // Loop processes
    for (ProcessID pid = 0; pid < ProcessClient::MaximumProcesses; pid++)
    {
        ProcessClient::Info info;

        const ProcessClient::Result result = process.processInfo(pid, info);

        if (result == ProcessClient::Success)
        {   
            if (pid == PID) {
                process.changePriorityLevel(pid, info, priority);
            }
        }
    }

    return Success;
}
