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

/*#define  PROXY_RIGGEDMESH               0x060109F0
static const uint32_t proxy_riggedmesh[] = {
	0xDE010000, 0x0600EFE8,
	0xDE010000, 0x0600F5E8,
	0xDE010000, 0x0600F9B8,
	0xDE010000, 0x0600FCC8,
	0xDE010000, 0x0600FF20,
	0xDE010000, 0x060101D0,
	0xDE010000, 0x060104E0,
	0xDE010000, 0x06010608,
	0xDE010000, 0x06010668,
	0xDE010000, 0x060106C8,
	0xDE010000, 0x06010730,
	0xDE010000, 0x06010790,
	0xDE010000, 0x060107F0,
	0xDE010000, 0x06010850,
	0xDE010000, 0x060108B0,
	0xDE010000, 0x06010910,
	0xDE010000, 0x06010970,
	0xDE010000, 0x060109D0,
};
static const uint32_t proxy_Kokiri[] = {
	0xDE010000, 0x06010F50,
	0xDE010000, 0x0600F5E8,
	0xDE010000, 0x0600F9B8,
	0xDE010000, 0x0600FCC8,
	0xDE010000, 0x0600FF20,
	0xDE010000, 0x060101D0,
	0xDE010000, 0x060104E0,
	0xDE010000, 0x06012358,
	0xDE010000, 0x06012D58,
	0xDE010000, 0x060131F8,
	0xDE010000, 0x060135D0,
	0xDE010000, 0x06013A20,
	0xDE010000, 0x06013DC0,
	0xDE010000, 0x06014020,
	0xDE010000, 0x060143E0,
	0xDE010000, 0x060147E0,
	0xDE010000, 0x06014918,
	0xDE010000, 0x06015608,
};
static const uint32_t proxy_Goron[] = {
	0xDE010000, 0x06015B78,
	0xDE010000, 0x0600F5E8,
	0xDE010000, 0x0600F9B8,
	0xDE010000, 0x0600FCC8,
	0xDE010000, 0x0600FF20,
	0xDE010000, 0x060101D0,
	0xDE010000, 0x060104E0,
	0xDE010000, 0x06016EA0,
	0xDE010000, 0x06017840,
	0xDE010000, 0x06017CE0,
	0xDE010000, 0x06018078,
	0xDE010000, 0x060184F8,
	0xDE010000, 0x06018898,
	0xDE010000, 0x06018AB8,
	0xDE010000, 0x06018EA8,
	0xDE010000, 0x06019288,
	0xDE010000, 0x060193B8,
	0xDE010000, 0x0601A258,
};
static const uint32_t proxy_Zora[] = {
	0xDE010000, 0x0601A7C0,
	0xDE010000, 0x0600F5E8,
	0xDE010000, 0x0600F9B8,
	0xDE010000, 0x0600FCC8,
	0xDE010000, 0x0600FF20,
	0xDE010000, 0x060101D0,
	0xDE010000, 0x060104E0,
	0xDE010000, 0x0601BBD0,
	0xDE010000, 0x0601C5D0,
	0xDE010000, 0x0601CBC0,
	0xDE010000, 0x0601CEE0,
	0xDE010000, 0x0601D2D0,
	0xDE010000, 0x0601D670,
	0xDE010000, 0x0601D850,
	0xDE010000, 0x0601DC00,
	0xDE010000, 0x0601E000,
	0xDE010000, 0x0601E138,
	0xDE010000, 0x0601E6F8,
};

#define  EQUIPPED_GEAR   (AVAL(Z64GL_SAVE_CONTEXT, uint16_t, 0x70))
#define  EQUIPPED_SWORD  (EQUIPPED_GEAR & 0x000F)
#define  EQUIPPED_SHIELD (EQUIPPED_GEAR & 0x00F0)
#define  EQUIPPED_TUNIC  (EQUIPPED_GEAR & 0x0F00)
#define  EQUIPPED_BOOTS  (EQUIPPED_GEAR & 0xF000)

#define  TUNIC_KOKIRI    0x0100
#define  TUNIC_GORON     0x0200
#define  TUNIC_ZORA      0x0300 */

void renderinit(void *zobj)
{
/*    static uint16_t prevTunic = -1;
    uint16_t curTunic = EQUIPPED_TUNIC;*/
    
    /* override riggedmesh with one of the available tunics */
    /*if (curTunic != prevTunic)
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
        }
        z_bcopy(proxy, overwrite, proxySize);
        prevTunic = curTunic; 
    }*/
}