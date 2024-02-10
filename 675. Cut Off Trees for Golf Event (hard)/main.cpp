// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ii = std::pair<int, int>;
using i_ii = std::pair<int, ii>;

constexpr ii DIRS[4] = {{1,0},{0,1},{-1,0},{0,-1}};
int dist[50][50];

class Solution {
  public:
  static int cutOffTree(const std::vector<std::vector<int>>& forest) {
    if (forest[0][0] == 0) {
      return -1;
    }
    const auto n = static_cast<int>(forest.size());
    const auto m = static_cast<int>(forest[0].size());

    std::map<int, ii> tree_pos;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (forest[i][j] > 1) {
          tree_pos.emplace(forest[i][j], ii{i, j});
        }
      }
    }

    int res = 0;
    ii src = {0, 0};
    for (const auto& [_, dst] : tree_pos) {
      std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INT_MAX);
      dist[src.first][src.second] = 0;

      std::queue<ii> q;
      q.emplace(src);
      while (!q.empty() && dist[dst.first][dst.second] == INT_MAX) {
        const auto vi = q.front().first;
        const auto vj = q.front().second;
        q.pop();
        for (const auto& dir : DIRS) {
          const auto ui = vi + dir.first;
          const auto uj = vj + dir.second;
          if (ui >= 0 && ui < n && uj >= 0 && uj < m && forest[ui][uj] > 0 && dist[ui][uj] == INT_MAX) {
            const auto u_dist = dist[vi][vj] + 1;
            dist[ui][uj] = u_dist;
            q.emplace(ui, uj);
          }
        }
      }
      
      if (dist[dst.first][dst.second] == INT_MAX) {
        return -1;
      }
      res += dist[dst.first][dst.second];
      src = dst;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{{1,2,3},{0,0,4},{7,6,5}};
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == 6);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{{1,2,3},{0,0,0},{7,6,5}};
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == -1);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{{2,3,4},{0,0,5},{8,7,6}};
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == 6);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{
      {54581641,64080174,24346381,69107959},
      {86374198,61363882,68783324,79706116},
      {668150,92178815,89819108,94701471},
      {83920491,22724204,46281641,47531096},
      {89078499,18904913,25462145,60813308}};
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == 57);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{
{584,41176,0,84851,5441,70639,56597,62679,49323,86340,5352,0,93554,0,12084,40642,93702,46453,21713,27842,1339,59987,3604,90313,77097,68238,60394},
{67899,70450,0,47502,99265,85901,13579,7320,36586,0,0,81886,90379,31744,90234,76250,10104,62356,59519,7782,71566,91515,24832,78046,204,63974,72204},
{3657,47544,54745,59243,44861,47148,83563,26920,81164,22887,85661,47198,90529,0,61724,63224,96440,28524,32600,37691,67572,77872,59735,19587,48869,69551,0},
{0,81904,55598,28273,61332,30929,95175,2596,62937,9711,36764,0,69181,40582,89972,34806,89956,35087,84547,88362,0,12632,28051,77608,17549,71324,7031},
{15555,0,91139,16345,71032,79505,32456,64864,77687,98643,95207,71967,95495,82715,76404,63943,63973,55193,11812,30160,17410,54556,60496,35945,64739,87782,45283},
{76521,7740,36829,0,78711,70264,88457,35349,40047,96915,50902,19002,0,31609,62536,46918,3386,55625,16156,14947,31147,66393,63296,80438,64446,97131,0},
{22397,55228,27150,9519,54197,26866,64562,95463,1952,26498,42378,5105,909,24560,21019,2270,37376,53928,6452,9305,22444,65989,77999,80300,95492,30322,80433},
{4736,79210,42457,23429,7138,36957,96801,10996,95622,66141,41590,337,89548,72250,86233,51111,44300,71974,62813,22195,3755,43518,4333,63540,8378,76457,66325},
{39196,0,96504,3942,3516,40470,68830,61639,42489,6841,30048,53638,31133,77646,3016,14014,25359,29856,90389,34929,0,1638,6440,60418,38462,7574,49059},
{32551,46791,9154,46218,11838,4169,84723,83850,0,5521,23503,54877,91954,3229,24989,52449,2404,36246,21387,27407,74997,73106,79400,75833,70818,17850,99594},
{96055,22364,48491,40218,66766,18706,94119,32361,81313,28969,0,78222,1247,55861,12770,86641,11552,70553,0,45633,43220,98035,0,0,50663,97908,30624},
{86578,40713,20328,76454,34313,0,23213,0,0,53316,3235,11475,4755,9671,81476,39129,30175,67985,28547,91578,0,89149,45768,0,89732,72480,69633},
{45641,87506,40356,27213,13512,14406,0,54267,45665,54893,62600,64803,97061,39195,64986,18539,0,24169,0,41540,0,47890,86003,0,15880,20283,29033},
{91217,88922,15946,1541,60641,55461,66377,62516,76719,43872,81218,0,0,67023,23349,6300,23862,23090,49655,43960,9390,96602,7291,93517,96320,41286,75862},
{12984,0,11418,36033,90978,11016,81388,9023,17361,28536,44317,87824,5028,52109,17297,3424,93246,15313,38295,90914,42382,88405,78363,38181,75694,14063,83030},
{78653,0,69802,74818,67980,12615,61595,89897,19098,6135,44671,12635,31584,8215,68928,57468,26781,48977,38781,7374,78059,99491,15483,55666,81777,26107,23195},
{95803,0,34621,15431,11437,0,42946,98472,9156,3895,61023,61370,74365,17231,43459,5130,42170,88326,10921,27233,67624,0,40570,49014,54062,15474,26875},
{39524,52632,28692,92559,49635,55362,92322,3878,55730,64614,17061,30708,6652,23458,29102,89160,62210,32167,10358,86971,82013,0,12979,93914,38533,0,21777},
{20298,0,0,54863,30028,25633,3397,18943,86887,0,7680,85736,24445,32654,81065,92349,70788,65234,8409,39904,76676,6311,41699,0,49766,19066,61389},
{98947,12747,12424,33975,0,91772,75442,89531,7900,90852,15257,84715,33881,17099,25810,0,17997,78578,10160,89605,27030,58687,28603,6972,79040,98632,92991},
{53890,23801,85650,63911,612,66980,75525,35940,19500,83181,76783,36814,13928,41578,79896,11658,59694,21287,88732,50685,9816,9215,90499,81561,59082,35397,664},
{10704,0,47683,91141,13000,59671,63986,65514,45447,79405,0,77599,8445,35668,43665,30164,85561,18640,23723,0,26745,15785,84867,83701,0,68958,22010},
{24454,77324,20725,89455,83717,82482,60498,7191,73315,94284,31921,84243,67118,62731,1678,46376,94405,4051,0,0,0,96329,75733,99345,26763,15444,30255}};
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == 9581);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> forest{
{46362,32601,72983,56271,26019,54579,55962,9265,88322,18670,41215,78738,81679,87588,53871,66445,99225,27506,3615,95487,18069,49495,2877,56179,75642,40368,87500,49278,99866,0,9449,0,9522,0,56248,19930,21867,11439,0,52676,56754,51753,24701,27123,13273,91666},
{0,59813,50534,36242,89504,75119,3385,67530,49880,37837,46715,91665,95908,3726,1932,55941,47642,47920,64825,93084,76640,44212,86456,30435,78039,25760,82843,0,6033,12185,26840,98131,43430,47234,16305,27915,76703,67226,70358,43260,82426,95791,19429,77090,81763,0},
{0,36720,9104,48681,0,80757,41932,97191,34686,95820,0,68754,25307,81711,73455,0,19617,93418,25745,32919,95526,6224,32030,46278,28922,28305,0,43103,43580,89708,72013,35319,5851,24141,0,14749,77548,49903,81317,50344,78205,52211,26552,72879,19021,45821},
{43458,65381,88583,62464,97622,71580,72944,34392,0,185,95764,43399,68766,48343,87995,21368,92607,69010,35964,77570,27203,77846,75268,67281,64968,43684,81403,79166,63798,42979,72419,33675,73288,48664,85453,60452,73368,56563,99717,72472,0,81703,71587,88921,5927,51849},
{20843,88732,0,40528,38717,72244,76375,93155,58889,56653,0,0,65375,13138,32418,55653,39433,0,60849,74015,1462,58671,22683,68027,61146,79440,17292,52738,45086,9670,63511,27523,35429,65629,14642,8124,27913,53756,46631,65883,85166,6630,84843,93640,59374,0},
{90616,25023,15484,70526,0,22650,34140,67954,8631,47379,49237,0,15607,38770,86621,749,44652,11733,11028,43888,32021,61905,55124,45832,51758,62451,32792,27606,69752,40098,88003,74610,65551,92944,29761,30517,57646,98223,89163,9547,49981,84873,37057,16684,35376,60240},
{31193,11652,77021,76747,60128,42576,30632,18033,58469,72620,93687,60024,71037,46028,56309,31934,24754,75493,18583,32878,51833,80661,0,15514,0,93378,57887,54215,26472,6085,0,4780,59883,53806,4296,31077,55775,36401,55882,55150,59639,95141,1381,24963,7742,4003},
{84527,23383,31289,75203,32550,53847,0,84820,21123,40746,38512,93451,0,50096,42762,52399,96383,77025,92952,15612,6250,58965,24868,98677,5525,66483,36444,0,74651,80219,72831,0,75826,0,4093,19792,98183,43650,18331,0,22142,99350,13156,14370,21712,72105},
{97532,90324,39327,19710,76671,15615,51068,54665,98170,7730,20769,0,0,0,5644,1073,29465,15464,78962,23743,16732,38414,95993,98746,38536,29898,28483,48156,36175,33658,41227,56736,29029,89126,15061,25069,0,62420,16179,98750,59393,88069,5427,57938,26851,21467},
{79811,48859,89207,84657,98629,23226,11397,60318,33335,70539,63274,69251,62005,73916,5870,80674,40396,56405,15030,66667,80228,96489,8293,41755,21022,32841,39127,80843,66831,82566,87014,20504,53735,82156,93963,13182,70990,83827,9755,46258,39986,49700,34150,7946,41889,3167},
{35132,69623,82837,11431,16570,0,0,518,72859,50481,27067,12108,75538,43783,11990,79370,14093,45881,25264,9965,74005,72922,17241,0,3560,2959,50462,26989,30349,3654,24450,98956,0,51334,32852,37513,41701,0,70269,0,8540,56682,34693,8836,0,0},
{58610,23874,66034,36824,93714,48725,51586,25845,50559,99348,49905,53039,38489,41876,59254,50948,0,68688,92062,6961,52517,97926,0,72147,30962,47894,40458,75512,52707,15791,75497,39600,89816,3682,89264,23051,0,14692,80758,50378,23815,30459,37486,65247,0,82019},
{31927,35711,25283,57833,66702,81681,79334,90272,47505,14230,94947,72966,80642,35578,67715,9697,39595,43237,35977,89748,38053,94374,45653,24676,1948,23962,58505,0,32939,93120,68579,59688,69169,0,0,75317,81142,0,34733,81476,40515,8286,55858,84242,43788,6724},
{24146,23036,55367,45476,19404,71171,2630,27268,61312,92848,7255,0,99686,34139,3331,53095,36734,40921,63523,53778,16340,0,41880,98129,45389,38890,44870,70721,7334,66174,0,33215,22704,15023,7995,17955,7337,51052,14687,5101,33132,50849,39228,46147,43959,35730},
{31163,5996,62467,84890,45084,47038,0,94610,65242,66684,4943,13223,81734,68088,58500,86359,93937,66079,16881,26040,43526,46860,69234,87554,0,493,42723,8592,33483,82562,34108,33402,67438,22173,46230,80130,63174,62923,83423,50918,81205,53399,0,22640,82760,0},
{98016,58605,33591,75113,0,31825,82446,81377,6212,1917,83674,60395,85818,25455,72241,87366,9807,11103,12623,12790,1762,10858,69611,1660,20471,90015,75995,1631,51358,64489,19170,54343,57218,55654,68178,19368,27267,26549,54877,16652,34907,36209,37527,90617,52618,57384},
{26333,48249,90583,17598,82582,73061,55646,51202,65721,3971,46997,55536,11077,56463,58740,60933,10781,52155,0,0,24355,8039,16680,74110,43407,49065,46238,58441,29439,83473,5862,69296,4835,52626,49250,22043,10419,53409,78763,14652,9369,0,59810,90689,73700,39537},
{71101,9304,22081,29507,0,96347,84083,72384,3559,65817,15459,1333,0,59822,89022,26247,77433,0,0,81007,11493,2186,0,9150,71751,98601,53112,53309,0,51524,85271,8801,0,62698,37237,0,21367,24272,84249,81730,12570,30755,84706,856,0,0},
{95543,62573,22706,83126,15518,65153,85786,85749,49523,0,30559,4494,40657,73574,83650,31573,3318,51192,26048,48369,0,96208,89440,42574,85977,98957,16947,80749,0,17312,85049,93257,3789,48769,54894,52642,44520,66926,34191,56854,40851,93327,95613,83233,6154,18649},
{87860,6636,0,43588,77305,63296,41833,41914,37240,0,15984,99788,49236,83928,78551,0,42701,39942,99989,5924,78111,0,97775,32524,76154,36999,66460,22796,33984,26528,51408,17421,53338,62388,95228,43603,64451,87941,94266,0,0,87447,89499,2179,61061,20003},
{91597,71756,82998,69619,33,70878,58114,29534,2109,73309,26962,85814,31362,60634,92086,39110,72653,55407,0,24902,0,99059,2122,1955,53429,2650,12488,78437,23707,40010,91799,19334,68929,0,64495,68565,0,84733,62663,78825,37857,19614,51072,8386,99829,77586},
{61847,49644,10274,0,46493,65133,53149,0,53589,0,16842,49773,28961,30907,32322,43521,2399,30476,39206,54335,53141,0,72785,94148,95203,0,72561,58725,20254,0,81169,60730,72639,83043,90049,32111,88797,57419,59744,20274,35027,6624,4862,28278,65020,96646},
{75423,29958,32062,0,1911,64071,72881,22685,0,9246,67591,57583,25995,0,83497,56235,50166,0,13637,17808,68495,70064,93018,45367,62294,49462,0,15710,88161,72884,27456,72510,77598,41113,72352,2418,50967,9418,99478,34024,62251,13563,52753,85850,10096,61172},
{0,95038,5586,47467,14761,41168,18815,0,27985,1003,8506,41766,98453,98023,46447,42254,82297,0,59488,34414,61386,89468,4826,44564,76252,13598,11575,61341,0,0,97671,81426,88124,19410,76656,89987,7517,30117,11705,0,47330,0,21906,75425,49263,0},
{95595,38998,3226,24205,7066,41074,5286,31410,94303,26763,31746,19719,4746,87424,42634,67696,36045,72937,86353,21829,0,55724,90664,43180,79510,14840,53997,83326,74825,51689,41554,66400,69897,7082,56143,57374,76928,21386,0,0,36714,11042,99896,40424,37892,0},
{19381,28212,15293,76333,46496,80441,99364,70212,80941,94267,68080,82258,80063,72577,39584,86593,49621,4417,0,93563,93258,68140,3128,98146,17017,23900,33384,18214,10047,70846,57522,39097,13298,0,70059,55219,54367,79630,50594,0,12631,3928,74058,18901,0,22546},
{10784,68542,43563,18513,44045,70444,8637,69126,64967,47994,41171,0,76189,0,42527,0,52329,78713,73201,38971,23940,0,9422,71408,30438,31446,76268,0,17462,68787,53201,35661,0,32501,91466,31655,11792,47540,4311,34129,82423,78278,6697,31567,0,72345},
{8510,11791,0,0,83096,77890,15120,23783,30820,9712,39751,0,0,52402,52480,67785,17264,94992,53071,94774,0,79990,35329,0,97986,53,92857,16428,43878,7422,51426,29894,94689,27616,30152,39750,1900,87572,63078,90209,36576,99352,7807,16228,57639,41119},
{27899,32917,97673,58341,99007,64423,63471,55645,67413,36233,62277,0,65051,0,28001,76276,9729,52272,2698,66826,31240,58337,67096,4014,20983,76888,68902,3793,61140,34625,66292,30789,12987,50801,90538,53859,94871,17610,96199,11927,36636,93414,53274,0,5555,6156},
{54227,19589,0,92050,78588,26306,21750,34917,82965,91386,42485,49477,58180,0,0,49085,33088,18401,51138,24140,80185,76484,3650,12768,68720,84017,44431,95660,22267,89678,25867,66470,92222,10447,63920,96116,6394,0,76511,0,20654,93695,0,98951,21427,56493},
{85138,1237,0,41186,38003,6754,37315,42462,94886,62620,0,9518,94961,96466,71927,26807,24107,55533,62356,0,57504,92209,18832,0,97452,41767,51286,39898,66306,56303,35171,88178,51234,95000,0,73160,71565,39664,27192,6425,40710,0,3255,99148,74411,0},
{25984,30904,72902,50012,4956,27287,81445,27838,69620,8647,631,16260,19072,99772,33423,69628,0,37332,91505,71459,75932,24543,85791,19702,0,1228,0,39834,38891,14480,0,58301,77271,31657,95704,22635,42060,11680,61588,67799,85896,91046,0,11954,45575,28376},
{54203,21037,17827,80405,19904,0,5110,29623,23851,49765,61403,21351,12089,0,12013,38702,58762,56502,0,19271,0,90019,78590,46829,0,53464,96316,12308,58957,5223,0,27427,84000,11485,42987,32851,85227,99034,88629,9723,12300,6356,16321,27235,12348,74032},
{10109,89134,94814,27281,94770,4416,28619,10602,53654,18235,1867,86825,2077,84328,97612,41908,92926,53455,64350,75053,61568,96648,33910,1715,81394,97958,20017,77842,84951,51930,82572,87159,59204,26034,77574,65307,37355,10441,30314,7709,93391,87300,13433,96305,51305,48301},
{38764,63368,95762,92526,71199,0,64251,15811,87527,6317,14705,83736,0,86117,50368,63777,68210,101,0,74481,46018,28948,93457,39563,0,78311,3701,11837,9727,0,0,0,27451,87461,43957,58053,9588,39489,31688,50500,50073,72179,20791,89275,53949,21060},
{92235,0,68152,46553,70590,61047,0,62670,11503,68620,36064,45890,57596,16878,49009,34300,28272,94810,60111,55043,84364,37769,81608,16592,53574,26111,35191,0,51562,31608,47706,15650,96829,12407,53287,26723,24176,52563,0,76423,43662,81022,20946,8507,72583,0},
{26965,36862,58523,90028,11428,34761,0,42336,59269,71454,62020,69198,24522,24813,49170,20870,48164,52646,96090,93105,83206,71542,55038,33600,6353,39064,73433,98658,18159,91491,68098,96482,63189,0,76108,85168,0,69922,48395,3896,87925,0,36695,38917,83352,38921},
{86315,47106,23919,67077,87956,39793,56040,93364,31548,36528,2965,55354,15808,87611,46650,82646,71002,93173,67218,0,0,48896,92130,2678,49304,84241,45430,93254,11631,6908,23633,40297,68310,30697,95721,85511,74839,37865,95733,0,34601,0,91727,27034,12847,61117},
{92547,37519,35465,14947,4102,47985,14339,47917,393,68337,47686,90645,30055,41824,28719,59927,41954,68278,74783,52020,41187,79744,56932,30529,70758,75948,6104,28046,47162,16301,77770,11442,59549,0,210,98233,34843,50690,27036,18315,40288,79906,66371,8559,27964,12206},
{55904,59108,57782,17674,6606,86189,56916,17333,19160,8151,93949,17407,39721,48767,61477,38864,15479,1647,79672,8959,86798,15372,40929,53312,55083,836,95452,42863,99103,0,87385,53025,94182,47943,82115,53953,35272,94030,62154,7076,32885,46681,0,0,23856,98390},
{0,47978,45522,66444,72184,32078,47482,89875,84301,74922,66251,17128,56726,49634,47381,95822,11282,46163,42659,80896,49890,81924,7458,65009,76820,61507,0,83896,48298,83752,79490,31425,83673,55379,43124,24637,3058,46919,18029,99883,0,73591,1545,41538,46296,509},
{57974,41984,4569,74089,79047,92762,90915,0,0,94229,46074,31922,4994,96309,10933,1584,0,88172,60623,22982,73479,75138,89763,87254,17983,61999,41389,28835,31155,10319,69386,88528,92846,0,37381,53617,60067,93960,12475,19059,45351,89111,69065,76215,22304,33191},
{32100,54614,25922,0,0,9923,1925,93317,81622,0,12842,37110,76784,0,56752,85362,0,85047,27460,15748,98520,81526,54790,31102,0,12000,26736,30666,55528,45686,82908,13655,22010,0,67239,11243,42008,3361,28845,93475,25237,71761,18845,57825,0,22699},
{0,26794,23268,58166,32324,75782,72486,8144,84105,10196,77434,0,39233,35157,5587,57693,25148,81370,97585,7757,57258,1079,144,0,0,38112,26770,85028,28126,96201,63068,49552,59763,4610,0,41350,18833,58656,46831,20142,27981,72543,9237,91688,7074,24511},
{12249,69732,3449,76389,0,88928,93168,53914,50999,99128,39414,22767,73342,44169,96988,86309,71282,97794,44875,33825,96702,21797,36879,73228,6938,73743,14280,81086,87791,79766,58914,3585,24597,60941,52355,57966,25559,98738,94502,15069,53612,66902,70071,21117,34640,70872},
{43782,31661,35262,40987,87141,43317,26428,9950,36960,32632,34472,0,56797,0,68284,18417,18805,1962,45239,86564,48349,89108,58004,0,62374,53963,79771,97385,85404,19636,40629,25676,13914,13505,4581,0,0,66921,34454,21433,9281,86295,60300,0,82206,47941},
{28542,61409,48190,3134,97406,94972,63207,0,87927,0,47237,27303,51514,5107,25453,57810,30308,58612,0,0,85390,3013,92233,11725,33740,72753,33203,52736,70303,74033,77347,30396,502,10632,85307,9382,78819,89876,81499,97740,15047,14253,69228,30084,20071,0},
{39001,33406,76907,81530,84700,70680,54033,39281,32652,82398,49787,56282,72812,11529,28980,19172,14358,68893,58061,85137,77756,0,81280,52321,82578,73064,21145,17998,53235,71460,27,19972,97210,28943,43647,27908,51156,173,0,2974,0,49195,30041,48457,76054,28490},
{27301,5324,15202,41082,87023,63071,16074,5336,13856,80137,27937,51453,0,34522,78452,55800,83838,60072,34016,0,30341,44871,85893,18673,73204,26849,1580,49150,40963,91453,63924,34616,90584,18079,47058,35541,8630,14390,67643,22909,83907,31516,31006,49802,0,2971}
    };
    const auto e_out = Solution::cutOffTree(forest);
    assert(e_out == 65669);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}