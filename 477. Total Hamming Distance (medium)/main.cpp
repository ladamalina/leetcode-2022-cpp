#include <algorithm>
#include <bitset>
#include <cassert>
#include <vector>

class Solution {
 public:
  static int totalHammingDistance(std::vector<int>& nums) {
    auto nums_len = nums.size();
    if (nums_len == 1)
      return 0;

    auto max_num_it = std::max_element(nums.begin(), nums.end());
    auto max_num_bits = std::bitset<32>(*max_num_it);
    uint16_t max_bits_len = 32;
    for (int i = 31; i >= 0; --i) {
      if (max_num_bits[i])
        break;
      else
        --max_bits_len;
    }
    std::vector<std::bitset<32>> nums_bits;
    nums_bits.reserve(nums.size());
    std::for_each(nums.begin(), nums.end(), [&nums_bits](const int& n) {
      nums_bits.push_back(std::bitset<32>(n));
    });

    unsigned long total_distance = 0;
    for (int bit_idx = max_bits_len-1; bit_idx >= 0; --bit_idx) {
      auto ones = std::count_if(nums_bits.begin(), nums_bits.end(), [&bit_idx](const auto& n_bits){
        return n_bits[bit_idx];
      });
      total_distance += ones * (nums_len - ones);
    }

    return total_distance;
  }
};

int main() {
  std::vector<int> v1{4,14,2};
  assert(Solution::totalHammingDistance(v1) == 6);

  std::vector<int> v2{1337};
  assert(Solution::totalHammingDistance(v2) == 0);

  std::vector<int> v3{1337,7331};
  assert(Solution::totalHammingDistance(v3) == 7);

  std::vector<int> v4{9156497,7921475,1238122,5137252,2571595,1247336,9996950,9335717,7869544,4969540,1793614,13753,2340805,9571521,2166055,3939920,2596830,167470,9247776,702425,1521717,3909411,7190355,3533786,6816320,8890771,3151619,3117270,5509228,3050486,2371098,6979705,5815663,1879415,5793378,2189086,9328137,5449261,1630208,5240536,540647,3592142,719032,8999943,4766644,5739924,3483309,3642161,9053300,6851386,1528010,4348240,4076638,8992140,6690845,7425449,5976240,1180493,3102384,7994405,5673875,6896746,6579440,6463482,1711600,1864656,3496245,9012868,7006363,9047201,8116405,5788761,7706835,5804825,8595949,5459537,4643339,4256503,3551636,9767381,2867606,772319,6274373,401043,5483270,6209780,5137337,5817101,6442924,2424630,8248739,2963054,4750852,2614647,3479345,8394635,7337476,971186,7435660,9941561,8842552,4540066,1435126,9568832,7919944,9186873,5762749,6798685,6560658,5129920,6487204,4956521,1900527,3264474,8695609,2917312,6225259,1521978,4571572,4162780,7559089,4624271,4514784,8123708,9705928,2227258,4823162,8233216,5532258,5048275,1152290,1950030,4878083,6831840,8559765,5330829,1222497,6161699,7423282,8042959,4283752,6379245,8842254,6903847,1253569,6876291,6823368,5301862,6664995,3912411,7169866,4795453,8452742,6583537,3888162,90879,8822973,5917302,4854395,7501759,4972984,9553811,9232909,5077624,9918112,4293720,6065198,1976066,9089266,6153147,8543484,1222106,675164,7927824,8724120,3886133,6430965,604916,1988512,7230632,7490747,4094970,7221175,7845258,6750540,9543668,4807308,9607282,3675138,9234159,2452552,4938527,2588789,6379317,8832514,9602312,9702859,5623352,9529398,4406818,718394,995454,8988204,7501738,8604704,7291179,125151,2204744,6950766,2325824,7955411,471274,404954,132693,6827849,6415607,4773877,2191088,7478572,9560389,2767933,3874408,9719735,1121641,9550664,2356613,6432223,1961877,1913500,4338440,801637,4486711,3401132,1059723,4742862,2875984,2710565,2197302,3383336,710040,1200822,3473130,1051196,741862,3742309,6190688,5036448,2039035,7941382,9372228,8303609,7284454,550610,7620216,4671670,2797131,6772950,7499026,4413521,6503114,7683513,3234904,4231220,6882257,895061,6264787,5090719,9011419,7079176,7499401,197992,8427651,9428367,4608336,1198060,7616796,2352043,1915100,5855572,4458620,9505230,8092131,3968066,8727605,7955707,8301613,3217280,5382940,9050273,1350665,2616340,5047016,9090811,212407,6118822,4928434,8836229,5718337,6077135,6753201,8128651,3988794,4461389,5874256,8266853,3906072,5147093,1649550,4868549,3875525,6708710,3820948,425181,359814,5890869,7695299,1796162,8853322,7503209,1647980,4115828,7184514,2508632,4326952,7983022,9259906,8342247,8794630,5694945,6087657,3642901,9627123,3722758,2438966,8245979,1994000,3407917,7125884,9360891,3868627,9138401,5903313,6063252,826354,28441,2756930,2504144,1448204,2653755,6048677,3652375,673552,6727162,9926578,8579981,2628986,443805,7785559,3954047,2624585,2751732,2622757,743758,3136226,4439586,3448369,5840981,7320128,4245285,844755,7735090,9220544,8464934,806770,9016796,3939704,9698427,2998085,3607513,8801476,4649690,3242181,8826626,8045182,2730715,2810105,6611412,6335487,7328038,2774230,7419468,7484239,1813101,522071,437398,8546400,9271675,9257250,4267455,217166,1600514,3013612,889534,6883209,1277283,1836134,6722257,7962199,5426189,4637459,3918831,5558741,2436675,47789,8198967,383271,5065247,4323582,1129677,2062896,8180875,8648340,6345919,1146150,1136561,4646616,2966864,1213479,6796396,6442081,4485417,3379141,4526208,2080877,829031,3203869,7635219,8690448,5137829,7980168,2194194,8033760,9494871,5974886,9936327,9575957,311531,6812466,7446016,8225742,2985962,1810253,2091135,3404794,1126912,8660763,8512901,1964916,5325038,7359673,2205275,1934814,4165994,368674,7351957,705552,1695695,9739853,9165954,5522319,3881745,6315671,8999350,4007759,169389,9469743,9359524,6818147,2361983,8456278,3417823,9631359,718788,3588547,9215113,6758607,1842760,3796373,4707246,6004139,9347077,7147462,2677581,476926,2452007,21332,6619369,2877807,5210835,4225386,6065396,1149628,5088486,6674168,1930599,2453242,2304468,6306742,5813979,3667071,1744535,7264310,2387693,7708781,2890957,1032353,8324896,9557884,3826264,6228015,6376004,5701991,2725335,4848869,6045897,4638048,2902709,2837283,6247525,6615639,4002807,4527147,334805,5994364,7777029,362603,7821282,1876105,3201211,2962213,1271409,8406971,302897,7502406,1955338,3738794,8840350,3683475,8608230,1866304,7086403,1558856,8715630,6034390,3972255,4492217,1742052,6006485,7003586,603697,3057489,9245718,2175398,2556898,984347,3518720,9968236,7654964,6223130,321609,6407167,8036664,470155,8008297,7307341,767775,6360187,9268605,8744762,7823670,5737935,4545276,6922484,2071650,2117020,7506077,9148766,3223536,6452221,4999041,2119742,5162286,5134944,7584418,7382663,2199560,4021700,2612419,3008325,4505328,5946206,9774924,6650250,1116419,2562865,110049,5822631,3967368,8676140,1166541,9298831,5149988,947080,4486341,7442743,4559386,3077144,7600835,3621560,1650626,4602483,5117556,502367,3991094,4753112,2719777,3266453,2995218,568178,3708145,3464654,9405886,9581438,5149075,2746822,620789,6993310,2488430,5052139,7179540,3796747,1694754,3620067,6680886,1296847,1777482,4852116,2876626,9302237,9583361,8091713,8501698,3325250,462240,5624405,6920522,3678050,162611,1002630,8893546,6754289,5115910,9373780,4218516,2464663,305015,3482944,4684606,379792,3478026,5798692,7944327,1159710,9850303,2980503,1176061,8997072,1262790,8389373,1450110,3131187,1001424,5555082,3672218,6784098,9366283,4324662,5724080,4597935,2359588,4309490,8179456,2417696,4915313,9700983,2659821,7909295,6178017,9862997,4646492,6166220,8812016,420048,1357127,7861284,953188,4761986,8400830,3229554,4481079,9355154,4026801,5412794,2058762,2381005,5607964,5282992,3592216,543130,7535877,5845390,8429634,421583,3080561,5504310,2380128,7877916,1602433,4915400,1985745,9045842,2601513,5299006,4512227,7134677,1861418,5362444,1109736,2578997,6036062,807269,4243623,1919411,2204572,6395027,7937905,7818621,7245570,4431956,2051093,2540210,1942730,9682361,5358334,7697454,7664402,2115240,2993904,8925269,1830305,5685032,1861377,6185869,2914315,664148,3042113,7828729,7999725,3621049,5092915,6621281,8523502,5767944,5363361,7376775,2765988,1108128,7507342,6685155,7504553,1062743,6278357,9358330,5849123,4162722,2736706,8342777,5060628,67918,5298957,833217,8748503,1737213,8571435,3238984,2803780,7179738,1109200,4485890,76541,8104408,2598472,6863098,9454348,3134360,436012,4473543,8362090,4033929,7503957,4082526,7524246,1919883,748522,8913460,73465,8878231,1004686,9294514,8272636,4948530,4526568,8514709,793014,9299749,3141613,2000317,1745492,4510276,1105441,5857644,1178548,9146479,9502503,3344444,7254220,4958840,4158937,9549721,5592167,3325991,4440470,5801135,9401119,5782201,1865092,3036051,2921919,8938532,4695100,1652562,8009834,1492346,8667858,7207945,9473315,8018706,9902360,4573079,4207505,3722518,5640463,4562907,1950192,6776016,6647777,9122950,8555669,7651024,9132303,6055939,5017098,9711519,2301172,9093959,692886,4666257,2157706,2916587,5215830,7474661,4606567,901877,8699989,5189017,1105905,5549668,3977877,1667081,9435401,6509042,5744720,5555747,4330719,2152259,713614,4033863,1798982,2615240,7033272,2435964,7747167,8732170,344150,7330866,3373648,3854959,9283235,2600506,6713024,5682833,4689029,5023800,444478,822937,7970742,4473102,4630471,2519315,3785489,3643215,3392009,8249864,8708815,5402687,4097968,8310251,8656347,7803900,5540657,6117376,2746822,9886632,3359982,2827542,1998405,2937683,5013280,8702259,9323773,9982203,6889423,6401444,5056515,7351103,7618664,8464095,9912009,512486,4365526,2311573,223298,9593617,1184483,6131201,3760642,1320862,4022165,5924853,634852,1579686,1828216,6330341,9159395,9132783,9697143,8471786,7738799,9480595,7381109,3699971,3138125,6739391,1123869,4401394,5145049,4607884,3127340,6832830,221918,5101200,2356565,2509819,3407862,3515589,5865474,103179,5990562,8867571,8375553,5025394,9142391,2307999,9116524,8002819,4629797,7083619,8799281,8199814,8773024};
  assert(Solution::totalHammingDistance(v4) == 5867094);

  return 0;
}
