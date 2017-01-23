typedef unsigned int size_t;
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
__extension__
typedef signed long long int __int64_t;
__extension__
typedef unsigned long long int __uint64_t;
__extension__
typedef long long int __quad_t;
__extension__
typedef unsigned long long int __u_quad_t;
__extension__
typedef __u_quad_t __dev_t;
__extension__
typedef unsigned int __uid_t;
__extension__
typedef unsigned int __gid_t;
__extension__
typedef unsigned long int __ino_t;
__extension__
typedef __u_quad_t __ino64_t;
__extension__
typedef unsigned int __mode_t;
__extension__
typedef unsigned int __nlink_t;
__extension__
typedef long int __off_t;
__extension__
typedef __quad_t __off64_t;
__extension__
typedef int __pid_t;
__extension__
typedef struct 
{
        int __val[2];
} __fsid_t;
__extension__
typedef long int __clock_t;
__extension__
typedef unsigned long int __rlim_t;
__extension__
typedef __u_quad_t __rlim64_t;
__extension__
typedef unsigned int __id_t;
__extension__
typedef long int __time_t;
__extension__
typedef unsigned int __useconds_t;
__extension__
typedef long int __suseconds_t;
__extension__
typedef int __daddr_t;
__extension__
typedef long int __swblk_t;
__extension__
typedef int __key_t;
__extension__
typedef int __clockid_t;
__extension__
typedef void * __timer_t;
__extension__
typedef long int __blksize_t;
__extension__
typedef long int __blkcnt_t;
__extension__
typedef __quad_t __blkcnt64_t;
__extension__
typedef unsigned long int __fsblkcnt_t;
__extension__
typedef __u_quad_t __fsblkcnt64_t;
__extension__
typedef unsigned long int __fsfilcnt_t;
__extension__
typedef __u_quad_t __fsfilcnt64_t;
__extension__
typedef int __ssize_t;
typedef __off64_t __loff_t;
typedef __quad_t * __qaddr_t;
typedef char * __caddr_t;
__extension__
typedef int __intptr_t;
__extension__
typedef unsigned int __socklen_t;
struct timespec
{
        __time_t tv_sec;
        long int tv_nsec;
};
struct sched_param
{
        int __sched_priority;
};
extern int clone(int (* __fn)(void * __arg), void * __child_stack, int __flags, void * __arg, ...) __attribute__((__nothrow__));
extern int unshare(int __flags) __attribute__((__nothrow__));
extern int sched_getcpu(void) __attribute__((__nothrow__));
struct __sched_param
{
        int __sched_priority;
};
typedef unsigned long int __cpu_mask;
typedef struct 
{
        __cpu_mask __bits[1024 / (8 * sizeof(__cpu_mask))];
} cpu_set_t;
extern int __sched_cpucount(size_t __setsize, cpu_set_t * __setp) __attribute__((__nothrow__));
extern int sched_setparam(__pid_t __pid, __const struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_getparam(__pid_t __pid, struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_setscheduler(__pid_t __pid, int __policy, __const struct sched_param * __param) __attribute__((__nothrow__));
extern int sched_getscheduler(__pid_t __pid) __attribute__((__nothrow__));
extern int sched_yield(void) __attribute__((__nothrow__));
extern int sched_get_priority_max(int __algorithm) __attribute__((__nothrow__));
extern int sched_get_priority_min(int __algorithm) __attribute__((__nothrow__));
extern int sched_rr_get_interval(__pid_t __pid, struct timespec * __t) __attribute__((__nothrow__));
typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
struct tm
{
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
        int tm_wday;
        int tm_yday;
        int tm_isdst;
        long int tm_gmtoff;
        __const char * tm_zone;
};
struct itimerspec
{
        struct timespec it_interval;
        struct timespec it_value;
};
struct sigevent;
typedef __pid_t pid_t;
extern clock_t clock(void) __attribute__((__nothrow__));
extern time_t time(time_t * __timer) __attribute__((__nothrow__));
extern double difftime(time_t __time1, time_t __time0) __attribute__((__nothrow__)) __attribute__((__const__));
extern time_t mktime(struct tm * __tp) __attribute__((__nothrow__));
extern size_t strftime(char *__restrict __s, size_t __maxsize, __const char *__restrict __format, __const struct tm *__restrict __tp) __attribute__((__nothrow__));
extern struct tm * gmtime(__const time_t * __timer) __attribute__((__nothrow__));
extern struct tm * localtime(__const time_t * __timer) __attribute__((__nothrow__));
extern struct tm * gmtime_r(__const time_t *__restrict __timer, struct tm *__restrict __tp) __attribute__((__nothrow__));
extern struct tm * localtime_r(__const time_t *__restrict __timer, struct tm *__restrict __tp) __attribute__((__nothrow__));
extern char * asctime(__const struct tm * __tp) __attribute__((__nothrow__));
extern char * ctime(__const time_t * __timer) __attribute__((__nothrow__));
extern char * asctime_r(__const struct tm *__restrict __tp, char *__restrict __buf) __attribute__((__nothrow__));
extern char * ctime_r(__const time_t *__restrict __timer, char *__restrict __buf) __attribute__((__nothrow__));
extern char * __tzname[2];
extern int __daylight;
extern long int __timezone;
extern char * tzname[2];
extern void tzset(void) __attribute__((__nothrow__));
extern int daylight;
extern long int timezone;
extern int stime(__const time_t * __when) __attribute__((__nothrow__));
extern time_t timegm(struct tm * __tp) __attribute__((__nothrow__));
extern time_t timelocal(struct tm * __tp) __attribute__((__nothrow__));
extern int dysize(int __year) __attribute__((__nothrow__)) __attribute__((__const__));
extern int nanosleep(__const struct timespec * __requested_time, struct timespec * __remaining);
extern int clock_getres(clockid_t __clock_id, struct timespec * __res) __attribute__((__nothrow__));
extern int clock_gettime(clockid_t __clock_id, struct timespec * __tp) __attribute__((__nothrow__));
extern int clock_settime(clockid_t __clock_id, __const struct timespec * __tp) __attribute__((__nothrow__));
extern int clock_nanosleep(clockid_t __clock_id, int __flags, __const struct timespec * __req, struct timespec * __rem);
extern int clock_getcpuclockid(pid_t __pid, clockid_t * __clock_id) __attribute__((__nothrow__));
extern int timer_create(clockid_t __clock_id, struct sigevent *__restrict __evp, timer_t *__restrict __timerid) __attribute__((__nothrow__));
extern int timer_delete(timer_t __timerid) __attribute__((__nothrow__));
extern int timer_settime(timer_t __timerid, int __flags, __const struct itimerspec *__restrict __value, struct itimerspec *__restrict __ovalue) __attribute__((__nothrow__));
extern int timer_gettime(timer_t __timerid, struct itimerspec * __value) __attribute__((__nothrow__));
extern int timer_getoverrun(timer_t __timerid) __attribute__((__nothrow__));
typedef int __sig_atomic_t;
typedef struct 
{
        unsigned long int __val[(1024 / (8 * sizeof(unsigned long int)))];
} __sigset_t;
typedef __sigset_t sigset_t;
typedef unsigned long int pthread_t;
typedef union 
{
        char __size[36];
        long int __align;
} pthread_attr_t;
typedef struct __pthread_internal_slist
{
        struct __pthread_internal_slist * __next;
} __pthread_slist_t;
typedef union 
{
        struct __pthread_mutex_s
        {
                int __lock;
                unsigned int __count;
                int __owner;
                int __kind;
                unsigned int __nusers;
                __extension__
                union 
                {
                        int __spins;
                        __pthread_slist_t __list;
                };
        } __data;
        char __size[24];
        long int __align;
} pthread_mutex_t;
typedef union 
{
        char __size[4];
        long int __align;
} pthread_mutexattr_t;
typedef union 
{
        struct 
        {
                int __lock;
                unsigned int __futex;
                __extension__
                unsigned long long int __total_seq;
                __extension__
                unsigned long long int __wakeup_seq;
                __extension__
                unsigned long long int __woken_seq;
                void * __mutex;
                unsigned int __nwaiters;
                unsigned int __broadcast_seq;
        } __data;
        char __size[48];
        __extension__
        long long int __align;
} pthread_cond_t;
typedef union 
{
        char __size[4];
        long int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union 
{
        struct 
        {
                int __lock;
                unsigned int __nr_readers;
                unsigned int __readers_wakeup;
                unsigned int __writer_wakeup;
                unsigned int __nr_readers_queued;
                unsigned int __nr_writers_queued;
                unsigned int __flags;
                int __writer;
        } __data;
        char __size[32];
        long int __align;
} pthread_rwlock_t;
typedef union 
{
        char __size[8];
        long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union 
{
        char __size[20];
        long int __align;
} pthread_barrier_t;
typedef union 
{
        char __size[4];
        int __align;
} pthread_barrierattr_t;
typedef int __jmp_buf[6];
enum 
{
    PTHREAD_CREATE_JOINABLE, 
    PTHREAD_CREATE_DETACHED
};
enum 
{
    PTHREAD_MUTEX_TIMED_NP, 
    PTHREAD_MUTEX_RECURSIVE_NP, 
    PTHREAD_MUTEX_ERRORCHECK_NP, 
    PTHREAD_MUTEX_ADAPTIVE_NP
};
enum 
{
    PTHREAD_RWLOCK_PREFER_READER_NP, 
    PTHREAD_RWLOCK_PREFER_WRITER_NP, 
    PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP, 
    PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
enum 
{
    PTHREAD_INHERIT_SCHED, 
    PTHREAD_EXPLICIT_SCHED
};
enum 
{
    PTHREAD_SCOPE_SYSTEM, 
    PTHREAD_SCOPE_PROCESS
};
enum 
{
    PTHREAD_PROCESS_PRIVATE, 
    PTHREAD_PROCESS_SHARED
};
struct _pthread_cleanup_buffer
{
        void (* __routine)(void *);
        void * __arg;
        int __canceltype;
        struct _pthread_cleanup_buffer * __prev;
};
enum 
{
    PTHREAD_CANCEL_ENABLE, 
    PTHREAD_CANCEL_DISABLE
};
enum 
{
    PTHREAD_CANCEL_DEFERRED, 
    PTHREAD_CANCEL_ASYNCHRONOUS
};
extern int pthread_create(pthread_t *__restrict __newthread, __const pthread_attr_t *__restrict __attr, void * (* __start_routine)(void *), void *__restrict __arg) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 3)));
extern void pthread_exit(void * __retval) __attribute__((__noreturn__));
extern int pthread_join(pthread_t __th, void * * __thread_return);
extern int pthread_detach(pthread_t __th) __attribute__((__nothrow__));
extern pthread_t pthread_self(void) __attribute__((__nothrow__)) __attribute__((__const__));
extern int pthread_equal(pthread_t __thread1, pthread_t __thread2) __attribute__((__nothrow__));
extern int pthread_attr_init(pthread_attr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_destroy(pthread_attr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getdetachstate(__const pthread_attr_t * __attr, int * __detachstate) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setdetachstate(pthread_attr_t * __attr, int __detachstate) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getguardsize(__const pthread_attr_t * __attr, size_t * __guardsize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setguardsize(pthread_attr_t * __attr, size_t __guardsize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getschedparam(__const pthread_attr_t *__restrict __attr, struct sched_param *__restrict __param) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setschedparam(pthread_attr_t *__restrict __attr, __const struct sched_param *__restrict __param) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_getschedpolicy(__const pthread_attr_t *__restrict __attr, int *__restrict __policy) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setschedpolicy(pthread_attr_t * __attr, int __policy) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getinheritsched(__const pthread_attr_t *__restrict __attr, int *__restrict __inherit) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setinheritsched(pthread_attr_t * __attr, int __inherit) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getscope(__const pthread_attr_t *__restrict __attr, int *__restrict __scope) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setscope(pthread_attr_t * __attr, int __scope) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getstackaddr(__const pthread_attr_t *__restrict __attr, void * *__restrict __stackaddr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2))) __attribute__((__deprecated__));
extern int pthread_attr_setstackaddr(pthread_attr_t * __attr, void * __stackaddr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1))) __attribute__((__deprecated__));
extern int pthread_attr_getstacksize(__const pthread_attr_t *__restrict __attr, size_t *__restrict __stacksize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_attr_setstacksize(pthread_attr_t * __attr, size_t __stacksize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_attr_getstack(__const pthread_attr_t *__restrict __attr, void * *__restrict __stackaddr, size_t *__restrict __stacksize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2, 3)));
extern int pthread_attr_setstack(pthread_attr_t * __attr, void * __stackaddr, size_t __stacksize) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_setschedparam(pthread_t __target_thread, int __policy, __const struct sched_param * __param) __attribute__((__nothrow__)) __attribute__((__nonnull__(3)));
extern int pthread_getschedparam(pthread_t __target_thread, int *__restrict __policy, struct sched_param *__restrict __param) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern int pthread_setschedprio(pthread_t __target_thread, int __prio) __attribute__((__nothrow__));
extern int pthread_once(pthread_once_t * __once_control, void (* __init_routine)(void)) __attribute__((__nonnull__(1, 2)));
extern int pthread_setcancelstate(int __state, int * __oldstate);
extern int pthread_setcanceltype(int __type, int * __oldtype);
extern int pthread_cancel(pthread_t __th);
extern void pthread_testcancel(void);
typedef struct 
{
        struct 
        {
                __jmp_buf __cancel_jmp_buf;
                int __mask_was_saved;
        } __cancel_jmp_buf[1];
        void * __pad[4];
} __pthread_unwind_buf_t __attribute__((__aligned__));
struct __pthread_cleanup_frame
{
        void (* __cancel_routine)(void *);
        void * __cancel_arg;
        int __do_it;
        int __cancel_type;
};
extern void __pthread_register_cancel(__pthread_unwind_buf_t * __buf) __attribute__((__regparm__(1)));
extern void __pthread_unregister_cancel(__pthread_unwind_buf_t * __buf) __attribute__((__regparm__(1)));
extern void __pthread_unwind_next(__pthread_unwind_buf_t * __buf) __attribute__((__regparm__(1))) __attribute__((__noreturn__)) __attribute__((__weak__));
struct __jmp_buf_tag;
extern int __sigsetjmp(struct __jmp_buf_tag * __env, int __savemask) __attribute__((__nothrow__));
extern int pthread_mutex_init(pthread_mutex_t * __mutex, __const pthread_mutexattr_t * __mutexattr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutex_destroy(pthread_mutex_t * __mutex) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutex_trylock(pthread_mutex_t * __mutex) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutex_lock(pthread_mutex_t * __mutex) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutex_timedlock(pthread_mutex_t *__restrict __mutex, __const struct timespec *__restrict __abstime) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_mutex_unlock(pthread_mutex_t * __mutex) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutexattr_init(pthread_mutexattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutexattr_destroy(pthread_mutexattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_mutexattr_getpshared(__const pthread_mutexattr_t *__restrict __attr, int *__restrict __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_mutexattr_setpshared(pthread_mutexattr_t * __attr, int __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_init(pthread_rwlock_t *__restrict __rwlock, __const pthread_rwlockattr_t *__restrict __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_destroy(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_rdlock(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_tryrdlock(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict __rwlock, __const struct timespec *__restrict __abstime) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_rwlock_wrlock(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_trywrlock(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict __rwlock, __const struct timespec *__restrict __abstime) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_rwlock_unlock(pthread_rwlock_t * __rwlock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlockattr_init(pthread_rwlockattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlockattr_destroy(pthread_rwlockattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlockattr_getpshared(__const pthread_rwlockattr_t *__restrict __attr, int *__restrict __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_rwlockattr_setpshared(pthread_rwlockattr_t * __attr, int __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_rwlockattr_getkind_np(__const pthread_rwlockattr_t *__restrict __attr, int *__restrict __pref) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t * __attr, int __pref) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_cond_init(pthread_cond_t *__restrict __cond, __const pthread_condattr_t *__restrict __cond_attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_cond_destroy(pthread_cond_t * __cond) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_cond_signal(pthread_cond_t * __cond) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_cond_broadcast(pthread_cond_t * __cond) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_cond_wait(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex) __attribute__((__nonnull__(1, 2)));
extern int pthread_cond_timedwait(pthread_cond_t *__restrict __cond, pthread_mutex_t *__restrict __mutex, __const struct timespec *__restrict __abstime) __attribute__((__nonnull__(1, 2, 3)));
extern int pthread_condattr_init(pthread_condattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_condattr_destroy(pthread_condattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_condattr_getpshared(__const pthread_condattr_t *__restrict __attr, int *__restrict __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_condattr_setpshared(pthread_condattr_t * __attr, int __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_condattr_getclock(__const pthread_condattr_t *__restrict __attr, __clockid_t *__restrict __clock_id) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_condattr_setclock(pthread_condattr_t * __attr, __clockid_t __clock_id) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_spin_init(pthread_spinlock_t * __lock, int __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_spin_destroy(pthread_spinlock_t * __lock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_spin_lock(pthread_spinlock_t * __lock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_spin_trylock(pthread_spinlock_t * __lock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_spin_unlock(pthread_spinlock_t * __lock) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrier_init(pthread_barrier_t *__restrict __barrier, __const pthread_barrierattr_t *__restrict __attr, unsigned int __count) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrier_destroy(pthread_barrier_t * __barrier) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrier_wait(pthread_barrier_t * __barrier) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrierattr_init(pthread_barrierattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrierattr_destroy(pthread_barrierattr_t * __attr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_barrierattr_getpshared(__const pthread_barrierattr_t *__restrict __attr, int *__restrict __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int pthread_barrierattr_setpshared(pthread_barrierattr_t * __attr, int __pshared) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_key_create(pthread_key_t * __key, void (* __destr_function)(void *)) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int pthread_key_delete(pthread_key_t __key) __attribute__((__nothrow__));
extern void * pthread_getspecific(pthread_key_t __key) __attribute__((__nothrow__));
extern int pthread_setspecific(pthread_key_t __key, __const void * __pointer) __attribute__((__nothrow__));
extern int pthread_getcpuclockid(pthread_t __thread_id, __clockid_t * __clock_id) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int pthread_atfork(void (* __prepare)(void), void (* __parent)(void), void (* __child)(void)) __attribute__((__nothrow__));
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
__extension__
typedef long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
__extension__
typedef unsigned long long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
__extension__
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
__extension__
typedef unsigned long long int uint_least64_t;
typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;
typedef struct mintaka_thread_info mintaka_thread_info;
mintaka_thread_info * mintaka_get_thread_info(void);
void mintaka_set_filebase(const char * tracefile_basename);
void mintaka_set_fullpath_filebase(const char * tracefile_basename);
const char * mintaka_get_filebase(void);
void mintaka_app_begin(void);
void mintaka_app_end(void);
void mintaka_merge(void);
static void mintaka_set_enable(int enable);
static int mintaka_get_enable(void);
void mintaka_thread_begin(int processor, int thread);
void mintaka_thread_end(void);
static void mintaka_state_run(void);
static void mintaka_state_schedule(void);
static void mintaka_state_block(void);
static void mintaka_state_synch(void);
static void mintaka_state_idle(void);
static void mintaka_set_state(int state);
static int mintaka_get_state(void);
static void mintaka_event(int event, uint64_t value);
static void mintaka_state_and_event(int state, int event, uint64_t value);
void mintaka_index_event(int event, const char * description);
int mintaka_index_get(const char * string, int number);
static int mintaka_index_allocate(const char * string, int number, int event);
static int mintaka_index_allocate2(const char * string, int number, const char * string2, int event);
int mintaka_index_allocate3(const char * string, int number, const char * string2, const char * string3, int event);
void mintaka_index_generate(void);
typedef intptr_t channel_t;
static void mintaka_wait_send(channel_t channel, int size);
static void mintaka_send(channel_t channel, int size);
static void mintaka_wait_receive(channel_t channel, int size);
static void mintaka_receive(channel_t channel, int size);
static void mintaka_clock_synchronize(uint64_t ts);
static void mintaka_ensure_buffer(int event_count);
static void mintaka_send_and_state(channel_t channel, int size, int state);
static void mintaka_receive_and_state(channel_t channel, int size, int state);
static void mintaka_record1(int event);
static void mintaka_record2(int event, uint64_t value);
static void mintaka_record3(int event, channel_t value, uint32_t size);
static void mintaka_record1_at(int event, uint64_t ts);
static void mintaka_record2_at(int event, uint64_t value, uint64_t ts);
static void mintaka_record3_at(int event, channel_t lvalue, uint32_t hvalue, uint64_t time);
static uint64_t mintaka_get_ts(void);
void mintaka_flush_buffer(void);
extern void __assert_fail(__const char * __assertion, __const char * __file, unsigned int __line, __const char * __function) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern void __assert_perror_fail(int __errnum, __const char * __file, unsigned int __line, __const char * __function) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern void __assert(const char * __assertion, const char * __file, int __line) __attribute__((__nothrow__)) __attribute__((__noreturn__));
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef struct _IO_FILE __FILE;
typedef int wchar_t;
typedef unsigned int wint_t;
typedef struct 
{
        int __count;
        union 
        {
                wint_t __wch;
                char __wchb[4];
        } __value;
} __mbstate_t;
typedef struct 
{
        __off_t __pos;
        __mbstate_t __state;
} _G_fpos_t;
typedef struct 
{
        __off64_t __pos;
        __mbstate_t __state;
} _G_fpos64_t;
enum 
{
    __GCONV_OK = 0, 
    __GCONV_NOCONV, 
    __GCONV_NODB, 
    __GCONV_NOMEM, 
    __GCONV_EMPTY_INPUT, 
    __GCONV_FULL_OUTPUT, 
    __GCONV_ILLEGAL_INPUT, 
    __GCONV_INCOMPLETE_INPUT, 
    __GCONV_ILLEGAL_DESCRIPTOR, 
    __GCONV_INTERNAL_ERROR
};
enum 
{
    __GCONV_IS_LAST = 0x0001, 
    __GCONV_IGNORE_ERRORS = 0x0002
};
struct __gconv_step;
struct __gconv_step_data;
struct __gconv_loaded_object;
struct __gconv_trans_data;
typedef int (* __gconv_fct)(struct __gconv_step *, struct __gconv_step_data *, __const unsigned char **, __const unsigned char *, unsigned char **, size_t *, int, int);
typedef wint_t (* __gconv_btowc_fct)(struct __gconv_step *, unsigned char);
typedef int (* __gconv_init_fct)(struct __gconv_step *);
typedef void (* __gconv_end_fct)(struct __gconv_step *);
typedef int (* __gconv_trans_fct)(struct __gconv_step *, struct __gconv_step_data *, void *, __const unsigned char *, __const unsigned char **, __const unsigned char *, unsigned char **, size_t *);
typedef int (* __gconv_trans_context_fct)(void *, __const unsigned char *, __const unsigned char *, unsigned char *, unsigned char *);
typedef int (* __gconv_trans_query_fct)(__const char *, __const char ***, size_t *);
typedef int (* __gconv_trans_init_fct)(void **, const char *);
typedef void (* __gconv_trans_end_fct)(void *);
struct __gconv_trans_data
{
        __gconv_trans_fct __trans_fct;
        __gconv_trans_context_fct __trans_context_fct;
        __gconv_trans_end_fct __trans_end_fct;
        void * __data;
        struct __gconv_trans_data * __next;
};
struct __gconv_step
{
        struct __gconv_loaded_object * __shlib_handle;
        __const char * __modname;
        int __counter;
        char * __from_name;
        char * __to_name;
        __gconv_fct __fct;
        __gconv_btowc_fct __btowc_fct;
        __gconv_init_fct __init_fct;
        __gconv_end_fct __end_fct;
        int __min_needed_from;
        int __max_needed_from;
        int __min_needed_to;
        int __max_needed_to;
        int __stateful;
        void * __data;
};
struct __gconv_step_data
{
        unsigned char * __outbuf;
        unsigned char * __outbufend;
        int __flags;
        int __invocation_counter;
        int __internal_use;
        __mbstate_t * __statep;
        __mbstate_t __state;
        struct __gconv_trans_data * __trans;
};
typedef struct __gconv_info
{
        size_t __nsteps;
        struct __gconv_step * __steps;
        __extension__
        struct __gconv_step_data __data[];
} * __gconv_t;
typedef union 
{
        struct __gconv_info __cd;
        struct 
        {
                struct __gconv_info __cd;
                struct __gconv_step_data __data;
        } __combined;
} _G_iconv_t;
typedef int _G_int16_t __attribute__((__mode__(__HI__)));
typedef int _G_int32_t __attribute__((__mode__(__SI__)));
typedef unsigned int _G_uint16_t __attribute__((__mode__(__HI__)));
typedef unsigned int _G_uint32_t __attribute__((__mode__(__SI__)));
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t;
struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker
{
        struct _IO_marker * _next;
        struct _IO_FILE * _sbuf;
        int _pos;
};
enum __codecvt_result
{
    __codecvt_ok, 
    __codecvt_partial, 
    __codecvt_error, 
    __codecvt_noconv
};
struct _IO_FILE
{
        int _flags;
        char * _IO_read_ptr;
        char * _IO_read_end;
        char * _IO_read_base;
        char * _IO_write_base;
        char * _IO_write_ptr;
        char * _IO_write_end;
        char * _IO_buf_base;
        char * _IO_buf_end;
        char * _IO_save_base;
        char * _IO_backup_base;
        char * _IO_save_end;
        struct _IO_marker * _markers;
        struct _IO_FILE * _chain;
        int _fileno;
        int _flags2;
        __off_t _old_offset;
        unsigned short _cur_column;
        signed char _vtable_offset;
        char _shortbuf[1];
        _IO_lock_t * _lock;
        __off64_t _offset;
        void * __pad1;
        void * __pad2;
        void * __pad3;
        void * __pad4;
        size_t __pad5;
        int _mode;
        char _unused2[15 * sizeof(int) - 4 * sizeof(void *) - sizeof(size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn(void * __cookie, char * __buf, size_t __nbytes);
typedef __ssize_t __io_write_fn(void * __cookie, __const char * __buf, size_t __n);
typedef int __io_seek_fn(void * __cookie, __off64_t * __pos, int __w);
typedef int __io_close_fn(void * __cookie);
extern int __underflow(_IO_FILE *);
extern int __uflow(_IO_FILE *);
extern int __overflow(_IO_FILE *, int);
extern wint_t __wunderflow(_IO_FILE *);
extern wint_t __wuflow(_IO_FILE *);
extern wint_t __woverflow(_IO_FILE *, wint_t);
extern int _IO_getc(_IO_FILE * __fp);
extern int _IO_putc(int __c, _IO_FILE * __fp);
extern int _IO_feof(_IO_FILE * __fp) __attribute__((__nothrow__));
extern int _IO_ferror(_IO_FILE * __fp) __attribute__((__nothrow__));
extern int _IO_peekc_locked(_IO_FILE * __fp);
extern void _IO_flockfile(_IO_FILE *) __attribute__((__nothrow__));
extern void _IO_funlockfile(_IO_FILE *) __attribute__((__nothrow__));
extern int _IO_ftrylockfile(_IO_FILE *) __attribute__((__nothrow__));
extern int _IO_vfscanf(_IO_FILE *__restrict, const char *__restrict, __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf(_IO_FILE *__restrict, const char *__restrict, __gnuc_va_list);
extern __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn(_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area(_IO_FILE *) __attribute__((__nothrow__));
typedef _G_fpos_t fpos_t;
extern struct _IO_FILE * stdin;
extern struct _IO_FILE * stdout;
extern struct _IO_FILE * stderr;
extern int remove(__const char * __filename) __attribute__((__nothrow__));
extern int rename(__const char * __old, __const char * __new) __attribute__((__nothrow__));
extern FILE * tmpfile(void);
extern char * tmpnam(char * __s) __attribute__((__nothrow__));
extern char * tmpnam_r(char * __s) __attribute__((__nothrow__));
extern char * tempnam(__const char * __dir, __const char * __pfx) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern int fclose(FILE * __stream);
extern int fflush(FILE * __stream);
extern int fflush_unlocked(FILE * __stream);
extern FILE * fopen(__const char *__restrict __filename, __const char *__restrict __modes);
extern FILE * freopen(__const char *__restrict __filename, __const char *__restrict __modes, FILE *__restrict __stream);
extern FILE * fdopen(int __fd, __const char * __modes) __attribute__((__nothrow__));
extern void setbuf(FILE *__restrict __stream, char *__restrict __buf) __attribute__((__nothrow__));
extern int setvbuf(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __n) __attribute__((__nothrow__));
extern void setbuffer(FILE *__restrict __stream, char *__restrict __buf, size_t __size) __attribute__((__nothrow__));
extern void setlinebuf(FILE * __stream) __attribute__((__nothrow__));
extern int fprintf(FILE *__restrict __stream, __const char *__restrict __format, ...);
extern int printf(__const char *__restrict __format, ...);
extern int sprintf(char *__restrict __s, __const char *__restrict __format, ...) __attribute__((__nothrow__));
extern int vfprintf(FILE *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg);
extern int vprintf(__const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf(char *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__));
extern int snprintf(char *__restrict __s, size_t __maxlen, __const char *__restrict __format, ...) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 4)));
extern int vsnprintf(char *__restrict __s, size_t __maxlen, __const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 0)));
extern int fscanf(FILE *__restrict __stream, __const char *__restrict __format, ...);
extern int scanf(__const char *__restrict __format, ...);
extern int sscanf(__const char *__restrict __s, __const char *__restrict __format, ...) __attribute__((__nothrow__));
extern int fgetc(FILE * __stream);
extern int getc(FILE * __stream);
extern int getchar(void);
extern int getc_unlocked(FILE * __stream);
extern int getchar_unlocked(void);
extern int fgetc_unlocked(FILE * __stream);
extern int fputc(int __c, FILE * __stream);
extern int putc(int __c, FILE * __stream);
extern int putchar(int __c);
extern int fputc_unlocked(int __c, FILE * __stream);
extern int putc_unlocked(int __c, FILE * __stream);
extern int putchar_unlocked(int __c);
extern int getw(FILE * __stream);
extern int putw(int __w, FILE * __stream);
extern char * fgets(char *__restrict __s, int __n, FILE *__restrict __stream);
extern char * gets(char * __s);
extern int fputs(__const char *__restrict __s, FILE *__restrict __stream);
extern int puts(__const char * __s);
extern int ungetc(int __c, FILE * __stream);
extern size_t fread(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern size_t fwrite(__const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __s);
extern size_t fread_unlocked(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern size_t fwrite_unlocked(__const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern int fseek(FILE * __stream, long int __off, int __whence);
extern long int ftell(FILE * __stream);
extern void rewind(FILE * __stream);
extern int fseeko(FILE * __stream, __off_t __off, int __whence);
extern __off_t ftello(FILE * __stream);
extern int fgetpos(FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos(FILE * __stream, __const fpos_t * __pos);
extern void clearerr(FILE * __stream) __attribute__((__nothrow__));
extern int feof(FILE * __stream) __attribute__((__nothrow__));
extern int ferror(FILE * __stream) __attribute__((__nothrow__));
extern void clearerr_unlocked(FILE * __stream) __attribute__((__nothrow__));
extern int feof_unlocked(FILE * __stream) __attribute__((__nothrow__));
extern int ferror_unlocked(FILE * __stream) __attribute__((__nothrow__));
extern void perror(__const char * __s);
extern int sys_nerr;
extern __const char *__const sys_errlist[];
extern int fileno(FILE * __stream) __attribute__((__nothrow__));
extern int fileno_unlocked(FILE * __stream) __attribute__((__nothrow__));
extern FILE * popen(__const char * __command, __const char * __modes);
extern int pclose(FILE * __stream);
extern char * ctermid(char * __s) __attribute__((__nothrow__));
extern void flockfile(FILE * __stream) __attribute__((__nothrow__));
extern int ftrylockfile(FILE * __stream) __attribute__((__nothrow__));
extern void funlockfile(FILE * __stream) __attribute__((__nothrow__));
struct timeval
{
        __time_t tv_sec;
        __suseconds_t tv_usec;
};
typedef __suseconds_t suseconds_t;
typedef long int __fd_mask;
typedef struct 
{
        __fd_mask __fds_bits[1024 / (8 * sizeof(__fd_mask))];
} fd_set;
typedef __fd_mask fd_mask;
extern int select(int __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout);
extern int pselect(int __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, const struct timespec *__restrict __timeout, const __sigset_t *__restrict __sigmask);
struct timezone
{
        int tz_minuteswest;
        int tz_dsttime;
};
typedef struct timezone *__restrict __timezone_ptr_t;
extern int gettimeofday(struct timeval *__restrict __tv, __timezone_ptr_t __tz) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int settimeofday(__const struct timeval * __tv, __const struct timezone * __tz) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int adjtime(__const struct timeval * __delta, struct timeval * __olddelta) __attribute__((__nothrow__));
enum __itimer_which
{
    ITIMER_REAL = 0, 
    ITIMER_VIRTUAL = 1, 
    ITIMER_PROF = 2
};
struct itimerval
{
        struct timeval it_interval;
        struct timeval it_value;
};
typedef int __itimer_which_t;
extern int getitimer(__itimer_which_t __which, struct itimerval * __value) __attribute__((__nothrow__));
extern int setitimer(__itimer_which_t __which, __const struct itimerval *__restrict __new, struct itimerval *__restrict __old) __attribute__((__nothrow__));
extern int utimes(__const char * __file, __const struct timeval __tvp[2]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int lutimes(__const char * __file, __const struct timeval __tvp[2]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int futimes(int __fd, __const struct timeval __tvp[2]) __attribute__((__nothrow__));
enum mintaka_state
{
    MINTAKA_STATE_STOP = 14, 
    MINTAKA_STATE_RUN = 1, 
    MINTAKA_STATE_SCHEDULE = 7, 
    MINTAKA_STATE_IDLE = 0, 
    MINTAKA_STATE_BLOCK = 4, 
    MINTAKA_STATE_SYNCH = 5, 
    MINTAKA_STATE_WAIT_SEND = 9, 
    MINTAKA_STATE_SEND = 10, 
    MINTAKA_STATE_WAIT_RECEIVE = 3, 
    MINTAKA_STATE_RECEIVE = 11, 
    MINTAKA_STATE_COUNT = 16
};
struct mintaka_record
{
        uint32_t state;
        uint16_t processor;
        uint16_t thread;
        uint64_t time;
        channel_t channel;
        uint32_t size;
};
struct mintaka_thread_info
{
        int processor;
        int thread;
        int state;
        struct mintaka_record record[4096];
        int current;
        FILE * file;
        uint64_t ts_offset;
};
extern int mintaka__enable;
extern __thread mintaka_thread_info mintaka__thread_info;
static inline uint64_t mintaka_get_ts(void)
{
    struct timeval tp;
    struct timezone tzp;
    uint64_t ts_offset = mintaka_get_thread_info()->ts_offset;
    (&gettimeofday)(&tp, &tzp);
    return (tp.tv_sec * (uint64_t) 1000000 + tp.tv_usec) - ts_offset;
}
static inline void mintaka_record3_at(int state, channel_t channel, uint32_t size, uint64_t time)
{
    if (!mintaka__enable)
        return;
    int i = mintaka_get_thread_info()->current;
    int processor = mintaka_get_thread_info()->processor;
    int thread = mintaka_get_thread_info()->thread;
    struct mintaka_record * record = &mintaka_get_thread_info()->record[0];
    record[i].state = state;
    record[i].processor = processor;
    record[i].thread = thread;
    record[i].time = time;
    record[i].channel = channel;
    record[i].size = size;
    mintaka_get_thread_info()->current = i + 1;
    if (i == 4096 - 2)
    {
        mintaka_flush_buffer();
    }
}
static inline void mintaka_record3(int state, channel_t channel, uint32_t size)
{
    uint64_t ts = mintaka_get_ts();
    mintaka_record3_at(state, channel, size, ts);
}
static inline void mintaka_record1(int state)
{
    mintaka_record3(state, 0, 0);
}
static inline void mintaka_record1_at(int state, uint64_t ts)
{
    mintaka_record3_at(state, 0, 0, ts);
}
static inline void mintaka_record2(int event, uint64_t value)
{
    uint32_t low = (uint32_t) value;
    uint32_t high = (uint32_t) (value >> 32);
    mintaka_record3(event, low, high);
}
static inline void mintaka_record2_at(int event, uint64_t value, uint64_t ts)
{
    uint32_t low = (uint32_t) value;
    uint32_t high = (uint32_t) (value >> 32);
    mintaka_record3_at(event, low, high, ts);
}
static inline void mintaka_ensure_buffer(int event_count)
{
    ((event_count >= 0) ? (void) (0) : __assert_fail("event_count >= 0", "/home/drodenas/install/include/mintaka.h", 291, __PRETTY_FUNCTION__));
    ((event_count < 4096 - 2) ? (void) (0) : __assert_fail("event_count < 4096 - 2", "/home/drodenas/install/include/mintaka.h", 292, __PRETTY_FUNCTION__));
    if (mintaka_get_thread_info()->current > 4096 - 2 - event_count)
    {
        mintaka_flush_buffer();
    }
}
static inline void mintaka_set_enable(int enable)
{
    mintaka__enable = enable;
}
static inline int mintaka_get_enable(void)
{
    return mintaka__enable;
}
static inline void mintaka_set_state(int state)
{
    ((state < MINTAKA_STATE_COUNT) ? (void) (0) : __assert_fail("state < MINTAKA_STATE_COUNT", "/home/drodenas/install/include/mintaka.h", 324, __PRETTY_FUNCTION__));
    mintaka_get_thread_info()->state = state;
    mintaka_record1(state);
}
static inline void mintaka_set_state_at(int state, uint64_t ts)
{
    ((state < MINTAKA_STATE_COUNT) ? (void) (0) : __assert_fail("state < MINTAKA_STATE_COUNT", "/home/drodenas/install/include/mintaka.h", 337, __PRETTY_FUNCTION__));
    mintaka_get_thread_info()->state = state;
    mintaka_record1_at(state, ts);
}
static inline int mintaka_get_state(void)
{
    return mintaka_get_thread_info()->state;
}
static inline void mintaka_state_run(void)
{
    mintaka_set_state(MINTAKA_STATE_RUN);
}
static inline void mintaka_state_schedule(void)
{
    mintaka_set_state(MINTAKA_STATE_SCHEDULE);
}
static inline void mintaka_state_block(void)
{
    mintaka_set_state(MINTAKA_STATE_BLOCK);
}
static inline void mintaka_state_synch(void)
{
    mintaka_set_state(MINTAKA_STATE_SYNCH);
}
static inline void mintaka_state_idle(void)
{
    mintaka_set_state(MINTAKA_STATE_IDLE);
}
static inline void mintaka_event(int event, uint64_t value)
{
    ((event >= MINTAKA_STATE_COUNT || event < 0) ? (void) (0) : __assert_fail("event >= MINTAKA_STATE_COUNT || event < 0", "/home/drodenas/install/include/mintaka.h", 415, __PRETTY_FUNCTION__));
    mintaka_record2(event, value);
}
static inline void mintaka_event_at(int event, uint64_t value, uint64_t ts)
{
    ((event >= MINTAKA_STATE_COUNT || event < 0) ? (void) (0) : __assert_fail("event >= MINTAKA_STATE_COUNT || event < 0", "/home/drodenas/install/include/mintaka.h", 427, __PRETTY_FUNCTION__));
    mintaka_record2_at(event, value, ts);
}
static inline void mintaka_wait_send(channel_t channel, int size)
{
    int current = mintaka_get_thread_info()->current;
    struct mintaka_record * record = &mintaka_get_thread_info()->record[0];
    ((current > 0 || !mintaka__enable) ? (void) (0) : __assert_fail("current > 0 || !mintaka__enable", "/home/drodenas/install/include/mintaka.h", 447, __PRETTY_FUNCTION__));
    int i = (current - 1 + 4096) % 4096;
    if (record[i].state == MINTAKA_STATE_WAIT_SEND && record[i].channel == (uint32_t) channel && record[i].size == size)
    {
    }
    else
        mintaka_record3(MINTAKA_STATE_WAIT_SEND, channel, size);
}
static inline void mintaka_send(channel_t channel, int size)
{
    mintaka_record3(MINTAKA_STATE_SEND, channel, size);
}
static inline void mintaka_send_at(channel_t channel, int size, uint64_t ts)
{
    mintaka_record3_at(MINTAKA_STATE_SEND, channel, size, ts);
}
static inline void mintaka_wait_receive(channel_t channel, int size)
{
    int current = mintaka_get_thread_info()->current;
    struct mintaka_record * record = &mintaka_get_thread_info()->record[0];
    ((current > 0 || !mintaka__enable) ? (void) (0) : __assert_fail("current > 0 || !mintaka__enable", "/home/drodenas/install/include/mintaka.h", 487, __PRETTY_FUNCTION__));
    int i = (current - 1 + 4096) % 4096;
    if (record[i].state == MINTAKA_STATE_WAIT_RECEIVE && record[i].channel == (uint32_t) channel && record[i].size == size)
    {
    }
    else
        mintaka_record3(MINTAKA_STATE_WAIT_RECEIVE, channel, size);
}
static inline void mintaka_receive(channel_t channel, int size)
{
    mintaka_record3(MINTAKA_STATE_RECEIVE, channel, size);
}
static inline void mintaka_receive_at(channel_t channel, int size, uint64_t ts)
{
    mintaka_record3_at(MINTAKA_STATE_RECEIVE, channel, size, ts);
}
static inline void mintaka_state_and_event(int state, int event, uint64_t value)
{
    if (!mintaka__enable)
        return;
    ((event >= MINTAKA_STATE_COUNT || event < 0) ? (void) (0) : __assert_fail("event >= MINTAKA_STATE_COUNT || event < 0", "/home/drodenas/install/include/mintaka.h", 521, __PRETTY_FUNCTION__));
    mintaka_ensure_buffer(2);
    uint64_t ts = mintaka_get_ts();
    mintaka_set_state_at(state, ts);
    mintaka_event_at(event, value, ts);
}
static inline void mintaka_send_and_state(channel_t channel, int size, int state)
{
    if (!mintaka__enable)
        return;
    mintaka_ensure_buffer(2);
    uint64_t ts = mintaka_get_ts();
    mintaka_send_at(channel, size, ts);
    mintaka_set_state_at(state, ts);
}
static inline void mintaka_receive_and_state(channel_t channel, int size, int state)
{
    if (!mintaka__enable)
        return;
    mintaka_ensure_buffer(2);
    uint64_t ts = mintaka_get_ts();
    mintaka_receive_at(channel, size, ts);
    mintaka_set_state_at(state, ts);
}
static inline int mintaka_index_allocate(const char * string, int number, int event)
{
    return mintaka_index_allocate3(string, number, ((void *) 0), ((void *) 0), event);
}
static inline int mintaka_index_allocate2(const char * string, int number, const char * string2, int event)
{
    return mintaka_index_allocate3(string, number, string2, ((void *) 0), event);
}
static inline void mintaka_clock_synchronize(uint64_t ts)
{
    uint64_t current;
    current = mintaka_get_ts();
    ((current < ts) ? (void) (0) : __assert_fail("current < ts", "/home/drodenas/install/include/mintaka.h", 582, __PRETTY_FUNCTION__));
    mintaka_get_thread_info()->ts_offset = current - ts;
}
typedef struct task * task_t;
int task_init(task_t * task, void (* start)(task_t), int team_count);
void task_start(task_t task);
void task_wait(task_t task);
void task_close();
int task_allopen();
void task_copyin(task_t task, int state, void * src, int size);
void task_copyout(task_t task, int state, void * dst, int size);
void * copyin_acquire(int state);
void * copyout_acquire(int state);
void task_oport(task_t task, int port, int esize, int gcount, int bsize);
void task_iport(task_t task, int port, int esize, int gcount, int bsize, void * ivalues, int isize);
void port_connect(task_t ot, int oport, task_t it, int iport);
void oport_acquire(int port, int ecount);
int oport_tryacquire(int port, int ecount);
void * oport_peek(int port, int enumber);
void oport_push(int port, int ecount);
void iport_acquire(int port, int ecount);
int iport_tryacquire(int port, int ecount);
void * iport_peek(int port, int enumber);
void iport_pop(int port, int ecount);
void ioport_bypass(int iport, int oport, int ecount);
void task_shared(task_t task, int state, void * ivalue, int size);
void shared_async(task_t utask, int ustate, task_t atask, int astate);
void shared_sync(task_t utask, int ustate, task_t atask, int astate);
void * shared_acquire(int state);
void shared_update(int state);
void shared_check(int state);
int task_leader();
int task_team_me();
void iport_replicate(task_t task, int port);
void trace_app_begin(char * name);
void trace_app_end();
void trace_instance_begin();
void trace_instance_end();
void trace_iteration_begin();
void trace_iteration_end();
void trace_teamreplicate_begin();
void trace_teamreplicate_end();
extern void * memcpy(void *__restrict __dest, __const void *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void * memmove(void * __dest, __const void * __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void * memccpy(void *__restrict __dest, __const void *__restrict __src, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void * memset(void * __s, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int memcmp(__const void * __s1, __const void * __s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern void * memchr(__const void * __s, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char * strcpy(char *__restrict __dest, __const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char * strncpy(char *__restrict __dest, __const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char * strcat(char *__restrict __dest, __const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char * strncat(char *__restrict __dest, __const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int strcmp(__const char * __s1, __const char * __s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strncmp(__const char * __s1, __const char * __s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strcoll(__const char * __s1, __const char * __s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern size_t strxfrm(char *__restrict __dest, __const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern char * strdup(__const char * __s) __attribute__((__nothrow__)) __attribute__((__malloc__)) __attribute__((__nonnull__(1)));
extern char * strchr(__const char * __s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char * strrchr(__const char * __s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern size_t strcspn(__const char * __s, __const char * __reject) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern size_t strspn(__const char * __s, __const char * __accept) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char * strpbrk(__const char * __s, __const char * __accept) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char * strstr(__const char * __haystack, __const char * __needle) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char * strtok(char *__restrict __s, __const char *__restrict __delim) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern char * __strtok_r(char *__restrict __s, __const char *__restrict __delim, char * *__restrict __save_ptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern char * strtok_r(char *__restrict __s, __const char *__restrict __delim, char * *__restrict __save_ptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern size_t strlen(__const char * __s) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char * strerror(int __errnum) __attribute__((__nothrow__));
extern int strerror_r(int __errnum, char * __buf, size_t __buflen) asm ("""__xpg_strerror_r") __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern void __bzero(void * __s, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void bcopy(__const void * __src, void * __dest, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void bzero(void * __s, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int bcmp(__const void * __s1, __const void * __s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char * index(__const char * __s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char * rindex(__const char * __s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern int ffs(int __i) __attribute__((__nothrow__)) __attribute__((__const__));
extern int strcasecmp(__const char * __s1, __const char * __s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strncasecmp(__const char * __s1, __const char * __s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char * strsep(char * *__restrict __stringp, __const char *__restrict __delim) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
typedef struct 
{
        int quot;
        int rem;
} div_t;
typedef struct 
{
        long int quot;
        long int rem;
} ldiv_t;
extern size_t __ctype_get_mb_cur_max(void) __attribute__((__nothrow__));
extern double atof(__const char * __nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern int atoi(__const char * __nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern long int atol(__const char * __nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int atoll(__const char * __nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern double strtod(__const char *__restrict __nptr, char * *__restrict __endptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int strtol(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern unsigned long int strtoul(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int strtoq(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern unsigned long long int strtouq(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int strtoll(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern unsigned long long int strtoull(__const char *__restrict __nptr, char * *__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern double __strtod_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern float __strtof_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long double __strtold_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int __strtol_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __base, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern unsigned long int __strtoul_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __base, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int __strtoll_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __base, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern unsigned long long int __strtoull_internal(__const char *__restrict __nptr, char * *__restrict __endptr, int __base, int __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern char * l64a(long int __n) __attribute__((__nothrow__));
extern long int a64l(__const char * __s) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int u_int16_t __attribute__((__mode__(__HI__)));
typedef unsigned int u_int32_t __attribute__((__mode__(__SI__)));
typedef unsigned int u_int64_t __attribute__((__mode__(__DI__)));
typedef int register_t __attribute__((__mode__(__word__)));
__extension__
extern __inline unsigned int gnu_dev_major(unsigned long long int __dev) __attribute__((__nothrow__));
__extension__
extern __inline unsigned int gnu_dev_minor(unsigned long long int __dev) __attribute__((__nothrow__));
__extension__
extern __inline unsigned long long int gnu_dev_makedev(unsigned int __major, unsigned int __minor) __attribute__((__nothrow__));
__extension__
extern __inline unsigned int __attribute__((__nothrow__)) gnu_dev_major(unsigned long long int __dev)
{
    return ((__dev >> 8) & 0xfff) | ((unsigned int) (__dev >> 32) & ~0xfff);
}
__extension__
extern __inline unsigned int __attribute__((__nothrow__)) gnu_dev_minor(unsigned long long int __dev)
{
    return (__dev & 0xff) | ((unsigned int) (__dev >> 12) & ~0xff);
}
__extension__
extern __inline unsigned long long int __attribute__((__nothrow__)) gnu_dev_makedev(unsigned int __major, unsigned int __minor)
{
    return ((__minor & 0xff) | ((__major & 0xfff) << 8) | (((unsigned long long int) (__minor & ~0xff)) << 12) | (((unsigned long long int) (__major & ~0xfff)) << 32));
}
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
extern long int random(void) __attribute__((__nothrow__));
extern void srandom(unsigned int __seed) __attribute__((__nothrow__));
extern char * initstate(unsigned int __seed, char * __statebuf, size_t __statelen) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern char * setstate(char * __statebuf) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
struct random_data
{
        int32_t * fptr;
        int32_t * rptr;
        int32_t * state;
        int rand_type;
        int rand_deg;
        int rand_sep;
        int32_t * end_ptr;
};
extern int random_r(struct random_data *__restrict __buf, int32_t *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int srandom_r(unsigned int __seed, struct random_data * __buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int initstate_r(unsigned int __seed, char *__restrict __statebuf, size_t __statelen, struct random_data *__restrict __buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 4)));
extern int setstate_r(char *__restrict __statebuf, struct random_data *__restrict __buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int rand(void) __attribute__((__nothrow__));
extern void srand(unsigned int __seed) __attribute__((__nothrow__));
extern int rand_r(unsigned int * __seed) __attribute__((__nothrow__));
extern double drand48(void) __attribute__((__nothrow__));
extern double erand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int lrand48(void) __attribute__((__nothrow__));
extern long int nrand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int mrand48(void) __attribute__((__nothrow__));
extern long int jrand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void srand48(long int __seedval) __attribute__((__nothrow__));
extern unsigned short int * seed48(unsigned short int __seed16v[3]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void lcong48(unsigned short int __param[7]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
struct drand48_data
{
        unsigned short int __x[3];
        unsigned short int __old_x[3];
        unsigned short int __c;
        unsigned short int __init;
        unsigned long long int __a;
};
extern int drand48_r(struct drand48_data *__restrict __buffer, double *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int erand48_r(unsigned short int __xsubi[3], struct drand48_data *__restrict __buffer, double *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int lrand48_r(struct drand48_data *__restrict __buffer, long int *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int nrand48_r(unsigned short int __xsubi[3], struct drand48_data *__restrict __buffer, long int *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int mrand48_r(struct drand48_data *__restrict __buffer, long int *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int jrand48_r(unsigned short int __xsubi[3], struct drand48_data *__restrict __buffer, long int *__restrict __result) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int srand48_r(long int __seedval, struct drand48_data * __buffer) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int seed48_r(unsigned short int __seed16v[3], struct drand48_data * __buffer) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int lcong48_r(unsigned short int __param[7], struct drand48_data * __buffer) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void * malloc(size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern void * calloc(size_t __nmemb, size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern void * realloc(void * __ptr, size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__)) __attribute__((__warn_unused_result__));
extern void free(void * __ptr) __attribute__((__nothrow__));
extern void cfree(void * __ptr) __attribute__((__nothrow__));
extern void * alloca(size_t __size) __attribute__((__nothrow__));
extern void * valloc(size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern int posix_memalign(void * * __memptr, size_t __alignment, size_t __size) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void abort(void) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern int atexit(void (* __func)(void)) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int on_exit(void (* __func)(int __status, void * __arg), void * __arg) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void exit(int __status) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern char * getenv(__const char * __name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern char * __secure_getenv(__const char * __name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int putenv(char * __string) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int setenv(__const char * __name, __const char * __value, int __replace) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int unsetenv(__const char * __name) __attribute__((__nothrow__));
extern int clearenv(void) __attribute__((__nothrow__));
extern char * mktemp(char * __template) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int mkstemp(char * __template) __attribute__((__nonnull__(1)));
extern char * mkdtemp(char * __template) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int system(__const char * __command);
extern char * realpath(__const char *__restrict __name, char *__restrict __resolved) __attribute__((__nothrow__));
typedef int (* __compar_fn_t)(__const void *, __const void *);
extern void * bsearch(__const void * __key, __const void * __base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__((__nonnull__(1, 2, 5)));
extern void qsort(void * __base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__((__nonnull__(1, 4)));
extern int abs(int __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long int labs(long int __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern div_t div(int __numer, int __denom) __attribute__((__nothrow__)) __attribute__((__const__));
extern ldiv_t ldiv(long int __numer, long int __denom) __attribute__((__nothrow__)) __attribute__((__const__));
extern char * ecvt(double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4)));
extern char * fcvt(double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4)));
extern char * gcvt(double __value, int __ndigit, char * __buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(3)));
extern char * qecvt(long double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4)));
extern char * qfcvt(long double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4)));
extern char * qgcvt(long double __value, int __ndigit, char * __buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(3)));
extern int ecvt_r(double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4, 5)));
extern int fcvt_r(double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4, 5)));
extern int qecvt_r(long double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4, 5)));
extern int qfcvt_r(long double __value, int __ndigit, int *__restrict __decpt, int *__restrict __sign, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(3, 4, 5)));
extern int mblen(__const char * __s, size_t __n) __attribute__((__nothrow__));
extern int mbtowc(wchar_t *__restrict __pwc, __const char *__restrict __s, size_t __n) __attribute__((__nothrow__));
extern int wctomb(char * __s, wchar_t __wchar) __attribute__((__nothrow__));
extern size_t mbstowcs(wchar_t *__restrict __pwcs, __const char *__restrict __s, size_t __n) __attribute__((__nothrow__));
extern size_t wcstombs(char *__restrict __s, __const wchar_t *__restrict __pwcs, size_t __n) __attribute__((__nothrow__));
extern int rpmatch(__const char * __response) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int posix_openpt(int __oflag);
extern int getloadavg(double __loadavg[], int __nelem) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern double acos(double __x) __attribute__((__nothrow__));
extern double __acos(double __x) __attribute__((__nothrow__));
extern double asin(double __x) __attribute__((__nothrow__));
extern double __asin(double __x) __attribute__((__nothrow__));
extern double atan(double __x) __attribute__((__nothrow__));
extern double __atan(double __x) __attribute__((__nothrow__));
extern double atan2(double __y, double __x) __attribute__((__nothrow__));
extern double __atan2(double __y, double __x) __attribute__((__nothrow__));
extern double cos(double __x) __attribute__((__nothrow__));
extern double __cos(double __x) __attribute__((__nothrow__));
extern double sin(double __x) __attribute__((__nothrow__));
extern double __sin(double __x) __attribute__((__nothrow__));
extern double tan(double __x) __attribute__((__nothrow__));
extern double __tan(double __x) __attribute__((__nothrow__));
extern double cosh(double __x) __attribute__((__nothrow__));
extern double __cosh(double __x) __attribute__((__nothrow__));
extern double sinh(double __x) __attribute__((__nothrow__));
extern double __sinh(double __x) __attribute__((__nothrow__));
extern double tanh(double __x) __attribute__((__nothrow__));
extern double __tanh(double __x) __attribute__((__nothrow__));
extern double acosh(double __x) __attribute__((__nothrow__));
extern double __acosh(double __x) __attribute__((__nothrow__));
extern double asinh(double __x) __attribute__((__nothrow__));
extern double __asinh(double __x) __attribute__((__nothrow__));
extern double atanh(double __x) __attribute__((__nothrow__));
extern double __atanh(double __x) __attribute__((__nothrow__));
extern double exp(double __x) __attribute__((__nothrow__));
extern double __exp(double __x) __attribute__((__nothrow__));
extern double frexp(double __x, int * __exponent) __attribute__((__nothrow__));
extern double __frexp(double __x, int * __exponent) __attribute__((__nothrow__));
extern double ldexp(double __x, int __exponent) __attribute__((__nothrow__));
extern double __ldexp(double __x, int __exponent) __attribute__((__nothrow__));
extern double log(double __x) __attribute__((__nothrow__));
extern double __log(double __x) __attribute__((__nothrow__));
extern double log10(double __x) __attribute__((__nothrow__));
extern double __log10(double __x) __attribute__((__nothrow__));
extern double modf(double __x, double * __iptr) __attribute__((__nothrow__));
extern double __modf(double __x, double * __iptr) __attribute__((__nothrow__));
extern double expm1(double __x) __attribute__((__nothrow__));
extern double __expm1(double __x) __attribute__((__nothrow__));
extern double log1p(double __x) __attribute__((__nothrow__));
extern double __log1p(double __x) __attribute__((__nothrow__));
extern double logb(double __x) __attribute__((__nothrow__));
extern double __logb(double __x) __attribute__((__nothrow__));
extern double pow(double __x, double __y) __attribute__((__nothrow__));
extern double __pow(double __x, double __y) __attribute__((__nothrow__));
extern double sqrt(double __x) __attribute__((__nothrow__));
extern double __sqrt(double __x) __attribute__((__nothrow__));
extern double hypot(double __x, double __y) __attribute__((__nothrow__));
extern double __hypot(double __x, double __y) __attribute__((__nothrow__));
extern double cbrt(double __x) __attribute__((__nothrow__));
extern double __cbrt(double __x) __attribute__((__nothrow__));
extern double ceil(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __ceil(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fabs(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __fabs(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double floor(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __floor(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fmod(double __x, double __y) __attribute__((__nothrow__));
extern double __fmod(double __x, double __y) __attribute__((__nothrow__));
extern int __isinf(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finite(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isinf(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finite(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double drem(double __x, double __y) __attribute__((__nothrow__));
extern double __drem(double __x, double __y) __attribute__((__nothrow__));
extern double significand(double __x) __attribute__((__nothrow__));
extern double __significand(double __x) __attribute__((__nothrow__));
extern double copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnan(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnan(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double j0(double) __attribute__((__nothrow__));
extern double __j0(double) __attribute__((__nothrow__));
extern double j1(double) __attribute__((__nothrow__));
extern double __j1(double) __attribute__((__nothrow__));
extern double jn(int, double) __attribute__((__nothrow__));
extern double __jn(int, double) __attribute__((__nothrow__));
extern double y0(double) __attribute__((__nothrow__));
extern double __y0(double) __attribute__((__nothrow__));
extern double y1(double) __attribute__((__nothrow__));
extern double __y1(double) __attribute__((__nothrow__));
extern double yn(int, double) __attribute__((__nothrow__));
extern double __yn(int, double) __attribute__((__nothrow__));
extern double erf(double) __attribute__((__nothrow__));
extern double __erf(double) __attribute__((__nothrow__));
extern double erfc(double) __attribute__((__nothrow__));
extern double __erfc(double) __attribute__((__nothrow__));
extern double lgamma(double) __attribute__((__nothrow__));
extern double __lgamma(double) __attribute__((__nothrow__));
extern double gamma(double) __attribute__((__nothrow__));
extern double __gamma(double) __attribute__((__nothrow__));
extern double lgamma_r(double, int * __signgamp) __attribute__((__nothrow__));
extern double __lgamma_r(double, int * __signgamp) __attribute__((__nothrow__));
extern double rint(double __x) __attribute__((__nothrow__));
extern double __rint(double __x) __attribute__((__nothrow__));
extern double nextafter(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __nextafter(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double remainder(double __x, double __y) __attribute__((__nothrow__));
extern double __remainder(double __x, double __y) __attribute__((__nothrow__));
extern double scalbn(double __x, int __n) __attribute__((__nothrow__));
extern double __scalbn(double __x, int __n) __attribute__((__nothrow__));
extern int ilogb(double __x) __attribute__((__nothrow__));
extern int __ilogb(double __x) __attribute__((__nothrow__));
extern double scalb(double __x, double __n) __attribute__((__nothrow__));
extern double __scalb(double __x, double __n) __attribute__((__nothrow__));
extern float acosf(float __x) __attribute__((__nothrow__));
extern float __acosf(float __x) __attribute__((__nothrow__));
extern float asinf(float __x) __attribute__((__nothrow__));
extern float __asinf(float __x) __attribute__((__nothrow__));
extern float atanf(float __x) __attribute__((__nothrow__));
extern float __atanf(float __x) __attribute__((__nothrow__));
extern float atan2f(float __y, float __x) __attribute__((__nothrow__));
extern float __atan2f(float __y, float __x) __attribute__((__nothrow__));
extern float cosf(float __x) __attribute__((__nothrow__));
extern float __cosf(float __x) __attribute__((__nothrow__));
extern float sinf(float __x) __attribute__((__nothrow__));
extern float __sinf(float __x) __attribute__((__nothrow__));
extern float tanf(float __x) __attribute__((__nothrow__));
extern float __tanf(float __x) __attribute__((__nothrow__));
extern float coshf(float __x) __attribute__((__nothrow__));
extern float __coshf(float __x) __attribute__((__nothrow__));
extern float sinhf(float __x) __attribute__((__nothrow__));
extern float __sinhf(float __x) __attribute__((__nothrow__));
extern float tanhf(float __x) __attribute__((__nothrow__));
extern float __tanhf(float __x) __attribute__((__nothrow__));
extern float acoshf(float __x) __attribute__((__nothrow__));
extern float __acoshf(float __x) __attribute__((__nothrow__));
extern float asinhf(float __x) __attribute__((__nothrow__));
extern float __asinhf(float __x) __attribute__((__nothrow__));
extern float atanhf(float __x) __attribute__((__nothrow__));
extern float __atanhf(float __x) __attribute__((__nothrow__));
extern float expf(float __x) __attribute__((__nothrow__));
extern float __expf(float __x) __attribute__((__nothrow__));
extern float frexpf(float __x, int * __exponent) __attribute__((__nothrow__));
extern float __frexpf(float __x, int * __exponent) __attribute__((__nothrow__));
extern float ldexpf(float __x, int __exponent) __attribute__((__nothrow__));
extern float __ldexpf(float __x, int __exponent) __attribute__((__nothrow__));
extern float logf(float __x) __attribute__((__nothrow__));
extern float __logf(float __x) __attribute__((__nothrow__));
extern float log10f(float __x) __attribute__((__nothrow__));
extern float __log10f(float __x) __attribute__((__nothrow__));
extern float modff(float __x, float * __iptr) __attribute__((__nothrow__));
extern float __modff(float __x, float * __iptr) __attribute__((__nothrow__));
extern float expm1f(float __x) __attribute__((__nothrow__));
extern float __expm1f(float __x) __attribute__((__nothrow__));
extern float log1pf(float __x) __attribute__((__nothrow__));
extern float __log1pf(float __x) __attribute__((__nothrow__));
extern float logbf(float __x) __attribute__((__nothrow__));
extern float __logbf(float __x) __attribute__((__nothrow__));
extern float powf(float __x, float __y) __attribute__((__nothrow__));
extern float __powf(float __x, float __y) __attribute__((__nothrow__));
extern float sqrtf(float __x) __attribute__((__nothrow__));
extern float __sqrtf(float __x) __attribute__((__nothrow__));
extern float hypotf(float __x, float __y) __attribute__((__nothrow__));
extern float __hypotf(float __x, float __y) __attribute__((__nothrow__));
extern float cbrtf(float __x) __attribute__((__nothrow__));
extern float __cbrtf(float __x) __attribute__((__nothrow__));
extern float ceilf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __ceilf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fabsf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __fabsf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float floorf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __floorf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fmodf(float __x, float __y) __attribute__((__nothrow__));
extern float __fmodf(float __x, float __y) __attribute__((__nothrow__));
extern int __isinff(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finitef(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isinff(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finitef(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float dremf(float __x, float __y) __attribute__((__nothrow__));
extern float __dremf(float __x, float __y) __attribute__((__nothrow__));
extern float significandf(float __x) __attribute__((__nothrow__));
extern float __significandf(float __x) __attribute__((__nothrow__));
extern float copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnanf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float j0f(float) __attribute__((__nothrow__));
extern float __j0f(float) __attribute__((__nothrow__));
extern float j1f(float) __attribute__((__nothrow__));
extern float __j1f(float) __attribute__((__nothrow__));
extern float jnf(int, float) __attribute__((__nothrow__));
extern float __jnf(int, float) __attribute__((__nothrow__));
extern float y0f(float) __attribute__((__nothrow__));
extern float __y0f(float) __attribute__((__nothrow__));
extern float y1f(float) __attribute__((__nothrow__));
extern float __y1f(float) __attribute__((__nothrow__));
extern float ynf(int, float) __attribute__((__nothrow__));
extern float __ynf(int, float) __attribute__((__nothrow__));
extern float erff(float) __attribute__((__nothrow__));
extern float __erff(float) __attribute__((__nothrow__));
extern float erfcf(float) __attribute__((__nothrow__));
extern float __erfcf(float) __attribute__((__nothrow__));
extern float lgammaf(float) __attribute__((__nothrow__));
extern float __lgammaf(float) __attribute__((__nothrow__));
extern float gammaf(float) __attribute__((__nothrow__));
extern float __gammaf(float) __attribute__((__nothrow__));
extern float lgammaf_r(float, int * __signgamp) __attribute__((__nothrow__));
extern float __lgammaf_r(float, int * __signgamp) __attribute__((__nothrow__));
extern float rintf(float __x) __attribute__((__nothrow__));
extern float __rintf(float __x) __attribute__((__nothrow__));
extern float nextafterf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __nextafterf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float remainderf(float __x, float __y) __attribute__((__nothrow__));
extern float __remainderf(float __x, float __y) __attribute__((__nothrow__));
extern float scalbnf(float __x, int __n) __attribute__((__nothrow__));
extern float __scalbnf(float __x, int __n) __attribute__((__nothrow__));
extern int ilogbf(float __x) __attribute__((__nothrow__));
extern int __ilogbf(float __x) __attribute__((__nothrow__));
extern float scalbf(float __x, float __n) __attribute__((__nothrow__));
extern float __scalbf(float __x, float __n) __attribute__((__nothrow__));
extern long double acosl(long double __x) __attribute__((__nothrow__));
extern long double __acosl(long double __x) __attribute__((__nothrow__));
extern long double asinl(long double __x) __attribute__((__nothrow__));
extern long double __asinl(long double __x) __attribute__((__nothrow__));
extern long double atanl(long double __x) __attribute__((__nothrow__));
extern long double __atanl(long double __x) __attribute__((__nothrow__));
extern long double atan2l(long double __y, long double __x) __attribute__((__nothrow__));
extern long double __atan2l(long double __y, long double __x) __attribute__((__nothrow__));
extern long double cosl(long double __x) __attribute__((__nothrow__));
extern long double __cosl(long double __x) __attribute__((__nothrow__));
extern long double sinl(long double __x) __attribute__((__nothrow__));
extern long double __sinl(long double __x) __attribute__((__nothrow__));
extern long double tanl(long double __x) __attribute__((__nothrow__));
extern long double __tanl(long double __x) __attribute__((__nothrow__));
extern long double coshl(long double __x) __attribute__((__nothrow__));
extern long double __coshl(long double __x) __attribute__((__nothrow__));
extern long double sinhl(long double __x) __attribute__((__nothrow__));
extern long double __sinhl(long double __x) __attribute__((__nothrow__));
extern long double tanhl(long double __x) __attribute__((__nothrow__));
extern long double __tanhl(long double __x) __attribute__((__nothrow__));
extern long double acoshl(long double __x) __attribute__((__nothrow__));
extern long double __acoshl(long double __x) __attribute__((__nothrow__));
extern long double asinhl(long double __x) __attribute__((__nothrow__));
extern long double __asinhl(long double __x) __attribute__((__nothrow__));
extern long double atanhl(long double __x) __attribute__((__nothrow__));
extern long double __atanhl(long double __x) __attribute__((__nothrow__));
extern long double expl(long double __x) __attribute__((__nothrow__));
extern long double __expl(long double __x) __attribute__((__nothrow__));
extern long double frexpl(long double __x, int * __exponent) __attribute__((__nothrow__));
extern long double __frexpl(long double __x, int * __exponent) __attribute__((__nothrow__));
extern long double ldexpl(long double __x, int __exponent) __attribute__((__nothrow__));
extern long double __ldexpl(long double __x, int __exponent) __attribute__((__nothrow__));
extern long double logl(long double __x) __attribute__((__nothrow__));
extern long double __logl(long double __x) __attribute__((__nothrow__));
extern long double log10l(long double __x) __attribute__((__nothrow__));
extern long double __log10l(long double __x) __attribute__((__nothrow__));
extern long double modfl(long double __x, long double * __iptr) __attribute__((__nothrow__));
extern long double __modfl(long double __x, long double * __iptr) __attribute__((__nothrow__));
extern long double expm1l(long double __x) __attribute__((__nothrow__));
extern long double __expm1l(long double __x) __attribute__((__nothrow__));
extern long double log1pl(long double __x) __attribute__((__nothrow__));
extern long double __log1pl(long double __x) __attribute__((__nothrow__));
extern long double logbl(long double __x) __attribute__((__nothrow__));
extern long double __logbl(long double __x) __attribute__((__nothrow__));
extern long double powl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __powl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double sqrtl(long double __x) __attribute__((__nothrow__));
extern long double __sqrtl(long double __x) __attribute__((__nothrow__));
extern long double hypotl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __hypotl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double cbrtl(long double __x) __attribute__((__nothrow__));
extern long double __cbrtl(long double __x) __attribute__((__nothrow__));
extern long double ceill(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __ceill(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fabsl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __fabsl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double floorl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __floorl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fmodl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __fmodl(long double __x, long double __y) __attribute__((__nothrow__));
extern int __isinfl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finitel(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isinfl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finitel(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double dreml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __dreml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double significandl(long double __x) __attribute__((__nothrow__));
extern long double __significandl(long double __x) __attribute__((__nothrow__));
extern long double copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnanl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double j0l(long double) __attribute__((__nothrow__));
extern long double __j0l(long double) __attribute__((__nothrow__));
extern long double j1l(long double) __attribute__((__nothrow__));
extern long double __j1l(long double) __attribute__((__nothrow__));
extern long double jnl(int, long double) __attribute__((__nothrow__));
extern long double __jnl(int, long double) __attribute__((__nothrow__));
extern long double y0l(long double) __attribute__((__nothrow__));
extern long double __y0l(long double) __attribute__((__nothrow__));
extern long double y1l(long double) __attribute__((__nothrow__));
extern long double __y1l(long double) __attribute__((__nothrow__));
extern long double ynl(int, long double) __attribute__((__nothrow__));
extern long double __ynl(int, long double) __attribute__((__nothrow__));
extern long double erfl(long double) __attribute__((__nothrow__));
extern long double __erfl(long double) __attribute__((__nothrow__));
extern long double erfcl(long double) __attribute__((__nothrow__));
extern long double __erfcl(long double) __attribute__((__nothrow__));
extern long double lgammal(long double) __attribute__((__nothrow__));
extern long double __lgammal(long double) __attribute__((__nothrow__));
extern long double gammal(long double) __attribute__((__nothrow__));
extern long double __gammal(long double) __attribute__((__nothrow__));
extern long double lgammal_r(long double, int * __signgamp) __attribute__((__nothrow__));
extern long double __lgammal_r(long double, int * __signgamp) __attribute__((__nothrow__));
extern long double rintl(long double __x) __attribute__((__nothrow__));
extern long double __rintl(long double __x) __attribute__((__nothrow__));
extern long double nextafterl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __nextafterl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double remainderl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __remainderl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double scalbnl(long double __x, int __n) __attribute__((__nothrow__));
extern long double __scalbnl(long double __x, int __n) __attribute__((__nothrow__));
extern int ilogbl(long double __x) __attribute__((__nothrow__));
extern int __ilogbl(long double __x) __attribute__((__nothrow__));
extern long double scalbl(long double __x, long double __n) __attribute__((__nothrow__));
extern long double __scalbl(long double __x, long double __n) __attribute__((__nothrow__));
extern int signgam;
typedef enum 
{
    _IEEE_ = -1, 
    _SVID_, 
    _XOPEN_, 
    _POSIX_, 
    _ISOC_
} _LIB_VERSION_TYPE;
extern _LIB_VERSION_TYPE _LIB_VERSION;
struct exception
{
        int type;
        char * name;
        double arg1;
        double arg2;
        double retval;
};
extern int matherr(struct exception * __exc);
void freq_sync_correl_2STS(int init, int input_I, int input_Q, int * output_I, int * output_Q, int * correlation_1ST_i, int * correlation_1ST_q);
void frequency_sync_slidsum(int mk_init, int rx_start, int correlation_1ST_real, int correlation_1ST_imag, int * burst_found_out, int * burst_found_pulse_out, int * burst_found_pulse_out_for_FT, int * freq_est_phase_out_real, int * freq_est_phase_out_imag, int * freq_est_norm_out, int * freq_est_norm_max_out);
void arctan(int init, int data_in_real, int data_in_imag, int burst_found_pulse, int * angle_out);
void cordic_turn(int init, int xin, int yin, int angle, int * res_output_x, int * res_output_y);
void fine_time_sync_init(int * maximum_found_out);
void fine_time_sync(int init, int burst_start_found, int data_in_real, int data_in_imag, int * data_out_real, int * data_out_imag, int * maximum_found_out);
void bf2_fifo_stage5(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2_fifo_stage4(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2_fifo_stage3(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2_fifo_stage2(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2_fifo_stage1(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2_fifo_stage0(float * data_i_in, float * data_q_in, float * data_i_out, float * data_q_out);
void bf2ii(int s, int t, float * data_n_i_in, float * data_n_q_in, float * data_n_ndiv2_i_in, float * data_n_ndiv2_q_in, float * data_n_ndiv2_i_out, float * data_n_ndiv2_q_out, float * data_n_i_out, float * data_n_q_out);
void bf2i(int s, float * data_n_i_in, float * data_n_q_in, float * data_n_ndiv2_i_in, float * data_n_ndiv2_q_in, float * data_n_ndiv2_i_out, float * data_n_ndiv2_q_out, float * data_n_i_out, float * data_n_q_out);
void twiddle_mult43(int init, int twiddle_ptr, float * data_re_in, float * data_im_in, float * mult_re_out, float * mult_im_out);
void twiddle_mult21(int init, int twiddle_ptr, float * data_re_in, float * data_im_in, float * mult_re_out, float * mult_im_out);
void fft64(int init, float real_in, float imag_in, float * data_i_out, float * data_q_out);
void mstream_demux(int init, float InData_re, float InData_im, int * start, float OutData_re[64], float OutData_im[64]);
void mark_GI_data(int init, int * GI_Flag);
void scale_reorder_removeGB(float input_I[64], float input_Q[64], float FFT_output_scale, int CHE_input_I[104], int CHE_input_Q[104], int payload_output_I[52], int payload_output_Q[52], int CHE_flag);
void channel_estimation(int input_I[104], int input_Q[104], int output_I[52], int output_Q[52]);
void channel_correction(int input_I[52], int input_Q[52], int output_CHE_I[52], int output_CHE_Q[52], int output_CHC_I[52], int output_CHC_Q[52]);
void task1_outline(task_t __task)
{
    trace_instance_begin();
    float freq_sync_correl_2STS_input_I;
    float freq_sync_correl_2STS_input_Q;
    int freq_sync_correl_2STS_output_I;
    int freq_sync_correl_2STS_output_Q;
    int correlation_1ST_i;
    int correlation_1ST_q;
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    oport_acquire(2, 1);
    oport_acquire(3, 1);
    oport_acquire(4, 1);
    oport_acquire(5, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_input_I)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(float));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_input_Q)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(float));
            }
        }
        trace_iteration_begin();
        freq_sync_correl_2STS(1, (int) (freq_sync_correl_2STS_input_I), (int) (freq_sync_correl_2STS_input_Q), &freq_sync_correl_2STS_output_I, &freq_sync_correl_2STS_output_Q, &correlation_1ST_i, &correlation_1ST_q);
        trace_iteration_end();
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(2, acotescc__for_peek_index), &((&freq_sync_correl_2STS_output_I)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(3, acotescc__for_peek_index), &((&freq_sync_correl_2STS_output_Q)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(4, acotescc__for_peek_index), &((&correlation_1ST_i)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(5, acotescc__for_peek_index), &((&correlation_1ST_q)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        iport_pop(0, 1);
        iport_pop(1, 1);
        oport_push(2, 1);
        oport_push(3, 1);
        oport_push(4, 1);
        oport_push(5, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        oport_acquire(2, 1);
        oport_acquire(3, 1);
        oport_acquire(4, 1);
        oport_acquire(5, 1);
    }
    task_close();
    trace_instance_end();
}
void task2_outline(task_t __task)
{
    trace_instance_begin();
    int burst_found_out;
    int freq_est_norm_out;
    int freq_est_norm_max_out;
    int init_modules;
    int rx_start;
    int correlation_1ST_i;
    int correlation_1ST_q;
    int burst_found_pulse_out;
    int burst_found_pulse_for_FT;
    int freq_est_phase_out_real;
    int freq_est_phase_out_imag;
    memcpy(&burst_found_out, copyin_acquire(0), sizeof(int) * 1);
    memcpy(&freq_est_norm_out, copyin_acquire(1), sizeof(int) * 1);
    memcpy(&freq_est_norm_max_out, copyin_acquire(2), sizeof(int) * 1);
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    iport_acquire(3, 1);
    oport_acquire(4, 1);
    oport_acquire(5, 1);
    oport_acquire(6, 1);
    oport_acquire(7, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&init_modules)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&rx_start)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&correlation_1ST_i)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&correlation_1ST_q)[acotescc__for_peek_index]), iport_peek(3, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        frequency_sync_slidsum(init_modules, rx_start, correlation_1ST_i, correlation_1ST_q, &burst_found_out, &burst_found_pulse_out, &burst_found_pulse_for_FT, &freq_est_phase_out_real, &freq_est_phase_out_imag, &freq_est_norm_out, &freq_est_norm_max_out);
        trace_iteration_end();
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(4, acotescc__for_peek_index), &((&burst_found_pulse_out)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(5, acotescc__for_peek_index), &((&burst_found_pulse_for_FT)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(6, acotescc__for_peek_index), &((&freq_est_phase_out_real)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(7, acotescc__for_peek_index), &((&freq_est_phase_out_imag)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_pop(3, 1);
        oport_push(4, 1);
        oport_push(5, 1);
        oport_push(6, 1);
        oport_push(7, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
        iport_acquire(3, 1);
        oport_acquire(4, 1);
        oport_acquire(5, 1);
        oport_acquire(6, 1);
        oport_acquire(7, 1);
    }
    task_close();
    trace_instance_end();
}
void task3_outline(task_t __task)
{
    trace_instance_begin();
    int init_modules;
    int freq_est_phase_out_real;
    int freq_est_phase_out_imag;
    int burst_found_pulse_out;
    int angle;
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    iport_acquire(3, 1);
    oport_acquire(4, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&init_modules)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_est_phase_out_real)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_est_phase_out_imag)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&burst_found_pulse_out)[acotescc__for_peek_index]), iport_peek(3, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        arctan(init_modules, freq_est_phase_out_real, freq_est_phase_out_imag, burst_found_pulse_out, &angle);
        trace_iteration_end();
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(4, acotescc__for_peek_index), &((&angle)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_pop(3, 1);
        oport_push(4, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
        iport_acquire(3, 1);
        oport_acquire(4, 1);
    }
    task_close();
    trace_instance_end();
}
void task4_outline(task_t __task)
{
    trace_instance_begin();
    int init_modules;
    int freq_sync_correl_2STS_output_I;
    int freq_sync_correl_2STS_output_Q;
    int angle;
    int cordic_out_real;
    int cordic_out_imag;
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    iport_acquire(3, 1);
    oport_acquire(4, 1);
    oport_acquire(5, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&init_modules)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_output_I)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_output_Q)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&angle)[acotescc__for_peek_index]), iport_peek(3, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        cordic_turn(init_modules, freq_sync_correl_2STS_output_I, freq_sync_correl_2STS_output_Q, angle, &cordic_out_real, &cordic_out_imag);
        trace_iteration_end();
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(4, acotescc__for_peek_index), &((&cordic_out_real)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(5, acotescc__for_peek_index), &((&cordic_out_imag)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_pop(3, 1);
        oport_push(4, 1);
        oport_push(5, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
        iport_acquire(3, 1);
        oport_acquire(4, 1);
        oport_acquire(5, 1);
    }
    task_close();
    trace_instance_end();
}
void task5_outline(task_t __task)
{
    trace_instance_begin();
    int init_modules;
    int burst_found_pulse_for_FT;
    int cordic_out_real;
    int cordic_out_imag;
    int data_out_FT_real;
    int data_out_FT_imag;
    int maximum_found;
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    iport_acquire(3, 1);
    oport_acquire(4, 1);
    oport_acquire(5, 1);
    oport_acquire(6, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&init_modules)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&burst_found_pulse_for_FT)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&cordic_out_real)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&cordic_out_imag)[acotescc__for_peek_index]), iport_peek(3, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        fine_time_sync(init_modules, burst_found_pulse_for_FT, cordic_out_real, cordic_out_imag, &data_out_FT_real, &data_out_FT_imag, &maximum_found);
        trace_iteration_end();
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(4, acotescc__for_peek_index), &((&data_out_FT_real)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(5, acotescc__for_peek_index), &((&data_out_FT_imag)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(oport_peek(6, acotescc__for_peek_index), &((&maximum_found)[acotescc__for_peek_index]), sizeof(int));
            }
        }
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_pop(3, 1);
        oport_push(4, 1);
        oport_push(5, 1);
        oport_push(6, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
        iport_acquire(3, 1);
        oport_acquire(4, 1);
        oport_acquire(5, 1);
        oport_acquire(6, 1);
    }
    task_close();
    trace_instance_end();
}
void task6_outline(task_t __task)
{
    trace_instance_begin();
    FILE * freq_sync_correl_2STS_out_I;
    FILE * freq_sync_correl_2STS_out_Q;
    FILE * FS_single_correl_I;
    FILE * FS_single_correl_Q;
    FILE * freq_est_phase_out_I;
    FILE * freq_est_phase_out_Q;
    int freq_sync_correl_2STS_output_I;
    int freq_sync_correl_2STS_output_Q;
    int correlation_1ST_i;
    int correlation_1ST_q;
    int freq_est_phase_out_real;
    int freq_est_phase_out_imag;
    memcpy(&freq_sync_correl_2STS_out_I, copyin_acquire(0), sizeof(FILE *) * 1);
    memcpy(&freq_sync_correl_2STS_out_Q, copyin_acquire(1), sizeof(FILE *) * 1);
    memcpy(&FS_single_correl_I, copyin_acquire(2), sizeof(FILE *) * 1);
    memcpy(&FS_single_correl_Q, copyin_acquire(3), sizeof(FILE *) * 1);
    memcpy(&freq_est_phase_out_I, copyin_acquire(4), sizeof(FILE *) * 1);
    memcpy(&freq_est_phase_out_Q, copyin_acquire(5), sizeof(FILE *) * 1);
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    iport_acquire(3, 1);
    iport_acquire(4, 1);
    iport_acquire(5, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_output_I)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_sync_correl_2STS_output_Q)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&correlation_1ST_i)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&correlation_1ST_q)[acotescc__for_peek_index]), iport_peek(3, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_est_phase_out_real)[acotescc__for_peek_index]), iport_peek(4, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&freq_est_phase_out_imag)[acotescc__for_peek_index]), iport_peek(5, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        {
            fprintf(freq_sync_correl_2STS_out_I, "%d\n", freq_sync_correl_2STS_output_I);
            fprintf(freq_sync_correl_2STS_out_Q, "%d\n", freq_sync_correl_2STS_output_Q);
            fprintf(FS_single_correl_I, "%d\n", correlation_1ST_i);
            fprintf(FS_single_correl_Q, "%d\n", correlation_1ST_q);
            fprintf(freq_est_phase_out_I, "%d\n", freq_est_phase_out_real);
            fprintf(freq_est_phase_out_Q, "%d\n", freq_est_phase_out_imag);
        }
        trace_iteration_end();
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_pop(3, 1);
        iport_pop(4, 1);
        iport_pop(5, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
        iport_acquire(3, 1);
        iport_acquire(4, 1);
        iport_acquire(5, 1);
    }
    task_close();
    trace_instance_end();
}
void task8_outline(task_t __task)
{
    trace_instance_begin();
    int mk_test;
    int data_out_FT_real;
    int data_out_FT_imag;
    float re_out;
    float im_out;
    int start_out;
    float real_out_demux[64];
    float imag_out_demux[64];
    float FFT_output_scale;
    int input_CHE_real[104];
    int input_CHE_imag[104];
    int data_remove_GI_reorder_real[52];
    int data_remove_GI_reorder_imag[52];
    int CHE_flag;
    int output_CHE_real[52];
    int output_CHE_imag[52];
    int output_CHC_real[52];
    int output_CHC_imag[52];
    int j;
    int i;
    int GI_Flag;
    FILE * fft_re_reversed;
    FILE * fft_im_reversed;
    FILE * fft_re_out;
    FILE * fft_im_out;
    FILE * CHE_out_I;
    FILE * CHE_out_Q;
    FILE * CHC_out_I;
    FILE * CHC_out_Q;
    int counter;
    int maximum_found;
    memcpy(&mk_test, copyin_acquire(0), sizeof(int) * 1);
    memcpy(&data_out_FT_real, copyin_acquire(1), sizeof(int) * 1);
    memcpy(&data_out_FT_imag, copyin_acquire(2), sizeof(int) * 1);
    memcpy(&re_out, copyin_acquire(3), sizeof(float) * 1);
    memcpy(&im_out, copyin_acquire(4), sizeof(float) * 1);
    memcpy(&start_out, copyin_acquire(5), sizeof(int) * 1);
    memcpy(real_out_demux, copyin_acquire(6), sizeof(float) * 64);
    memcpy(imag_out_demux, copyin_acquire(7), sizeof(float) * 64);
    memcpy(&FFT_output_scale, copyin_acquire(8), sizeof(float) * 1);
    memcpy(input_CHE_real, copyin_acquire(9), sizeof(int) * 104);
    memcpy(input_CHE_imag, copyin_acquire(10), sizeof(int) * 104);
    memcpy(data_remove_GI_reorder_real, copyin_acquire(11), sizeof(int) * 52);
    memcpy(data_remove_GI_reorder_imag, copyin_acquire(12), sizeof(int) * 52);
    memcpy(&CHE_flag, copyin_acquire(13), sizeof(int) * 1);
    memcpy(output_CHE_real, copyin_acquire(14), sizeof(int) * 52);
    memcpy(output_CHE_imag, copyin_acquire(15), sizeof(int) * 52);
    memcpy(output_CHC_real, copyin_acquire(16), sizeof(int) * 52);
    memcpy(output_CHC_imag, copyin_acquire(17), sizeof(int) * 52);
    memcpy(&j, copyin_acquire(18), sizeof(int) * 1);
    memcpy(&i, copyin_acquire(19), sizeof(int) * 1);
    memcpy(&GI_Flag, copyin_acquire(20), sizeof(int) * 1);
    memcpy(&fft_re_reversed, copyin_acquire(21), sizeof(FILE *) * 1);
    memcpy(&fft_im_reversed, copyin_acquire(22), sizeof(FILE *) * 1);
    memcpy(&fft_re_out, copyin_acquire(23), sizeof(FILE *) * 1);
    memcpy(&fft_im_out, copyin_acquire(24), sizeof(FILE *) * 1);
    memcpy(&CHE_out_I, copyin_acquire(25), sizeof(FILE *) * 1);
    memcpy(&CHE_out_Q, copyin_acquire(26), sizeof(FILE *) * 1);
    memcpy(&CHC_out_I, copyin_acquire(27), sizeof(FILE *) * 1);
    memcpy(&CHC_out_Q, copyin_acquire(28), sizeof(FILE *) * 1);
    memcpy(&counter, copyin_acquire(29), sizeof(int) * 1);
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&data_out_FT_real)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&data_out_FT_imag)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&maximum_found)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        if (maximum_found == 1)
        {
            mintaka__enable = counter > 41000 && counter < 41050;
            counter++;
            mark_GI_data(mk_test, &GI_Flag);
            if (GI_Flag == 0)
            {
                mk_test = 1;
                fft64(1, data_out_FT_real, data_out_FT_imag, &re_out, &im_out);
                fprintf(fft_re_reversed, "%12f\n", re_out);
                fprintf(fft_im_reversed, "%12f\n", im_out);
                mstream_demux(1, (float) (re_out), (float) (im_out), &start_out, real_out_demux, imag_out_demux);
                if (i < 63)
                {
                    i++;
                }
                else
                {
                    for (j = 0;
                        j < 64;
                        j++)
                    {
                        fprintf(fft_re_out, "%12f\n", real_out_demux[j]);
                        fprintf(fft_im_out, "%12f\n", imag_out_demux[j]);
                    }
                    scale_reorder_removeGB(real_out_demux, imag_out_demux, FFT_output_scale, input_CHE_real, input_CHE_imag, data_remove_GI_reorder_real, data_remove_GI_reorder_imag, CHE_flag);
                    if (CHE_flag == 3)
                    {
                        channel_estimation(input_CHE_real, input_CHE_imag, output_CHE_real, output_CHE_imag);
                        for (i = 0;
                            i < 52;
                            i++)
                        {
                            fprintf(CHE_out_I, "%d \n", output_CHE_real[i]);
                            fprintf(CHE_out_Q, "%d \n", output_CHE_imag[i]);
                        }
                    }
                    if (CHE_flag >= 3)
                    {
                        channel_correction(data_remove_GI_reorder_real, data_remove_GI_reorder_imag, output_CHE_real, output_CHE_imag, output_CHC_real, output_CHC_imag);
                        for (i = 0;
                            i < 52;
                            i++)
                        {
                            fprintf(CHC_out_I, "%d \n", (int) (output_CHC_real[i]));
                            fprintf(CHC_out_Q, "%d \n", (int) (output_CHC_imag[i]));
                        }
                    }
                    i = 0;
                    if (CHE_flag < 5)
                    {
                        CHE_flag++;
                    }
                }
            }
        }
        trace_iteration_end();
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
    }
    task_close();
    trace_instance_end();
}
void task7_outline(task_t __task)
{
    trace_instance_begin();
    int downsampling_flag;
    int data_out_FT_real;
    int data_out_FT_imag;
    int maximum_found;
    memcpy(&downsampling_flag, copyin_acquire(0), sizeof(int) * 1);
    iport_acquire(0, 1);
    iport_acquire(1, 1);
    iport_acquire(2, 1);
    while (task_allopen())
    {
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&data_out_FT_real)[acotescc__for_peek_index]), iport_peek(0, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&data_out_FT_imag)[acotescc__for_peek_index]), iport_peek(1, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        {
            int acotescc__for_peek_index;
            for (acotescc__for_peek_index = 0;
                acotescc__for_peek_index < 1;
                acotescc__for_peek_index++)
            {
                memcpy(&((&maximum_found)[acotescc__for_peek_index]), iport_peek(2, 0 + acotescc__for_peek_index), sizeof(int));
            }
        }
        trace_iteration_begin();
        if (downsampling_flag == 0)
        {
            {
                oport_acquire(3, 1);
                {
                    int acotescc__for_peek_index;
                    for (acotescc__for_peek_index = 0;
                        acotescc__for_peek_index < 1;
                        acotescc__for_peek_index++)
                    {
                        memcpy(oport_peek(3, acotescc__for_peek_index), &((&data_out_FT_real)[acotescc__for_peek_index]), sizeof(int));
                    }
                }
                oport_push(3, 1);
                oport_acquire(4, 1);
                {
                    int acotescc__for_peek_index;
                    for (acotescc__for_peek_index = 0;
                        acotescc__for_peek_index < 1;
                        acotescc__for_peek_index++)
                    {
                        memcpy(oport_peek(4, acotescc__for_peek_index), &((&data_out_FT_imag)[acotescc__for_peek_index]), sizeof(int));
                    }
                }
                oport_push(4, 1);
                oport_acquire(5, 1);
                {
                    int acotescc__for_peek_index;
                    for (acotescc__for_peek_index = 0;
                        acotescc__for_peek_index < 1;
                        acotescc__for_peek_index++)
                    {
                        memcpy(oport_peek(5, acotescc__for_peek_index), &((&maximum_found)[acotescc__for_peek_index]), sizeof(int));
                    }
                }
                oport_push(5, 1);
            }
            downsampling_flag = 1;
        }
        else
        {
            downsampling_flag = 0;
        }
        trace_iteration_end();
        iport_pop(0, 1);
        iport_pop(1, 1);
        iport_pop(2, 1);
        iport_acquire(0, 1);
        iport_acquire(1, 1);
        iport_acquire(2, 1);
    }
    task_close();
    trace_instance_end();
}
int acotescc__main(int argc, char * * argv)
{
    {
        int init_modules = 0;
        int rx_start = 0;
        float freq_sync_correl_2STS_input_I, freq_sync_correl_2STS_input_Q;
        int freq_sync_correl_2STS_output_I, freq_sync_correl_2STS_output_Q;
        int correlation_1ST_i, correlation_1ST_q;
        int burst_found_out;
        int burst_found_pulse_out;
        int freq_est_phase_out_real;
        int freq_est_phase_out_imag;
        int freq_est_norm_out;
        int freq_est_norm_max_out;
        int angle;
        int cordic_out_real;
        int cordic_out_imag;
        int burst_found_pulse_for_FT;
        int data_out_FT_real;
        int data_out_FT_imag;
        int maximum_found;
        float re_out;
        float im_out;
        int start_out;
        static float real_out_demux[64], imag_out_demux[64];
        int i = 0;
        int j;
        float FFT_output_scale = 11.0 / 8.0;
        int data_remove_GI_reorder_real[52], data_remove_GI_reorder_imag[52];
        int input_CHE_real[104];
        int input_CHE_imag[104];
        int output_CHE_real[52];
        int output_CHE_imag[52];
        int output_CHC_real[52];
        int output_CHC_imag[52];
        static int CHE_flag = 0;
        int downsampling_flag = 0;
        int mk_test = 0;
        int GI_Flag = 0;
        FILE * file_re_in, * file_im_in;
        file_re_in = fopen("./CCSS_ref_data/rx_real_data.am", "r");
        file_im_in = fopen("./CCSS_ref_data/rx_imag_data.am", "r");
        char re_in[20];
        char im_in[20];
        FILE * freq_sync_correl_2STS_out_I, * freq_sync_correl_2STS_out_Q;
        FILE * FS_single_correl_I, * FS_single_correl_Q;
        FILE * fft_re_reversed, * fft_im_reversed;
        FILE * freq_est_phase_out_I, * freq_est_phase_out_Q;
        FILE * CHE_out_I, * CHE_out_Q;
        FILE * CHC_out_I, * CHC_out_Q;
        FILE * fft_re_out, * fft_im_out;
        freq_sync_correl_2STS_out_I = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_I.am", "w");
        freq_sync_correl_2STS_out_Q = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_Q.am", "w");
        FS_single_correl_I = fopen("./plainC_SimOutput/FS_single_correl_I.am", "w");
        FS_single_correl_Q = fopen("./plainC_SimOutput/FS_single_correl_Q.am", "w");
        fft_re_reversed = fopen("./plainC_SimOutput/fft_reversed_re_out.am", "w");
        fft_im_reversed = fopen("./plainC_SimOutput/fft_reversed_im_out.am", "w");
        freq_est_phase_out_I = fopen("./plainC_SimOutput/freq_est_phase_out_I.am", "w");
        freq_est_phase_out_Q = fopen("./plainC_SimOutput/freq_est_phase_out_Q.am", "w");
        CHE_out_I = fopen("./plainC_SimOutput/CHE_out_I.am", "w");
        CHE_out_Q = fopen("./plainC_SimOutput/CHE_out_Q.am", "w");
        CHC_out_I = fopen("./plainC_SimOutput/CHC_out_I.am", "w");
        CHC_out_Q = fopen("./plainC_SimOutput/CHC_out_Q.am", "w");
        fft_re_out = fopen("./plainC_SimOutput/fft_re_out.am", "w");
        fft_im_out = fopen("./plainC_SimOutput/fft_im_out.am", "w");
        int counter = 0;
        fine_time_sync_init(&maximum_found);
        {
            task_t task0;
            task_init(&task0, (void *) 0, 0);
            task_t task1;
            task_init(&task1, task1_outline, 0);
            task_t task2;
            task_init(&task2, task2_outline, 0);
            task_t task3;
            task_init(&task3, task3_outline, 0);
            task_t task4;
            task_init(&task4, task4_outline, 0);
            task_t task5;
            task_init(&task5, task5_outline, 0);
            task_t task6;
            task_init(&task6, task6_outline, 0);
            task_t task7;
            task_init(&task7, task7_outline, 0);
            task_t task8;
            task_init(&task8, task8_outline, 0);
            task_oport(task0, 0, sizeof(float), 1, 1);
            task_oport(task0, 1, sizeof(float), 1, 1);
            task_oport(task0, 2, sizeof(int), 1, 1);
            task_oport(task0, 3, sizeof(int), 1, 1);
            task_oport(task0, 4, sizeof(int), 1, 1);
            task_oport(task0, 5, sizeof(int), 1, 1);
            task_oport(task0, 6, sizeof(int), 1, 1);
            task_iport(task1, 0, sizeof(float), 1, 0 + 1, (void *) 0, 0);
            task_iport(task1, 1, sizeof(float), 1, 0 + 1, (void *) 0, 0);
            task_oport(task1, 2, sizeof(int), 1, 1);
            task_oport(task1, 3, sizeof(int), 1, 1);
            task_oport(task1, 4, sizeof(int), 1, 1);
            task_oport(task1, 5, sizeof(int), 1, 1);
            task_iport(task2, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task2, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task2, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task2, 3, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_oport(task2, 4, sizeof(int), 1, 1);
            task_oport(task2, 5, sizeof(int), 1, 1);
            task_oport(task2, 6, sizeof(int), 1, 1);
            task_oport(task2, 7, sizeof(int), 1, 1);
            task_iport(task3, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task3, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task3, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task3, 3, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_oport(task3, 4, sizeof(int), 1, 1);
            task_iport(task4, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task4, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task4, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task4, 3, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_oport(task4, 4, sizeof(int), 1, 1);
            task_oport(task4, 5, sizeof(int), 1, 1);
            task_iport(task5, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task5, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task5, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task5, 3, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_oport(task5, 4, sizeof(int), 1, 1);
            task_oport(task5, 5, sizeof(int), 1, 1);
            task_oport(task5, 6, sizeof(int), 1, 1);
            task_iport(task6, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task6, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task6, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task6, 3, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task6, 4, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task6, 5, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task7, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task7, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task7, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_oport(task7, 3, sizeof(int), 1, 1);
            task_oport(task7, 4, sizeof(int), 1, 1);
            task_oport(task7, 5, sizeof(int), 1, 1);
            task_iport(task8, 0, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task8, 1, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            task_iport(task8, 2, sizeof(int), 1, 0 + 1, (void *) 0, 0);
            port_connect(task0, 0, task1, 0);
            port_connect(task0, 1, task1, 1);
            port_connect(task0, 2, task2, 0);
            port_connect(task0, 3, task2, 1);
            port_connect(task0, 4, task3, 0);
            port_connect(task0, 5, task4, 0);
            port_connect(task0, 6, task5, 0);
            port_connect(task7, 3, task8, 0);
            port_connect(task7, 4, task8, 1);
            port_connect(task7, 5, task8, 2);
            port_connect(task1, 4, task2, 2);
            port_connect(task1, 4, task6, 2);
            port_connect(task1, 5, task2, 3);
            port_connect(task1, 5, task6, 3);
            port_connect(task1, 2, task4, 1);
            port_connect(task1, 2, task6, 0);
            port_connect(task1, 3, task4, 2);
            port_connect(task1, 3, task6, 1);
            port_connect(task2, 6, task3, 1);
            port_connect(task2, 6, task6, 4);
            port_connect(task2, 7, task3, 2);
            port_connect(task2, 7, task6, 5);
            port_connect(task2, 4, task3, 3);
            port_connect(task2, 5, task5, 1);
            port_connect(task3, 4, task4, 3);
            port_connect(task4, 4, task5, 2);
            port_connect(task4, 5, task5, 3);
            port_connect(task5, 4, task7, 0);
            port_connect(task5, 5, task7, 1);
            port_connect(task5, 6, task7, 2);
            task_copyin(task2, 0, &burst_found_out, sizeof(int) * 1);
            task_copyin(task2, 1, &freq_est_norm_out, sizeof(int) * 1);
            task_copyin(task2, 2, &freq_est_norm_max_out, sizeof(int) * 1);
            task_copyin(task6, 0, &freq_sync_correl_2STS_out_I, sizeof(FILE *) * 1);
            task_copyin(task6, 1, &freq_sync_correl_2STS_out_Q, sizeof(FILE *) * 1);
            task_copyin(task6, 2, &FS_single_correl_I, sizeof(FILE *) * 1);
            task_copyin(task6, 3, &FS_single_correl_Q, sizeof(FILE *) * 1);
            task_copyin(task6, 4, &freq_est_phase_out_I, sizeof(FILE *) * 1);
            task_copyin(task6, 5, &freq_est_phase_out_Q, sizeof(FILE *) * 1);
            task_copyin(task7, 0, &downsampling_flag, sizeof(int) * 1);
            task_copyin(task8, 0, &mk_test, sizeof(int) * 1);
            task_copyin(task8, 1, &data_out_FT_real, sizeof(int) * 1);
            task_copyin(task8, 2, &data_out_FT_imag, sizeof(int) * 1);
            task_copyin(task8, 3, &re_out, sizeof(float) * 1);
            task_copyin(task8, 4, &im_out, sizeof(float) * 1);
            task_copyin(task8, 5, &start_out, sizeof(int) * 1);
            task_copyin(task8, 6, real_out_demux, sizeof(float) * 64);
            task_copyin(task8, 7, imag_out_demux, sizeof(float) * 64);
            task_copyin(task8, 8, &FFT_output_scale, sizeof(float) * 1);
            task_copyin(task8, 9, input_CHE_real, sizeof(int) * 104);
            task_copyin(task8, 10, input_CHE_imag, sizeof(int) * 104);
            task_copyin(task8, 11, data_remove_GI_reorder_real, sizeof(int) * 52);
            task_copyin(task8, 12, data_remove_GI_reorder_imag, sizeof(int) * 52);
            task_copyin(task8, 13, &CHE_flag, sizeof(int) * 1);
            task_copyin(task8, 14, output_CHE_real, sizeof(int) * 52);
            task_copyin(task8, 15, output_CHE_imag, sizeof(int) * 52);
            task_copyin(task8, 16, output_CHC_real, sizeof(int) * 52);
            task_copyin(task8, 17, output_CHC_imag, sizeof(int) * 52);
            task_copyin(task8, 18, &j, sizeof(int) * 1);
            task_copyin(task8, 19, &i, sizeof(int) * 1);
            task_copyin(task8, 20, &GI_Flag, sizeof(int) * 1);
            task_copyin(task8, 21, &fft_re_reversed, sizeof(FILE *) * 1);
            task_copyin(task8, 22, &fft_im_reversed, sizeof(FILE *) * 1);
            task_copyin(task8, 23, &fft_re_out, sizeof(FILE *) * 1);
            task_copyin(task8, 24, &fft_im_out, sizeof(FILE *) * 1);
            task_copyin(task8, 25, &CHE_out_I, sizeof(FILE *) * 1);
            task_copyin(task8, 26, &CHE_out_Q, sizeof(FILE *) * 1);
            task_copyin(task8, 27, &CHC_out_I, sizeof(FILE *) * 1);
            task_copyin(task8, 28, &CHC_out_Q, sizeof(FILE *) * 1);
            task_copyin(task8, 29, &counter, sizeof(int) * 1);
            task_start(task0);
            task_start(task1);
            task_start(task2);
            task_start(task3);
            task_start(task4);
            task_start(task5);
            task_start(task6);
            task_start(task7);
            task_start(task8);
            trace_iteration_begin();
            while (!feof(file_re_in) || !feof(file_im_in))
            {
                fgets(re_in, 20, file_re_in);
                freq_sync_correl_2STS_input_I = atof(re_in);
                fgets(im_in, 20, file_im_in);
                freq_sync_correl_2STS_input_Q = atof(im_in);
                {
                    oport_acquire(0, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(0, acotescc__for_peek_index), &((&freq_sync_correl_2STS_input_I)[acotescc__for_peek_index]), sizeof(float));
                        }
                    }
                    oport_push(0, 1);
                    oport_acquire(1, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(1, acotescc__for_peek_index), &((&freq_sync_correl_2STS_input_Q)[acotescc__for_peek_index]), sizeof(float));
                        }
                    }
                    oport_push(1, 1);
                }
                {
                    oport_acquire(2, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(2, acotescc__for_peek_index), &((&init_modules)[acotescc__for_peek_index]), sizeof(int));
                        }
                    }
                    oport_push(2, 1);
                    oport_acquire(3, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(3, acotescc__for_peek_index), &((&rx_start)[acotescc__for_peek_index]), sizeof(int));
                        }
                    }
                    oport_push(3, 1);
                }
                {
                    oport_acquire(4, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(4, acotescc__for_peek_index), &((&init_modules)[acotescc__for_peek_index]), sizeof(int));
                        }
                    }
                    oport_push(4, 1);
                }
                {
                    oport_acquire(5, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(5, acotescc__for_peek_index), &((&init_modules)[acotescc__for_peek_index]), sizeof(int));
                        }
                    }
                    oport_push(5, 1);
                }
                {
                    oport_acquire(6, 1);
                    {
                        int acotescc__for_peek_index;
                        for (acotescc__for_peek_index = 0;
                            acotescc__for_peek_index < 1;
                            acotescc__for_peek_index++)
                        {
                            memcpy(oport_peek(6, acotescc__for_peek_index), &((&init_modules)[acotescc__for_peek_index]), sizeof(int));
                        }
                    }
                    oport_push(6, 1);
                }
                {
                }
                {
                }
                init_modules = 1;
            }
            trace_iteration_end();
            task_close();
            task_wait(task8);
            task_wait(task7);
            task_wait(task6);
            task_wait(task5);
            task_wait(task4);
            task_wait(task3);
            task_wait(task2);
            task_wait(task1);
            task_wait(task0);
        }
        fclose(file_re_in);
        fclose(file_im_in);
        fclose(freq_sync_correl_2STS_out_I);
        fclose(freq_sync_correl_2STS_out_Q);
        fclose(FS_single_correl_I);
        fclose(FS_single_correl_Q);
        fclose(fft_re_reversed);
        fclose(fft_im_reversed);
        fclose(fft_re_out);
        fclose(fft_im_out);
        fclose(freq_est_phase_out_I);
        fclose(freq_est_phase_out_Q);
        fclose(CHC_out_I);
        fclose(CHC_out_Q);
        fclose(CHE_out_I);
        fclose(CHE_out_Q);
        return 0;
    }
    return 0;
}
int main(int argc, char * * argv)
{
    int result;
    trace_app_begin(argv[0]);
    result = acotescc__main(argc, argv);
    trace_app_end();
    return result;
}
