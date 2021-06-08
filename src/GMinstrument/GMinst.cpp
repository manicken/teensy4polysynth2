#include "GMinst.h"

#include "Piano1_samples.h" 
#include "ChurchOrg1_samples.h"
#include "NylonstrGt_samples.h"
#include "Violin_samples.h"
#include "Flute_samples.h"
#include "SpaceVoice_samples.h"
#include "Harpsichord_samples.h"
#include "Glockenspiel_samples.h"
#include "Tubularbell_samples.h"
#include "ChoirAahs_samples.h"
#include "SynthDrum_samples.h"
#include "SteelDrums_samples.h"
#include "Banjo_samples.h"
#include "Bird_samples.h"
#include "BottleBlow_samples.h"
#include "Brightness_samples.h"
#include "Clarinet_samples.h"
#include "EPiano2_samples.h"
#include "EchoDrops_samples.h"
#include "Harp_samples.h"
#include "Honkytonk_samples.h"
#include "Marimba_samples.h"
#include "OrchestraHit_samples.h"
#include "PanFlute_samples.h"
#include "StarTheme_samples.h"
#include "Xylophone_samples.h"
#include "Bandoneon_samples.h"
#include "BaritoneSax_samples.h"
#include "Bassoon_samples.h"
#include "BowedGlass_samples.h"
#include "BreathNoise_samples.h"
#include "Clav_samples.h"
#include "EPiano1_samples.h"
#include "GtHarmonics_samples.h"
#include "Harmonica_samples.h"
#include "Helicopter_samples.h"
#include "Kalimba_samples.h"
#include "MusicBox_samples.h"
#include "PizzicatoStr_samples.h"
#include "ReedOrgan_samples.h"
#include "Santur_samples.h"
#include "Sitar_samples.h"
#include "Taiko_samples.h"
#include "Telephone1_samples.h"
#include "TinkleBell_samples.h"
#include "Whistle_samples.h"
#include "Applause_samples.h"
#include "Contrabass_samples.h"
#include "Crystal_samples.h"
#include "EnglishHorn_samples.h"
#include "Goblin_samples.h"
#include "MeloTom1_samples.h"
#include "Oboe_samples.h"
#include "Organ2_samples.h"
#include "Piccolo_samples.h"
#include "Recorder_samples.h"
#include "ReverseCym_samples.h"
#include "Shamisen_samples.h"
#include "AccordionFr_samples.h"
#include "AltoSax_samples.h"
#include "Cello_samples.h"
#include "ChifferLead_samples.h"
#include "Fiddle_samples.h"
#include "FingeredBs_samples.h"
#include "Koto_samples.h"
#include "MutedGt_samples.h"
#include "Ocarina_samples.h"
#include "Organ3_samples.h"
#include "Shanai_samples.h"
#include "SoloVox_samples.h"
#include "TenorSax_samples.h"
#include "Atmosphere_samples.h"
#include "Bagpipe_samples.h"
#include "Fantasia_samples.h"
#include "IceRain_samples.h"
#include "Seashore_samples.h"
#include "SlapBass2_samples.h"
#include "SynVox_samples.h"
#include "Tuba_samples.h"
#include "Viola_samples.h"
#include "VoiceOohs_samples.h"
#include "5thSawWave_samples.h"
#include "Charang_samples.h"
#include "CleanGt_samples.h"
#include "MutedTrumpet_samples.h"
#include "Trombone_samples.h"
#include "Trumpet_samples.h"
#include "Vibraphone_samples.h"
#include "AcousticBs_samples.h"
#include "Agogo_samples.h"
#include "BassLead_samples.h"
#include "Brass1_samples.h"
#include "Celesta_samples.h"
#include "DistortionGt_samples.h"
#include "FrenchHorns_samples.h"
#include "FretlessBs_samples.h"
#include "HaloPad_samples.h"
#include "JazzGt_samples.h"
#include "MetalPad_samples.h"
#include "Organ1_samples.h"
#include "OverdriveGt_samples.h"
#include "Piano2_samples.h"
#include "Piano3_samples.h"
#include "PickedBs_samples.h"
#include "Polysynth_samples.h"
#include "SawWave_samples.h"
#include "Shakuhachi_samples.h"
#include "SlapBass1_samples.h"
#include "SlowStrings_samples.h"
#include "SopranoSax_samples.h"
#include "Soundtrack_samples.h"
#include "SquareWave_samples.h"
#include "SteelstrGt_samples.h"
#include "Strings_samples.h"
#include "SweepPad_samples.h"
#include "SynCalliope_samples.h"
#include "SynStrings1_samples.h"
#include "SynStrings2_samples.h"
#include "SynthBass1_samples.h"
#include "SynthBass2_samples.h"
#include "SynthBrass1_samples.h"
#include "SynthBrass2_samples.h"
#include "TremoloStr_samples.h"
#include "WarmPad_samples.h"

// the following are some of the 128 instruments in the General MIDI 
// instrument bank
const PROGMEM AudioSynthWavetable::instrument_data * GMinst[] = {
    &Piano1,
    &Piano1, //&Piano2
    &Piano1, //&Piano3
    &Piano1, //&Honkytonk,
    &Piano1, //&EPiano1,
    &Piano1, //&EPiano2,
    &Piano1, //&Harpsichord,
    &Piano1, //&Clav,
    &Celesta,
    &Glockenspiel,
    &Vibraphone, //&MusicBox,
    &Vibraphone,
    &Vibraphone, //&Marimba,
    &Vibraphone, //&Xylophone,
    &Vibraphone, //&Tubularbell,
    &Piano1,
    &ChurchOrg1, //&Organ1,
    &ChurchOrg1, //&Organ2,
    &ChurchOrg1, //&Organ3,
    &ChurchOrg1,
    &ChurchOrg1, //&ReedOrgan,
    &AccordionFr,
    &Piano1, //&Harmonica,
    &Piano1, //&Bandoneon,
    &NylonstrGt,
    &NylonstrGt, //&SteelstrGt,
    &NylonstrGt, //&JazzGt,
    &NylonstrGt, //&CleanGt,
    &NylonstrGt, //&MutedGt,
    &NylonstrGt, //&OverdriveGt,
    &NylonstrGt, //&DistortionGt,
    &NylonstrGt, //&GtHarmonics,
    &NylonstrGt, //&AcousticBs,
    &NylonstrGt, //&FingeredBs,
    &NylonstrGt, //&PickedBs,
    &NylonstrGt, //&FretlessBs,
    &NylonstrGt, //&SlapBass1,
    &NylonstrGt, //&SlapBass2,
    &NylonstrGt, //&SynthBass1,
    &NylonstrGt, //&SynthBass2,
    &Violin,
    &Piano1, //&Viola,
    &Piano1, //&Cello,
    &Contrabass,
    &Piano1, //&TremoloStr,
    &Piano1, //&PizzicatoStr,
    &Piano1, //&Harp,
    &Piano1, //&SynthDrum, // should be timpani
    &Piano1, //&Strings,
    &Piano1, //&SlowStrings,
    &Piano1, //&SynStrings1,
    &Piano1, //&SynStrings2,
    &ChoirAahs,
    &VoiceOohs,
    &SynVox,
    &OrchestraHit,
    &Trumpet,
    &Piano1, //&Trombone,
    &Piano1, //&Tuba,
    &Piano1, //&MutedTrumpet,
    &Piano1, //&FrenchHorns,
    &Piano1, //&Brass1,
    &Piano1, //&SynthBrass1,
    &Piano1, //&SynthBrass2,
    &SopranoSax,
    &AltoSax,
    &TenorSax,
    &BaritoneSax,
    &Oboe,
    &EnglishHorn,
    &Bassoon,
    &Clarinet,
    &Piccolo,
    &Flute,
    &Recorder,
    &PanFlute,
    &BottleBlow,
    &Shakuhachi,
    &Whistle,
    &Ocarina,
    &SquareWave,
    &SawWave,
    &SynCalliope,
    &ChifferLead,
    &Charang,
    &SoloVox,
    &FifthSawWave,
    &BassLead,
    &Fantasia,
    &WarmPad,
    &Polysynth,
    &SpaceVoice,
    &BowedGlass,
    &MetalPad,
    &HaloPad,
    &SweepPad,
    &IceRain,
    &Soundtrack,
    &Crystal,
    &Atmosphere,
    &Brightness,
    &Goblin,
    &EchoDrops,
    &StarTheme,
    &Sitar,
    &Banjo,
    &Shamisen,
    &Koto,
    &Kalimba,
    &Bagpipe,
    &Fiddle,
    &Shanai,
    &Piano1, //&TinkleBell,
    &Piano1, //&Agogo,
    &Piano1, //&SteelDrums,
    &Piano1, //&SynthDrum, // woodblock
    &Piano1, //&Taiko,
    &Piano1, //&MeloTom1,
    &Piano1, //&SynthDrum,
    &Piano1, //&ReverseCym,
    &Piano1, //&SynthDrum, // gt fret noise
    &Piano1, //&BreathNoise,
    &Piano1, //&Seashore,
    &Piano1, //&Bird,
    &Piano1, //&Telephone1,
    &Piano1, //&Helicopter,
    &Piano1, //&Applause,
    &Piano1 //&SynthDrum, // gun shot
};
