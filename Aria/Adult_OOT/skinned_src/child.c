/* something hacky:
 * force jump from beginning of .text section to
 * the renderinit function in case of reordering
 * or functions not being inlined
 */
void renderinit(void *zobj);
asm(".section .text \n\
   renderinit_wow:  \n\
   j renderinit     \n\
   nop              \n\
");

//#define RENDERINIT_OOT_10U /* building for 10u */

#ifdef RENDERINIT_OOT_10U
#  include <z64ovl/oot/u10.h>
#else
#  include <z64ovl/oot/debug.h>
#endif
#include <z64ovl/helpers.h>
#include <z64ovl/oot/sfx.h>
#include <z64ovl/oot/shared.h>
#include "child.h"

void renderinit(void *zobj)
{

const uint32_t eyesDay[] = {
    TEX_EYES_PNG_0
    , TEX_EYES_PNG_1
    , TEX_EYES_PNG_2
    , TEX_EYES_PNG_3
    , TEX_EYES_PNG_4
    , TEX_EYES_PNG_5
    , TEX_EYES_PNG_6
    , TEX_EYES_PNG_7
};
const uint32_t eyesNight[] = {
    TEX_EYES_NIGHT_PNG_0
    , TEX_EYES_NIGHT_PNG_1
    , TEX_EYES_NIGHT_PNG_2
    , TEX_EYES_NIGHT_PNG_3
    , TEX_EYES_NIGHT_PNG_4
    , TEX_EYES_NIGHT_PNG_5
    , TEX_EYES_NIGHT_PNG_6
    , TEX_EYES_NIGHT_PNG_7
};
int isNight = *(uint32_t*)Z64GL_IS_NIGHT;
static int wasNight = -1;
if (isNight != wasNight)
{
    void *src = eyesDay;
    wasNight = isNight;
    if (isNight)
        src = eyesNight;
    z_bcopy(src, (void*)0x80125FD8, sizeof(eyesDay));
}
}