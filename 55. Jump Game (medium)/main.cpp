#include <cassert>
#include <vector>

class Solution {
public:
  static bool canJump(std::vector<int>& nums) {
    std::vector<bool> jumps(nums.size(), false);
    jumps[0] = true;
    for (size_t i = 0; i < nums.size() - 1; ++i) {
      if (!jumps[i])
        continue;
      int max_jumps = nums[i];
      if (i+max_jumps >= jumps.size())
        return true;
      for (size_t j = i+1; j <= i+max_jumps && j < jumps.size(); ++j) {
        jumps[j] = true;
      }
    }
    return jumps.back();
  }
};

int main() {
  std::vector<int> v1 = {2,3,1,1,4};
  assert(Solution::canJump(v1));

  std::vector<int> v2 = {3,2,1,0,4};
  assert(Solution::canJump(v2) == false);

  std::vector<int> v3 = {0};
  assert(Solution::canJump(v3));

  std::vector<int> v4 = {0,2,3};
  assert(Solution::canJump(v4) == false);

  std::vector<int> v5 = {5957,16239,15762,3698,11932,18482,4897,7548,16342,14440,10643,4619,3581,8906,16762,10564,14276,6239,11477,5484,1325,18551,17968,6107,12313,12076,13898,4511,18387,16569,7497,15393,11539,17459,3024,10762,5949,13206,10897,1753,16459,13046,8831,14988,6186,17994,2364,14083,5621,17961,8703,14086,14079,10191,9898,2523,12443,16231,8632,12534,1868,9756,7259,19674,19677,736,11660,5553,19735,13072,3506,6524,7059,18649,4271,3862,3797,9220,18063,6392,10322,10165,11249,2091,2276,9627,5153,19826,17105,5141,19386,2582,18638,17434,405,13582,1801,12984,12063,9032,5999,9335,9051,18081,18932,441,432,18809,3613,1198,3735,13607,18821,3457,14559,3421,12295,14137,11078,6924,12265,5816,3733,6121,18838,12659,17882,8913,19117,15210,4825,17249,3733,11807,5361,4242,4818,14208,16705,16225,19042,16081,11437,4045,17977,12873,2290,9478,12861,1441,3302,7682,2962,8768,3134,8473,12957,2643,11127,6614,6467,16451,87,13564,19927,14636,6077,8813,10948,86,12102,2947,14808,14080,10571,10409,10250,3354,5327,10210,7597,9736,6183,475,14466,19361,12003,1941,10511,19267,13641,1489,8060,533,10178,9125,12345,15641,18381,15404,15104,17265,92,16214,19422,18212,19528,5569,17229,8583,14196,17372,18280,1044,10516,18494,5065,16591,3509,12624,562,5523,2475,13719,2285,3635,13608,8794,2001,17214,2638,4427,16602,17264,19485,6415,11416,5049,4031,1568,7547,6387,12194,11738,12600,13720,7674,13077,19668,7822,14885,1085,17663,2148,478,19338,11097,9148,17514,4824,14834,9412,19372,16165,10367,15715,2294,10907,13598,3604,19842,8406,14005,7089,11180,9408,19213,17217,6907,13117,9299,883,12237,11727,4135,12857,10756,17992,18978,6212,4411,13152,3093,1479,16571,4353,10143,1598,3246,1091,9796,15863,6246,9118,9728,1378,11436,5313,8549,19433,17089,2799,8988,16266,5525,9968,7603,1413,5557,3918,8636,15494,12088,5709,16314,6304,7743,9756,1574,5151,17225,12358,11469,6095,18093,7931,13299,17410,6421,1975,9087,17301,699,6177,10585,11222,10324,1805,6287,944,9079,2237,6149,9851,2037,15204,7545,13995,2357,4444,12309,6526,5,6108,15986,8603,2728,10484,18528,3235,6521,11349,13063,11098,5422,8094,16626,727,2491,16415,11292,9473,8894,9766,3971,2864,4814,19536,18801,19313,17267,2105,13127,8900,15395,14347,14172,10049,7256,10287,16047,5626,15183,15959,10886,11092,10375,10518,2070,14058,19069,3327,1652,2244,7770,7927,15989,6747,12316,1081,16085,1051,4558,16163,7879,18773,712,11541,13451,8414,1815,8006,14543,2390,12495,17595,16004,10825,7740,15042,18311,961,5040,10069,6212,2894,14730,9286,10547,16700,10635,14009,13297,5950,1574,6636,271,7422,2645,10169,11788,11504,8039,14869,14236,13511,5217,18531,89,16765,16921,15217,10790,11479,8165,15761,2061,19519,6462,305,195,1352,129,16958,14425,6876,12939,13914,9028,17764,16529,10840,12205,5038,19769,8012,4820,16398,2035,18179,6867,17624,8544,148,7583,11608,7290,1110,14621,3218,13787,1065,19870,14548,6028,8841,12364,18909,15546,1619,12602,10529,13095,5600,15388,10520,12965,19281,2884,2302,3023,11744,18310,689,6664,7536,5038,7605,12519,15659,3092,1116,11328,13634,13250,8363,16987,19843,5170,1026,11465,16099,12664,3189,2054,14401,13137,17177,12497,15639,14057,4367,13202,5863,4980,16743,15452,16930,11479,15443,1582,16592,17171,7777,11426,5011,17312,298,9150,11114,2443,19616,3781,9958,11198,18496,5142,17920,16833,3373,16148,4688,2248,11379,9005,18034,4099,10427,10196,13938,11315,6885,15756,9388,3652,16804,6040,16678,14265,11365,15877,4071,1822,123,16621,11298,2499,7050,2423,8565,13111,9757,11551,4156,4791,19787,13374,578,8821,3704,8811,13212,19439,14575,13242,6645,15320,9335,13846,734,13568,13960,18892,10477,8071,11368,18998,4271,4404,760,10621,13034,4260,13855,3390,12350,1414,16849,18487,2497,11296,2904,13667,14603,16708,4940,19178,12982,272,19295,3559,2620,3861,4967,10714,9105,11408,3248,17639,6114,15847,16993,5373,8070,7982,2986,2654,1887,15737,18403,12018,18917,7082,11345,15201,12008,9932,16157,476,11726,4519,3036,14766,1424,2903,17537,9033,5001,7425,7508,1274,11703,3386,19520,19413,3000,5359,15437,12222,19875,701,11447,10000,16891,18999,845,1722,1360,16293,5731,11294,5182,3702,8980,19389,3816,91,18070,14861,10333,4683,10896,2758,19329,10443,17716,6579,13036,3152,7450,1108,19796,6657,13528,12737,14124,8886,8642,4851,12355,18085,4156,7249,13533,3166,3623,12791,3750,9005,13491,12479,8465,4700,9017,3910,2561,10396,13021,14478,6532,9746,8386,18646,7462,14562,16803,6189,5319,9266,8818,16418,19202,18813,2647,7302,7933,4497,10402,8384,9972,11428,6403,17752,11046,16827,11678,12808,6397,18428,3304,17827,12005,15892,14077,19862,10506,438,2709,18187,5764,15121,18914,4866,10271,9909,2679,3522,3672,6207,1830,14501,9107,2825,2159,9288,13809,9087,15914,1592,15528,5337,14794,4300,1836,10185,14227,289,2121,5653,1412,15061,9861,17440,13807,14961,217,17432,3980,7044,1667,3104,5558,2285,14243,11759,14522,14050,19701,1343,4841,13060,19350,2948,10495,18283,7580,4645,8704,6379,10085,11642,16163,15589,9352,11458,12383,184,14572,6522,14301,10168,5159,11436,3731,9323,18324,16069,7557,1289,3990,19931,10220,2468,1899,2897,12043,17060,13718,6847,4050,5945,14262,9833,6923,485,6540,7120,4776,6967,15436,6975,916,7265,19067,15893,12662,10440,8805,8513,2203,6221,10218,11823,14079,12405,9007,17697,19523,2245,12117,16727,4632,8491,15202,5876,3363,1017,9450,8545,10249,2966,16703,2239,17407,2143,11289,7519,5804,18805,4172,4014,1319,6386,10462,11799,16824,11077,2008,3996,18814,7516,13418,8319,5235,16895,14979,11849,14683,16056,12646,10801,6700,7260,12799,2696,15931,11923,4686,2880,5165,2198,1930,277,10188,3187,299,2226,1871,14947,3818,16587,13390,19631,18385,1388,8491,4128,9719,19317,5612,9805,8062,6154,12051,7416,7482,14410,15205,2227,17950,3548,17890,9464,13236,8043,16569,13321,4476,8287,15155,18522,10284,11635,3157,14849,15468,15802,13765,7370,9444,11532,16827,8134,10199,14741,10825,16100,8907,2313,19302,14437,2758,16229,17810,1730,4239,2288,3359,18712,19168,3650,13115,3031,15185,11095,16104,19164,15766,16010,1136,12765,19387,12462,8544,19401,1671,2381,7281,9295,10657,19102,3500,733,19197,8732,2171,11251,8893,12658,13240,1399,15907,9175,8851,11199,17646,615,12988,8230,12893,15198,327,9079,8360,8746,403,1451,6984,2540,2926,1077,7300,499,19842,14357,13607,17922,735,15642,8973,10186,6279,4473,2821,2355,12453,10003,11573,12049,8209,13267,15948,9582,7673,18529,9476,6941,15707,5699,6254,2892,4537,19114,2027,17974,10711,12383,11729,8133,9738,7704,18225,4950,3810,17526,2993,13587,3095,7404,18939,8847,16469,12284,10338,5132,11189,10611,10225,44,3859,697,8486,17285,8228,19345,17522,14781,3018,14548,3363,10539,11657,13403,19146,9090,13930,2466,18799,12225,5221,14736,11194,19150,5427,13701,4063,19202,4109,9974,19738,17420,1299,17388,6966,19583,19042,10489,13899,5592,10161,4363,10460,17393,2089,7004,7704,19931,17417,19154,15316,8504,17247,3857,18432,17161,4614,9670,13365,7309,16277,18452,3479,7784,15286,3376,10907,10060,4359,1019,15853,10498,1536,19879,494,6459,7129,7818,16310,14866,9830,9424,14129,8653,17765,12625,17337,18866,7874,8007,14227,14958,9996,4310,7710,13289,18491,17253,3547,2384,337,6232,3372,6254,4924,3987,921,16581,13122,5004,14976,5602,10026,6755,10229,13363,13730,13874,6514,4575,2177,1957,13309,4697,4115,18881,10296,4116,1306,18199,10438,1649,11934,12680,1949,7199,7186,14206,17362,7083,11075,14182,7467,14046,15582,6313,10835,18318,17144,15242,11981,11372,19175,13079,4809,10650,15043,14586,13791,8446,13217,19786,10520,8768,16849,4111,12205,18990,14786,9967,5640,2127,3492,14295,1770,7610,15499,1907,14355,2102,14393,12753,10056,4355,4219,17984,6287,2999,9472,15605,13843,7875,19160,10921,4799,3032,19382,667,5035,7596,7517,8691,9967,11622,16513,5380,13103,10825,10917,9593,14634,19239,17602,10629,246,19248,355,13735,14355,5257,8271,13631,17178,14515,7936,6163,19479,12887,16943,3855,11552,17380,10556,14736,5723,17043,18666,11411,10555,13718,19130,19670,19017,16982,10691,8769,3634,17437,18026,12829,10078,8350,3152,13286,13499,2238,14103,6690,633,4428,19256,536,265,4979,17602,19874,9382,7392,9771,12105,17624,17594,12790,9667,18267,6845,16023,18388,8392,19042,10503,10267,11191,14902,7346,15796,12992,9693,12084,14857,8577,4598,2673,17405,10470,19143,7402,18775,12562,18200,5255,184,5809,6693,10109,5752,14492,13689,18798,15663,7106,6690,12789,7073,15323,17386,9083,2366,15091,9769,11388,771,18134,290,6921,8749,9171,18249,15673,4581,6768,13479,17265,6217,6354,1713,8016,769,13041,16716,14293,12378,925,2857,11633,15036,942,9346,5310,10409,17194,8109,2685,1702,9756,7464,17350,6955,9753,9776,17565,6724,5792,9828,13379,8864,755,19327,4851,12142,15699,4995,5033,2173,12858,9764,10994,9389,4704,8123,5750,7554,326,14815,8177,4634,13750,69,6634,10289,7623,13389,16449,1486,2348,10671,9390,7130,11221,14806,13610,7783,10682,10604,18687,11945,14972,8955,13345,3545,18277,10646,14796,10974,16816,2879,920,17844,13231,3301,12689,15950,69,1775,181,15634,15984,12327,19006,7900,14498,7638,16749,16370,1083,5678,4643,11012,10223,9704,6216,16356,10386,16366,8725,905,18844,18514,6950,10833,19727,7615,14950,18231,2140,5426,13847,825,2226,8077,4125,12369,18336,6411,2903,6584,11507,6909,1257,17142,1083,9833,11511,16318,18109,19882,13407,19529,2429,8300,1427,6434,8978,696,4079,6776,14073,7850,13577,6784,7474,15177,5929,3278,5045,3644,4761,1881,1260,14434,6339,19176,3084,8517,6986,2491,14452,17269,4201,13062,10931,14889,6979,13498,12419,17963,3189,13692,5868,18528,17468,18170,6130,2055,4842,8054,18156,7479,1604,4916,14563,11337,8679,796,15938,8046,5147,4900,10277,4471,16463,18846,11496,3764,13243,14635,11970,2815,5470,10675,13015,6189,8878,13706,18060,8636,13868,15619,14849,7629,13098,5633,3108,12604,19843,3097,4171,7685,9888,10824,15159,19032,15830,18891,8826,13354,18471,14184,2682,13549,12515,9317,13408,16683,16908,3747,6558,19908,1241,5321,959,6669,10444,4822,18008,5229,6308,16410,11740,5884,9530,7112,7849,10485,17823,8460,6464,1770,16073,7416,2932,13709,12780,2610,807,5793,6817,11991,19701,7158,1416,19941,13269,1320,12665,12220,1741,5744,9999,13312,4513,8217,2388,8263,1854,5072,17218,11697,7240,6123,882,7146,2570,10197,16221,13643,11558,13562,13378,11859,8578,18712,14187,1637,19321,14001,19422,4836,7959,15561,5753,2059,9152,4218,7953,6018,4725,14335,3139,19178,2762,8272,6087,8595,11087,13977,17123,19868,6463,11733,16830,15546,9572,7627,15873,17620,18076,17946,19816,1747,15629,15588,5489,14885,1291,6402,12569,19414,14551,8853,779,13055,15395,4743,16423,15293,5883,1820,12140,5375,7098,13821,14757,12691,18757,11229,16943,14351,3910,15307,11610,16989,17612,3758,10968,6091,19420,7781,5611,9671,5999,11748,19912,14640,13875,7704,3761,14526,14898,18742,9842,11280,1443,19235,19731,16604,15810,8380,14573,14388,18805,13961,11386,5432,4063,8363,16401,13966,17605,10670,12522,5000,4567,9724,19650,18572,12244,17076,8276,101,18465,15959,14212,4152,9036,12475,2505,11611,2564,2219,12609,4875,3514,13871,3945,15477,5919,12702,18617,2750,4739,6517,5002,6625,13561,4712,16586,19277,14401,19761,3025,13949,8074,3015,8505,11269,12479,14776,7196,13552,19316,16366,7544,613,15885,503,12977,15721,17616,10542,17465,16734,7085,6466,3749,12125,11089,6325,8642,1806,924,15132,19969,16687,14527,11925,18105,17917,18381,15125,13696,17809,2097,11701,15326,9505,7791,6111,13023,1134,10303,16843,7936,19766,18545,13219,1606,17848,11720,16315,6677,280,7235,8009,16756,5678,10512,18969,12219,2607,16957,5853,2375,19052,1689,9372,12995,8425,517,3915,7080,10727,16880,6511,10399,16734,4745,16668,510,380,10767,3828,17124,763,14758,7636,10484,3404,7509,15071,12410,16188,1203,4112,15612,19161,19533,826,3207,3117,16129,4108,9646,17647,2924,11381,15429,5830,6705,4956,17949,9053,11497,7093,6389,9010,5066,9996,17882,8824,8134,19996,11737,19939,19374,9360,9593,6135,3606,19933,9756,14585,14077,10386,775,5523,19856,2576,19441,11758,15143,15051,1409,19187,18593,6278,16472,12864,10926,7738,16617,19881,13411,6387,12382,13831,17964,10312,6134,18570,8915,4130,6965,7725,12371,8195,14245,4881,7730,13527,15473,9967,1198,1196,311,19453,18523,9364,1906,220,7447,2412,16126,13001,4402,14746,3663,1191,12336,1876,7274,8757,12537,15620,2691,13157,16945,15203,16875,815,14590,10590,162,18260,4730,4731,16367,4781,15171,1283,1173,9134,15122,15564,4320,12754,3555,2632,19899,7320,18682,8169,7834,18347,3347,10300,17989,1880,13884,6413,10709,16890,16160,5574,7758,11380,15495,11199,11381,6163,19653,8088,14116,10940,12413,19509,4561,4733,6947,1291,13697,15897,360,12604,6708,8781,3763,19529,3890,5641,11576,6762,17251,4204,267,5609,5858,9832,14902,569,15332,17799,7832,3793,9523,8365,2720,12810,4613,17731,14677,13980,4237,9417,15441,719,3631,8221,6510,12255,11904,16756,1000,17050,15189,4808,12106,14433,2905,5680,7984,15546,16911,2523,12853,1391,19558,9388,14636,919,5949,12247,17696,6151,2122,9958,16364,7056,4694,17346,8939,7207,12297,18240,16647,10112,4203,18395,14984,4232,15165,16242,15110,16525,19454,14141,13539,5296,18082,18845,1422,1664,7593,17626,5270,15054,8065,3785,9728,657,4155,6490,16424,524,1280,12064,11472,8418,3916,5600,276,7267,12791,19952,9981,15153,12066,17469,16308,10220,16818,6236,1877,10908,10491,12468,11721,18588,10761,7487,8483,16469,17524,9815,16199,15458,961,5909,14243,18843,6516,2580,9353,5140,3757,12128,17626,2798,18532,9077,1728,7418,7465,10890,10348,6952,12814,14014,10331,153,17824,2571,19548,7559,26,4500,4683,4647,18374,1075,382,15887,9596,19424,11504,3867,16192,11281,7861,5020,11764,17206,3625,9382,17636,3992,17237,858,10576,18015,10536,13628,10517,19857,820,3563,2692,14269,8498,19514,4199,17638,8355,6787,10010,1647,9864,19197,14944,19567,17722,12541,8846,13967,19912,10910,17929,15869,11873,2933,14343,9448,18919,7792,10594,12951,10409,12913,6399,6966,7385,18139,16650,19513,1693,19224,19989,6143,3144,10937,7777,9904,7438,4318,107,11641,14515,4370,7300,7868,17863,10863,750,1804,18977,6377,9727,6699,15436,3926,15279,13082,9803,15557,4782,14951,4877,11920,9040,1711,12125,16874,11162,16823,1854,15597,16368,7386,16982,6746,2571,16842,18120,8984,17695,11216,12286,927,10371,2814,15272,17927,3498,6876,15646,18870,60,10623,17331,16780,1746,3889,12953,3734,6048,3771,11956,12578,5084,4394,13841,11618,14858,7787,7285,15328,12591,5479,12764,19799,12188,6819,17675,4809,18991,1359,18972,3732,13954,12939,19927,483,11350,6744,7998,19205,348,11369,17446,8549,16957,3550,11389,7229,11351,8228,14914,15217,11257,12185,5099,12796,717,13897,18282,12226,2851,3358,8161,15558,11054,13782,2755,13745,16537,13138,252,2925,10347,1215,15550,14277,1805,15010,15382,19595,7659,17507,7666,16759,2060,14448,1749,4269,6029,17800,13744,5269,12918,18757,6675,8868,3857,7002,9432,5064,9800,14102,14964,11507,15732,362,13450,9514,5957,9125,13243,11100,19492,3643,12724,17029,784,13840,9101,289,1824,17545,5880,1102,10627,9919,11659,9113,12016,12469,8261,9696,15953,9520,5699,9402,18139,11858,5956,1881,19454,11380,3745,2445,3880,153,17412,18298,41,15808,17553,2939,8817,19355,9581,3631,7730,19296,869,2560,14428,9857,1052,3422,9431,15401,15242,7988,7650,9785,9692,11005,11974,17880,17788,6814,18770,16556,6458,11688,1361,5909,579,14819,10354,4278,16381,3816,9346,4734,12288,2121,13593,14150,3873,2127,12249,7868,12589,12681,8486,9295,5025,12469,4039,6270,6916,10088,8669,15443,19801,7208,16372,16434,9965,12090,11041,6514,10992,4004,6693,11890,16673,17879,7586,14136,226,16528,1848,16986,4956,11354,14284,11435,6778,413,7644,14694,18671,8345,13659,6366,9763,13018,205,4265,17103,1438,16692,3339,2056,18270,12568,7119,3785,2309,2620,2846,11964,15090,9880,18779,11245,16443,13943,14003,18212,131,15012,6486,10581,6149,13717,19396,340,13440,17509,10941,7492,18620,14969,1521,6894,11131,17039,2330,15137,18908,11866,4073,16937,1410,10731,16539,12360,7339,11380,18188,8605,2742,12867,14405,15467,14670,19196,8008,6681,17940,18752,11297,3697,13685,4622,17484,16921,6818,4795,13746,4500,401,568,6075,3674,16710,5372,15716,15363,16473,11863,2866,15484,19379,8890,12862,8565,19643,16763,14620,11705,2994,1790,7543,9603,18330,250,8090,12424,10352,7581,18060,2925,145,19409,6458,18122,2443,17630,5430,10350,13191,19487,16794,13350,3889,17579,18238,14644,4365,17395,16618,14702,19728,1748,13466,12736,19236,778,1783,13626,2508,940,853,9744,19689,7659,11339,18062,2744,19077,13853,4982,4781,1507,12834,11608,13925,6388,3274,336,4654,16251,12823,17527,11091,15026,16986,4879,148,10938,3707,15217,6494,14804,10704,12604,2599,17386,11787,1092,700,2080,16596,10171,5797,10698,2901,17915,7006,10320,17145,19886,4641,2667,19572,8433,3462,12763,12952,4056,18714,19186,3116,15940,16944,9527,12943,1210,16752,18986,12145,14436,15561,13683,7761,9942,7638,570,1997,17499,17630,14193,13297,12832,5994,15857,3730,7198,3776,19034,5686,19442,7317,16794,15425,13128,15011,13143,19142,3245,9743,16312,10478,1498,15686,18468,10834,12926,10639,17599,8242,10999,10481,3107,15369,15372,7052,10673,14733,5293,3868,18127,5011,19715,4732,17804,5180,3270,11638,8131,8550,14719,16878,18191,18953,912,2918,4911,4630,4649,13359,16718,17153,4342,6813,2146,3353,11405,6015,8233,21,13807,11177,14424,4308,3952,2305,6752,2254,15206,15039,18727,5697,17287,15686,9330,7018,11391,14834,2299,19319,11095,281,16262,10505,55,5901,4996,1190,6385,18602,11737,3068,4958,1726,6632,710,6426,718,3438,6454,15016,9566,3383,830,2740,8037,11240,2604,19845,8692,16202,15297,9013,2117,13830,12194,5672,11433,1973,10696,6609,10533,19706,11856,7448,10126,1996,18709,17489,6727,8602,14534,10825,8833,4241,16632,16792,2181,9018,8481,19964,11371,2065,7231,11602,198,11334,8022,100,5551,15202,14766,9854,2412,13177,9025,18497,10972,18917,14588,996,6803,6477,2115,782,3331,5722,7461,7265,10526,19191,4184,14497,15915,17646,5314,12422,357,15623,18751,9690,12760,19053,847,13034,13364,19101,8743,503,12025,1608,754,13968,18544,13820,750,19488,9536,9791,18527,5535,4654,11751,13689,6632,14696,17928,11861,13339,16557,8740,9299,18756,1875,6734,13966,16436,19897,18796,12403,7174,14433,1135,11753,18567,7727,7869,13613,9439,12107,12909,9821,12101,3957,18734,9946,17424,6585,10113,15046,4355,9593,10100,3186,17873,14047,3815,7317,5402,22,10656,10741,4386,14908,13129,9127,8540,575,12795,17191,19279,15269,7247,7387,16040,17045,14092,13179,2185,4900,14648,16654,12866,3913,28,19434,7855,18973,13570,12792,4004,12818,17519,15990,3685,13328,6809,5045,11286,13622,2267,18288,2700,8838,15998,19174,1587,15557,7473,12973,1607,16070,17357,9636,10874,6496,9193,11504,3348,8668,5056,13637,3768,8421,1962,4148,11733,13711,4643,15389,7355,3144,17140,17135,6684,3091,10206,16466,7940,16362,6692,5270,3195,2260,15592,8003,5119,3706,16723,18723,8559,6210,16853,4485,8599,7618,18411,13142,185,4367,9392,15801,12567,15505,18079,18958,336,11440,11000,17741,1786,7379,2764,15204,15644,4109,5958,14044,15345,9180,2123,12767,5903,18357,2386,7870,17798,15928,8272,13909,12255,16946,12973,13700,12566,16393,3616,7640,12010,15570,18272,17491,9242,5167,6086,11278,10362,3555,2564,16902,1057,10480,9563,3461,19936,6491,17559,2097,14529,939,19342,1294,9181,8715,4722,15336,19424,15811,11142,5078,606,8974,9171,17963,8132,16879,7583,2032,6535,1382,12135,7220,1123,13592,9256,1939,3777,17907,14023,7597,13341,15783,9649,17896,3609,7170,18010,8870,5501,17977,15216,3581,6767,13720,10428,11142,1031,5522,11716,10400,16112,16642,15327,5921,3534,7008,8167,3134,17938,12023,7490,1381,10992,2575,10428,18993,7,4491,9230,15935,16087,3904,8606,4858,2305,4609,4254,1635,114,17431,377,8367,6350,4469,11986,14526,7827,14394,8439,5412,5599,7366,14320,18858,10992,1950,14290,16999,10791,542,18669,2594,12297,5516,16425,7311,14565,17691,8543,11920,11976,6052,3120,18013,2852,14028,2610,12942,19983,18489,14169,5006,16013,19331,10897,11102,16554,13772,16876,18667,12480,19533,6023,696,1852,6795,316,3766,12410,11570,8930,4873,15038,18552,3813,1486,4302,7344,3902,1128,6964,16555,17642,5334,17767,3740,1012,15057,15248,11960,11539,7832,18097,2192,19834,9387,19979,3326,6195,13527,2176,9878,6571,13266,13147,3295,123,17767,2018,5277,226,19580,14309,11236,15371,12838,14181,6231,1689,14208,10174,11321,4561,19412,4114,15595,3462,4387,5244,10273,4569,18181,10075,13994,16177,16041,9167,18087,9534,6059,12967,12930,323,8376,18923,7320,1686,2983,7112,14242,18056,19627,18318,9822,12228,12249,10681,8032,14881,16829,1798,2478,18093,17521,12456,5809,5709,1995,8169,2901,13504,3163,14174,16568,2722,4018,10866,7972,14652,17747,19176,19672,17032,4502,3484,1076,4596,4752,18631,1809,630,2440,19951,13046,860,9791,16722,16386,5688,7317,8821,7609,13341,14601,3283,15617,8672,10752,14780,8242,12334,7496,12542,10998,90,576,3468,2306,13133,18201,8319,15407,9998,9894,18728,9648,14464,5651,3639,19228,6209,17904,8177,8182,3336,19677,7602,12798,6435,7291,14215,9227,10521,455,10129,1300,3498,11278,18708,10255,15268,10446,6060,2395,10760,4414,15153,18851,6887,17520,675,8025,538,5953,13075,19589,17672,10933,5644,11970,7747,9705,19954,12594,10965,6257,16396,10932,557,3435,1909,9012,1484,2538,4947,14141,9253,14402,17712,5881,15107,16268,1844,12449,16922,10361,6106,18200,6400,11829,4625,896,9628,14676,17274,2731,17195,3934,1088,17510,13991,16224,16906,10961,8775,19409,15801,10280,11988,7147,2029,4782,14465,19532,12454,7979,10501,10588,10354,1457,6039,5779,18061,18651,976,16299,6995,13621,10583,14978,3989,10897,4143,12800,1830,14215,16541,1629,6033,14622,5935,4832,283,13606,6173,1435,14656,6932,10591,4201,6800,10167,10874,15897,13136,15751,3341,13641,18450,4859,6900,15307,6050,3117,16358,545,8471,3242,15975,5667,10265,8546,15963,15642,958,17539,8252,5185,244,8803,4558,10578,13578,3960,14736,11194,6845,12444,14532,429,4707,11576,19233,16413,7796,15843,17100,7624,1394,1389,8251,436,9912,10346,11339,10327,12047,14666,6216,1697,18159,10627,16467,7434,2820,3238,13070,4215,9553,7845,17444,15505,14254,13178,9919,2049,15725,9740,13121,12888,8570,7717,1022,6530,13284,5368,9184,626,2034,11562,3964,10815,5728,13956,2555,5458,12503,2431,7830,11382,4854,9014,631,16247,16063,6348,9428,1573,7171,16482,7289,12227,7857,8553,15704,266,6845,11638,17259,14540,1383,15280,13052,8783,33,11733,12754,6482,5628,19782,17712,5992,2579,14403,14930,2521,16992,1824,2442,6821,9220,15226,5114,13222,16224,5132,12292,10299,18165,4394,15985,17418,17562,7491,4591,7784,10293,2858,2689,13885,5598,14933,18889,11886,13315,7976};
  assert(Solution::canJump(v5));

  return 0;
}
