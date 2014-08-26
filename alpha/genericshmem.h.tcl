set SHC(genericshmem.h) "
#ifndef __[set subsys]_H__
#define __[set subsys]_H__

class shm_[set subsys] \{
   public:
     virtual void Handle();
[set TOPICPROPS($subsys)]
     static void * m_shared_mem;
     void * operator new (unsigned int);
\};



void GetObject_[set subsys](shm_[set subsys] ** pshm_[set subsys]);

#endif //__[set subsys]_H__
"

