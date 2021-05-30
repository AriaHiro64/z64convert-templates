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
#include <z64ovl/oot/shared.h>
#include <z64ovl/helpers.h>
#include <z64ovl/oot/sfx.h>
#include "adult.h"

#define QPT(OFS) (void*)(((char*)(zobj)) + ((OFS) & 0xFFFFFF))
#define QV32(OFS) *(uint32_t*)QPT(OFS)
#define QVLO(OFS) *(uint32_t*)QPT(OFS+4)
#define PLAYER_WATER_DEPTH (zh_get_player((void*)GLOBAL_CONTEXT)->actor.water_surface_dist)
#define ARRAY_COUNT(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

#define  EQUIPPED_GEAR   (AVAL(Z64GL_SAVE_CONTEXT, uint16_t, 0x70))
#define  EQUIPPED_SWORD  (EQUIPPED_GEAR & 0x000F)
#define  EQUIPPED_SHIELD (EQUIPPED_GEAR & 0x00F0)
#define  EQUIPPED_TUNIC  (EQUIPPED_GEAR & 0x0F00)
#define  EQUIPPED_BOOTS  (EQUIPPED_GEAR & 0xF000)

#define  TUNIC_TOPLESS   0x0000
#define  TUNIC_KOKIRI    0x0100
#define  TUNIC_GORON     0x0200
#define  TUNIC_ZORA      0x0300

#define  SWORD_NONE      0x0000
#define  SWORD_KOKIRI    0x0001
#define  SWORD_MASTER    0x0002
#define  SWORD_GORON     0x0003
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 this is static display list sourcery that doesnt move

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MATRIX_SWORD_BACK_A              0x06005000
#define MATRIX_SWORD_BACK_B              0x06005040
#define DL_SWORD_SHEATHED_MATRIX_WRAPPER 0x06005080
#define DL_DF_COMMAND                    0x06005090

void renderinit(void *zobj)
{
    static uint16_t prevTunic = -1;
    uint16_t curTunic = EQUIPPED_TUNIC;
    static uint16_t prevSword = -1;
    uint16_t curSword = EQUIPPED_SWORD;
    
    /* override riggedmesh with one of the available tunics */
    if (curTunic != prevTunic)
    {
        unsigned proxySize = sizeof(proxy_Kokiri);
        const void *proxy = 0;
        void *overwrite = (void*)zh_seg2ram(PROXY_RIGGEDMESH);
        switch (curTunic)
        {
             
            case TUNIC_KOKIRI:
                proxy = proxy_Kokiri;
                break;
            case TUNIC_GORON:
                proxy = proxy_Goron;
                break;
            case TUNIC_ZORA:
                proxy = proxy_Zora;
                break;
            default:
                proxy = proxy_Topless;
                break;
        }
        z_bcopy(proxy, overwrite, proxySize);
        prevTunic = curTunic;
    }
    if (curSword != prevSword)
    {
        switch (curSword)
        {
            case SWORD_NONE:
                QVLO(DL_HILT_2_PROXY) = DL_DF_COMMAND;
                QVLO(DL_BLADE_2_PROXY) = DL_DF_COMMAND;
                QVLO(DL_SHEATH_PROXY) = DL_DF_COMMAND;
                QVLO(DL_SWORD_SHEATHED_MATRIX_WRAPPER) = MATRIX_SWORD_BACK_B;
                break;

           case SWORD_KOKIRI:
                QVLO(DL_HILT_2_PROXY) = DL_HILT_1;
                QVLO(DL_BLADE_2_PROXY) = DL_BLADE_1;
                QVLO(DL_SHEATH_PROXY) = DL_SHEATH_KOKIRI;
                QVLO(DL_SWORD_SHEATHED_MATRIX_WRAPPER) = MATRIX_SWORD_BACK_A;
                break;
            case SWORD_MASTER:
                QVLO(DL_HILT_2_PROXY) = DL_HILT_2;
                QVLO(DL_BLADE_2_PROXY) = DL_BLADE_2;
                QVLO(DL_SHEATH_PROXY) = DL_SHEATH;
                 QVLO(DL_SWORD_SHEATHED_MATRIX_WRAPPER) = MATRIX_SWORD_BACK_B;
                break;
            case SWORD_GORON:
                QVLO(DL_HILT_2_PROXY) = DL_HILT_3;
                QVLO(DL_SHEATH_PROXY) = DL_SHEATH_BIGGORON;
                QVLO(DL_SWORD_SHEATHED_MATRIX_WRAPPER) = MATRIX_SWORD_BACK_B;
                break;
        }
        prevSword = curSword;
    }

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

/* TODO updating pointers based on day/night
 *      left as an exercise for the student
 */
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