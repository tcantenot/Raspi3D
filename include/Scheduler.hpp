#ifndef RPI_SCHEDULER_HPP
#define RPI_SCHEDULER_HPP

#include <sched.h>
#include <stdexcept>

namespace RPi {

    enum SchedulerType : decltype(SCHED_OTHER)
    {
        Idle       = SCHED_IDLE,
        Normal     = SCHED_OTHER,
        Batch      = SCHED_BATCH,
        Fifo       = SCHED_FIFO,
        RoundRobin = SCHED_RR
    };

    class Scheduler
    {
        public:
            Scheduler() = delete;
            ~Scheduler() = delete;

            static void SetScheduler(pid_t pid, SchedulerType sched, int priority)
                throw(std::runtime_error);

            static SchedulerType GetScheduler(pid_t pid) throw(std::runtime_error);

            static std::string GetSchedulerName(pid_t pid) throw(std::runtime_error);
    };
}

#endif //RPI_SCHEDULER_HPP
