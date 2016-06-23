#ifndef __LINUX_COMPILER_H
#error "Please don't include <linux/compiler-gcc4.h> directly, include <linux/compiler.h> instead."
#endif

#ifdef CONFIG_FORCED_INLINING
# undef inline
# undef __inline__
# undef __inline
# define inline			inline		__attribute__((always_inline))
# define __inline__		__inline__	__attribute__((always_inline))
# define __inline		__inline	__attribute__((always_inline))
#endif

#define __used			__attribute__((__used__))
#define __must_check 		__attribute__((warn_unused_result))
#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)

#if __GNUC_MINOR__ >= 3
/* Mark functions as cold. gcc will assume any path leading to a call
   to them will be unlikely.  This means a lot of manual unlikely()s
   are unnecessary now for any paths leading to the usual suspects
   like BUG(), printk(), panic() etc. [but let's keep them for now for
   older compilers]

   Early snapshots of gcc 4.3 don't support this and we can't detect this
   in the preprocessor, but we can live with this because they're unreleased.
   Maketime probing would be overkill here.

   gcc also has a __attribute__((__hot__)) to move hot functions into
   a special section, but I don't see any sense in this right now in
   the kernel context */
#define __cold			__attribute__((__cold__))

#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)
#endif


#if __GNUC_MINOR__ >= 5
/*
 * Mark a position in code as unreachable.  This can be used to
 * suppress control flow warnings after asm blocks that transfer
 * control elsewhere.
 *
 * Early snapshots of gcc 4.5 don't support this and we can't detect
 * this in the preprocessor, but we can live with this because they're
 * unreleased.  Really, we need to have autoconf for the kernel.
 */
#define unreachable() __builtin_unreachable()
#endif


#if __GNUC_MINOR__ >= 6
/*
 * Tell the optimizer that something else uses this function or variable.
 */
#define __visible __attribute__((externally_visible))
#endif
