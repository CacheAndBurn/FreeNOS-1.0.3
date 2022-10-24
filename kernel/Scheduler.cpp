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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    return m_queue_p5.count() + m_queue_p4.count() + m_queue_p3.count() + m_queue_p2.count() + m_queue_p1.count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    if(proc->getPriorityLevel() == 5)
        m_queue_p5.push(proc);
    else if(proc->getPriorityLevel() == 4)
        m_queue_p4.push(proc);
    else if(proc->getPriorityLevel() == 3)
        m_queue_p3.push(proc);
    else if(proc->getPriorityLevel() == 2)
        m_queue_p2.push(proc);
    else if(proc->getPriorityLevel() == 1)
        m_queue_p1.push(proc);

    return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    for (Size i = 0; i < m_queue_p5.count(); i++)
    {
        Process *p = m_queue_p5.pop();

        if (p->getPriorityLevel() == 4)
        {
            m_queue_p4.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 3)
        {
            m_queue_p3.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 2)
        {
            m_queue_p2.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 1)
        {
            m_queue_p1.push(p);
            continue;
        }

        if (p == proc)
            return Success;
        else
            m_queue_p5.push(p);
    }
    for (Size i = 0; i < m_queue_p4.count(); i++)
    {
        Process *p = m_queue_p4.pop();

        if (p->getPriorityLevel() == 5)
        {
            m_queue_p5.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 3)
        {
            m_queue_p3.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 2)
        {
            m_queue_p2.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 1)
        {
            m_queue_p1.push(p);
            continue;
        }

        if (p == proc)
            return Success;
        else
            m_queue_p4.push(p);
    }
    for (Size i = 0; i < m_queue_p3.count(); i++)
    {
        Process *p = m_queue_p3.pop();

        if (p->getPriorityLevel() == 5)
        {
            m_queue_p5.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 4)
        {
            m_queue_p4.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 2)
        {
            m_queue_p2.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 1)
        {
            m_queue_p1.push(p);
            continue;
        }

        if (p == proc)
            return Success;
        else
            m_queue_p3.push(p);
    }
    for (Size i = 0; i < m_queue_p2.count(); i++)
    {
        Process *p = m_queue_p2.pop();

        if (p->getPriorityLevel() == 5)
        {
            m_queue_p5.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 4)
        {
            m_queue_p4.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 3)
        {
            m_queue_p3.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 1)
        {
            m_queue_p1.push(p);
            continue;
        }

        if (p == proc)
            return Success;
        else
            m_queue_p2.push(p);
    }
    for (Size i = 0; i < m_queue_p1.count(); i++)
    {
        Process *p = m_queue_p1.pop();

        if (p->getPriorityLevel() == 5)
        {
            m_queue_p5.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 4)
        {
            m_queue_p4.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 3)
        {
            m_queue_p3.push(p);
            continue;
        }
        else if (p->getPriorityLevel() == 2)
        {
            m_queue_p2.push(p);
            continue;
        }

        if (p == proc)
            return Success;
        else
            m_queue_p1.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    if (m_queue_p5.count() > 0)
    {
        Process *p = m_queue_p5.pop();
        m_queue_p5.push(p);

        return p;
    }
    else if (m_queue_p4.count() > 0)
    {
        Process *p = m_queue_p4.pop();
        m_queue_p4.push(p);

        return p;
    }
    else if (m_queue_p3.count() > 0)
    {
        Process *p = m_queue_p3.pop();
        m_queue_p3.push(p);

        return p;
    }
    else if (m_queue_p2.count() > 0)
    {
        Process *p = m_queue_p2.pop();
        m_queue_p2.push(p);

        return p;
    }
    else if (m_queue_p1.count() > 0)
    {
        Process *p = m_queue_p1.pop();
        m_queue_p1.push(p);

        return p;
    }

    return (Process *) NULL;
}
