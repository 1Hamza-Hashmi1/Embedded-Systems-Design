Done Using Cooperative Multitasking using OSThreadYield and unticking Round Robin in wizard

If OSThreadYield removed and Round Robin enabled, program will exacute Task C first (highest priority), then will give even time to Task A and Task D(medium priority) and finaly even time is given to Task B and Task E(lowest priority).  

Mutex is used to provide exclusive access to a shared resource. It allows only one thread to access the critical section (shared resource) at a time.  
A semaphore is used for signaling between threads. It can be used to control access to a shared resource but is more flexible than a mutex.
