/*------------------------------------------------------------------------------

   MiniLight C : minimal global illumination renderer
   Harrison Ainsworth / HXA7241 : 2006-2009

   http://www.hxa.name/minilight/

------------------------------------------------------------------------------*/


#include "RandomMwc.h"




/* constants ---------------------------------------------------------------- */

/* default seeds */
static const udword SEEDS[2] = { 521288629u, 362436069u };




/* initialisation ----------------------------------------------------------- */

RandomMwc RandomMwcCreate
(
   dword seed
)
{
   RandomMwc r;
   r.aSeeds[0] = (0 != seed) ? (udword)seed : SEEDS[0];
   r.aSeeds[1] = (0 != seed) ? (udword)seed : SEEDS[1];

   return r;
}




/* queries ------------------------------------------------------------------ */

dword RandomMwcDword
(
   RandomMwc* pR
)
{
   /* Use any pair of non-equal numbers from this list for the two constants:
      18000 18030 18273 18513 18879 19074 19098 19164 19215 19584
      19599 19950 20088 20508 20544 20664 20814 20970 21153 21243
      21423 21723 21954 22125 22188 22293 22860 22938 22965 22974
      23109 23124 23163 23208 23508 23520 23553 23658 23865 24114
      24219 24660 24699 24864 24948 25023 25308 25443 26004 26088
      26154 26550 26679 26838 27183 27258 27753 27795 27810 27834
      27960 28320 28380 28689 28710 28794 28854 28959 28980 29013
      29379 29889 30135 30345 30459 30714 30903 30963 31059 31083 */

   pR->aSeeds[0] = 18000u * (pR->aSeeds[0] & 0xFFFFu) + (pR->aSeeds[0] >> 16);
   pR->aSeeds[1] = 30903u * (pR->aSeeds[1] & 0xFFFFu) + (pR->aSeeds[1] >> 16);

   return (dword)( (pR->aSeeds[0] << 16) + (pR->aSeeds[1] & 0xFFFFu) );
}


float RandomMwcFloat
(
   RandomMwc* pR
)
{
   return (float)((udword)RandomMwcDword( pR )) / 4294967296.0f;
}
