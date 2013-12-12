#include <Scheduler.hpp>

#include <map>
#include <iostream>


namespace RPi {

namespace {

    std::map<int, SchedulerType> s_schedTypesFromEnum =
    {
        { SCHED_IDLE,  SchedulerType::Idle       },
        { SCHED_OTHER, SchedulerType::Normal     },
        { SCHED_BATCH, SchedulerType::Batch      },
        { SCHED_FIFO,  SchedulerType::Fifo       },
        { SCHED_RR,    SchedulerType::RoundRobin }
    };

    std::map<SchedulerType, std::string> s_schedNamesFromType =
    {
        { SchedulerType::Idle       , "SCHED_IDLE"   },
        { SchedulerType::Normal     , "SCHED_NORMAL" },
        { SchedulerType::Batch      , "SCHED_BATCH"  },
        { SchedulerType::Fifo       , "SCHED_FIFO"   },
        { SchedulerType::RoundRobin , "SCHED_RR"     }
    };

    std::map<std::string, SchedulerType> s_schedTypesFromName =
    {
        { "SCHED_IDLE"   , SchedulerType::Idle       },
        { "SCHED_NORMAL" , SchedulerType::Normal     },
        { "SCHED_BATCH"  , SchedulerType::Batch      },
        { "SCHED_FIFO"   , SchedulerType::Fifo       },
        { "SCHED_RR"     , SchedulerType::RoundRobin }
    };
}


void Scheduler::SetScheduler(pid_t pid, SchedulerType sched, int priority)
    throw(std::runtime_error)
{
    static struct sched_param param;

    if(sched == SchedulerType::Idle || sched== SchedulerType::Normal)
    {
        priority = 0;
    }

    param.sched_priority = priority;

    if(sched_setscheduler(pid, sched, &param) != 0)
    {
        perror("Scheduler::SetScheduler");
        throw std::runtime_error("Failed to set scheduler");
    }
}

void Scheduler::SetScheduler(pid_t pid, std::string const & sched, int priority)
    throw(std::runtime_error)
{
    std::cout << "sched : " << s_schedNamesFromType[s_schedTypesFromName[sched]] << std::endl;
    Scheduler::SetScheduler(pid, s_schedTypesFromName[sched], priority);
}

void Scheduler::SetScheduler(pid_t pid, int sched, int priority)
    throw(std::runtime_error)
{
    Scheduler::SetScheduler(pid, s_schedTypesFromEnum[sched], priority);
}


SchedulerType Scheduler::GetScheduler(pid_t pid) throw(std::runtime_error)
{
    auto sched = sched_getscheduler(pid);
 
    if(sched < 0)
    {
        perror("Scheduler::GetScheduler");
        throw std::runtime_error("Failed to get scheduler");
    }
    
    return s_schedTypesFromEnum[sched];
}


std::string Scheduler::GetSchedulerName(pid_t pid) throw(std::runtime_error)
{
    return s_schedNamesFromType[Scheduler::GetScheduler(pid)];
}

SchedulerType Scheduler::SchedulerTypeFromName(std::string const & name)
{
    return s_schedTypesFromName[name];
}

std::string Scheduler::SchedulerNameFromType(SchedulerType type)
{
    return s_schedNamesFromType[type];
}

}
