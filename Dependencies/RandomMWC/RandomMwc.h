/*------------------------------------------------------------------------------

   MiniLight C : minimal global illumination renderer
   Harrison Ainsworth / HXA7241 : 2006-2009

   http://www.hxa.name/minilight/

------------------------------------------------------------------------------*/


#ifndef RandomMwc_h
#define RandomMwc_h


#include "Primitives.h"




/**
 * Simple, fast, good random number generator (Multiply-with-carry).<br/><br/>
 *
 * Perhaps the fastest of any generator that passes the Diehard tests.<br/><br/>
 *
 * @implementation
 * Concatenation of following two 16-bit multiply-with-carry generators
 * x(n)=a*x(n-1)+carry mod 2^16 and y(n)=b*y(n-1)+carry mod 2^16, number and
 * carry packed within the same 32 bit integer. Algorithm recommended by
 * Marsaglia. Copyright (c) 2005, Glenn Rhoads.<br/><br/>
 *
 * <cite>http://web.archive.org/web/20050213041650/http://
 * paul.rutgers.edu/~rhoads/Code/code.html</cite>
 */

struct RandomMwc
{
   udword aSeeds[2];
};

typedef struct RandomMwc RandomMwc;




/* initialisation ----------------------------------------------------------- */

RandomMwc RandomMwcCreate
(
   dword seed
);




/* queries ------------------------------------------------------------------ */

dword RandomMwcDword
(
   RandomMwc*
);

float RandomMwcFloat
(
   RandomMwc*
);




#endif
