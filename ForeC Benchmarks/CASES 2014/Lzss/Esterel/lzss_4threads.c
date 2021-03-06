/* Generated by EEC */
#include "lzss_data.h"
#include "lzss.h"
#include "string.h"

#include "esterel_mutex.h"
#define FSL_ESTEREL_MUTEX0_ID	3
#define FSL_ESTEREL_MUTEX1_ID	4
#define FSL_ESTEREL_MUTEX2_ID	5

#include "thread_queue.h"
#define FSL_THREAD_QUEUE_ID		6

static struct {
    unsigned char fileName;
    unsigned char done;
    unsigned char error;
    unsigned char Done;
    unsigned char Error;
    unsigned char Done_1;
    unsigned char Error_1;
} _s = {  0,  0,  0,  0,  0,  0,  0 };

#define tick 1
static char fileName_v[STRLEN];

static union {
    unsigned int val;
    struct {
        unsigned int t0 : 1;
    } lock;
} _Done_locks;
#define _MASK_Done_locks 0x1

static union {
    unsigned int val;
    struct {
        unsigned int t0 : 1;
    } lock;
} _Done_1_locks;
#define _MASK_Done_1_locks 0x1

/* Variable declaration */
static integer fileSize;

/* State variables */
static unsigned char _state_1 = 5;

/* Termination variables */
static int _term_16;
static int _term_19;
static int _term_79;

/* Thread variables */
static void* _thread_0 = 0;
static void* _thread_1 = 0;
static void* _thread_2 = 0;
static void* _thread_3 = 0;
static void* _thread_4 = 0;
static void* _thread_5 = 0;
static void* _thread_6 = 0;
static int _thread_0_count = 0;

#define _FORK(id)
#define _JOIN(id)
#define _PAUSE


/* Definitions for input functions */
void lzss_archiver_I_fileName(string _v)
{
    _s.fileName = 1;
    strcpy(fileName_v, _v);
}


int lzss_archiver(int isSlave)
{
	void *fslData;
	
    if (isSlave) {
        thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
        goto *fslData;
    }

	esterel_mutex_set_key(&_Done_locks, FSL_ESTEREL_MUTEX0_ID);
	esterel_mutex_lock(0, FSL_ESTEREL_MUTEX1_ID);
	esterel_mutex_set_key(&_Done_locks, FSL_ESTEREL_MUTEX0_ID);
	esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
	
	esterel_mutex_set_key(&_Done_1_locks, FSL_ESTEREL_MUTEX0_ID);
	esterel_mutex_lock(0, FSL_ESTEREL_MUTEX1_ID);
	esterel_mutex_set_key(&_Done_1_locks, FSL_ESTEREL_MUTEX0_ID);
	esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);

    _term_16 = 0;

    for(;;) {
        _term_16 &= 0x7fffffff;

        if (_thread_0) goto *_thread_0;
        switch (_state_1) {
            case 0:
                goto N17;
            case 1:
                slideWindow();
                _state_1 = 2;
                _FORK(0);
                thread_queue_push(&&M127, FSL_THREAD_QUEUE_ID);
                thread_queue_push(&&M123, FSL_THREAD_QUEUE_ID);
                thread_queue_push(&&M119, FSL_THREAD_QUEUE_ID);
                thread_queue_push(&&M110, FSL_THREAD_QUEUE_ID);
                _thread_0_count = 4;
                thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
                goto *fslData;
            M127:
                ;
                searchWindow4();
                /* Vacuous terminate */;
//            M124:
                /* Exit thread 4 */;
                esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
                esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                _thread_0_count--;
                esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
                if (_thread_0_count) {
                    thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
                    goto *fslData;
                } else {
                    goto M113_join;
                }
            M123:
                ;
                searchWindow3();
                /* Vacuous terminate */;
//            M120:
                /* Exit thread 3 */;
                esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
                esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                _thread_0_count--;
                esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
                if (_thread_0_count) {
                    thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
                    goto *fslData;
                } else {
                    goto M113_join;
                }
            M119:
                ;
                searchWindow2();
                /* Vacuous terminate */;
//            M116:
                /* Exit thread 2 */;
                esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
                esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                _thread_0_count--;
                esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
                if (_thread_0_count) {
                    thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
                    goto *fslData;
                } else {
                    goto M113_join;
                }
            M110:
                ;
                searchWindow1();
                /* Vacuous terminate */;
//            M113:
                /* Exit thread 1 */;
                esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
                esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                _thread_0_count--;
                esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
                if (_thread_0_count) {
                    thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
                    goto *fslData;
                }
            M113_join:
                _JOIN(0);
                writeToArchive();
                if ((getBytesProcessed() == fileSize)) {
                    _s.Done_1 = 1;
                	esterel_mutex_set_key(&_Done_1_locks, FSL_ESTEREL_MUTEX0_ID);
					esterel_mutex_lock(0, FSL_ESTEREL_MUTEX1_ID);
                    goto N72;
                } else {
                    _state_1 = 1;
                    goto N38;
                }
                break;
            case 2:
                _FORK(0);
//            M103:
                ;
                /* Vacuous terminate */;
//            M105:
                /* Exit thread 4 */;
 //           M100:
                ;
                /* Vacuous terminate */;
//            M102:
                /* Exit thread 3 */;
//            M97:
                ;
                /* Vacuous terminate */;
//            M99:
                /* Exit thread 2 */;
//            M95:
                ;
                /* Vacuous terminate */;
//            M93:
                /* Exit thread 1 */;
                _JOIN(0);
                writeToArchive();
                if ((getBytesProcessed() == fileSize)) {
                    _s.Done_1 = 1;
                    goto N72;
                } else {
                    _state_1 = 1;
                    goto N38;
                }
                break;
            case 3:
                if (_s.fileName) {
                    if (openFile(fileName_v)) {
                        fileSize = getFileSize();
                        slideWindow();
                        _state_1 = 2;
                        _FORK(0);
                        thread_queue_push(&&M155, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M151, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M147, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M135, FSL_THREAD_QUEUE_ID);
                        _thread_0_count = 4;
						thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
						goto *fslData;
                    M155:
                        ;
                        searchWindow4();
                        /* Vacuous terminate */;
//                    M152:
                        /* Exit thread 4 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
                        } else {
                            goto M138_join;
                        }
                    M151:
                        ;
                        searchWindow3();
                        /* Vacuous terminate */;
//                    M148:
                        /* Exit thread 3 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
                        } else {
                            goto M138_join;
                        }
                    M147:
                        ;
                        searchWindow2();
                        /* Vacuous terminate */;
//                    M144:
                        /* Exit thread 2 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
                        } else {
                            goto M138_join;
                        }
                    M135:
                        ;
                        searchWindow1();
                        /* Vacuous terminate */;
//                    M138:
                        /* Exit thread 1 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
                        }
                    M138_join:
                        _JOIN(0);
                        writeToArchive();
                        if ((getBytesProcessed() == fileSize)) {
                            _s.Done_1 = 1;
                            goto N72;
                        } else {
                            _state_1 = 1;
                            goto N38;
                        }
                    } else {
                        _s.Error_1 = 1;
                    N72:
                        _state_1 = 4;
                        _FORK(1); _thread_0 = &&M85; _term_79 = 0;
                    M85:
                        if (_thread_6) goto *_thread_6;
                        if (_s.Error_1) {
                            _s.error = 1;
                        }
                        _thread_6 = &&M81; /* Vacuous terminate */;
                    M81:
                        /* Exit thread 6 */;
//                    M74:
                        if (_thread_5) goto *_thread_5;
                    M75:
                    	esterel_mutex_set_key(&_Done_1_locks, FSL_ESTEREL_MUTEX0_ID);
                    	esterel_mutex_unlocked(fslData, FSL_ESTEREL_MUTEX2_ID);
                        if (fslData) {
                            _thread_5 = &&M75;
                            _term_79 |= 0x80000000;
                        } else {
                            if (_s.Done_1) {
                                _s.done = 1;
                            }
                            _thread_5 = &&M78; /* Vacuous terminate */;
                        }
                    M78:
                        /* Exit thread 5 */;
                        _JOIN(1);
                        switch (_term_79) {
                            case 0:
                                _thread_5 = 0; _thread_6 = 0;
                                goto N18;
                            default:
                                _term_16 = 0x80000000;
                                _term_79 &= 0x7fffffff;
                                break;
                        }
                    }
                } else {
                    goto N38;
                }
                break;
            case 4:
                _FORK(1);
//            M163:
                ;
                /* Vacuous terminate */;
//            M161:
                /* Exit thread 6 */;
//            M157:
                ;
                /* Vacuous terminate */;
//            M159:
                /* Exit thread 5 */;
                _JOIN(1);
                goto N18;
            case 5:
                _s.Error = 0;
                _s.Done = 0;
                if (_s.fileName) {
                    if (openFile(fileName_v)) {
                        fileSize = getFileSize();
                        slideWindow();
                        _state_1 = 2;
                        _FORK(0);
                        thread_queue_push(&&M67, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M63, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M59, FSL_THREAD_QUEUE_ID);
                        thread_queue_push(&&M50, FSL_THREAD_QUEUE_ID);
                        _thread_0_count = 4;
						thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
						goto *fslData;
                    M67:
                        ;
                        searchWindow4();
                        /* Vacuous terminate */;
//                    M64:
                        /* Exit thread 4 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
				        } else {
                            goto M53_join;
                        }
                    M63:
                        ;
                        searchWindow3();
                        /* Vacuous terminate */;
//                    M60:
                        /* Exit thread 3 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
				        } else {
                            goto M53_join;
                        }
                    M59:
                        ;
                        searchWindow2();
                        /* Vacuous terminate */;
//                    M56:
                        /* Exit thread 2 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
				        } else {
                            goto M53_join;
                        }
                    M50:
                        ;
                        searchWindow1();
                        /* Vacuous terminate */;
//                    M53:
                        /* Exit thread 1 */;
				        esterel_mutex_set_key(&_thread_0_count, FSL_ESTEREL_MUTEX0_ID);
				        esterel_mutex_lock(1, FSL_ESTEREL_MUTEX1_ID);
                        _thread_0_count--;
                		esterel_mutex_unlock(&_thread_0_count, FSL_ESTEREL_MUTEX2_ID);
				        if (_thread_0_count) {
				            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
				            goto *fslData;
				        }
                    M53_join:
                        _JOIN(0);
                        writeToArchive();
                        if ((getBytesProcessed() == fileSize)) {
                            _s.Done = 1;
                            esterel_mutex_set_key(&_Done_locks, FSL_ESTEREL_MUTEX0_ID);
                            esterel_mutex_lock(0, FSL_ESTEREL_MUTEX1_ID);
                            goto N43;
                        } else {
                            _state_1 = 1;
                            goto N38;
                        }
                    } else {
                        _s.Error = 1;
                    N43:
                        _state_1 = 4;
                        _FORK(1); _thread_0 = &&M29; _term_19 = 0;
                    M29:
                        if (_thread_6) goto *_thread_6;
                        if (_s.Error) {
                            _s.error = 1;
                        }
                        _thread_6 = &&M32; /* Vacuous terminate */;
                    M32:
                        /* Exit thread 6 */;
//                    M27:
                        if (_thread_5) goto *_thread_5;
                    M25:
                    	esterel_mutex_set_key(&_Done_locks, FSL_ESTEREL_MUTEX0_ID);
                    	esterel_mutex_unlocked(fslData, FSL_ESTEREL_MUTEX2_ID);
                        if (fslData) {
                            _thread_5 = &&M25;
                            _term_19 |= 0x80000000;
                        } else {
                            if (_s.Done) {
                                _s.done = 1;
                            }
                            _thread_5 = &&M21; /* Vacuous terminate */;
                        }
                    M21:
                        /* Exit thread 5 */;
                        _JOIN(1);
                        switch (_term_19) {
                            case 0:
                                _thread_5 = 0; _thread_6 = 0;
                            N18:
                                _thread_0 = 0; /* Vacuous terminate */;
                            N17:
                                _state_1 = 0;
                                break;
                            default:
                                _term_16 = 0x80000000;
                                _term_19 &= 0x7fffffff;
                                break;
                        }
                    }
                } else {
                    _state_1 = 3;
                N38:
                    _thread_0 = 0; _PAUSE;
                }
                break;
        }
        if (_term_16 < 0) continue;

        if (_s.done) { lzss_archiver_O_done(); _s.done = 0; }
        if (_s.error) { lzss_archiver_O_error(); _s.error = 0; }
#ifdef TESTBENCH
#endif
        _s.fileName = 0;

    M999:
        if (isSlave) {
            thread_queue_push(&&M999, FSL_THREAD_QUEUE_ID);

            thread_queue_pop(fslData, FSL_THREAD_QUEUE_ID);
            goto *fslData;
        }

        return _state_1;
    }
}

int lzss_archiver_reset(void)
{
    _state_1 = 5;
    _s.fileName = 0;
    _thread_0 = 0;
    _thread_1 = 0;
    _thread_2 = 0;
    _thread_3 = 0;
    _thread_4 = 0;
    _thread_5 = 0;
    _thread_6 = 0;
    return 0;
}
