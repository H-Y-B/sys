# syscall-fork

1. 

   ```c
   
   ```
   
   
   
2. 源码库

   ```C
   //riscv-glibc/sysdeps/nptl/fork.c
   weak_alias (__libc_fork, fork)
   ```

   TODO: Where is “weak_alias” defined ？
   
   ```c
   //riscv-glibc/sysdeps/unix/sysv/linux/riscv/arc-fork.h
#include <sysdeps/unix/sysv/linux/i386/arch-fork.h>
   
   
   //riscv-glibc/sysdeps/unix/sysv/linux/i386/arc-fork.h
   #define ARCH_FORK() \
     INLINE_SYSCALL (clone, 5,						      \
   		  CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID | SIGCHLD, 0,     \
		  NULL, NULL, &THREAD_SELF->tid)
   ```
   
   ```c
   //riscv-glibc/sysdeps/unix/sysv/linux/riscv/sysdep.h
   //           系统调用名称、参数个数、系统调用需要的参数（变长）
   #define INLINE_SYSCALL(name, nr, args...)				\
     ({ INTERNAL_SYSCALL_DECL(err);					\
        long __sys_result = INTERNAL_SYSCALL (name, err, nr, args);	\
        if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P(__sys_result, ), 0)) \
          {								\
            __set_errno (INTERNAL_SYSCALL_ERRNO (__sys_result, ));		\
   	 __sys_result = (unsigned long) -1;				\
          }								\
        __sys_result; })
   ```
   
   ```c
      //riscv-glibc/sysdeps/unix/sysv/linux/riscv/sysdep.h
      #define INTERNAL_SYSCALL(name, err, nr, args...) \
      	internal_syscall##nr (SYS_ify (name), err, args)
      //   __NR_clone
      
      //riscv-glibc/sysdeps/unix/sysv/linux/riscv/sysdep.h
      #define SYS_ify(syscall_name)	__NR_##syscall_name
      
      //riscv-linux/usr/include/asm-generic/unistd.h
      #define __NR_clone 220
      __SYSCALL(__NR_clone, sys_clone)
   ```
   
   ```c
   //riscv-glibc/sysdeps/unix/sysv/linux/riscv/sysdep.h
      #define internal_syscall0(number, err, dummy...)			\
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0");					\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "=r" (__a0)							\
      	: "r" (__a7)							\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall1(number, err, arg0)				\
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7)							\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall2(number, err, arg0, arg1)	    		\
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1)						\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall3(number, err, arg0, arg1, arg2)      		\
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	register long __a2 asm("a2") = (long) (arg2);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1), "r"(__a2)				\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall4(number, err, arg0, arg1, arg2, arg3)	  \
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	register long __a2 asm("a2") = (long) (arg2);			\
      	register long __a3 asm("a3") = (long) (arg3);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1), "r"(__a2), "r"(__a3)			\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall5(number, err, arg0, arg1, arg2, arg3, arg4)    \
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	register long __a2 asm("a2") = (long) (arg2);			\
      	register long __a3 asm("a3") = (long) (arg3);			\
      	register long __a4 asm("a4") = (long) (arg4);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1), "r"(__a2), "r"(__a3), "r"(__a4)	\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall6(number, err, arg0, arg1, arg2, arg3, arg4, arg5) \
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	register long __a2 asm("a2") = (long) (arg2);			\
      	register long __a3 asm("a3") = (long) (arg3);			\
      	register long __a4 asm("a4") = (long) (arg4);			\
      	register long __a5 asm("a5") = (long) (arg5);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1), "r"(__a2), "r"(__a3), "r"(__a4), "r"(__a5)	\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
      
      #define internal_syscall7(number, err, arg0, arg1, arg2, arg3, arg4, arg5, arg6) \
      ({ 									\
      	long _sys_result;						\
      									\
      	{								\
      	register long __a7 asm("a7") = number;				\
      	register long __a0 asm("a0") = (long) (arg0);			\
      	register long __a1 asm("a1") = (long) (arg1);			\
      	register long __a2 asm("a2") = (long) (arg2);			\
      	register long __a3 asm("a3") = (long) (arg3);			\
      	register long __a4 asm("a4") = (long) (arg4);			\
      	register long __a5 asm("a5") = (long) (arg5);			\
      	register long __a6 asm("a6") = (long) (arg6);			\
      	__asm__ volatile ( 						\
      	"scall\n\t" 							\
      	: "+r" (__a0)							\
      	: "r" (__a7), "r"(__a1), "r"(__a2), "r"(__a3), "r"(__a4), "r"(__a5), "r"(__a6)	\
      	: __SYSCALL_CLOBBERS); 						\
      	_sys_result = __a0;						\
      	}								\
      	_sys_result;							\
      })
   ```
   
   

   

