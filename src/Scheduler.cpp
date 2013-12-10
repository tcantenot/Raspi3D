#include <Scheduler.hpp>

#include <map>


namespace RPi {

namespace {

    std::map<int, SchedulerType> s_schedTypes =
    {
        { SCHED_IDLE,  SchedulerType::Idle       },
        { SCHED_OTHER, SchedulerType::Normal     },
        { SCHED_BATCH, SchedulerType::Batch      },
        { SCHED_FIFO,  SchedulerType::Fifo       },
        { SCHED_RR,    SchedulerType::RoundRobin }
    };

    std::map<SchedulerType, std::string> s_schedNames =
    {
        { SchedulerType::Idle       , "SCHED_IDLE"   },
        { SchedulerType::Normal     , "SCHED_NORMAL" },
        { SchedulerType::Batch      , "SCHED_BATCH"  },
        { SchedulerType::Fifo       , "SCHED_FIFO"   },
        { SchedulerType::RoundRobin , "SCHED_RR"     }
    };
}


void Scheduler::SetScheduler(pid_t pid, SchedulerType sched, int priority)
    throw(std::runtime_error)
{
    static struct sched_param param;

    param.sched_priority = priority;

    if(sched_setscheduler(pid, sched, &param) != 0)
    {
        perror("Scheduler::SetScheduler");
        throw std::runtime_error("Failed to set scheduler");
    }
}

SchedulerType Scheduler::GetScheduler(pid_t pid) throw(std::runtime_error)
{
    auto sched = sched_getscheduler(pid);
 
    if(sched < 0)
    {
        perror("Scheduler::GetScheduler");
        throw std::runtime_error("Failed to get scheduler");
    }
    
    return s_schedTypes[sched];
}


std::string Scheduler::GetSchedulerName(pid_t pid) throw(std::runtime_error)
{
    return s_schedNames[Scheduler::GetScheduler(pid)];
}

}
