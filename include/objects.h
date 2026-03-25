/* NetHack 3.7	objects.h	$NHDT-Date: 1749097644 2025/06/04 20:27:24 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.30 $ */
/* Copyright (c) Mike Threepoint, 1989.                           */
/* NetHack may be freely redistributed.  See license for details. */

/*
   The data in this file is processed multiple times by its inclusion
   in several places in the code. The results depend on the definition
   of the following:
     OBJECTS_ENUM        to construct object onames enum entries (decl.h).
     OBJECTS_DESCR_INIT to construct obj_descr[] array entries (objects.c).
     OBJECTS_INIT       to construct objects[] array entries (objects.c).
*/

#ifndef NoDes
#define NoDes (char *) 0 /* less visual distraction for 'no description' */
#endif

#ifndef lint
#define HARDGEM(n) (n >= 8)
#else
#define HARDGEM(n) (0)
#endif

/*
 * Note...
 *  OBJECTS() currently has 15 parameters; it more become needed, some
 *  will need to be combined the way BITS() is used, because compilers
 *  are allowed to impose a limit of 15.
 */

#if defined(OBJECTS_DESCR_INIT)
#define OBJ(name,desc)  name, desc
#define OBJECT(obj,bits,prp,sym,prob,dly,wt, \
               cost,sdam,ldam,oc1,oc2,nut,color,sn)  { obj }
#define MARKER(tag,sn) /*empty*/

#elif defined(OBJECTS_INIT)
/* notes: 'sub' was once a bitfield but got changed to separate schar when
   it was overloaded to hold negative weapon skill indices; the first zero
   is padding for oc_prediscovered which has variable init at run-time;
   the second zero is oc_spare1 for padding between oc_tough and oc_dir */
#define BITS(nmkn,mrg,uskn,ctnr,mgc,chrg,uniq,nwsh,big,tuf,dir,sub,mtrl) \
    nmkn,mrg,uskn,0,mgc,chrg,uniq,nwsh,big,tuf,0,dir,mtrl,sub /*cpp fodder*/
/* note: 0UL-1UL is a method of expressing the largest possible
   unsigned long value whilst working around a false-positive warning
   in Microsoft Visual C (which assumes that a negative number was
   intended despite the explicit U suffix) */
#define OBJECT(obj,bits,prp,sym,prob,dly,wt,        \
               cost,sdam,ldam,oc1,oc2,nut,color,sn) \
  { 0, 0, (char *) 0, bits, prp, sym, dly, color, prob, wt, \
    cost, sdam, ldam, oc1, oc2, nut, (0UL-1UL), 0, (0UL-1UL), 0 }
#define MARKER(tag,sn) /*empty*/

#elif defined(OBJECTS_ENUM)
#define OBJ(name,desc)
#define OBJECT(obj,bits,prp,sym,prob,dly,wt,        \
               cost,sdam,ldam,oc1,oc2,nut,color,sn) \
    sn
#define MARKER(tag,sn) tag = sn,

#elif defined(DUMP_ENUMS)
#define OBJ(name,desc)
#define OBJECT(obj,bits,prp,sym,prob,dly,wt,        \
               cost,sdam,ldam,oc1,oc2,nut,color,sn) \
  { sn, #sn }
#define MARKER(tag,sn) /*empty*/

#else
#error Unproductive inclusion of objects.h
#endif  /* OBJECTS_DESCR_INIT || OBJECTS_INIT || OBJECTS_ENUM */

#define GENERIC(desc, class, gen_enum) \
    OBJECT(OBJ("generic " desc, desc),                                  \
           BITS(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, P_NONE, 0),            \
           0, class, 0, 0, 0, 0, 0, 0, 0, 0, 0, CLR_GRAY, gen_enum)

/* dummy object[0] -- description [2nd arg] *must* be NULL */
OBJECT(OBJ("objeto extraño", NoDes),
       BITS(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, 0),
       0, ILLOBJ_CLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, STRANGE_OBJECT),
/* slots [1] through [MAXOCLASSES-1] are indexed by class; some are
   used for display purposes, most aren't used; none are actual objects;
   note that 'real' strange object is in slot [0] but ILLOBJ_CLASS is 1
   so we add a dummy for it in slot [1] to simplify accessing the rest;
   there isn't any entry for RANDOM_CLASS (0) */
GENERIC("extraño",    ILLOBJ_CLASS,  GENERIC_ILLOBJ),  /* [1] */
GENERIC("arma",     WEAPON_CLASS,  GENERIC_WEAPON),  /* [2] */
GENERIC("armadura",      ARMOR_CLASS,   GENERIC_ARMOR),   /* [3] */
GENERIC("anillo",       RING_CLASS,    GENERIC_RING),    /* [4] */
GENERIC("amuleto",     AMULET_CLASS,  GENERIC_AMULET),  /* [5] */
GENERIC("herramienta",       TOOL_CLASS,    GENERIC_TOOL),    /* [6] */
GENERIC("comida",       FOOD_CLASS,    GENERIC_FOOD),    /* [7] */
GENERIC("poción",     POTION_CLASS,  GENERIC_POTION),  /* [8] */
GENERIC("pergamino",     SCROLL_CLASS,  GENERIC_SCROLL),  /* [9] */
GENERIC("libro de hechizos",  SPBOOK_CLASS,  GENERIC_SPBOOK),  /* [10] */
GENERIC("varita",       WAND_CLASS,    GENERIC_WAND),    /* [11] */
GENERIC("moneda",       COIN_CLASS,    GENERIC_COIN),    /* [12] */
GENERIC("gema",        GEM_CLASS,     GENERIC_GEM),     /* [13] */
GENERIC("roca grande", ROCK_CLASS,    GENERIC_ROCK),    /* [14] bldr+statue */
GENERIC("bola de hierro",  BALL_CLASS,    GENERIC_BALL),    /* [15] */
GENERIC("cadena de hierro", CHAIN_CLASS,   GENERIC_CHAIN),   /* [16] */
GENERIC("veneno",      VENOM_CLASS,   GENERIC_VENOM),   /* [17] */
#undef GENERIC
/* FIRST_OBJECT: it would be simpler just to use MARKER(FIRST_OBJECT,ARROW)
   below but that is vulnerable to neglecting to update the marker enum
   after inserting something in front of arrow */
MARKER(LAST_GENERIC, GENERIC_VENOM)
MARKER(FIRST_OBJECT, LAST_GENERIC + 1)
/* this definition of FIRST_OBJECT advances the default value for next enum;
   backtrack to fix that, otherwise ARROW and the rest would be off by 1 */
MARKER(OBJCLASS_HACK, FIRST_OBJECT - 1)

/* weapons ... */
#define WEAPON(name,desc,kn,mg,bi,prob,wt,                          \
               cost,sdam,ldam,hitbon,typ,sub,metal,color,sn)        \
    OBJECT(OBJ(name,desc),                                          \
           BITS(kn, mg, 1, 0, 0, 1, 0, 0, bi, 0, typ, sub, metal),  \
           0, WEAPON_CLASS, prob, 0, wt,                            \
           cost, sdam, ldam, hitbon, 0, wt, color,sn)
#define PROJECTILE(name,desc,kn,prob,wt,                            \
                   cost,sdam,ldam,hitbon,metal,sub,color,sn)        \
    OBJECT(OBJ(name,desc),                                          \
           BITS(kn, 1, 1, 0, 0, 1, 0, 0, 0, 0, PIERCE, sub, metal), \
           0, WEAPON_CLASS, prob, 0, wt,                            \
           cost, sdam, ldam, hitbon, 0, wt, color, sn)
#define BOW(name,desc,kn,prob,wt,cost,hitbon,metal,sub,color,sn)    \
    OBJECT(OBJ(name,desc),                                          \
           BITS(kn, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, sub, metal),      \
           0, WEAPON_CLASS, prob, 0, wt,                            \
           cost, 2, 2, hitbon, 0, wt, color, sn)

/* Note: for weapons that don't do an even die of damage (ex. 2-7 or 3-18)
   the extra damage is added on in weapon.c, not here! */

/* weapon strike mode overloads the oc_dir field */
#define P PIERCE
#define S SLASH
#define B WHACK

/* missiles; materiel reflects the arrowhead, not the shaft */
PROJECTILE("flecha", NoDes,
           1, 55, 1, 2, 6, 6, 0,        IRON, -P_BOW, HI_METAL,
                                                        ARROW),
PROJECTILE("flecha élfica", "flecha rúnica",
           0, 20, 1, 2, 7, 6, 0,        WOOD, -P_BOW, HI_WOOD,
                                                        ELVEN_ARROW),
PROJECTILE("flecha orca", "flecha cruda",
           0, 20, 1, 2, 5, 6, 0,        IRON, -P_BOW, CLR_BLACK,
                                                        ORCISH_ARROW),
PROJECTILE("flecha de plata", NoDes,
           1, 12, 1, 5, 6, 6, 0,        SILVER, -P_BOW, HI_SILVER,
                                                        SILVER_ARROW),
PROJECTILE("ya", "flecha de bambú",
           0, 15, 1, 4, 7, 7, 1,        METAL, -P_BOW, HI_METAL, YA),
PROJECTILE("virote de ballesta", NoDes,
           1, 55, 1, 2, 4, 6, 0,        IRON, -P_CROSSBOW, HI_METAL,
                                                        CROSSBOW_BOLT),

/* missiles that don't use a launcher */
WEAPON("dardo", NoDes,
       1, 1, 0, 60,   1,   2,  3,  2, 0, P,   -P_DART, IRON, HI_METAL,
                                                        DART),
WEAPON("shuriken", "estrella arrojadiza",
       0, 1, 0, 35,   1,   5,  8,  6, 2, P,   -P_SHURIKEN, IRON, HI_METAL,
                                                        SHURIKEN),
WEAPON("bumerán", NoDes,
       1, 1, 0, 15,   5,  20,  9,  9, 0, 0,   -P_BOOMERANG, WOOD, HI_WOOD,
                                                        BOOMERANG),

/* spears [note: javelin used to have a separate skill from spears,
   because the latter are primarily stabbing weapons rather than
   throwing ones; but for playability, they've been merged together
   under spear skill and spears can now be thrown like javelins] */
WEAPON("lanza", NoDes,
       1, 1, 0, 50,  30,   3,  6,  8, 0, P,   P_SPEAR, IRON, HI_METAL,
                                                        SPEAR),
WEAPON("lanza élfica", "lanza rúnica",
       0, 1, 0, 10,  30,   3,  7,  8, 0, P,   P_SPEAR, WOOD, HI_WOOD,
                                                        ELVEN_SPEAR),
WEAPON("lanza orca", "lanza cruda",
       0, 1, 0, 13,  30,   3,  5,  8, 0, P,   P_SPEAR, IRON, CLR_BLACK,
                                                        ORCISH_SPEAR),
WEAPON("lanza enana", "lanza robusta",
       0, 1, 0, 12,  35,   3,  8,  8, 0, P,   P_SPEAR, IRON, HI_METAL,
                                                        DWARVISH_SPEAR),
WEAPON("lanza de plata", NoDes,
       1, 1, 0,  2,  36,  40,  6,  8, 0, P,   P_SPEAR, SILVER, HI_SILVER,
                                                        SILVER_SPEAR),
WEAPON("jabalina", "lanza arrojadiza",
       0, 1, 0, 10,  20,   3,  6,  6, 0, P,   P_SPEAR, IRON, HI_METAL,
                                                        JAVELIN),

/* spearish; doesn't stack, not intended to be thrown */
WEAPON("tridente", NoDes,
       1, 0, 0,  8,  25,   5,  6,  4, 0, P,   P_TRIDENT, IRON, HI_METAL,
                                                        TRIDENT),
        /* +1 small, +2d4 large */

/* blades; all stack */
WEAPON("daga", NoDes,
       1, 1, 0, 30,  10,   4,  4,  3, 2, P,   P_DAGGER, IRON, HI_METAL,
                                                        DAGGER),
WEAPON("daga élfica", "daga rúnica",
       0, 1, 0, 10,  10,   4,  5,  3, 2, P,   P_DAGGER, WOOD, HI_WOOD,
                                                        ELVEN_DAGGER),
WEAPON("daga orca", "daga cruda",
       0, 1, 0, 12,  10,   4,  3,  3, 2, P,   P_DAGGER, IRON, CLR_BLACK,
                                                        ORCISH_DAGGER),
WEAPON("daga de plata", NoDes,
       1, 1, 0,  3,  12,  40,  4,  3, 2, P,   P_DAGGER, SILVER, HI_SILVER,
                                                        SILVER_DAGGER),
WEAPON("athame", NoDes,
       1, 1, 0,  0,  10,   4,  4,  3, 2, S,   P_DAGGER, IRON, HI_METAL,
                                                        ATHAME),
WEAPON("bisturí", NoDes,
       1, 1, 0,  0,   5,   6,  3,  3, 2, S,   P_KNIFE, METAL, HI_METAL,
                                                        SCALPEL),
WEAPON("cuchillo", NoDes,
       1, 1, 0, 20,   5,   4,  3,  2, 0, P|S, P_KNIFE, IRON, HI_METAL,
                                                        KNIFE),
WEAPON("estileto", NoDes,
       1, 1, 0,  5,   5,   4,  3,  2, 0, P|S, P_KNIFE, IRON, HI_METAL,
                                                        STILETTO),
/* 3.6: worm teeth and crysknives now stack;
   when a stack of teeth is enchanted at once, they fuse into one crysknife;
   when a stack of crysknives drops, the whole stack reverts to teeth */
/* 3.7: change crysknife from MINERAL to BONE and worm tooth from 0 to BONE */
WEAPON("diente de gusano", NoDes,
       1, 1, 0,  0,  20,   2,  2,  2, 0, 0,   P_KNIFE, BONE, CLR_WHITE,
                                                        WORM_TOOTH),
WEAPON("crysknife", NoDes,
       1, 1, 0,  0,  20, 100, 10, 10, 3, P,   P_KNIFE, BONE, CLR_WHITE,
                                                        CRYSKNIFE),

/* axes */
WEAPON("hacha", NoDes,
       1, 0, 0, 40,  60,   8,  6,  4, 0, S,   P_AXE, IRON, HI_METAL,
                                                        AXE),
WEAPON("hacha de batalla", "hacha de doble filo",       /* "double-bitted"? */
       0, 0, 1, 10, 120,  40,  8,  6, 0, S,   P_AXE, IRON, HI_METAL,
                                                        BATTLE_AXE),

/* swords */
WEAPON("espada corta", NoDes,
       1, 0, 0,  8,  30,  10,  6,  8, 0, P,   P_SHORT_SWORD, IRON, HI_METAL,
                                                        SHORT_SWORD),
WEAPON("espada corta élfica", "espada corta rúnica",
       0, 0, 0,  2,  30,  10,  8,  8, 0, P,   P_SHORT_SWORD, WOOD, HI_WOOD,
                                                        ELVEN_SHORT_SWORD),
WEAPON("espada corta orca", "espada corta cruda",
       0, 0, 0,  3,  30,  10,  5,  8, 0, P,   P_SHORT_SWORD, IRON, CLR_BLACK,
                                                        ORCISH_SHORT_SWORD),
WEAPON("espada corta enana", "espada corta ancha",
       0, 0, 0,  2,  30,  10,  7,  8, 0, P,   P_SHORT_SWORD, IRON, HI_METAL,
                                                        DWARVISH_SHORT_SWORD),
WEAPON("cimitarra", "espada curva",
       0, 0, 0, 15,  40,  15,  8,  8, 0, S,   P_SABER, IRON, HI_METAL,
                                                        SCIMITAR),
WEAPON("sable de plata", NoDes,
       1, 0, 0,  6,  40,  75,  8,  8, 0, S,   P_SABER, SILVER, HI_SILVER,
                                                        SILVER_SABER),
WEAPON("mandoble", NoDes,
       1, 0, 0,  8,  70,  10,  4,  6, 0, S,   P_BROAD_SWORD, IRON, HI_METAL,
                                                        BROADSWORD),
        /* +d4 small, +1 large */
WEAPON("mandoble élfico", "mandoble rúnico",
       0, 0, 0,  4,  70,  10,  6,  6, 0, S,   P_BROAD_SWORD, WOOD, HI_WOOD,
                                                        ELVEN_BROADSWORD),
        /* +d4 small, +1 large */
WEAPON("espada larga", NoDes,
       1, 0, 0, 50,  40,  15,  8, 12, 0, S,   P_LONG_SWORD, IRON, HI_METAL,
                                                        LONG_SWORD),
WEAPON("espada a dos manos", NoDes,
       1, 0, 1, 22, 150,  50, 12,  6, 0, S,   P_TWO_HANDED_SWORD,
                                                            IRON, HI_METAL,
                                                        TWO_HANDED_SWORD),
        /* +2d6 large */
WEAPON("katana", "espada samurái",
       0, 0, 0,  4,  40,  80, 10, 12, 1, S,   P_LONG_SWORD, IRON, HI_METAL,
                                                        KATANA),
/* special swords set up for artifacts */
WEAPON("tsurugi", "espada samurái larga",
       0, 0, 1,  0,  60, 500, 16,  8, 2, S,   P_TWO_HANDED_SWORD,
                                                            METAL, HI_METAL,
                                                        TSURUGI),
        /* +2d6 large */
WEAPON("espada rúnica", "mandoble rúnico",
       0, 0, 0,  0,  40, 300,  4,  6, 0, S,   P_BROAD_SWORD, IRON, CLR_BLACK,
                                                        RUNESWORD),
        /* +d4 small, +1 large; Stormbringer: +5d2 +d8 from level drain */

/* polearms */
/* spear-type */
WEAPON("partisana", "alabarda vulgar",
       0, 0, 1,  5,  80,  10,  6,  6, 0, P,   P_POLEARMS, IRON, HI_METAL,
                                                        PARTISAN),
        /* +1 large */
WEAPON("ranseur", "alabarda con empuñadura",
       0, 0, 1,  5,  50,   6,  4,  4, 0, P,   P_POLEARMS, IRON, HI_METAL,
                                                        RANSEUR),
        /* +d4 both */
WEAPON("spetum", "alabarda bifurcada",
       0, 0, 1,  5,  50,   5,  6,  6, 0, P,   P_POLEARMS, IRON, HI_METAL,
                                                        SPETUM),
        /* +1 small, +d6 large */
WEAPON("gladio", "alabarda de un filo",
       0, 0, 1,  8,  75,   6,  6, 10, 0, S,   P_POLEARMS, IRON, HI_METAL,
                                                        GLAIVE),
/* axe-type */
WEAPON("alabarda", "hacha de asta angular",
       0, 0, 1,  8, 150,  10, 10,  6, 0, P|S, P_POLEARMS, IRON, HI_METAL,
                                                        HALBERD),
        /* +1d6 large */
WEAPON("barda", "hacha de asta larga",
       0, 0, 1,  4, 120,   7,  4,  4, 0, S,   P_POLEARMS, IRON, HI_METAL,
                                                        BARDICHE),
        /* +1d4 small, +2d4 large */
WEAPON("voulga", "cuchilla de asta",
       0, 0, 1,  4, 125,   5,  4,  4, 0, S,   P_POLEARMS, IRON, HI_METAL,
                                                        VOULGE),
        /* +d4 both */
/* curved/hooked */
WEAPON("hoz de asta", "hoz de guerra",
       0, 0, 1,  6,  60,   5,  6,  8, 0, P|S, P_POLEARMS, IRON, HI_METAL,
                                                        FAUCHARD),
WEAPON("guisarma", "gancho de poda",
       0, 0, 1,  6,  80,   5,  4,  8, 0, S,   P_POLEARMS, IRON, HI_METAL,
                                                        GUISARME),
        /* +1d4 small */
WEAPON("guisarma de gancho", "alabarda con gancho",
       0, 0, 1,  4, 120,   7,  4, 10, 0, P|S, P_POLEARMS, IRON, HI_METAL,
                                                        BILL_GUISARME),
        /* +1d4 small */
/* other */
WEAPON("martillo de lucerna", "alabarda tridente",
       0, 0, 1,  5, 150,   7,  4,  6, 0, B|P, P_POLEARMS, IRON, HI_METAL,
                                                        LUCERN_HAMMER),
        /* +1d4 small */
WEAPON("pico de cuervo", "alabarda con pico",
       0, 0, 1,  4, 100,   8,  8,  6, 0, B|P, P_POLEARMS, IRON, HI_METAL,
                                                        BEC_DE_CORBIN),

/* formerly grouped with the polearms but don't use polearms skill;
   lance isn't even two-handed */
WEAPON("pico enano", "pico ancho",
       0, 0, 1, 13, 120,  50, 12,  8, -1, B,  P_PICK_AXE, IRON, HI_METAL,
                                                        DWARVISH_MATTOCK),
WEAPON("lanza", NoDes,
       1, 0, 0,  4, 180,  10,  6,  8, 0, P,   P_LANCE, IRON, HI_METAL,
                                                        LANCE),
        /* +2d10 when jousting with lance as primary weapon,
           +2d2 when jousting with it as secondary when dual wielding */

/* bludgeons */
WEAPON("maza", NoDes,
       1, 0, 0, 40,  30,   5,  6,  6, 0, B,   P_MACE, IRON, HI_METAL,
                                                        MACE),
        /* +1 small */
WEAPON("maza de plata", NoDes,
       1, 0, 0,  2,  36,  60,  6,  6, 0, B,   P_MACE, SILVER, HI_SILVER,
                                                        SILVER_MACE),
        /* +1 small */
WEAPON("estrella de la mañana", NoDes,
       1, 0, 0, 12, 120,  10,  4,  6, 0, B,   P_MORNING_STAR, IRON, HI_METAL,
                                                        MORNING_STAR),
        /* +d4 small, +1 large */
WEAPON("martillo de guerra", NoDes,
       1, 0, 0, 15,  50,   5,  4,  4, 0, B,   P_HAMMER, IRON, HI_METAL,
                                                        WAR_HAMMER),
        /* +1 small */
WEAPON("porra", NoDes,
       1, 0, 0, 12,  30,   3,  6,  3, 0, B,   P_CLUB, WOOD, HI_WOOD,
                                                        CLUB),
WEAPON("manguera de goma", NoDes,
       1, 0, 0,  0,  20,   3,  4,  3, 0, B,   P_WHIP, PLASTIC, CLR_BROWN,
                                                        RUBBER_HOSE),
WEAPON("bordón", "báculo",
       0, 0, 1, 11,  40,   5,  6,  6, 0, B,   P_QUARTERSTAFF, WOOD, HI_WOOD,
                                                        QUARTERSTAFF),
/* two-piece */
WEAPON("aklys", "porra con correa",
       0, 0, 0,  8,  15,   4,  6,  3, 0, B,   P_CLUB, IRON, HI_METAL,
                                                        AKLYS),
WEAPON("mangual", NoDes,
       1, 0, 0, 40,  15,   4,  6,  4, 0, B,   P_FLAIL, IRON, HI_METAL,
                                                        FLAIL),
        /* +1 small, +1d4 large */

/* misc */
WEAPON("látigo", NoDes,
       1, 0, 0,  2,  20,   4,  2,  1, 0, 0,   P_WHIP, LEATHER, CLR_BROWN,
                                                        BULLWHIP),

/* bows */
BOW("arco", NoDes,               1, 24, 30, 60, 0, WOOD, P_BOW, HI_WOOD,
                                                        BOW),
BOW("arco élfico", "arco rúnico",  0, 12, 30, 60, 0, WOOD, P_BOW, HI_WOOD,
                                                        ELVEN_BOW),
BOW("arco orco", "arco crudo", 0, 12, 30, 60, 0, WOOD, P_BOW, CLR_BLACK,
                                                        ORCISH_BOW),
BOW("yumi", "arco largo",        0,  0, 30, 60, 0, WOOD, P_BOW, HI_WOOD,
                                                        YUMI),
BOW("honda", NoDes,             1, 40,  3, 20, 0, LEATHER, P_SLING, HI_LEATHER,
                                                        SLING),
BOW("ballesta", NoDes,          1, 45, 50, 40, 0, WOOD, P_CROSSBOW, HI_WOOD,
                                                        CROSSBOW),

#undef P
#undef S
#undef B

#undef WEAPON
#undef PROJECTILE
#undef BOW

/* armor ... */
        /* IRON denotes ferrous metals, including steel.
         * Only IRON weapons and armor can rust.
         * Only COPPER (including brass) corrodes.
         * Some creatures are vulnerable to SILVER.
         */
#define ARMOR(name,desc,kn,mgc,blk,power,prob,delay,wt,  \
              cost,ac,can,sub,metal,c,sn)                   \
    OBJECT(OBJ(name, desc),                                         \
           BITS(kn, 0, 1, 0, mgc, 1, 0, 0, blk, 0, 0, sub, metal),  \
           power, ARMOR_CLASS, prob, delay, wt,                     \
           cost, 0, 0, 10 - ac, can, wt, c, sn)
#define HELM(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c,sn)  \
    ARMOR(name, desc, kn, mgc, 0, power, prob, delay, wt,  \
          cost, ac, can, ARM_HELM, metal, c, sn)
#define CLOAK(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c,sn)  \
    ARMOR(name, desc, kn, mgc, 0, power, prob, delay, wt,  \
          cost, ac, can, ARM_CLOAK, metal, c,sn)
#define SHIELD(name,desc,kn,mgc,blk,pow,prob,delay,wt,cost,ac,can,metal,c,sn) \
    ARMOR(name, desc, kn, mgc, blk, pow, prob, delay, wt, \
          cost, ac, can, ARM_SHIELD, metal, c,sn)
#define GLOVES(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c,sn)  \
    ARMOR(name, desc, kn, mgc, 0, power, prob, delay, wt,  \
          cost, ac, can, ARM_GLOVES, metal, c,sn)
#define BOOTS(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c,sn)  \
    ARMOR(name, desc, kn, mgc, 0, power, prob, delay, wt,  \
          cost, ac, can, ARM_BOOTS, metal, c,sn)

/* helmets */
HELM("casco de cuero élfico", "sombrero de cuero",
     0, 0,           0,  6, 1,  3,  8,  9, 0, LEATHER, HI_LEATHER,
                                                        ELVEN_LEATHER_HELM),
HELM("casco orco", "casco de hierro",
     0, 0,           0,  6, 1, 30, 10,  9, 0, IRON, CLR_BLACK,
                                                        ORCISH_HELM),
HELM("casco de hierro enano", "casco duro",
     0, 0,           0,  6, 1, 40, 20,  8, 0, IRON, HI_METAL,
                                                        DWARVISH_IRON_HELM),
HELM("fedora", NoDes,
     1, 0,           0,  0, 0,  3,  1, 10, 0, CLOTH, CLR_BROWN,
                                                        FEDORA),
HELM("cornuthaum", "sombrero cónico",
     0, 1, CLAIRVOYANT,  5, 1,  4, 80, 10, 1, CLOTH, CLR_BLUE,
        /* name coined by devteam; confers clairvoyance for wizards,
           blocks clairvoyance if worn by role other than wizard */
                                                        CORNUTHAUM),
HELM("gorro de burro", "sombrero cónico",
     0, 1,           0,  5, 1,  4,  1, 10, 0, CLOTH, CLR_BLUE,
        /* sets Int and Wis to fixed value of 6, so actually provides
           protection against death caused by Int being drained below 3 */
                                                        DUNCE_CAP),
HELM("olla abollada", NoDes,
     1, 0,           0,  2, 0, 10,  8,  9, 0, IRON, CLR_BLACK,
                                                        DENTED_POT),
HELM("casco de brillantez", "casco de cristal",
     0, 1,           0,  6, 1, 40, 50,  9, 0, GLASS, CLR_WHITE,
        /* used to be iron and shuffled as "etched helmet" but required
           special case for the effect of iron armor on spell casting */
                                                        HELM_OF_BRILLIANCE),
/* with shuffled appearances... */
HELM("casco", "casco emplumado",
     0, 0,           0, 10, 1, 30, 10,  9, 0, IRON, HI_METAL,
                                                        HELMET),
HELM("casco de precaución", "casco grabado",
     0, 1,     WARNING,  6, 1, 50, 50,  9, 0, IRON, CLR_GREEN,
                                                        HELM_OF_CAUTION),
HELM("casco de alineamiento opuesto", "casco con cresta",
     0, 1,           0, 10, 1, 50, 50,  9, 0, IRON, HI_METAL,
                                                 HELM_OF_OPPOSITE_ALIGNMENT),
HELM("casco de telepatía", "casco con visera",
     0, 1,     TELEPAT,  4, 1, 50, 50,  9, 0, IRON, HI_METAL,
                                                 HELM_OF_TELEPATHY),

/* suits of armor */
/*
 * There is code in polyself.c that assumes (1) and (2).
 * There is code in obj.h, objnam.c, mon.c, read.c that assumes (2).
 *      (1) The dragon scale mails and the dragon scales are together.
 *      (2) That the order of the dragon scale mail and dragon scales
 *          is the same as order of dragons defined in monst.c.
 */
#define DRGN_ARMR(name,mgc,power,cost,ac,color,snam)  \
    ARMOR(name, NoDes, 1, mgc, 1, power, 0, 5, 40,  \
          cost, ac, 0, ARM_SUIT, DRAGON_HIDE, color,snam)
/* 3.4.1: dragon scale mail reclassified as "magic" since magic is
   needed to create them */
DRGN_ARMR("cota de malla de dragón gris",    1, ANTIMAGIC,  1200, 1, CLR_GRAY,
                                                    GRAY_DRAGON_SCALE_MAIL),
    /* gold DSM is a light source; there's no property for that */
DRGN_ARMR("cota de malla de dragón dorado",    1, 0,           900, 1, HI_GOLD,
                                                    GOLD_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón plateado",  1, REFLECTING, 1200, 1, DRAGON_SILVER,
                                                    SILVER_DRAGON_SCALE_MAIL),
#if 0 /* DEFERRED */
DRGN_ARMR("shimmering dragon scale mail", 1, DISPLACED, 1200, 1, CLR_CYAN,
                                                SHIMMERING_DRAGON_SCALE_MAIL),
#endif
DRGN_ARMR("cota de malla de dragón rojo",     1, FIRE_RES,    900, 1, CLR_RED,
                                                    RED_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón blanco",   1, COLD_RES,    900, 1, CLR_WHITE,
                                                    WHITE_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón naranja",  1, SLEEP_RES,   900, 1, CLR_ORANGE,
                                                    ORANGE_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón negro",   1, DISINT_RES, 1200, 1, CLR_BLACK,
                                                    BLACK_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón azul",    1, SHOCK_RES,   900, 1, CLR_BLUE,
                                                    BLUE_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón verde",   1, POISON_RES,  900, 1, CLR_GREEN,
                                                    GREEN_DRAGON_SCALE_MAIL),
DRGN_ARMR("cota de malla de dragón amarillo",  1, ACID_RES,    900, 1, CLR_YELLOW,
                                                    YELLOW_DRAGON_SCALE_MAIL),
/* For now, only dragons leave these. */
/* 3.4.1: dragon scales left classified as "non-magic"; they confer magical
   properties but are produced "naturally"; affects use as polypile fodder */
DRGN_ARMR("escamas de dragón gris",        0, ANTIMAGIC,   700, 7, CLR_GRAY,
                                                        GRAY_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón dorado",        0, 0,           500, 7, HI_GOLD,
                                                        GOLD_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón plateado",      0, REFLECTING,  700, 7, DRAGON_SILVER,
                                                        SILVER_DRAGON_SCALES),
#if 0 /* DEFERRED */
DRGN_ARMR("shimmering dragon scales",  0, DISPLACED,   700, 7, CLR_CYAN,
                                                    SHIMMERING_DRAGON_SCALES),
#endif
DRGN_ARMR("escamas de dragón rojo",         0, FIRE_RES,    500, 7, CLR_RED,
                                                        RED_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón blanco",       0, COLD_RES,    500, 7, CLR_WHITE,
                                                        WHITE_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón naranja",      0, SLEEP_RES,   500, 7, CLR_ORANGE,
                                                        ORANGE_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón negro",       0, DISINT_RES,  700, 7, CLR_BLACK,
                                                        BLACK_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón azul",        0, SHOCK_RES,   500, 7, CLR_BLUE,
                                                        BLUE_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón verde",       0, POISON_RES,  500, 7, CLR_GREEN,
                                                        GREEN_DRAGON_SCALES),
DRGN_ARMR("escamas de dragón amarillo",      0, ACID_RES,    500, 7, CLR_YELLOW,
                                                        YELLOW_DRAGON_SCALES),
#undef DRGN_ARMR
/* other suits */
ARMOR("armadura de placas", NoDes,
      1, 0, 1,  0, 40, 5, 450, 600,  3, 2,  ARM_SUIT, IRON, HI_METAL,
                                                        PLATE_MAIL),
ARMOR("armadura de placas de cristal", NoDes,
      1, 0, 1,  0, 10, 5, 415, 820,  3, 2,  ARM_SUIT, GLASS, CLR_WHITE,
                                                        CRYSTAL_PLATE_MAIL),
ARMOR("armadura de placas de bronce", NoDes,
      1, 0, 1,  0, 23, 5, 450, 400,  4, 1,  ARM_SUIT, COPPER, HI_COPPER,
                                                        BRONZE_PLATE_MAIL),
ARMOR("cota de malla de segmentos", NoDes,
      1, 0, 1,  0, 57, 5, 400,  80,  4, 1,  ARM_SUIT, IRON, HI_METAL,
                                                        SPLINT_MAIL),
ARMOR("cota de malla con bandas", NoDes,
      1, 0, 1,  0, 66, 5, 350,  90,  4, 1,  ARM_SUIT, IRON, HI_METAL,
                                                        BANDED_MAIL),
ARMOR("túnica de mithril enana", NoDes,
      1, 0, 0,  0, 10, 1, 150, 240,  4, 2,  ARM_SUIT, MITHRIL, HI_SILVER,
                                                        DWARVISH_MITHRIL_COAT),
ARMOR("túnica de mithril élfica", NoDes,
      1, 0, 0,  0, 15, 1, 150, 240,  5, 2,  ARM_SUIT, MITHRIL, HI_SILVER,
                                                        ELVEN_MITHRIL_COAT),
ARMOR("cota de malla", NoDes,
      1, 0, 0,  0, 66, 5, 300,  75,  5, 1,  ARM_SUIT, IRON, HI_METAL,
                                                        CHAIN_MAIL),
ARMOR("cota de malla orca", "cota de malla cruda",
      0, 0, 0,  0, 19, 5, 300,  75,  6, 1,  ARM_SUIT, IRON, CLR_BLACK,
                                                        ORCISH_CHAIN_MAIL),
ARMOR("cota de escamas", NoDes,
      1, 0, 0,  0, 66, 5, 250,  45,  6, 1,  ARM_SUIT, IRON, HI_METAL,
                                                        SCALE_MAIL),
ARMOR("armadura de cuero con tachuelas", NoDes,
      1, 0, 0,  0, 66, 3, 200,  15,  7, 1,  ARM_SUIT, LEATHER, HI_LEATHER,
                                                        STUDDED_LEATHER_ARMOR),
ARMOR("cota de anillos", NoDes,
      1, 0, 0,  0, 66, 5, 250, 100,  7, 1,  ARM_SUIT, IRON, HI_METAL,
                                                        RING_MAIL),
ARMOR("cota de anillos orca", "cota de anillos cruda",
      0, 0, 0,  0, 19, 5, 250,  80,  8, 1,  ARM_SUIT, IRON, CLR_BLACK,
                                                        ORCISH_RING_MAIL),
ARMOR("armadura de cuero", NoDes,
      1, 0, 0,  0, 75, 3, 150,   5,  8, 1,  ARM_SUIT, LEATHER, HI_LEATHER,
                                                        LEATHER_ARMOR),
ARMOR("chaqueta de cuero", NoDes,
      1, 0, 0,  0, 11, 0,  30,  10,  9, 0,  ARM_SUIT, LEATHER, CLR_BLACK,
                                                        LEATHER_JACKET),

/* shirts */
ARMOR("camisa hawaiana", NoDes,
      1, 0, 0,  0,  8, 0,   5,   3, 10, 0,  ARM_SHIRT, CLOTH, CLR_MAGENTA,
                                                        HAWAIIAN_SHIRT),
ARMOR("camiseta", NoDes,
      1, 0, 0,  0,  2, 0,   5,   2, 10, 0,  ARM_SHIRT, CLOTH, CLR_WHITE,
                                                        T_SHIRT),

/* cloaks */
CLOAK("vendas de momia", NoDes,
      1, 0,          0,  0, 0,  3,  2, 10, 1,  CLOTH, CLR_GRAY,
                                                        MUMMY_WRAPPING),
        /* worn mummy wrapping blocks invisibility */
CLOAK("capa élfica", "palidez desvanecida",
      0, 1,    STEALTH,  8, 0, 10, 60,  9, 1,  CLOTH, CLR_BLACK, ELVEN_CLOAK),
CLOAK("capa orca", "manto basto",
      0, 0,          0,  8, 0, 10, 40, 10, 1,  CLOTH, CLR_BLACK,
                                                        ORCISH_CLOAK),
CLOAK("capa enana", "capa con capucha",
      0, 0,          0,  8, 0, 10, 50, 10, 1,  CLOTH, HI_CLOTH,
                                                        DWARVISH_CLOAK),
CLOAK("capa de piel de aceite", "capa resbaladiza",
      0, 0,          0,  8, 0, 10, 50,  9, 2,  CLOTH, HI_CLOTH,
                                                        OILSKIN_CLOAK),
CLOAK("túnica", NoDes,
      1, 1,          0,  6, 0, 15, 50,  8, 2,  CLOTH, CLR_RED, ROBE),
        /* robe was adopted from slash'em, where it's worn as a suit
           rather than as a cloak and there are several variations */
CLOAK("bata de alquimista", "delantal",
      0, 1, POISON_RES, 11, 0, 10, 50,  9, 1,  CLOTH, CLR_WHITE,
                                                        ALCHEMY_SMOCK),
CLOAK("capa de cuero", NoDes,
      1, 0,          0,  8, 0, 15, 40,  9, 1,  LEATHER, CLR_BROWN,
                                                        LEATHER_CLOAK),
/* with shuffled appearances... */
CLOAK("capa de protección", "capa raída",
      0, 1, PROTECTION, 11, 0, 10, 50,  7, 3,  CLOTH, HI_CLOTH,
                                                        CLOAK_OF_PROTECTION),
        /* cloak of protection is now the only item conferring MC 3 */
CLOAK("capa de invisibilidad", "capa de ópera",
      0, 1,      INVIS, 12, 0, 10, 60,  9, 1,  CLOTH, CLR_BRIGHT_MAGENTA,
                                                        CLOAK_OF_INVISIBILITY),
CLOAK("capa de resistencia mágica", "capa ornamental",
      0, 1,  ANTIMAGIC,  6, 0, 10, 60,  9, 1,  CLOTH, CLR_WHITE,
                                                   CLOAK_OF_MAGIC_RESISTANCE),
        /*  'cope' is not a spelling mistake... leave it be */
CLOAK("capa de desplazamiento", "pedazo de tela",
      0, 1,  DISPLACED, 12, 0, 10, 50,  9, 1,  CLOTH, HI_CLOTH,
                                                        CLOAK_OF_DISPLACEMENT),

/* shields */
SHIELD("escudo pequeño", "escudo de madera",
       0, 0, 0,          0,  6, 0,  30,  3, 9, 0,  WOOD, HI_WOOD,
                                                        SMALL_SHIELD),
SHIELD("escudo de resistencia al drenaje", "escudo de madera",
       0, 1, 0,  DRAIN_RES, 12, 0,  30, 50, 9, 0,  WOOD, HI_WOOD,
                                                  SHIELD_OF_DRAIN_RESISTANCE),
SHIELD("escudo de resistencia al choque", "escudo de madera",
       0, 1, 0,  SHOCK_RES, 12, 0,  30, 50, 9, 0,  WOOD, HI_WOOD,
                                                  SHIELD_OF_SHOCK_RESISTANCE),
SHIELD("escudo élfico", "escudo azul y verde",
       0, 0, 0,          0,  2, 0,  40,  7, 8, 0,  WOOD, CLR_GREEN,
                                                        ELVEN_SHIELD),
SHIELD("escudo Uruk-hai", "escudo de mano blanca",
       0, 0, 0,          0,  2, 0,  50,  7, 9, 0,  IRON, HI_METAL,
                                                        URUK_HAI_SHIELD),
SHIELD("escudo orco", "escudo de ojos rojos",
       0, 0, 0,          0,  2, 0,  50,  7, 9, 0,  IRON, CLR_RED,
                                                        ORCISH_SHIELD),
SHIELD("escudo grande", NoDes,
       1, 0, 1,          0,  4, 0, 100, 10, 8, 0,  IRON, HI_METAL,
                                                        LARGE_SHIELD),
SHIELD("escudo redondo enano", "escudo redondo grande",
       0, 0, 0,          0,  3, 0, 100, 10, 8, 0,  IRON, HI_METAL,
                                                        DWARVISH_ROUNDSHIELD),
SHIELD("escudo de reflexión", "escudo de plata pulido",
       0, 1, 0, REFLECTING,  7, 0,  50, 50, 8, 0,  SILVER, HI_SILVER,
                                                        SHIELD_OF_REFLECTION),

/* gloves */
/* These have their color but not material shuffled, so the IRON must
 * stay CLR_BROWN (== HI_LEATHER) even though it's normally either
 * HI_METAL or CLR_BLACK.  All have shuffled descriptions.
 */
GLOVES("guantes de cuero", "guantes viejos",
       0, 0,        0, 15, 1, 10,  8, 9, 0,  LEATHER, HI_LEATHER,
                                                        LEATHER_GLOVES),
GLOVES("guanteletes de torpeza", "guantes acolchados",
       0, 1, FUMBLING,  8, 1, 10, 50, 9, 0,  LEATHER, HI_LEATHER,
                                                    GAUNTLETS_OF_FUMBLING),
GLOVES("guanteletes de poder", "guantes de montar",
       0, 1,        0,  8, 1, 30, 50, 9, 0,  IRON, CLR_BROWN,
                                                    GAUNTLETS_OF_POWER),
GLOVES("guanteletes de destreza", "guantes de esgrima",
       0, 1,        0,  8, 1, 10, 50, 9, 0,  LEATHER, HI_LEATHER,
                                                    GAUNTLETS_OF_DEXTERITY),

/* boots */
BOOTS("botas bajas", "zapatos para caminar",
      0, 0,          0, 23, 2, 10,  8, 9, 0, LEATHER, HI_LEATHER, LOW_BOOTS),
BOOTS("zapatos de hierro", "zapatos duros",
      0, 0,          0,  7, 2, 50, 16, 8, 0, IRON, HI_METAL, IRON_SHOES),
BOOTS("botas altas", "botas de militar",
      0, 0,          0, 14, 2, 20, 12, 8, 0, LEATHER, HI_LEATHER, HIGH_BOOTS),
/* with shuffled appearances... */
BOOTS("botas de velocidad", "botas de combate",
      0, 1,       FAST, 12, 2, 20, 50, 9, 0, LEATHER, HI_LEATHER, SPEED_BOOTS),
BOOTS("botas de caminar sobre el agua", "botas de jungla",
      0, 1,   WWALKING, 12, 2, 15, 50, 9, 0, LEATHER, HI_LEATHER,
                                                        WATER_WALKING_BOOTS),
BOOTS("botas de salto", "botas de senderismo",
      0, 1,    JUMPING, 12, 2, 20, 50, 9, 0, LEATHER, HI_LEATHER,
                                                        JUMPING_BOOTS),
BOOTS("botas élficas", "botas de lodo",
      0, 1,    STEALTH, 12, 2, 15,  8, 9, 0, LEATHER, HI_LEATHER,
                                                        ELVEN_BOOTS),
BOOTS("botas de patear", "botas con hebilla",
      0, 1,          0, 12, 2, 50,  8, 9, 0, IRON, CLR_BROWN,
                                                        KICKING_BOOTS),
        /* CLR_BROWN for same reason as gauntlets of power */
BOOTS("botas de torpeza", "botas de montar",
      0, 1,   FUMBLING, 12, 2, 20, 30, 9, 0, LEATHER, HI_LEATHER,
                                                        FUMBLE_BOOTS),
BOOTS("botas de levitación", "botas de nieve",
      0, 1, LEVITATION, 12, 2, 15, 30, 9, 0, LEATHER, HI_LEATHER,
                                                        LEVITATION_BOOTS),
#undef HELM
#undef CLOAK
#undef SHIELD
#undef GLOVES
#undef BOOTS
#undef ARMOR

/* rings ... */
#define RING(name,stone,power,cost,mgc,spec,mohs,metal,color,sn) \
    OBJECT(OBJ(name, stone),                                          \
           BITS(0, 0, spec, 0, mgc, spec, 0, 0, 0,                    \
                HARDGEM(mohs), 0, P_NONE, metal),                     \
           power, RING_CLASS, 1, 0, 3, cost, 0, 0, 0, 0, 15, color,sn)
RING("adorno", "de madera",
     ADORNED,                  100, 1, 1, 2, WOOD, HI_WOOD, RIN_ADORNMENT),
RING("ganar fuerza", "granito",
     0,                        150, 1, 1, 7, MINERAL, HI_MINERAL,
                                                            RIN_GAIN_STRENGTH),
RING("ganar constitución", "ópalo",
     0,                        150, 1, 1, 7, MINERAL, HI_MINERAL,
                                                        RIN_GAIN_CONSTITUTION),
RING("aumentar precisión", "arcilla",
     0,                        150, 1, 1, 4, MINERAL, CLR_RED,
                                                        RIN_INCREASE_ACCURACY),
RING("aumentar daño", "coral",
     0,                        150, 1, 1, 4, MINERAL, CLR_ORANGE,
                                                        RIN_INCREASE_DAMAGE),
RING("protección", "ónix negro",
     PROTECTION,               100, 1, 1, 7, MINERAL, CLR_BLACK,
                                                        RIN_PROTECTION),
        /* 'PROTECTION' intrinsic enhances MC from worn armor by +1,
           regardless of ring's enchantment; wearing a second ring of
           protection (or even one ring of protection combined with
           cloak of protection) doesn't give a second MC boost */
RING("regeneración", "piedra lunar",
     REGENERATION,             200, 1, 0,  6, MINERAL, HI_MINERAL,
                                                        RIN_REGENERATION),
RING("búsqueda", "ojo de tigre",
     SEARCHING,                200, 1, 0,  6, GEMSTONE, CLR_BROWN,
                                                        RIN_SEARCHING  ),
RING("sigilo", "jade",
     STEALTH,                  100, 1, 0,  6, GEMSTONE, CLR_GREEN,
                                                        RIN_STEALTH),
RING("mantener habilidad", "bronce",
     FIXED_ABIL,               100, 1, 0,  4, COPPER, HI_COPPER,
                                                        RIN_SUSTAIN_ABILITY),
RING("levitación", "ágata",
     LEVITATION,               200, 1, 0,  7, GEMSTONE, CLR_RED,
                                                        RIN_LEVITATION),
RING("hambre", "topacio",
     HUNGER,                   100, 1, 0,  8, GEMSTONE, CLR_CYAN,
                                                        RIN_HUNGER),
RING("agrevantar monstruo", "zafiro",
     AGGRAVATE_MONSTER,        150, 1, 0,  9, GEMSTONE, CLR_BLUE,
                                                        RIN_AGGRAVATE_MONSTER),
RING("conflicto", "rubí",
     CONFLICT,                 300, 1, 0,  9, GEMSTONE, CLR_RED,
                                                        RIN_CONFLICT),
RING("advertencia", "diamante",
     WARNING,                  100, 1, 0, 10, GEMSTONE, CLR_WHITE,
                                                        RIN_WARNING),
RING("resistencia al veneno", "perla",
     POISON_RES,               150, 1, 0,  4, BONE, CLR_WHITE,
                                                        RIN_POISON_RESISTANCE),
RING("resistencia al fuego", "hierro",
     FIRE_RES,                 200, 1, 0,  5, IRON, HI_METAL,
                                                        RIN_FIRE_RESISTANCE),
RING("resistencia al frío", "latón",
     COLD_RES,                 150, 1, 0,  4, COPPER, HI_COPPER,
                                                        RIN_COLD_RESISTANCE),
RING("resistencia al choque", "cobre",
     SHOCK_RES,                150, 1, 0,  3, COPPER, HI_COPPER,
                                                        RIN_SHOCK_RESISTANCE),
RING("acción libre", "retorcido",
     FREE_ACTION,              200, 1, 0,  6, IRON, HI_METAL,
                                                        RIN_FREE_ACTION),
RING("digestión lenta", "acero",
     SLOW_DIGESTION,           200, 1, 0,  8, IRON, HI_METAL,
                                                        RIN_SLOW_DIGESTION),
RING("teletransportación", "plata",
     TELEPORT,                 200, 1, 0,  3, SILVER, HI_SILVER,
                                                        RIN_TELEPORTATION),
RING("control de teletransportación", "oro",
     TELEPORT_CONTROL,         300, 1, 0,  3, GOLD, HI_GOLD,
                                                        RIN_TELEPORT_CONTROL),
RING("polimorfia", "marfil",
     POLYMORPH,                300, 1, 0,  4, BONE, CLR_WHITE,
                                                        RIN_POLYMORPH),
RING("control de polimorfia", "esmeralda",
     POLYMORPH_CONTROL,        300, 1, 0,  8, GEMSTONE, CLR_BRIGHT_GREEN,
                                                        RIN_POLYMORPH_CONTROL),
RING("invisibilidad", "alambre",
     INVIS,                    150, 1, 0,  5, IRON, HI_METAL,
                                                        RIN_INVISIBILITY),
RING("ver invisible", "compromiso",
     SEE_INVIS,                150, 1, 0,  5, IRON, HI_METAL,
                                                        RIN_SEE_INVISIBLE),
RING("protección contra cambiantes de forma", "brillante",
     PROT_FROM_SHAPE_CHANGERS, 100, 1, 0,  5, IRON, CLR_BRIGHT_CYAN,
                                               RIN_PROTECTION_FROM_SHAPE_CHAN),
#undef RING

/* amulets ... - THE Amulet comes last because it is special */
#define AMULET(name,desc,power,prob,sn) \
    OBJECT(OBJ(name, desc),                                            \
           BITS(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, P_NONE, IRON),        \
           power, AMULET_CLASS, prob, 0, 20, 150, 0, 0, 0, 0, 20, HI_METAL, sn)
AMULET("amuleto de PER",                "circular", TELEPAT, 120,
                                                        AMULET_OF_ESP),
MARKER(FIRST_AMULET, AMULET_OF_ESP)
AMULET("amuleto salvavidas",       "esférico", LIFESAVED, 75,
                                                        AMULET_OF_LIFE_SAVING),
AMULET("amuleto de estrangulamiento",          "oval", STRANGLED, 115,
                                                      AMULET_OF_STRANGULATION),
AMULET("amuleto de sueño reparador",    "triangular", SLEEPY, 115,
                                                      AMULET_OF_RESTFUL_SLEEP),
AMULET("amuleto contra veneno",        "piramidal", POISON_RES, 115,
                                                        AMULET_VERSUS_POISON),
AMULET("amuleto de cambio",               "cuadrado", 0, 115,
                                                        AMULET_OF_CHANGE),
AMULET("amuleto de inmutabilidad",          "cóncavo", UNCHANGING, 60,
                                                        AMULET_OF_UNCHANGING),
AMULET("amuleto de reflexión",        "hexagonal", REFLECTING, 75,
                                                        AMULET_OF_REFLECTION),
AMULET("amuleto de respiración mágica", "octogonal", MAGICAL_BREATHING, 75,
                                                  AMULET_OF_MAGICAL_BREATHING),
        /* +2 AC and +2 MC; +2 takes naked hero past 'warded' to 'guarded' */
AMULET("amuleto de protección",         "perforado", PROTECTION, 75,
                                                        AMULET_OF_GUARDING),
        /* cubical: some descriptions are already three dimensional and
           parallelogrammatical (real word!) would be way over the top */
AMULET("amuleto de vuelo",              "cúbico", FLYING, 60,
                                                        AMULET_OF_FLYING),
/* fixed descriptions; description duplication is deliberate;
 * fake one must come before real one because selection for
 * description shuffling stops when a non-magic amulet is encountered
 */
OBJECT(OBJ("imitación barata de plástico del Amuleto de Yendor",
           "Amuleto de Yendor"),
       BITS(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, PLASTIC),
       0, AMULET_CLASS, 0, 0, 20, 0, 0, 0, 0, 0, 1, HI_METAL,
                                                FAKE_AMULET_OF_YENDOR),
OBJECT(OBJ("Amuleto de Yendor", /* note: description == name */
           "Amuleto de Yendor"),
       BITS(0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, MITHRIL),
       0, AMULET_CLASS, 0, 0, 20, 30000, 0, 0, 0, 0, 20, HI_METAL,
                                                AMULET_OF_YENDOR),
MARKER(LAST_AMULET, AMULET_OF_YENDOR)
#undef AMULET

/* tools ... */
/* tools with weapon characteristics come last */
#define TOOL(name,desc,kn,mrg,mgc,chg,prob,wt,cost,mat,color,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(kn, mrg, chg, 0, mgc, chg, 0, 0, 0, 0, 0, P_NONE, mat), \
           0, TOOL_CLASS, prob, 0, wt, cost, 0, 0, 0, 0, wt, color, sn)
#define CONTAINER(name,desc,kn,mgc,chg,prob,wt,cost,mat,color,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(kn, 0, chg, 1, mgc, chg, 0, 0, 0, 0, 0, P_NONE, mat),   \
           0, TOOL_CLASS, prob, 0, wt, cost, 0, 0, 0, 0, wt, color, sn)
#define EYEWEAR(name,desc,kn,prop,prob,wt,cost,mat,color,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(kn, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, mat),         \
           prop, TOOL_CLASS, prob, 0, wt, cost, 0, 0, 0, 0, wt, color, sn)
#define WEPTOOL(name,desc,kn,mgc,bi,prob,wt,cost,sdam,ldam,hitbon,sub, \
                mat,clr,sn)                                             \
    OBJECT(OBJ(name, desc),                                             \
           BITS(kn, 0, 1, 0, mgc, 1, 0, 0, bi, 0, hitbon, sub, mat),    \
CONTAINER("caja grande",       NoDes, 1, 0, 0, 40, 350,   8, WOOD, HI_WOOD,
                                                                LARGE_BOX),
CONTAINER("cofre",           NoDes, 1, 0, 0, 35, 600, 16, WOOD, HI_WOOD,
                                                                CHEST),
CONTAINER("caja de hielo",         NoDes, 1, 0, 0, 5, 900, 42, PLASTIC, CLR_WHITE,
                                                                ICE_BOX),
CONTAINER("saco",           "bolsa", 0, 0, 0, 35, 15,   2, CLOTH, HI_CLOTH,
                                                                SACK),
CONTAINER("saco impermeable",   "bolsa", 0, 0, 0, 5, 15, 100, CLOTH, HI_CLOTH,
                                                                OILSKIN_SACK),
CONTAINER("bolsa de contención", "bolsa", 0, 1, 0, 20, 15, 100, CLOTH, HI_CLOTH,
                                                               BAG_OF_HOLDING),
CONTAINER("bolsa de trucos",  "bolsa", 0, 1, 1, 20, 15, 100, CLOTH, HI_CLOTH,
                                                                BAG_OF_TRICKS),
#undef CONTAINER

/* lock opening tools */
TOOL("llave esquelética",       "llave", 0, 0, 0, 0, 80,  3, 10, IRON, HI_METAL,
                                                                SKELETON_KEY),
TOOL("ganzúa",           NoDes, 1, 0, 0, 0, 60,  4, 20, IRON, HI_METAL,
                                                                LOCK_PICK),
TOOL("tarjeta de crédito",         NoDes, 1, 0, 0, 0, 15,  1, 10, PLASTIC, CLR_WHITE,
                                                                CREDIT_CARD),
/* light sources */
TOOL("vela de sebo",   "vela", 0, 1, 0, 0, 20,  2, 10, WAX, CLR_WHITE,
                                                                TALLOW_CANDLE),
TOOL("vela de cera",      "vela", 0, 1, 0, 0,  5,  2, 20, WAX, CLR_WHITE,
                                                                WAX_CANDLE),
TOOL("farol de latón",       NoDes, 1, 0, 0, 0, 30, 30, 12, COPPER, CLR_YELLOW,
                                                                BRASS_LANTERN),
TOOL("lámpara de aceite",          "lámpara", 0, 0, 0, 0, 45, 20, 10, COPPER, CLR_YELLOW,
                                                                OIL_LAMP),
TOOL("lámpara mágica",        "lámpara", 0, 0, 1, 0, 15, 20, 50, COPPER, CLR_YELLOW,
                                                                MAGIC_LAMP),
/* other tools */
TOOL("cámara cara",    NoDes, 1, 0, 0, 1, 15, 12,200, PLASTIC, CLR_BLACK,
                                                            EXPENSIVE_CAMERA),
TOOL("espejo",   "lupa", 0, 0, 0, 0, 45, 13, 10, GLASS, HI_SILVER,
                                                                MIRROR),
TOOL("bola de cristal", "orbe de vidrio", 0, 0, 1, 1, 15,150, 60, GLASS, HI_GLASS,
                                                                CRYSTAL_BALL),
/* eyewear - tools which can be worn on the face; (!mrg, !chg, !mgc)
   worn lenses don't confer the Blinded property, blindfolds and towels do;
   wet towel can be used as a weapon but is not a weptool and uses obj->spe
   differently from weapons and weptools */
EYEWEAR("lentes",           NoDes, 1,       0,  5,  3, 80, GLASS, HI_GLASS,
                                                                LENSES),
EYEWEAR("venda",        NoDes, 1, BLINDED, 50,  2, 20, CLOTH, CLR_BLACK,
                                                                BLINDFOLD),
EYEWEAR("toalla",            NoDes, 1, BLINDED, 50,  5, 50, CLOTH, CLR_MAGENTA,
                                                                TOWEL),
#undef EYEWEAR

/* still other tools */
TOOL("montura",              NoDes, 1, 0, 0, 0,  5,200,150, LEATHER, HI_LEATHER,
                                                                SADDLE),
TOOL("correa",               NoDes, 1, 0, 0, 0, 65, 12, 20, LEATHER, HI_LEATHER,
                                                                LEASH),
TOOL("estetoscopio",         NoDes, 1, 0, 0, 0, 25,  4, 75, IRON, HI_METAL,
                                                                STETHOSCOPE),
TOOL("kit de enlatado",         NoDes, 1, 0, 0, 1, 15,100, 30, IRON, HI_METAL,
                                                                TINNING_KIT),
TOOL("abrelatas",          NoDes, 1, 0, 0, 0, 35,  4, 30, IRON, HI_METAL,
                                                                TIN_OPENER),
TOOL("lata de grasa",       NoDes, 1, 0, 0, 1, 15, 15, 20, IRON, HI_METAL,
                                                                CAN_OF_GREASE),
TOOL("figurina",            NoDes, 1, 0, 1, 0, 25, 50, 80, MINERAL, HI_MINERAL,
                                                                FIGURINE),
        /* monster type specified by obj->corpsenm */
TOOL("marcador mágico",        NoDes, 1, 0, 1, 1, 15,  2, 50, PLASTIC, CLR_RED,
                                                                MAGIC_MARKER),
/* traps */
TOOL("mina terrestre",           NoDes, 1, 0, 0, 0, 0, 200,180, IRON, CLR_RED,
                                                                LAND_MINE),
TOOL("trampa para osos",            NoDes, 1, 0, 0, 0, 0, 200, 60, IRON, HI_METAL,
                                                                BEARTRAP),
/* instruments;
   "If tin whistles are made out of tin, what do they make foghorns out of?" */
TOOL("silbato de lata",    "silbato", 0, 0, 0, 0,100, 3, 10, METAL, HI_METAL,
                                                                TIN_WHISTLE),
TOOL("silbato mágico",  "silbato", 0, 0, 1, 0, 30, 3, 10, METAL, HI_METAL,
                                                                MAGIC_WHISTLE),
TOOL("flauta de madera",     "flauta", 0, 0, 0, 0,  4, 5, 12, WOOD, HI_WOOD,
                                                                WOODEN_FLUTE),
TOOL("flauta mágica",      "flauta", 0, 0, 1, 1,  2, 5, 36, WOOD, HI_WOOD,
                                                                MAGIC_FLUTE),
TOOL("cuerno trabajado",       "cuerno", 0, 0, 0, 0,  5, 18, 15, BONE, CLR_WHITE,
                                                                TOOLED_HORN),
TOOL("cuerno de hielo",        "cuerno", 0, 0, 1, 1,  2, 18, 50, BONE, CLR_WHITE,
                                                                FROST_HORN),
TOOL("cuerno de fuego",         "cuerno", 0, 0, 1, 1,  2, 18, 50, BONE, CLR_WHITE,
                                                                FIRE_HORN),
TOOL("cuerno de la abundancia",    "cuerno", 0, 0, 1, 1,  2, 18, 50, BONE, CLR_WHITE,
                                                            HORN_OF_PLENTY),
        /* horn, but not an instrument */
TOOL("arpa de madera",       "arpa", 0, 0, 0, 0,  4, 30, 50, WOOD, HI_WOOD,
                                                                WOODEN_HARP),
TOOL("arpa mágica",        "arpa", 0, 0, 1, 1,  2, 30, 50, WOOD, HI_WOOD,
                                                                MAGIC_HARP),
TOOL("campana",                NoDes, 1, 0, 0, 0,  2, 30, 50, COPPER, HI_COPPER,
                                                                BELL),
TOOL("corneta",               NoDes, 1, 0, 0, 0,  4, 10, 15, COPPER, HI_COPPER,
                                                                BUGLE),
TOOL("tambor de cuero",      "tambor", 0, 0, 0, 0,  4, 25, 25, LEATHER, HI_LEATHER,
                                                                LEATHER_DRUM),
TOOL("tambor de terremoto","tambor", 0, 0, 1, 1,  2, 25, 25, LEATHER, HI_LEATHER,
                                                          DRUM_OF_EARTHQUAKE),
/* tools useful as weapons */
WEPTOOL("pico-azada", NoDes,
        1, 0, 0, 20, 100,  50,  6,  3, WHACK,  P_PICK_AXE, IRON, HI_METAL,
                                                                PICK_AXE),
WEPTOOL("gancho de agarre", NoDes,
        1, 0, 0,  5,  30,  50,  2,  6, WHACK,  P_FLAIL,    IRON, HI_METAL,
                                                             GRAPPLING_HOOK),
WEPTOOL("cuerno de unicornio", NoDes,
        1, 1, 1,  0,  20, 100, 12, 12, PIERCE, P_UNICORN_HORN,
                                                           BONE, CLR_WHITE,
                                                                UNICORN_HORN),
        /* 3.4.1: unicorn horn left classified as "magic" */
/* two unique tools;
 * not artifacts, despite the comment which used to be here
 */
OBJECT(OBJ("Candelabro de Invocación", "candelabro"),
       BITS(0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, P_NONE, GOLD),
       0, TOOL_CLASS, 0, 0, 10, 5000, 0, 0, 0, 0, 200, HI_GOLD,
                                                   CANDELABRUM_OF_INVOCATION),
OBJECT(OBJ("Campana de Apertura", "campana de plata"),
       BITS(0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, P_NONE, SILVER),
       0, TOOL_CLASS, 0, 0, 10, 5000, 0, 0, 0, 0, 50, HI_SILVER,
                                                   BELL_OF_OPENING),
#undef TOOL
#undef WEPTOOL

/* Comestibles ... */
#define FOOD(name, prob, delay, wt, unk, tin, nutrition, color, sn) \
    OBJECT(OBJ(name, NoDes),                                            \
           BITS(1, 1, unk, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, tin), 0,     \
           FOOD_CLASS, prob, delay, wt, nutrition / 20 + 5, 0, 0, 0, 0, \
           nutrition, color, sn)
/* All types of food (except tins & corpses) must have a delay of at least 1.
 * Delay on corpses is computed and is weight dependent.
 * Domestic pets prefer tripe rations above all others.
 * Fortune cookies can be read, using them up without ingesting them.
 * Carrots improve your vision.
 * +0 tins contain monster meat.
 * +1 tins (of spinach) make you stronger (like Popeye).
 * Meatballs/sticks/rings are only created from objects via stone to flesh.
 */
/* meat */
FOOD("ración de tripas",        140,  2, 10, 0, FLESH, 200, CLR_BROWN,
                                                        TRIPE_RATION),
FOOD("cadáver",                0,  1,  0, 0, FLESH,   0, CLR_BROWN,
                                                        CORPSE),
FOOD("huevo",                  85,  1,  1, 1, FLESH,  80, CLR_WHITE,
                                                        EGG),
FOOD("albóndiga",              0,  1,  1, 0, FLESH,   5, CLR_BROWN,
                                                        MEATBALL),
FOOD("palito de carne",            0,  1,  1, 0, FLESH,   5, CLR_BROWN,
                                                        MEAT_STICK),
/* formerly "huge chunk of meat" */
FOOD("albóndiga enorme",     0, 20,400, 0, FLESH,2000, CLR_BROWN,
                                                        ENORMOUS_MEATBALL),
/* special case because it's not mergeable */
OBJECT(OBJ("anillo de carne", NoDes),
       BITS(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, FLESH),
FOOD("glóbulo de babosa gris",     0,  2, 20, 0, FLESH,  20, CLR_GRAY,
                                                       GLOB_OF_GRAY_OOZE),
FOOD("glóbulo de pudín marrón", 0,  2, 20, 0, FLESH,  20, CLR_BROWN,
                                                       GLOB_OF_BROWN_PUDDING),
FOOD("glóbulo de lima verde",   0,  2, 20, 0, FLESH,  20, CLR_GREEN,
                                                       GLOB_OF_GREEN_SLIME),
FOOD("glóbulo de pudín negro", 0,  2, 20, 0, FLESH,  20, CLR_BLACK,
                                                       GLOB_OF_BLACK_PUDDING),
/* ... */

/* fruits & veggies */
FOOD("fronda de alga",            0,  1,  1, 0, VEGGY,  30, CLR_GREEN, KELP_FROND),
FOOD("hoja de eucalipto",       3,  1,  1, 0, VEGGY,   1, CLR_GREEN,
                                                          EUCALYPTUS_LEAF),
FOOD("manzana",                15,  1,  2, 0, VEGGY,  50, CLR_RED, APPLE),
FOOD("naranja",               10,  1,  2, 0, VEGGY,  80, CLR_ORANGE, ORANGE),
FOOD("pera",                 10,  1,  2, 0, VEGGY,  50, CLR_BRIGHT_GREEN,
                                                          PEAR),
FOOD("melón",                10,  1,  5, 0, VEGGY, 100, CLR_BRIGHT_GREEN,
                                                          MELON),
FOOD("plátano",               10,  1,  2, 0, VEGGY,  80, CLR_YELLOW, BANANA),
FOOD("zanahoria",               15,  1,  2, 0, VEGGY,  50, CLR_ORANGE, CARROT),
FOOD("ramita de acónito",    7,  1,  1, 0, VEGGY,  40, CLR_GREEN,
                                                          SPRIG_OF_WOLFSBANE),
FOOD("diente de ajo",       7,  1,  1, 0, VEGGY,  40, CLR_WHITE,
                                                          CLOVE_OF_GARLIC),
/* name of slime mold is changed based on player's OPTION=fruit:something
   and bones data might have differently named ones from prior games */
FOOD("moho viscoso",           75,  1,  5, 0, VEGGY, 250, HI_ORGANIC,
                                                          SLIME_MOLD),

/* people food */
FOOD("trozo de jalea real",   0,  1,  2, 0, VEGGY, 200, CLR_YELLOW,
                                                        LUMP_OF_ROYAL_JELLY),
FOOD("tarta de crema",            25,  1, 10, 0, VEGGY, 100, CLR_WHITE, CREAM_PIE),
FOOD("barra de caramelo",            13,  1,  2, 0, VEGGY, 100, CLR_BRIGHT_BLUE,
                                                                CANDY_BAR),
FOOD("galleta de la fortuna",       55,  1,  1, 0, VEGGY,  40, CLR_YELLOW,
                                                              FORTUNE_COOKIE),
FOOD("panqueque",              25,  2,  2, 0, VEGGY, 200, CLR_YELLOW, PANCAKE),
FOOD("oblea de lembas",         20,  2,  5, 0, VEGGY, 800, CLR_WHITE,
                                                                LEMBAS_WAFER),
FOOD("ración de cram",          20,  3, 15, 0, VEGGY, 600, HI_ORGANIC,
                                                                CRAM_RATION),
FOOD("ración de comida",         380,  5, 20, 0, VEGGY, 800, HI_ORGANIC,
                                                                FOOD_RATION),
FOOD("Ración-K",              0,  1, 10, 0, VEGGY, 400, HI_ORGANIC, K_RATION),
FOOD("Ración-C",              0,  1, 10, 0, VEGGY, 300, HI_ORGANIC, C_RATION),
/* tins have type specified by obj->spe (+1 for spinach, other implies
   flesh; negative specifies preparation method {homemade,boiled,&c})
   and by obj->corpsenm (type of monster flesh) */
FOOD("lata",                  75,  0, 10, 1, METAL,   0, HI_METAL, TIN),
#undef FOOD

/* potions ... */
#define POTION(name,desc,mgc,power,prob,cost,color,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(0, 1, 0, 0, mgc, 0, 0, 0, 0, 0, 0, P_NONE, GLASS),      \
           power, POTION_CLASS, prob, 0, 20, cost, 0, 0, 0, 0, 10, color, sn)
POTION("ganar habilidad",           "rubí",  1, 0, 40, 300, CLR_RED,
                                                        POT_GAIN_ABILITY),
POTION("restaurar habilidad",        "rosa",  1, 0, 40, 100, CLR_BRIGHT_MAGENTA,
                                                        POT_RESTORE_ABILITY),
POTION("confusión",            "naranja",  1, CONFUSION, 40, 100, CLR_ORANGE,
                                                        POT_CONFUSION),
POTION("ceguera",            "amarillo",  1, BLINDED, 30, 150, CLR_YELLOW,
                                                        POT_BLINDNESS),
POTION("parálisis",           "esmeralda",  1, 0, 40, 300, CLR_BRIGHT_GREEN,
                                                        POT_PARALYSIS),
POTION("velocidad",            "verde oscuro",  1, FAST, 40, 200, CLR_GREEN,
                                                        POT_SPEED),
POTION("levitación",             "cian",  1, LEVITATION, 40, 200, CLR_CYAN,
                                                        POT_LEVITATION),
POTION("alucinación",      "cielo azul",  1, HALLUC, 30, 100, CLR_CYAN,
                                                        POT_HALLUCINATION),
POTION("invisibilidad", "azul brillante",  1, INVIS, 40, 150, CLR_BRIGHT_BLUE,
                                                        POT_INVISIBILITY),
POTION("ver invisible",       "magenta",  1, SEE_INVIS, 40, 50, CLR_MAGENTA,
                                                        POT_SEE_INVISIBLE),
POTION("curación",          "púrpura-rojo",  1, 0, 115, 20, CLR_MAGENTA,
                                                        POT_HEALING),
POTION("curación extra",          "pardo",  1, 0, 45, 100, CLR_RED,
                                                        POT_EXTRA_HEALING),
POTION("ganar nivel",            "lechoso",  1, 0, 20, 300, CLR_WHITE,
                                                        POT_GAIN_LEVEL),
POTION("iluminación",        "remolino",  1, 0, 20, 200, CLR_BROWN,
                                                        POT_ENLIGHTENMENT),
POTION("detección de monstruos",    "burbujeante",  1, 0, 40, 150, CLR_WHITE,
                                                        POT_MONSTER_DETECTION),
POTION("detección de objetos",      "humoso",  1, 0, 40, 150, CLR_GRAY,
                                                        POT_OBJECT_DETECTION),
POTION("ganar energía",          "nublado",  1, 0, 40, 150, CLR_WHITE,
                                                        POT_GAIN_ENERGY),
POTION("dormir",       "efervescente",  1, 0, 40, 100, CLR_GRAY,
                                                        POT_SLEEPING),
POTION("curación completa",          "negro",  1, 0, 10, 200, CLR_BLACK,
                                                        POT_FULL_HEALING),
POTION("polimorfia",            "dorado",  1, 0, 10, 200, CLR_YELLOW,
                                                        POT_POLYMORPH),
POTION("alcohol",                 "marrón",  0, 0, 40,  50, CLR_BROWN,
                                                        POT_BOOZE),
POTION("enfermedad",              "gaseoso",  0, 0, 40,  50, CLR_CYAN,
                                                        POT_SICKNESS),
POTION("zumo de fruta",            "oscuro",  0, 0, 40,  50, CLR_BLACK,
                                                        POT_FRUIT_JUICE),
POTION("ácido",                  "blanco",  0, 0, 10, 250, CLR_WHITE,
                                                        POT_ACID),
POTION("aceite",                   "turbio",  0, 0, 30, 250, CLR_BROWN,
                                                        POT_OIL),
/* fixed description
 */
POTION("agua",                 "claro",  0, 0, 80, 100, CLR_CYAN,
                                                        POT_WATER),
#undef POTION

/* scrolls ... */
#define SCROLL(name,text,mgc,prob,cost,sn) \
    OBJECT(OBJ(name, text),                                           \
           BITS(0, 1, 0, 0, mgc, 0, 0, 0, 0, 0, 0, P_NONE, PAPER),    \
           0, SCROLL_CLASS, prob, 0, 5, cost, 0, 0, 0, 0, 6, \
           HI_PAPER, sn)
SCROLL("encantar armadura",              "ZELGO MER", 1, 63,  80,
                                                        SCR_ENCHANT_ARMOR),
SCROLL("destruir armadura",         "JUYED AWK YACC", 1, 45, 100,
                                                        SCR_DESTROY_ARMOR),
SCROLL("confundir monstruo",                 "NR 9", 1, 53, 100,
                                                        SCR_CONFUSE_MONSTER),
SCROLL("asustar monstruo",   "XIXAXA XOXAXA XUXAXA", 1, 35, 100,
                                                        SCR_SCARE_MONSTER),
SCROLL("quitar maldición",             "PRATYAVAYAH", 1, 65, 80,
                                                        SCR_REMOVE_CURSE),
SCROLL("encantar arma",         "DAIYEN FOOELS", 1, 80, 60,
                                                        SCR_ENCHANT_WEAPON),
SCROLL("crear monstruo",       "LEP GEX VEN ZEA", 1, 45, 200,
                                                        SCR_CREATE_MONSTER),
SCROLL("domar",                   "PRIRUTSENIE", 1, 15, 200,
                                                        SCR_TAMING),
SCROLL("genocidio",                  "ELBIB YLOH", 1, 15, 300,
                                                        SCR_GENOCIDE),
SCROLL("luz",                 "VERR YED HORRE", 1, 90, 50,
                                                        SCR_LIGHT),
SCROLL("teleportación",        "VENZAR BORGAVVE",  1,  55, 100,
                                                        SCR_TELEPORTATION),
SCROLL("detección de oro",                 "THARR",  1,  33, 100,
                                                        SCR_GOLD_DETECTION),
SCROLL("detección de comida",               "YUM YUM",  1, 25, 100,
                                                        SCR_FOOD_DETECTION),
SCROLL("identificar",                  "KERNOD WEL", 1, 180,  20,
                                                        SCR_IDENTIFY),
SCROLL("mapa mágico",              "ELAM EBOW", 1, 45, 100,
                                                        SCR_MAGIC_MAPPING),
SCROLL("amnesia",                   "DUAM XNAHT", 1, 35, 200,
                                                        SCR_AMNESIA),
SCROLL("fuego",                  "ANDOVA BEGARIN", 1, 30, 100,
                                                        SCR_FIRE),
SCROLL("tierra",                          "KIRJE", 1, 18, 200,
                                                        SCR_EARTH),
SCROLL("castigo",            "VE FORBRYDERNE", 1, 15, 300,
                                                        SCR_PUNISHMENT),
SCROLL("cargar",                "HACKEM MUCHE", 1, 15, 300,
                                                        SCR_CHARGING),
SCROLL("nube apestosa",             "VELOX NEB", 1, 15, 300,
                                                        SCR_STINKING_CLOUD),
    /* Extra descriptions, shuffled into use at start of new game.
     * Code in win/share/tilemap.c depends on SCR_STINKING_CLOUD preceding
     * these and on how many of them there are.  If a real scroll gets added
     * after stinking cloud or the number of extra descriptions changes,
/* ... */
     * tilemap.c must be modified to match.  Mgc,Prob,Cost are superfluous.
     * SC values must be distinct but are only used by 'nethack --dumpenums'.
     */
#define XTRA_SCROLL_LABEL(text, sn) SCROLL(NoDes, text, 1, 0, 100, sn)
XTRA_SCROLL_LABEL(     "FOOBIE BLETCH", SC01),
XTRA_SCROLL_LABEL(             "TEMOV", SC02),
XTRA_SCROLL_LABEL(        "GARVEN DEH", SC03),
XTRA_SCROLL_LABEL(           "READ ME", SC04),
XTRA_SCROLL_LABEL(     "ETAOIN SHRDLU", SC05),
XTRA_SCROLL_LABEL(       "LOREM IPSUM", SC06),
XTRA_SCROLL_LABEL(             "FNORD", SC07), /* Illuminati */
XTRA_SCROLL_LABEL(           "KO BATE", SC08), /* Kurd Lasswitz */
XTRA_SCROLL_LABEL(     "ABRA KA DABRA", SC09), /* traditional incantation */
XTRA_SCROLL_LABEL(      "ASHPD SODALG", SC10), /* Portal */
XTRA_SCROLL_LABEL(           "ZLORFIK", SC11), /* Zak McKracken */
XTRA_SCROLL_LABEL(     "GNIK SISI VLE", SC12), /* Zak McKracken */
XTRA_SCROLL_LABEL(   "HAPAX LEGOMENON", SC13),
XTRA_SCROLL_LABEL( "EIRIS SAZUN IDISI", SC14), /* Merseburg Incantations */
XTRA_SCROLL_LABEL(   "PHOL ENDE WODAN", SC15), /* Merseburg Incantations */
XTRA_SCROLL_LABEL(             "GHOTI", SC16), /* pronounced as 'fish',
                                                * George Bernard Shaw */
XTRA_SCROLL_LABEL("MAPIRO MAHAMA DIROMAT", SC17), /* Wizardry */
XTRA_SCROLL_LABEL( "VAS CORP BET MANI", SC18), /* Ultima */
XTRA_SCROLL_LABEL(           "XOR OTA", SC19), /* Aarne Haapakoski */
XTRA_SCROLL_LABEL("STRC PRST SKRZ KRK", SC20), /* Czech and Slovak
                                                * tongue-twister */
#undef XTRA_SCROLL_LABEL
    /* These must come last because they have special fixed descriptions.
     */
#ifdef MAIL_STRUCTURES
SCROLL("correo",          "sellado", 0,   0,   0, SCR_MAIL),
#endif
SCROLL("papel en blanco", "sin etiqueta", 0, 28, 60, SCR_BLANK_PAPER),
#undef SCROLL

/* spellbooks ... */
    /* Expanding beyond 52 spells would require changes in spellcasting
     * or imposition of a limit on number of spells hero can know because
     * they are currently assigned successive letters, a-zA-Z, when learned.
     * [The existing spell sorting capability could conceivably be extended
     * to enable moving spells from beyond Z to within it, bumping others
     * out in the process, allowing more than 52 spells be known but keeping
     * only 52 be castable at any given time.]
     */
#define SPELL(name,desc,sub,prob,delay,level,mgc,dir,color,sn)  \
    OBJECT(OBJ(name, desc),                                             \
           BITS(0, 0, 0, 0, mgc, 0, 0, 0, 0, 0, dir, sub, PAPER),       \
           0, SPBOOK_CLASS, prob, delay, 50, level * 100,               \
           0, 0, 0, level, 20, color, sn)
/* Spellbook description normally refers to book covers (primarily color).
   Parchment and vellum would never be used for such, but rather than
   eliminate those, finagle their definitions to refer to the pages
   rather than the cover.  They are made from animal skin (typically of
   a goat or sheep) and books using them for pages generally need heavy
   covers with straps or clamps to tightly close the book in order to
   keep the pages flat.  (However, a wooden cover might itself be covered
   by a sheet of parchment, making this become less of an exception.  Also,
   changing the internal composition from paper to leather makes eating a
   parchment or vellum spellbook break vegetarian conduct, as it should.) */
#define PAPER LEATHER /* override enum for use in SPELL() expansion */
SPELL("cavar",             "pergamino",
      P_MATTER_SPELL,      20,  6, 5, 1, RAY, HI_LEATHER, SPE_DIG),
MARKER(FIRST_SPELL, SPE_DIG)
/* magic missile ... finger of death must be in this order; see buzz() */
SPELL("misil mágico",   "vitela",
      P_ATTACK_SPELL,      45,  2, 2, 1, RAY, HI_LEATHER, SPE_MAGIC_MISSILE),
#undef PAPER /* revert to normal material */
SPELL("bola de fuego",        "rasgado",
      P_ATTACK_SPELL,      20,  4, 4, 1, RAY, HI_PAPER, SPE_FIREBALL),
SPELL("cono de frío",    "orejas de perro",
      P_ATTACK_SPELL,      10,  7, 4, 1, RAY, HI_PAPER, SPE_CONE_OF_COLD),
SPELL("dormir",           "manchado",
      P_ENCHANTMENT_SPELL, 30,  1, 3, 1, RAY, HI_PAPER, SPE_SLEEP),
SPELL("dedo de la muerte", "manchado",
      P_ATTACK_SPELL,       5, 10, 7, 1, RAY, HI_PAPER, SPE_FINGER_OF_DEATH),
SPELL("luz",           "tela",
      P_DIVINATION_SPELL,  45,  1, 1, 1, NODIR, HI_CLOTH, SPE_LIGHT),
SPELL("detectar monstruos", "corroso",
      P_DIVINATION_SPELL,  43,  1, 1, 1, NODIR, HI_LEATHER,
                                                        SPE_DETECT_MONSTERS),
SPELL("curación",         "blanco",
      P_HEALING_SPELL,     40,  2, 1, 1, IMMEDIATE, CLR_WHITE,
                                                        SPE_HEALING),
SPELL("golpear",           "rosa",
      P_MATTER_SPELL,      25,  1, 1, 1, IMMEDIATE, CLR_BRIGHT_MAGENTA,
                                                        SPE_KNOCK),
SPELL("rayo de fuerza",      "rojo",
      P_ATTACK_SPELL,      30,  2, 1, 1, IMMEDIATE, CLR_RED,
                                                        SPE_FORCE_BOLT),
SPELL("confundir monstruo", "naranja",
      P_ENCHANTMENT_SPELL, 49,  2, 1, 1, IMMEDIATE, CLR_ORANGE,
                                                        SPE_CONFUSE_MONSTER),
SPELL("curar ceguera",  "amarillo",
      P_HEALING_SPELL,     25,  2, 2, 1, IMMEDIATE, CLR_YELLOW,
                                                        SPE_CURE_BLINDNESS),
SPELL("drenar vida",      "terciopelo",
      P_ATTACK_SPELL,      10,  2, 2, 1, IMMEDIATE, CLR_MAGENTA,
                                                        SPE_DRAIN_LIFE),
SPELL("ralentizar monstruo",    "verde claro",
      P_ENCHANTMENT_SPELL, 30,  2, 2, 1, IMMEDIATE, CLR_BRIGHT_GREEN,
                                                        SPE_SLOW_MONSTER),
SPELL("cerradura de mago",     "verde oscuro",
      P_MATTER_SPELL,      25,  3, 2, 1, IMMEDIATE, CLR_GREEN,
                                                        SPE_WIZARD_LOCK),
SPELL("crear monstruo",  "turquesa",
      P_CLERIC_SPELL,      35,  3, 2, 1, NODIR, CLR_BRIGHT_CYAN,
                                                        SPE_CREATE_MONSTER),
SPELL("detectar comida",     "cian",
      P_DIVINATION_SPELL,  30,  3, 2, 1, NODIR, CLR_CYAN,
                                                        SPE_DETECT_FOOD),
SPELL("causar miedo",      "azul claro",
      P_ENCHANTMENT_SPELL, 25,  3, 3, 1, NODIR, CLR_BRIGHT_BLUE,
                                                        SPE_CAUSE_FEAR),
SPELL("clarividencia",    "azul oscuro",
      P_DIVINATION_SPELL,  15,  3, 3, 1, NODIR, CLR_BLUE,
                                                        SPE_CLAIRVOYANCE),
SPELL("curar enfermedad",   "índigo",
      P_HEALING_SPELL,     32,  3, 3, 1, NODIR, CLR_BLUE,
                                                        SPE_CURE_SICKNESS),
SPELL("encantar monstruo",   "magenta",
      P_ENCHANTMENT_SPELL, 20,  3, 5, 1, IMMEDIATE, CLR_MAGENTA,
                                                        SPE_CHARM_MONSTER),
SPELL("acelerar",      "púrpura",
      P_ESCAPE_SPELL,      33,  4, 3, 1, NODIR, CLR_MAGENTA,
                                                        SPE_HASTE_SELF),
SPELL("detectar invisible",   "violeta",
      P_DIVINATION_SPELL,  20,  4, 3, 1, NODIR, CLR_MAGENTA,
                                                        SPE_DETECT_UNSEEN),
SPELL("levitación",      "bronceado",
      P_ESCAPE_SPELL,      20,  4, 4, 1, NODIR, CLR_BROWN,
                                                        SPE_LEVITATION),
SPELL("curación extra",   "cuadros",
      P_HEALING_SPELL,     27,  5, 3, 1, IMMEDIATE, CLR_GREEN,
                                                        SPE_EXTRA_HEALING),
SPELL("restaurar habilidad", "marrón claro",
      P_HEALING_SPELL,     25,  5, 4, 1, NODIR, CLR_BROWN,
                                                        SPE_RESTORE_ABILITY),
SPELL("invisibilidad",    "marrón oscuro",
      P_ESCAPE_SPELL,      20,  5, 4, 1, NODIR, CLR_BROWN,
                                                        SPE_INVISIBILITY),
SPELL("detectar tesoro", "gris",
      P_DIVINATION_SPELL,  20,  5, 4, 1, NODIR, CLR_GRAY,
                                                        SPE_DETECT_TREASURE),
SPELL("quitar maldición",    "arrugado",
      P_CLERIC_SPELL,      25,  5, 3, 1, NODIR, HI_PAPER,
                                                        SPE_REMOVE_CURSE),
SPELL("mapa mágico",   "polvoriento",
      P_DIVINATION_SPELL,  18,  7, 5, 1, NODIR, HI_PAPER,
                                                        SPE_MAGIC_MAPPING),
SPELL("identificar",        "bronce",
      P_DIVINATION_SPELL,  20,  6, 3, 1, NODIR, HI_COPPER,
                                                        SPE_IDENTIFY),
SPELL("convertir no-muerto",     "cobre",
      P_CLERIC_SPELL,      16,  8, 6, 1, IMMEDIATE, HI_COPPER,
                                                        SPE_TURN_UNDEAD),
SPELL("polimorfia",       "plata",
      P_MATTER_SPELL,      10,  8, 6, 1, IMMEDIATE, HI_SILVER,
                                                        SPE_POLYMORPH),
SPELL("teletransportar lejos",   "oro",
      P_ESCAPE_SPELL,      15,  6, 6, 1, IMMEDIATE, HI_GOLD,
                                                        SPE_TELEPORT_AWAY),
SPELL("crear familiar", "brillante",
      P_CLERIC_SPELL,      10,  7, 6, 1, NODIR, CLR_WHITE,
                                                        SPE_CREATE_FAMILIAR),
SPELL("cancelación",    "resplandeciente",
      P_MATTER_SPELL,      15,  8, 7, 1, IMMEDIATE, CLR_WHITE,
                                                        SPE_CANCELLATION),
SPELL("protección",      "opaco",
      P_CLERIC_SPELL,      18,  3, 1, 1, NODIR, HI_PAPER,
                                                        SPE_PROTECTION),
SPELL("saltar",         "delgado",
      P_ESCAPE_SPELL,      20,  3, 1, 1, IMMEDIATE, HI_PAPER,
                                                        SPE_JUMPING),
SPELL("piedra a carne",  "grueso",
      P_HEALING_SPELL,     15,  1, 3, 1, IMMEDIATE, HI_PAPER,
                                                        SPE_STONE_TO_FLESH),
SPELL("rayo en cadena", "cuadriculado",
      P_ATTACK_SPELL,      25,  4, 2, 1, NODIR, CLR_GRAY,
                                                        SPE_CHAIN_LIGHTNING),

#if 0 /* DEFERRED */
/* from slash'em, create a tame critter which explodes when attacking,
   damaging adjacent creatures--friend or foe--and dying in the process */
SPELL("flame sphere",    "canvas",
      P_MATTER_SPELL,      20,  2, 1, 1, NODIR, CLR_BROWN,
                                                        SPE_FLAME_SPHERE),
SPELL("freeze sphere",   "hardcover",
      P_MATTER_SPELL,      20,  2, 1, 1, NODIR, CLR_BROWN,
                                                        SPE_FREEZE_SPHERE),
#endif
/* books with fixed descriptions
 */
SPELL("papel en blanco", "liso", P_NONE, 18, 0, 0, 0, 0, HI_PAPER,
                                                        SPE_BLANK_PAPER),
/* LAST_SPELL is used to calculate MAXSPELL, allocation size of spl_book[];
   by including blank paper, which has no actual spell, we ensure that
   even if hero learns every spell, spl_book[] will have at least one
   unused slot at end; an unused slot is needed for use as terminator */
MARKER(LAST_SPELL, SPE_BLANK_PAPER)
/* tribute book added in 3.6 */
OBJECT(OBJ("novela", "libro de bolsillo"),
       BITS(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, PAPER),
       0, SPBOOK_CLASS, 1, 0, 10, 20, 0, 0, 0, 1, 20, CLR_BRIGHT_BLUE,
                                                        SPE_NOVEL),
/* a special, one of a kind, spellbook */
OBJECT(OBJ("Libro de los Muertos", "papiro"),
       BITS(0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, P_NONE, PAPER),
       0, SPBOOK_CLASS, 0, 0, 50, 10000, 0, 0, 0, 7, 20, HI_PAPER,
                                                        SPE_BOOK_OF_THE_DEAD),
#undef SPELL

/* wands ... */
#define WAND(name,typ,prob,cost,mgc,dir,metal,color,sn) \
    OBJECT(OBJ(name, typ),                                              \
           BITS(0, 0, 1, 0, mgc, 1, 0, 0, 0, 0, dir, P_NONE, metal),    \
           0, WAND_CLASS, prob, 0, 7, cost, 0, 0, 0, 0, 30, color, sn)
WAND("luz",           "vidrio", 95, 100, 1, NODIR, GLASS, HI_GLASS,
                                                            WAN_LIGHT),
WAND("detección de puertas secretas",
                        "balsa", 50, 150, 1, NODIR, WOOD, HI_WOOD,
                                                    WAN_SECRET_DOOR_DETECTION),
WAND("iluminación", "cristal", 15, 150, 1, NODIR, GLASS, HI_GLASS,
                                                    WAN_ENLIGHTENMENT),
WAND("crear monstruo",  "arce", 45, 200, 1, NODIR, WOOD, HI_WOOD,
                                                    WAN_CREATE_MONSTER),
WAND("deseo",          "pino", 5, 500, 1, NODIR, WOOD, HI_WOOD,
                                                    WAN_WISHING),
WAND("estasis",        "madera roja", 45, 150, 1, NODIR, WOOD, CLR_RED,
                                                    WAN_STASIS),
WAND("nada",           "roble", 25, 100, 0, IMMEDIATE, WOOD, HI_WOOD,
                                                    WAN_NOTHING),
WAND("golpear",        "ébano", 30, 150, 1, IMMEDIATE, WOOD, HI_WOOD,
                                                    WAN_STRIKING),
WAND("hacer invisible", "mármol", 45, 150, 1, IMMEDIATE, MINERAL, HI_MINERAL,
                                                    WAN_MAKE_INVISIBLE),
WAND("ralentizar monstruo",      "estaño", 50, 150, 1, IMMEDIATE, METAL, HI_METAL,
                                                    WAN_SLOW_MONSTER),
WAND("acelerar monstruo",   "latón", 50, 150, 1, IMMEDIATE, COPPER, HI_COPPER,
                                                    WAN_SPEED_MONSTER),
WAND("convertir no-muerto", "cobre", 50, 150, 1, IMMEDIATE, COPPER, HI_COPPER,
                                                    WAN_UNDEAD_TURNING),
WAND("polimorfia",      "plata", 45, 200, 1, IMMEDIATE, SILVER, HI_SILVER,
                                                    WAN_POLYMORPH),
WAND("cancelación", "platino", 45, 200, 1, IMMEDIATE, PLATINUM, CLR_WHITE,
                                                    WAN_CANCELLATION),
WAND("teletransportación", "iridio", 45, 200, 1, IMMEDIATE, METAL,
                                     CLR_BRIGHT_CYAN, WAN_TELEPORTATION),
WAND("abrir",          "cinc", 25, 150, 1, IMMEDIATE, METAL, HI_METAL,
                                                    WAN_OPENING),
WAND("cerrar",      "aluminio", 25, 150, 1, IMMEDIATE, METAL, HI_METAL,
                                                    WAN_LOCKING),
WAND("sondar",       "uranio", 30, 150, 1, IMMEDIATE, METAL, HI_METAL,
                                                    WAN_PROBING),
WAND("cavar",          "hierro", 55, 150, 1, RAY, IRON, HI_METAL,
                                                    WAN_DIGGING),
/* magic missile ... lightning must be in this order; see buzz() */
WAND("misil mágico",   "acero", 50, 150, 1, RAY, IRON, HI_METAL,
                                                    WAN_MAGIC_MISSILE),
WAND("fuego",        "hexagonal", 40, 175, 1, RAY, IRON, HI_METAL,
                                                    WAN_FIRE),
WAND("frío",            "corto", 40, 175, 1, RAY, IRON, HI_METAL,
                                                    WAN_COLD),
WAND("dormir",           "rúnico", 50, 175, 1, RAY, IRON, HI_METAL,
                                                    WAN_SLEEP),
WAND("muerte",            "largo", 5, 500, 1, RAY, IRON, HI_METAL,
                                                    WAN_DEATH),
WAND("rayo",      "curvado", 40, 175, 1, RAY, IRON, HI_METAL,
                                                    WAN_LIGHTNING),
/* extra descriptions, shuffled into use at start of new game */
WAND(NoDes,             "forked",  0, 150, 1, 0, WOOD, HI_WOOD, WAN1),
WAND(NoDes,             "spiked",  0, 150, 1, 0, IRON, HI_METAL, WAN2),
WAND(NoDes,            "jeweled",  0, 150, 1, 0, IRON, HI_MINERAL, WAN3),
#undef WAND

/* coins ... - so far, gold is all there is */
#define COIN(name,prob,metal,worth,sn) \
    OBJECT(OBJ(name, NoDes),                                         \
           BITS(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, metal),    \
           0, COIN_CLASS, prob, 0, 1, worth, 0, 0, 0, 0, 0, HI_GOLD, sn)
COIN("moneda de oro", 1000, GOLD, 1, GOLD_PIECE),
#undef COIN

/* gems ... - includes stones and rocks but not boulders */
#define GEM(name,desc,prob,wt,gval,nutr,mohs,glass,color,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(0, 1, 0, 0, 0, 0, 0, 0, 0,                              \
                HARDGEM(mohs), 0, -P_SLING, glass),                     \
           0, GEM_CLASS, prob, 0, wt, gval, 3, 3, 0, 0, nutr, color, sn)
#define ROCK(name,desc,kn,prob,wt,gval,sdam,ldam,mgc,nutr,mohs,glass,colr,sn) \
    OBJECT(OBJ(name, desc),                                             \
           BITS(kn, 1, 0, 0, mgc, 0, 0, 0, 0,                           \
                HARDGEM(mohs), 0, -P_SLING, glass),                     \
           0, GEM_CLASS, prob, 0, wt, gval, sdam, ldam, 0, 0, nutr, colr, sn)
GEM("cristal de dilitio", "blanco",  2, 1, 4500, 15,  5, GEMSTONE, CLR_WHITE,
                                                        DILITHIUM_CRYSTAL),
MARKER(FIRST_REAL_GEM, DILITHIUM_CRYSTAL)
GEM("diamante",           "blanco",  3, 1, 4000, 15, 10, GEMSTONE, CLR_WHITE,
                                                        DIAMOND),
GEM("rubí",                "rojo", 4, 1, 3500, 15,  9, GEMSTONE, CLR_RED,
                                                        RUBY),
GEM("jacinto",          "naranja",  3, 1, 3250, 15,  9, GEMSTONE, CLR_ORANGE,
                                                        JACINTH),
GEM("zafiro",           "azul", 4, 1, 3000, 15,  9, GEMSTONE, CLR_BLUE,
                                                        SAPPHIRE),
GEM("ópalo negro",        "negro", 3, 1, 2500, 15,  8, GEMSTONE, CLR_BLACK,
                                                        BLACK_OPAL),
GEM("esmeralda",           "verde", 5, 1, 2500, 15,  8, GEMSTONE, CLR_GREEN,
                                                        EMERALD),
GEM("turquesa",         "verde", 6, 1, 2000, 15,  6, GEMSTONE, CLR_GREEN,
                                                        TURQUOISE),
GEM("citrino",          "amarillo", 4, 1, 1500, 15,  6, GEMSTONE, CLR_YELLOW,
                                                        CITRINE),
GEM("acuamarina",        "verde",  6, 1, 1500, 15,  8, GEMSTONE, CLR_GREEN,
                                                        AQUAMARINE),
GEM("ámbar",   "amarillo marrón",  8, 1, 1000, 15,  2, GEMSTONE, CLR_BROWN,
                                                        AMBER),
GEM("topacio",   "amarillo marrón", 10, 1,  900, 15,  8, GEMSTONE, CLR_BROWN,
                                                        TOPAZ),
GEM("jet",               "negro",  6, 1,  850, 15,  7, GEMSTONE, CLR_BLACK,
                                                        JET),
GEM("ópalo",              "blanco", 12, 1,  800, 15,  6, GEMSTONE, CLR_WHITE,
                                                        OPAL),
GEM("crisoberilo",      "amarillo", 8, 1, 700, 15, 5, GEMSTONE, CLR_YELLOW,
                                                        CHRYSOBERYL),
GEM("granate",              "rojo", 12, 1, 700, 15, 7, GEMSTONE, CLR_RED,
                                                        GARNET),
GEM("ametista",         "violeta", 14, 1, 600, 15, 7, GEMSTONE, CLR_MAGENTA,
                                                        AMETHYST),
GEM("jaspe",              "rojo", 15, 1, 500, 15, 7, GEMSTONE, CLR_RED,
                                                        JASPER),
GEM("fluorita",         "violeta", 15, 1, 400, 15, 4, GEMSTONE, CLR_MAGENTA,
                                                        FLUORITE),
GEM("obsidiana",          "negro", 9, 1, 200, 15, 6, GEMSTONE, CLR_BLACK,
                                                        OBSIDIAN),
GEM("ágata",            "naranja", 12, 1, 200, 15, 6, GEMSTONE, CLR_ORANGE,
                                                        AGATE),
GEM("jade",              "verde", 10, 1, 300, 15, 6, GEMSTONE, CLR_GREEN,
                                                        JADE),
MARKER(LAST_REAL_GEM, JADE)
GEM("trozo sin valor de vidrio blanco", "blanco",
    77, 1, 0, 6, 5, GLASS, CLR_WHITE, WORTHLESS_WHITE_GLASS),
MARKER(FIRST_GLASS_GEM, WORTHLESS_WHITE_GLASS)
GEM("trozo sin valor de vidrio azul", "azul",
    77, 1, 0, 6, 5, GLASS, CLR_BLUE, WORTHLESS_BLUE_GLASS),
GEM("trozo sin valor de vidrio rojo", "rojo",
    77, 1, 0, 6, 5, GLASS, CLR_RED, WORTHLESS_RED_GLASS),
GEM("trozo sin valor de vidrio amarillo parduzco", "amarillo parduzco",
    77, 1, 0, 6, 5, GLASS, CLR_BROWN, WORTHLESS_YELLOWBROWN_GLASS),
GEM("trozo sin valor de vidrio naranja", "naranja",
    76, 1, 0, 6, 5, GLASS, CLR_ORANGE, WORTHLESS_ORANGE_GLASS),
GEM("trozo sin valor de vidrio amarillo", "amarillo",
    77, 1, 0, 6, 5, GLASS, CLR_YELLOW, WORTHLESS_YELLOW_GLASS),
GEM("trozo sin valor de vidrio negro", "negro",
    76, 1, 0, 6, 5, GLASS, CLR_BLACK, WORTHLESS_BLACK_GLASS),
GEM("trozo sin valor de vidrio verde", "verde",
    77, 1, 0, 6, 5, GLASS, CLR_GREEN, WORTHLESS_GREEN_GLASS),
GEM("trozo sin valor de vidrio violeta", "violeta",
    77, 1, 0, 6, 5, GLASS, CLR_MAGENTA, WORTHLESS_VIOLET_GLASS),
MARKER(LAST_GLASS_GEM, WORTHLESS_VIOLET_GLASS)

/* Placement note: there is a wishable subrange for
 * "gray stones" in the o_ranges[] array in objnam.c
 * that is currently everything between luckstones and flint
 * (inclusive).
 */
ROCK("piedra de la suerte", "gris", 0, 10, 10, 60, 3, 3, 1, 10, 7, MINERAL, CLR_GRAY,
                                                                    LUCKSTONE),
ROCK("piedra de carga", "gris", 0, 10, 500, 1, 3, 3, 1, 10, 6, MINERAL, CLR_GRAY,
                                                                    LOADSTONE),
ROCK("piedra de toque", "gris", 0,   8, 10, 45, 3, 3, 1, 10, 6, MINERAL, CLR_GRAY,
                                                                  TOUCHSTONE),
ROCK("sílex", "gris",      0, 10, 10,  1, 6, 6, 0, 10, 7, MINERAL, CLR_GRAY,
                                                                    FLINT),
ROCK("roca", NoDes,         1, 100,  10,  0, 3, 3, 0, 10, 7, MINERAL, CLR_GRAY,
                                                                    ROCK),
#undef GEM
#undef ROCK

/* miscellaneous ... */
/* Note: boulders and rocks are not normally created at random; the
 * probabilities only come into effect when you try to polymorph them.
 * Boulders weigh more than MAX_CARR_CAP; statues use corpsenm to take
 * on a specific type and may act as containers (both affect weight).
 */
OBJECT(OBJ("roca", NoDes),
       BITS(1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, P_NONE, MINERAL), 0,
       ROCK_CLASS, 100, 0, 6000, 0, 20, 20, 0, 0, 2000, HI_MINERAL, BOULDER),
OBJECT(OBJ("estatua", NoDes),
       BITS(1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, P_NONE, MINERAL), 0,
       ROCK_CLASS, 900, 0, 2500, 0, 20, 20, 0, 0, 2500, CLR_WHITE, STATUE),

OBJECT(OBJ("bola de hierro pesada", NoDes),
       BITS(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHACK, P_NONE, IRON), 0,
       BALL_CLASS, 1000, 0, 480, 10, 25, 25, 0, 0, 200, HI_METAL,
                                                            HEAVY_IRON_BALL),
        /* +d4 when "very heavy" */
OBJECT(OBJ("cadena de hierro", NoDes),
       BITS(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHACK, P_NONE, IRON), 0,
       CHAIN_CLASS, 1000, 0, 120, 0, 4, 4, 0, 0, 200, HI_METAL, IRON_CHAIN),
        /* +1 both l & s */

/* Venom is normally a transitory missile (spit by various creatures)
 */
OBJECT(OBJ("salpicadura de veneno cegador", "salpicadura de veneno"),
       BITS(0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, P_NONE, LIQUID), 0,
       VENOM_CLASS, 500, 0, 1, 0, 0, 0, 0, 0, 0, HI_ORGANIC, BLINDING_VENOM),
OBJECT(OBJ("salpicadura de veneno ácido", "salpicadura de veneno ácido"),
       BITS(0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, P_NONE, LIQUID), 0,
       VENOM_CLASS, 500, 0, 1, 0, 6, 6, 0, 0, 0, HI_ORGANIC, ACID_VENOM),
        /* +d6 small or large */

#if defined(OBJECTS_DESCR_INIT) || defined(OBJECTS_INIT)
/* fencepost, the deadly Array Terminator -- name [1st arg] *must* be NULL */
OBJECT(OBJ(NoDes, NoDes),
       BITS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, P_NONE, 0), 0,
       ILLOBJ_CLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#undef BITS
#endif

#undef OBJ
#undef OBJECT
#undef MARKER
#undef HARDGEM
#undef NoDes

/*objects.c*/
