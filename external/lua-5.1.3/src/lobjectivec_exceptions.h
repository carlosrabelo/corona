/* Interface to allow Lua to use Objective-C exceptions with minimal impact to core.
 * Eric Wing. MIT License.
 */

#ifndef lobjectivec_exceptions_h
#define lobjectivec_exceptions_h

#define luai_jmpbuf	int  /* dummy variable */

/* Moved ldo.c definition to here */
struct lua_longjmp {
  struct lua_longjmp *previous;
  luai_jmpbuf b;
  volatile int status;  /* error code */
};

LUAI_FUNC void luai_objcthrow(struct lua_longjmp* errorJmp);

/* Throw is moved into a real function instead of a macro because NSException is needed
 * which brings in #imports from Foundation which polutes the namespace 
 * and causes some name collisions like for 'check'.
 */
#define LUAI_THROW(L,c)	luai_objcthrow(c)

/* used for pfunc */
#include "ldo.h"
LUAI_FUNC void luai_objcttry(lua_State *L, struct lua_longjmp* c_lua_longjmp, Pfunc a_func, void* userdata);
#define LUAI_TRY(L,c,a,u)	luai_objcttry(L,c,a,u)

#endif /* lobjectivec_exceptions_h */

