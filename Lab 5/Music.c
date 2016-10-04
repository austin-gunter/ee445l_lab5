#include <stdint.h>

// These are three instrument wave patterns
// They will be switched between with the mode button
const unsigned short Trumpet64[64]={
  987, 1049, 1090, 1110, 1134, 1160, 1139, 1092, 1070, 1042, 1035, 1029, 1008, 1066, 1150, 1170, 1087, 915, 679, 372, 151, 
  558, 1014, 1245, 1260, 1145, 1063, 984, 934, 960, 1027, 1077, 1081, 1074, 1064, 1042, 1010, 974, 968, 974, 994, 1039, 
  1094, 1129, 1125, 1092, 1056, 1056, 1082, 1059, 1046, 1058, 1061, 1045, 1034, 1050, 1094, 1112, 1092, 1063, 1053, 1065, 1052, 992
};

const unsigned short Bassoon64[64]={
	1068, 1169, 1175, 1161, 1130, 1113, 1102, 1076, 1032, 985, 963, 987, 1082, 1343, 1737, 1863, 
	1575, 1031, 538, 309, 330, 472, 626, 807, 1038, 1270, 1420, 1461, 1375, 1201, 1005, 819, 658, 
	532, 496, 594, 804, 1055, 1248, 1323, 1233, 1049, 895, 826, 826, 850, 862, 861, 899, 961, 1006, 
	1023, 1046, 1092, 1177, 1224, 1186, 1133, 1098, 1102, 1109, 1076, 1027, 1003
};

const unsigned short Oboe64[64]={
	1024, 1024, 1014, 1008, 1022, 1065, 1093, 1006, 858, 711, 612, 596, 672, 806, 952, 1074, 1154, 1191, 
	1202, 1216, 1236, 1255, 1272, 1302, 1318, 1299, 1238, 1140, 1022, 910, 827, 779, 758, 757, 782, 856, 
	972, 1088, 1177, 1226, 1232, 1203, 1157, 1110, 1067, 1028, 993, 958, 929, 905, 892, 900, 940, 1022, 
	1125, 1157, 1087, 965, 836, 783, 816, 895, 971, 1017
};


// This array will contain the notes for the melody in the chorus from
// Let It Go - Frozen (The movie)
// The number stored inside represents the frequency of the note to be played
// This array says nothing about how long each note will be played, just the order of notes to be played
uint32_t NoteArray[57] = {
	349, 392, 415,  // F G Ab   Let it go
	311, 523, 466,  // Eb C Bb   Let it go
	415, 392, 349, 349, 349, 349, 392, 415,  // Ab G F F F G Ab  Can't hold it back anymore
	349, 392, 415,  // F G Ab   Let it go
	311, 523, 466,  // Eb C Bb   Let it go
	415, 466, 523, 523, 554, 523, 466, 415,  // Ab Bb C C Db C Bb Ab  Turn away and slam the door
	622, 523, 466, 415, 415, 622, 622, 523, 415,  // Eb C Bb Ab Ab Eb C Ab  I don't care, what they're going to say
	415, 415, 392, 311, 311, // Ab Ab G Eb Eb  Let the storm rage on
	415, 554, 554, 523, 554, 523, 554, 554, 523, 415,  // Ab Db Db C Db C Db Db C Ab The storm never bothered me anyway
	415, 554, 415, 554, 523  // Ab Db Ab Db C  Boo Dee Boo Dee Bee (Not real lyrics)
};

// These lengths are all in terms of number of eigth notes held consecutively
uint32_t LengthArray[57] = {
	1, 1, 6,
	1, 1, 7,
	1, 1, 1, 1, 2, 1, 2, 6,
	1, 1, 6,
	1, 1, 6, 
	1, 1, 2, 2, 1, 1, 2, 8,
	3, 3, 6, 2, 2, 1, 2, 3, 8,
	1, 1, 3, 3, 9,
	1, 2, 1, 1, 1, 1, 1, 1, 1, 2,
	1, 1, 1, 1, 4
};


