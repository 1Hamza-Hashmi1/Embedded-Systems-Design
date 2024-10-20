Done Using Cooperative Multitasking using OSThreadYield and unticking Round Robin in wizard

If OSThreadYield removed and Round Robin enabled, program will exacute Task C first (highest priority), then will give even time to Task A and Task D(medium priority) and finaly even time is given to Task B and Task E(lowest priority).  

When a task with a higher priority than the currently running task becomes ready to run, RTX suspends the currently running task. A preemptive task switch occurs when:  
•A token is returned to a semaphore, and a higher priority task is
waiting for the semaphore token. The currently running task is
suspended, and the higher priority task starts to run. The token can be
returned by the currently running task or by an interrupt service
routine.  
•A mutex is released and a higher priority task is waiting for the mutex.
The currently running task is suspended, and the higher priority task
starts to run.
