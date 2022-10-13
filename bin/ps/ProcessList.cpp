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
#include <unistd.h>
#include <ProcessClient.h>
#include "ProcessList.h"

ProcessList::ProcessList(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Output system process list");
    parser().registerFlag('l', "level", "Display priority level of process(es)");
}

ProcessList::Result ProcessList::exec()
{
    const ProcessClient process;
    String out;
    u8 default_level = 3;

    // user enters "ps -l"
    if (arguments().get("level"))
        out << "ID  PARENT  USER GROUP PRIORITY STATUS     CMD\r\n";
    // Print header
    else
        out << "ID  PARENT  USER GROUP STATUS     CMD\r\n";

    // Loop processes
    for (ProcessID pid = 0; pid < ProcessClient::MaximumProcesses; pid++)
    {
        ProcessClient::Info info;

        const ProcessClient::Result result = process.processInfo(pid, info);
        if (result == ProcessClient::Success)
        {
            DEBUG("PID " << pid << " state = " << *info.textState);

            // Output a line
            char line[128];
            if (arguments().get("level"))
            {
                snprintf(line, sizeof(line),
                    "%3d %7d %4d %5d %8d %10s %32s\r\n",
                     pid, info.kernelState.parent,
                     0, 0, default_level, *info.textState, *info.command);
            }
            else
            {
                snprintf(line, sizeof(line),
                    "%3d %7d %4d %5d %10s %32s\r\n",
                     pid, info.kernelState.parent,
                     0, 0, *info.textState, *info.command);
            }
            out << line;
        }
    }

    // Output the table
    write(1, *out, out.length());
    return Success;
}
