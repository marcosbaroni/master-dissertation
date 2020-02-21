/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

	int table[1000] = {
		1782373628,1915643482,1325071767, 730233089, 133253703, 463701182,1184296582,1644790578,1921023156,1460384300,
		 729443184, 266493076, 315526958, 927121793,1788387747,1926372661,1583126706,1005342318, 131700598, 452966753,
		 930405367,1374168128,1934108257,1458826973,1010875071, 532969777,  47086829, 631037524,1259435963,1854233368,
		1347453174, 718177103, 126403907, 442200700, 633118323,1128692079,1858441027,2010701013, 725121907, 263345866,
		 295480707, 896755150,1248051201,1860794359,2137706435,1546653880, 118732387, 426740939, 900909428,1377312178,
		1860809708,2021703304,1544472782,1065955946, 553046124,  94189987,1740618206,1262089390,1299693240,1776168781,
		 108004249, 586477098,  67301260,1600027111,1256689456,1436370582,1777248618, 252818049, 583584915, 884417777,
		1728924596,1266318588,1577059457,2037660386, 115784183, 578051743, 868553026, 273742284,1261700976,1450217184,
		2045257979, 526675357, 575032552, 590996236, 141285941,1793491863,1321573589,1799012409,  98153825, 573384689,
		 592290545,  19236469,1811064835,1201627497,1790215433, 237442253, 579804955, 853465486, 114764335,1801868002,
		1069668732,1540342635, 111724666, 573351873, 847466561, 251739287,1801787134,1206114694,1538208516,2131797247,
		 560787595,1106110678,1721132299, 188402505, 745336258, 813740981, 215939883,1770803542,1170433871,1695389096,
		   8604431, 742629011, 947849025, 215961395,1903063532,1172970575,1424176852, 134618898, 748067064,1094953925,
		 479650849,1781554793,1167862520,1422259498,1904377936, 740485839, 966319518, 505652538,2107562933,1167249714,
		1156826241,1768337427, 221949271, 837146464, 242332649,1762337271,1161879457,1140836619,1599359137, 219624909,
		 685144158, 231586769,1900604537,1156185430,1406269344,1736925937, 218966801, 547502989,1048960209,1771556600,
		1163298123,1394525643,1879558458, 204417520, 687860647,1053334323, 535334289,1150144971,1656274421,1181908705,
		 741045747, 282621052, 192857978, 707907351,1143906608,1651833250,1039319406, 696927114,  89365560, 196285129,
		 802511691,1146753003,1753603382,1184761230, 688690363,  38421744, 471123221, 672796735,1159610921,1891736269,
		1845935974, 714457630,  86426147, 474868112,1072006579,1159657020,1753703694,1706980134,1220564491, 229512278,
		 213907300, 691367413,1136941503,2139419366,1559592748,1214269102, 626985513, 223435007, 832578277,1146687370,
		1753937298,1694951565,1219868837, 503492897,  35569167, 691269058,1149556462,1882753814,1819791165,1218694910,
		 626123890,  31394263, 507857070,1121523969,1737372456,2082771365,1489158811, 852724254, 239025615, 376790680,
		 896855307,1490688926,2089208257,1627629328, 899690134, 431865417, 291769922, 753296020,1475771452,1954150036,
		1484999375, 904127325, 562027252,  17192486, 889373630,1485305104,1822217785,1896240270, 912565441, 431971966,
		  10921905, 489020388,1476829609,1949038727,2043402621,1446555041, 294032253, 269215268, 866072737,1496183289,
		1562868914,2104987534,1453552880, 959320134, 273267262, 731806954,1498489096,1959206378,2051083194,1450136247,
		1099768045, 486162601, 869496678,1480953236,1826227766,1932688183,1473071837,1011288700, 494444021,  79916881,
		1483287861,1960567421,1521606345,1981204853, 296538013, 758294588, 920169765, 443914919,1038670896,1674340040,
		2003527615, 484650969, 816157240, 770245607, 437453619,1971316572,1537037465,2012349460, 617637289,1096307029,
		 915811035, 439329700,1850383001,1370271908,2030478419, 463189930,1074001565, 493818108, 413237242,1982642772,
		1362537200,1482305343, 359037844, 821173758, 897436201, 438015499,1556593085,1095024385,1501122292,2097906089,
		 801946120, 751885768, 418835537,1968321177,1105514420,1505938335,2054534448, 535810674, 888401001, 408947685,
		1842845413,1375672135,1495313332,2106947306, 460229305,1070654252, 465000231,1994711966,1380271032, 982369251,
		 379562330,1931195849,1276894063,1482107855,  47283981, 565194991,1112620686, 383653154,1894195597,1415831094,
		1262414296,2007075432, 303600279, 991343437, 382764923,2078655141,1605747795,1393903842,2002023645, 178747497,
		 774384646, 392783332,2083208427,1605107341, 988294928,2001428463, 328135218, 787772011, 936892393,1925399339,
		1333230722,1377429887,1972551204,  76825066, 514096251, 941744863, 449062371,1345609831,1244329807,1975700597,
		 322351095, 511407493, 948345570, 603078325,2109580175,1428933686,1977171773, 172868687, 786447815, 949754664,
		 477191664,2144031613,1664744547,1975790662, 310397199, 787579394, 416047845, 879798598,1391222690,1853910241,
		2014035072, 459038907,  13538955, 427830831,1041470141,1382685667,1997755592,2021026633,1411584521,  16229844,
		 426016334,1175862819,1651179349,1866429763,2002896558,1254020186, 811396058, 446888436,1038468995,1665154500,
		2044088034,2001559341,1418536047, 787129151, 193745317, 905550313,1397898193,1855140196,2004570596,1006869118,
		 528672903,  71121943, 529078774,1382488972,1976008847,1995920854,1395683261, 529389095,  70134377, 655580672,
		1130063095,1857570278,1996972581,1252100319, 801079443,  62774186, 403048189,1015732570,1632665030,2051928587,
		1432746160, 820194906, 209512558, 129393474, 749502779,1316668718,1974843109,1705462787,1090545175, 478002052,
		    595636, 753696078,1314270604,1793692188,1793523527,1313601316, 591171776, 116579221, 459554184,1039664679,
		1917498103,1799396629,1460790175, 863712393, 122723070, 583349364,1043909119,1506510135,1803104318,1343467639,
		 848466832, 386706721, 697926043,1324995991,1925007574,1808240305,1755492998,1124136447, 532012894,  34368580,
		1332336132,1778802537,1800772832,1324329478,1129077469, 650536056, 107020681, 502522134,1924266321,1825114506,
		1482754806, 863925490, 527771531,  20981395, 499376933, 977991632,1817774877,1341262696, 858685090, 396931335,
		 670848081, 208171762,1862391529,1401815885,2056310090, 588080866,1050862700, 538448973, 216207275,1732163933,
		1407195491,1302602747, 555697837,1169273215, 392900979,  84469756,1867333438,1387866585,1441328222,1918662790,
		1058649326, 546550901,  65046500,1463564748,1395118777,1297844781,1913674311, 376470477, 669930117, 192501753,
		1861760490,1394732404,1731539179,2095382995, 510744562, 972343636, 186171279,1738979015,1411223251,1333058337,
		1884027064, 642434170,1230960246, 431717822,  45529075,1348916640,1276809092,2022726864, 510374995, 988904418,
		 450716003, 159817387,1398874428,1328349805,1939213342, 373851379, 982172503,1251605999,1852558018, 332585725,
		1204832983, 593092354,2125996441,1516607587,1092594633,1840321088, 142127335, 887813446, 831592621,2077388917,
		1769675368, 946310553,1544025462, 287969124, 886201444, 969385865, 371698942,1632396399,1079702309,1540376500,
		 128529738, 874925585, 813198371, 352390832,2035883599,1220927800,1817707342, 270200867, 875976705,1235323754,
		 621873249,2102352564,1576528460,1831189570, 130804210, 878675793, 784328138, 594177336,2014931658,1554358610,
		 987067029, 233965742, 828735232, 926361435, 334371316,2146938157,1552400706, 987521410,1453944826, 826484718,
		 794296100, 329626754,2031603288,1569824237,1805260111,1330288241, 872208538, 718059297,1179577203,1642394614,
		2108683755,1795046563,1200245502, 876080191, 283912933,1181657946,1776363451,2104901147,1501769852,1292754401,
		 846963181,  99109721, 350439308,1603875864,2083290256,1503818629, 897885166, 837648568, 242699974, 358360333,
		 956914453,2083940174,1758754686,1283415746, 817593118, 185870953, 615120585,1071639787,1571564677,1776752859,
		1182015065, 817911746, 220358258, 609215979,1204055373,1543630470,2133893257,1304368913, 810183054,  81179697,
		 441046213, 920442219,1663962107,2141294163,1543799233, 930010745, 308226559, 305596212, 903977664,1534414699,
		2135017147,1965149957,1352835629, 759108268, 179687417, 432546729,1123292877,1741223638,2076496495,1330681735,
		 855117476,  94582289, 382651223,1130373590,1614395181,2069675284,1365183071, 767332958, 377551161, 506594080,
		1015700762,1463379058,2047315695,1770134462, 747785632, 280777945, 146395336, 607218980,1624509290,1982670466,
		1379088975, 765578910, 684160612, 137547146, 471078088,1083525311,1982276425,1507021242, 779230019, 290988478,
		 120339873, 357511387,1069301891,1548750851,1363535730, 785593287, 434713423, 128661997, 456396777,1084835072,
		1411586609,1977054914, 752843595, 292192245, 178927862, 656256098,1096185175,1575527646,1412351295,1873833925,
		1279105909, 444202588,  24849843,1628551453,1168531542,1540067968,1867493169, 349877334, 439890534, 153764847,
		1643016556,1028206844,1406066394,1883479477, 437573415, 898108383,  80000847,1603745992, 885548325,1807597933,
		1877201438, 343595251, 956152669, 644605906,1635454892,1022864147,1433918105,1896740300, 745448925,1206105467,
		 402590841,  75794199,1592253370,1437126758,1892338129, 340670062,1208115922, 345622693,  19243572,1572844522,
		1438823233,1899462311, 476902980, 954366953, 486221590,   6909680,1443248034, 965556431,1892984588, 343382148,
		 947667897, 620780069,  07215722,1575142428, 963680703, 832177585,1939498284,1759550102, 918883456,1512570701,
		  04373405, 587227187, 999412381, 266903818,1918416141, 918094207,1406228361,  27059464, 445468478, 856049048,
		 247391903,2083022189,1467961733,1529638911,  30206808, 299461001,1259549582, 252941978,1947827039,1471806493,
		1122041970,  32476112, 436640904, 852114663, 256088265,1943217240,1749403046, 992788068,1588664979, 562115228,
		1019230085, 289162582,1974091958,1786996908, 896810267,1622777786,  62331632, 893793251, 275818898,2076954398,
		1466291528, 964735821,1614130111, 206855467, 387596089, 291896914,1935351204,1457848529,1099167691,1574241911,
		  89837968, 387476289, 286737434,1811119065,2013329875,1499215756,1020992432, 584657614, 103814040, 271951217,
		 884605080,2013820138,1403677316,1057360135, 478071561, 142227494, 313288911,1058140694,1502911914,1529966366,
		1058281301, 342868249, 145493557, 303131604, 927108170,1503586144,2116279276,1058729078, 451346579, 140254404,
		 306275719,1311204359,1802695503,2034829799,1605303232, 579818438, 108135189, 301296819, 913838631,1790693792,
		1895495255,1602156817,1006533879, 125531981, 344494676, 806112739,1571964215,2031483583,1510029357,1029684101,
		 284982035, 191147032, 814852568,1429506426,2041958935,1640438925,1029447195, 418973890, 193527161, 258706810,
		 886513886,1499054719,2038486083,1661682267, 955663483, 345255411, 133212793, 884037647,1364998064,2113799177,
		1702595158, 956020496, 483344685,   1436951, 613812478,1507308172,2018133213,1666390800,1320080287, 707521589,
		 236666426, 707999360,1189181597,1667804784,1679767258,1182423448, 723224325, 233471965, 289804274, 919124760,
		1517782304,2079474807,1055726415, 459941351, 236613154, 696121889, 895388241,1373376309,2074099301,1727375640,
		 474123069, 245560710, 590123703,1166618864,1510672097,2087769030,1860877249,1281864311, 210368197, 688765034,
		1131722597,1607966953,2119780548,1696898858,1253300758, 773429834, 256489881,1395835694, 920292690,1645044497,
		2113148491, 444944820, 923715204, 678255879,1397656540, 783957255,1635700631,2046732294, 450475645,1064011451,
		 546082088,  68755614, 981884035,1630366768,1872907803, 737339080, 926342079, 693453116,  95725755,1646236715,
		1664474314,2036886971, 705307728,1301055737, 245476843, 214024984,1468689049,1005091369,2131136106, 446444235};


/* Int comparison function (for qsort) */
int cmpint(const void *a, const void *b){
	return *((int*)a) - *((int*)b);
}

int *int_quicksort( int *v, int n){
	qsort(v, n, sizeof(int), cmpint);
	return v;
}
/* Int array comparison function */
int eq_groups(int *v1, int *v2, int n){
	int *va, *vb;
	int i, eq;

	va = (int*)malloc(n*sizeof(int));
	vb = (int*)malloc(n*sizeof(int));

	memcpy(va, v1, n*sizeof(int));
	memcpy(vb, v2, n*sizeof(int));

	int_quicksort(va, n);
	int_quicksort(vb, n);

	eq = 1;
	for( i = 0 ; i < n ; i++ )
		if( va[i] != vb[i] )
			eq = 0;

	free(va);
	free(vb);

	return eq;
}

int count_groups(int *v, int n){
	int g, i;
	int *v2;

	v2 = (int*)malloc(n*sizeof(int));
	memcpy(v2, v, n*sizeof(int));
	int_quicksort(v2, n);

	g = 1;
	for( i = 1 ; i < n ; i++ )
		if( v2[i-1] != v2[i] )
			g++;

	free(v2);
	return g;
}

IntHashTable *new_inthashtable(int k){
	int i;
	IntHashTable *h;

	h = (IntHashTable*)malloc(sizeof(IntHashTable));
	h->k = k;
	h->as = (int**)malloc(k*sizeof(int*));
	h->ns = (int*)malloc(k*sizeof(int));
	h->nmaxs = (int*)malloc(k*sizeof(int));
	h->n = 0;

	for( i = 0 ; i < k ; i++ ){
		h->nmaxs[i] = 10;
		h->as[i] = (int*)malloc(10*sizeof(int));
		h->ns[i] = 0;
	}

	return h;
}

int inthashtable_has(IntHashTable *h, int a){
	int idx, i, n;
	int *v;
	
	idx = a%h->k;
	n = h->ns[idx];
	v = h->as[idx];
	for( i = 0 ; i < n ; i++ )
		if( a == v[i] )
			return 1;
	return 0;
}

IntHashTable *inthashtable_insert(IntHashTable *h, int a){
	int idx;

	idx = a%(h->k);

	if( h->nmaxs[idx] <= h->ns[idx] ){
		h->as[idx] = realloc(h->as[idx], h->nmaxs[idx]*2*sizeof(int));
		h->nmaxs[idx] *= 2;
	}

	h->as[idx][h->ns[idx]] = a;
	h->ns[idx]++;
	h->n++;

	return h;
}

IntHashTable *inthashtable_reset(IntHashTable *h){
	int i;
	for( i = 0 ; i < h->k ; i++ )
		h->ns[i] = 0;
	h->n = 0;
	return h;
}

void free_inthashtable(IntHashTable *h){
	int i;
	for( i = 0 ; i < h->k ; i++ )
		free(h->as[i]);
	free(h->as);
	free(h->ns);
	free(h->nmaxs);
	free(h);
	return;
}
