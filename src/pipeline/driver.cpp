#include "fetch_stage.h"
#include "decode_stage.h"
#include "execute_stage.h"
#include "memory_stage.h"
#include "writeback_stage.h"

#include <iostream>
#include <vector>
#include "../mem/cache.h"

uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory memory(10);
Cache cache(&memory, 5);
uint32_t registers[32];

std::vector<int> dependency_list;

MemorySystem *mem_sys = &cache; // cache enabled

void enable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Cache* cache) {
    fetch_stage.set_mem_sys(cache);
    memory_stage.set_mem_sys(cache);
}

void disable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Memory* memory) {
    fetch_stage.set_mem_sys(memory);
    memory_stage.set_mem_sys(memory);
}

void load_instructions_matmul_4x4() {
    memory.memory[0][0] = 2216689665;
    memory.memory[0][1] = 2082472032;
    memory.memory[0][2] = 2216689666;
    memory.memory[0][3] = 2082472033;
    memory.memory[1][0] = 2216689667;
    memory.memory[1][1] = 2082472034;
    memory.memory[1][2] = 2216689668;
    memory.memory[1][3] = 2082472035;
    memory.memory[2][0] = 2216689669;
    memory.memory[2][1] = 2082472036;
    memory.memory[2][2] = 2216689670;
    memory.memory[2][3] = 2082472037;
    memory.memory[3][0] = 2216689671;
    memory.memory[3][1] = 2082472038;
    memory.memory[3][2] = 2216689672;
    memory.memory[3][3] = 2082472039;
    memory.memory[4][0] = 2216689665;
    memory.memory[4][1] = 2082472040;
    memory.memory[4][2] = 2216689666;
    memory.memory[4][3] = 2082472041;
    memory.memory[5][0] = 2216689667;
    memory.memory[5][1] = 2082472042;
    memory.memory[5][2] = 2216689668;
    memory.memory[5][3] = 2082472043;
    memory.memory[6][0] = 2216689669;
    memory.memory[6][1] = 2082472044;
    memory.memory[6][2] = 2216689670;
    memory.memory[6][3] = 2082472045;
    memory.memory[7][0] = 2216689671;
    memory.memory[7][1] = 2082472046;
    memory.memory[7][2] = 2216689672;
    memory.memory[7][3] = 2082472047;
    memory.memory[8][0] = 2216689669;
    memory.memory[8][1] = 2082472048;
    memory.memory[8][2] = 2216689670;
    memory.memory[8][3] = 2082472049;
    memory.memory[9][0] = 2216689671;
    memory.memory[9][1] = 2082472050;
    memory.memory[9][2] = 2216689672;
    memory.memory[9][3] = 2082472051;
    memory.memory[10][0] = 2216689665;
    memory.memory[10][1] = 2082472052;
    memory.memory[10][2] = 2216689666;
    memory.memory[10][3] = 2082472053;
    memory.memory[11][0] = 2216689667;
    memory.memory[11][1] = 2082472054;
    memory.memory[11][2] = 2216689668;
    memory.memory[11][3] = 2082472055;
    memory.memory[12][0] = 2216689669;
    memory.memory[12][1] = 2082472056;
    memory.memory[12][2] = 2216689670;
    memory.memory[12][3] = 2082472057;
    memory.memory[13][0] = 2216689671;
    memory.memory[13][1] = 2082472058;
    memory.memory[13][2] = 2216689672;
    memory.memory[13][3] = 2082472059;
    memory.memory[14][0] = 2216689665;
    memory.memory[14][1] = 2082472060;
    memory.memory[14][2] = 2216689666;
    memory.memory[14][3] = 2082472061;
    memory.memory[15][0] = 2216689667;
    memory.memory[15][1] = 2082472062;
    memory.memory[15][2] = 2216689668;
    memory.memory[15][3] = 2082472063;
    memory.memory[16][0] = 2214592516;
    memory.memory[16][1] = 2216689664;
    memory.memory[16][2] = 2218786816;
    memory.memory[16][3] = 2220883968;
    memory.memory[17][0] = 2222981120;
    memory.memory[17][1] = 2225078368;
    memory.memory[17][2] = 2227175536;
    memory.memory[17][3] = 2248146944;
    memory.memory[18][0] = 2216689664;
    memory.memory[18][1] = 2222981120;
    memory.memory[18][2] = 149028864;
    memory.memory[18][3] = 14956544;
    memory.memory[19][0] = 15022080;
    memory.memory[19][1] = 2164719616;
    memory.memory[19][2] = 153354240;
    memory.memory[19][3] = 19089408;
    memory.memory[20][0] = 19286016;
    memory.memory[20][1] = 2169044992;
    memory.memory[20][2] = 155734016;
    memory.memory[20][3] = 2183168;
    memory.memory[21][0] = 1552154625;
    memory.memory[21][1] = 2416181322;
    memory.memory[21][2] = 165806080;
    memory.memory[21][3] = 31684608;
    memory.memory[22][0] = 32536576;
    memory.memory[22][1] = 2083454976;
    memory.memory[22][2] = 1549991937;
    memory.memory[22][3] = 2416115784;
    memory.memory[23][0] = 1547829249;
    memory.memory[23][1] = 2220883968;
    memory.memory[23][2] = 2416050248;
    memory.memory[23][3] = 4227858432;
}

void load_instructions_matmul_huge() {
    memory.memory[0][0] = 2214592512;
    memory.memory[0][1] = 2216690364;
    memory.memory[0][2] = 2080440320;
    memory.memory[0][3] = 2214592513;
    memory.memory[1][0] = 2216690365;
    memory.memory[1][1] = 2080440320;
    memory.memory[1][2] = 2214592514;
    memory.memory[1][3] = 2216690366;
    memory.memory[2][0] = 2080440320;
    memory.memory[2][1] = 2214592515;
    memory.memory[2][2] = 2216690367;
    memory.memory[2][3] = 2080440320;
    memory.memory[3][0] = 2214592516;
    memory.memory[3][1] = 2216690368;
    memory.memory[3][2] = 2080440320;
    memory.memory[3][3] = 2214592517;
    memory.memory[4][0] = 2216690369;
    memory.memory[4][1] = 2080440320;
    memory.memory[4][2] = 2214592518;
    memory.memory[4][3] = 2216690370;
    memory.memory[5][0] = 2080440320;
    memory.memory[5][1] = 2214592519;
    memory.memory[5][2] = 2216690371;
    memory.memory[5][3] = 2080440320;
    memory.memory[6][0] = 2214592520;
    memory.memory[6][1] = 2216690372;
    memory.memory[6][2] = 2080440320;
    memory.memory[6][3] = 2214592521;
    memory.memory[7][0] = 2216690373;
    memory.memory[7][1] = 2080440320;
    memory.memory[7][2] = 2214592522;
    memory.memory[7][3] = 2216690374;
    memory.memory[8][0] = 2080440320;
    memory.memory[8][1] = 2214592523;
    memory.memory[8][2] = 2216690375;
    memory.memory[8][3] = 2080440320;
    memory.memory[9][0] = 2214592524;
    memory.memory[9][1] = 2216690376;
    memory.memory[9][2] = 2080440320;
    memory.memory[9][3] = 2214592525;
    memory.memory[10][0] = 2216690377;
    memory.memory[10][1] = 2080440320;
    memory.memory[10][2] = 2214592526;
    memory.memory[10][3] = 2216690378;
    memory.memory[11][0] = 2080440320;
    memory.memory[11][1] = 2214592527;
    memory.memory[11][2] = 2216690379;
    memory.memory[11][3] = 2080440320;
    memory.memory[12][0] = 2214592528;
    memory.memory[12][1] = 2216690380;
    memory.memory[12][2] = 2080440320;
    memory.memory[12][3] = 2214592529;
    memory.memory[13][0] = 2216690381;
    memory.memory[13][1] = 2080440320;
    memory.memory[13][2] = 2214592530;
    memory.memory[13][3] = 2216690382;
    memory.memory[14][0] = 2080440320;
    memory.memory[14][1] = 2214592531;
    memory.memory[14][2] = 2216690383;
    memory.memory[14][3] = 2080440320;
    memory.memory[15][0] = 2214592532;
    memory.memory[15][1] = 2216690384;
    memory.memory[15][2] = 2080440320;
    memory.memory[15][3] = 2214592533;
    memory.memory[16][0] = 2216690385;
    memory.memory[16][1] = 2080440320;
    memory.memory[16][2] = 2214592534;
    memory.memory[16][3] = 2216690386;
    memory.memory[17][0] = 2080440320;
    memory.memory[17][1] = 2214592535;
    memory.memory[17][2] = 2216690387;
    memory.memory[17][3] = 2080440320;
    memory.memory[18][0] = 2214592536;
    memory.memory[18][1] = 2216690388;
    memory.memory[18][2] = 2080440320;
    memory.memory[18][3] = 2214592537;
    memory.memory[19][0] = 2216690389;
    memory.memory[19][1] = 2080440320;
    memory.memory[19][2] = 2214592538;
    memory.memory[19][3] = 2216690390;
    memory.memory[20][0] = 2080440320;
    memory.memory[20][1] = 2214592539;
    memory.memory[20][2] = 2216690391;
    memory.memory[20][3] = 2080440320;
    memory.memory[21][0] = 2214592540;
    memory.memory[21][1] = 2216690392;
    memory.memory[21][2] = 2080440320;
    memory.memory[21][3] = 2214592541;
    memory.memory[22][0] = 2216690393;
    memory.memory[22][1] = 2080440320;
    memory.memory[22][2] = 2214592542;
    memory.memory[22][3] = 2216690394;
    memory.memory[23][0] = 2080440320;
    memory.memory[23][1] = 2214592543;
    memory.memory[23][2] = 2216690395;
    memory.memory[23][3] = 2080440320;
    memory.memory[24][0] = 2214592544;
    memory.memory[24][1] = 2216690396;
    memory.memory[24][2] = 2080440320;
    memory.memory[24][3] = 2214592545;
    memory.memory[25][0] = 2216690397;
    memory.memory[25][1] = 2080440320;
    memory.memory[25][2] = 2214592546;
    memory.memory[25][3] = 2216690398;
    memory.memory[26][0] = 2080440320;
    memory.memory[26][1] = 2214592547;
    memory.memory[26][2] = 2216690399;
    memory.memory[26][3] = 2080440320;
    memory.memory[27][0] = 2214592548;
    memory.memory[27][1] = 2216690400;
    memory.memory[27][2] = 2080440320;
    memory.memory[27][3] = 2214592549;
    memory.memory[28][0] = 2216690401;
    memory.memory[28][1] = 2080440320;
    memory.memory[28][2] = 2214592550;
    memory.memory[28][3] = 2216690402;
    memory.memory[29][0] = 2080440320;
    memory.memory[29][1] = 2214592551;
    memory.memory[29][2] = 2216690403;
    memory.memory[29][3] = 2080440320;
    memory.memory[30][0] = 2214592552;
    memory.memory[30][1] = 2216690404;
    memory.memory[30][2] = 2080440320;
    memory.memory[30][3] = 2214592553;
    memory.memory[31][0] = 2216690405;
    memory.memory[31][1] = 2080440320;
    memory.memory[31][2] = 2214592554;
    memory.memory[31][3] = 2216690406;
    memory.memory[32][0] = 2080440320;
    memory.memory[32][1] = 2214592555;
    memory.memory[32][2] = 2216690407;
    memory.memory[32][3] = 2080440320;
    memory.memory[33][0] = 2214592556;
    memory.memory[33][1] = 2216690408;
    memory.memory[33][2] = 2080440320;
    memory.memory[33][3] = 2214592557;
    memory.memory[34][0] = 2216690409;
    memory.memory[34][1] = 2080440320;
    memory.memory[34][2] = 2214592558;
    memory.memory[34][3] = 2216690410;
    memory.memory[35][0] = 2080440320;
    memory.memory[35][1] = 2214592559;
    memory.memory[35][2] = 2216690411;
    memory.memory[35][3] = 2080440320;
    memory.memory[36][0] = 2214592560;
    memory.memory[36][1] = 2216690412;
    memory.memory[36][2] = 2080440320;
    memory.memory[36][3] = 2214592561;
    memory.memory[37][0] = 2216690413;
    memory.memory[37][1] = 2080440320;
    memory.memory[37][2] = 2214592562;
    memory.memory[37][3] = 2216690414;
    memory.memory[38][0] = 2080440320;
    memory.memory[38][1] = 2214592563;
    memory.memory[38][2] = 2216690415;
    memory.memory[38][3] = 2080440320;
    memory.memory[39][0] = 2214592564;
    memory.memory[39][1] = 2216690416;
    memory.memory[39][2] = 2080440320;
    memory.memory[39][3] = 2214592565;
    memory.memory[40][0] = 2216690417;
    memory.memory[40][1] = 2080440320;
    memory.memory[40][2] = 2214592566;
    memory.memory[40][3] = 2216690418;
    memory.memory[41][0] = 2080440320;
    memory.memory[41][1] = 2214592567;
    memory.memory[41][2] = 2216690419;
    memory.memory[41][3] = 2080440320;
    memory.memory[42][0] = 2214592568;
    memory.memory[42][1] = 2216690420;
    memory.memory[42][2] = 2080440320;
    memory.memory[42][3] = 2214592569;
    memory.memory[43][0] = 2216690421;
    memory.memory[43][1] = 2080440320;
    memory.memory[43][2] = 2214592570;
    memory.memory[43][3] = 2216690422;
    memory.memory[44][0] = 2080440320;
    memory.memory[44][1] = 2214592571;
    memory.memory[44][2] = 2216690423;
    memory.memory[44][3] = 2080440320;
    memory.memory[45][0] = 2214592572;
    memory.memory[45][1] = 2216690424;
    memory.memory[45][2] = 2080440320;
    memory.memory[45][3] = 2214592573;
    memory.memory[46][0] = 2216690425;
    memory.memory[46][1] = 2080440320;
    memory.memory[46][2] = 2214592574;
    memory.memory[46][3] = 2216690426;
    memory.memory[47][0] = 2080440320;
    memory.memory[47][1] = 2214592575;
    memory.memory[47][2] = 2216690427;
    memory.memory[47][3] = 2080440320;
    memory.memory[48][0] = 2214592576;
    memory.memory[48][1] = 2216690428;
    memory.memory[48][2] = 2080440320;
    memory.memory[48][3] = 2214592577;
    memory.memory[49][0] = 2216690429;
    memory.memory[49][1] = 2080440320;
    memory.memory[49][2] = 2214592578;
    memory.memory[49][3] = 2216690430;
    memory.memory[50][0] = 2080440320;
    memory.memory[50][1] = 2214592579;
    memory.memory[50][2] = 2216690431;
    memory.memory[50][3] = 2080440320;
    memory.memory[51][0] = 2214592580;
    memory.memory[51][1] = 2216690432;
    memory.memory[51][2] = 2080440320;
    memory.memory[51][3] = 2214592581;
    memory.memory[52][0] = 2216690433;
    memory.memory[52][1] = 2080440320;
    memory.memory[52][2] = 2214592582;
    memory.memory[52][3] = 2216690434;
    memory.memory[53][0] = 2080440320;
    memory.memory[53][1] = 2214592583;
    memory.memory[53][2] = 2216690435;
    memory.memory[53][3] = 2080440320;
    memory.memory[54][0] = 2214592584;
    memory.memory[54][1] = 2216690436;
    memory.memory[54][2] = 2080440320;
    memory.memory[54][3] = 2214592585;
    memory.memory[55][0] = 2216690437;
    memory.memory[55][1] = 2080440320;
    memory.memory[55][2] = 2214592586;
    memory.memory[55][3] = 2216690438;
    memory.memory[56][0] = 2080440320;
    memory.memory[56][1] = 2214592587;
    memory.memory[56][2] = 2216690439;
    memory.memory[56][3] = 2080440320;
    memory.memory[57][0] = 2214592588;
    memory.memory[57][1] = 2216690440;
    memory.memory[57][2] = 2080440320;
    memory.memory[57][3] = 2214592589;
    memory.memory[58][0] = 2216690441;
    memory.memory[58][1] = 2080440320;
    memory.memory[58][2] = 2214592590;
    memory.memory[58][3] = 2216690442;
    memory.memory[59][0] = 2080440320;
    memory.memory[59][1] = 2214592591;
    memory.memory[59][2] = 2216690443;
    memory.memory[59][3] = 2080440320;
    memory.memory[60][0] = 2214592592;
    memory.memory[60][1] = 2216690444;
    memory.memory[60][2] = 2080440320;
    memory.memory[60][3] = 2214592593;
    memory.memory[61][0] = 2216690445;
    memory.memory[61][1] = 2080440320;
    memory.memory[61][2] = 2214592594;
    memory.memory[61][3] = 2216690446;
    memory.memory[62][0] = 2080440320;
    memory.memory[62][1] = 2214592595;
    memory.memory[62][2] = 2216690447;
    memory.memory[62][3] = 2080440320;
    memory.memory[63][0] = 2214592596;
    memory.memory[63][1] = 2216690448;
    memory.memory[63][2] = 2080440320;
    memory.memory[63][3] = 2214592597;
    memory.memory[64][0] = 2216690449;
    memory.memory[64][1] = 2080440320;
    memory.memory[64][2] = 2214592598;
    memory.memory[64][3] = 2216690450;
    memory.memory[65][0] = 2080440320;
    memory.memory[65][1] = 2214592599;
    memory.memory[65][2] = 2216690451;
    memory.memory[65][3] = 2080440320;
    memory.memory[66][0] = 2214592600;
    memory.memory[66][1] = 2216690452;
    memory.memory[66][2] = 2080440320;
    memory.memory[66][3] = 2214592601;
    memory.memory[67][0] = 2216690453;
    memory.memory[67][1] = 2080440320;
    memory.memory[67][2] = 2214592602;
    memory.memory[67][3] = 2216690454;
    memory.memory[68][0] = 2080440320;
    memory.memory[68][1] = 2214592603;
    memory.memory[68][2] = 2216690455;
    memory.memory[68][3] = 2080440320;
    memory.memory[69][0] = 2214592604;
    memory.memory[69][1] = 2216690456;
    memory.memory[69][2] = 2080440320;
    memory.memory[69][3] = 2214592605;
    memory.memory[70][0] = 2216690457;
    memory.memory[70][1] = 2080440320;
    memory.memory[70][2] = 2214592606;
    memory.memory[70][3] = 2216690458;
    memory.memory[71][0] = 2080440320;
    memory.memory[71][1] = 2214592607;
    memory.memory[71][2] = 2216690459;
    memory.memory[71][3] = 2080440320;
    memory.memory[72][0] = 2214592608;
    memory.memory[72][1] = 2216690460;
    memory.memory[72][2] = 2080440320;
    memory.memory[72][3] = 2214592609;
    memory.memory[73][0] = 2216690461;
    memory.memory[73][1] = 2080440320;
    memory.memory[73][2] = 2214592610;
    memory.memory[73][3] = 2216690462;
    memory.memory[74][0] = 2080440320;
    memory.memory[74][1] = 2214592611;
    memory.memory[74][2] = 2216690463;
    memory.memory[74][3] = 2080440320;
    memory.memory[75][0] = 2214592512;
    memory.memory[75][1] = 2216690464;
    memory.memory[75][2] = 2080440320;
    memory.memory[75][3] = 2214592513;
    memory.memory[76][0] = 2216690465;
    memory.memory[76][1] = 2080440320;
    memory.memory[76][2] = 2214592514;
    memory.memory[76][3] = 2216690466;
    memory.memory[77][0] = 2080440320;
    memory.memory[77][1] = 2214592515;
    memory.memory[77][2] = 2216690467;
    memory.memory[77][3] = 2080440320;
    memory.memory[78][0] = 2214592516;
    memory.memory[78][1] = 2216690468;
    memory.memory[78][2] = 2080440320;
    memory.memory[78][3] = 2214592517;
    memory.memory[79][0] = 2216690469;
    memory.memory[79][1] = 2080440320;
    memory.memory[79][2] = 2214592518;
    memory.memory[79][3] = 2216690470;
    memory.memory[80][0] = 2080440320;
    memory.memory[80][1] = 2214592519;
    memory.memory[80][2] = 2216690471;
    memory.memory[80][3] = 2080440320;
    memory.memory[81][0] = 2214592520;
    memory.memory[81][1] = 2216690472;
    memory.memory[81][2] = 2080440320;
    memory.memory[81][3] = 2214592521;
    memory.memory[82][0] = 2216690473;
    memory.memory[82][1] = 2080440320;
    memory.memory[82][2] = 2214592522;
    memory.memory[82][3] = 2216690474;
    memory.memory[83][0] = 2080440320;
    memory.memory[83][1] = 2214592523;
    memory.memory[83][2] = 2216690475;
    memory.memory[83][3] = 2080440320;
    memory.memory[84][0] = 2214592524;
    memory.memory[84][1] = 2216690476;
    memory.memory[84][2] = 2080440320;
    memory.memory[84][3] = 2214592525;
    memory.memory[85][0] = 2216690477;
    memory.memory[85][1] = 2080440320;
    memory.memory[85][2] = 2214592526;
    memory.memory[85][3] = 2216690478;
    memory.memory[86][0] = 2080440320;
    memory.memory[86][1] = 2214592527;
    memory.memory[86][2] = 2216690479;
    memory.memory[86][3] = 2080440320;
    memory.memory[87][0] = 2214592528;
    memory.memory[87][1] = 2216690480;
    memory.memory[87][2] = 2080440320;
    memory.memory[87][3] = 2214592529;
    memory.memory[88][0] = 2216690481;
    memory.memory[88][1] = 2080440320;
    memory.memory[88][2] = 2214592530;
    memory.memory[88][3] = 2216690482;
    memory.memory[89][0] = 2080440320;
    memory.memory[89][1] = 2214592531;
    memory.memory[89][2] = 2216690483;
    memory.memory[89][3] = 2080440320;
    memory.memory[90][0] = 2214592532;
    memory.memory[90][1] = 2216690484;
    memory.memory[90][2] = 2080440320;
    memory.memory[90][3] = 2214592533;
    memory.memory[91][0] = 2216690485;
    memory.memory[91][1] = 2080440320;
    memory.memory[91][2] = 2214592534;
    memory.memory[91][3] = 2216690486;
    memory.memory[92][0] = 2080440320;
    memory.memory[92][1] = 2214592535;
    memory.memory[92][2] = 2216690487;
    memory.memory[92][3] = 2080440320;
    memory.memory[93][0] = 2214592536;
    memory.memory[93][1] = 2216690488;
    memory.memory[93][2] = 2080440320;
    memory.memory[93][3] = 2214592537;
    memory.memory[94][0] = 2216690489;
    memory.memory[94][1] = 2080440320;
    memory.memory[94][2] = 2214592538;
    memory.memory[94][3] = 2216690490;
    memory.memory[95][0] = 2080440320;
    memory.memory[95][1] = 2214592539;
    memory.memory[95][2] = 2216690491;
    memory.memory[95][3] = 2080440320;
    memory.memory[96][0] = 2214592540;
    memory.memory[96][1] = 2216690492;
    memory.memory[96][2] = 2080440320;
    memory.memory[96][3] = 2214592541;
    memory.memory[97][0] = 2216690493;
    memory.memory[97][1] = 2080440320;
    memory.memory[97][2] = 2214592542;
    memory.memory[97][3] = 2216690494;
    memory.memory[98][0] = 2080440320;
    memory.memory[98][1] = 2214592543;
    memory.memory[98][2] = 2216690495;
    memory.memory[98][3] = 2080440320;
    memory.memory[99][0] = 2214592544;
    memory.memory[99][1] = 2216690496;
    memory.memory[99][2] = 2080440320;
    memory.memory[99][3] = 2214592545;
    memory.memory[100][0] = 2216690497;
    memory.memory[100][1] = 2080440320;
    memory.memory[100][2] = 2214592546;
    memory.memory[100][3] = 2216690498;
    memory.memory[101][0] = 2080440320;
    memory.memory[101][1] = 2214592547;
    memory.memory[101][2] = 2216690499;
    memory.memory[101][3] = 2080440320;
    memory.memory[102][0] = 2214592548;
    memory.memory[102][1] = 2216690500;
    memory.memory[102][2] = 2080440320;
    memory.memory[102][3] = 2214592549;
    memory.memory[103][0] = 2216690501;
    memory.memory[103][1] = 2080440320;
    memory.memory[103][2] = 2214592550;
    memory.memory[103][3] = 2216690502;
    memory.memory[104][0] = 2080440320;
    memory.memory[104][1] = 2214592551;
    memory.memory[104][2] = 2216690503;
    memory.memory[104][3] = 2080440320;
    memory.memory[105][0] = 2214592552;
    memory.memory[105][1] = 2216690504;
    memory.memory[105][2] = 2080440320;
    memory.memory[105][3] = 2214592553;
    memory.memory[106][0] = 2216690505;
    memory.memory[106][1] = 2080440320;
    memory.memory[106][2] = 2214592554;
    memory.memory[106][3] = 2216690506;
    memory.memory[107][0] = 2080440320;
    memory.memory[107][1] = 2214592555;
    memory.memory[107][2] = 2216690507;
    memory.memory[107][3] = 2080440320;
    memory.memory[108][0] = 2214592556;
    memory.memory[108][1] = 2216690508;
    memory.memory[108][2] = 2080440320;
    memory.memory[108][3] = 2214592557;
    memory.memory[109][0] = 2216690509;
    memory.memory[109][1] = 2080440320;
    memory.memory[109][2] = 2214592558;
    memory.memory[109][3] = 2216690510;
    memory.memory[110][0] = 2080440320;
    memory.memory[110][1] = 2214592559;
    memory.memory[110][2] = 2216690511;
    memory.memory[110][3] = 2080440320;
    memory.memory[111][0] = 2214592560;
    memory.memory[111][1] = 2216690512;
    memory.memory[111][2] = 2080440320;
    memory.memory[111][3] = 2214592561;
    memory.memory[112][0] = 2216690513;
    memory.memory[112][1] = 2080440320;
    memory.memory[112][2] = 2214592562;
    memory.memory[112][3] = 2216690514;
    memory.memory[113][0] = 2080440320;
    memory.memory[113][1] = 2214592563;
    memory.memory[113][2] = 2216690515;
    memory.memory[113][3] = 2080440320;
    memory.memory[114][0] = 2214592564;
    memory.memory[114][1] = 2216690516;
    memory.memory[114][2] = 2080440320;
    memory.memory[114][3] = 2214592565;
    memory.memory[115][0] = 2216690517;
    memory.memory[115][1] = 2080440320;
    memory.memory[115][2] = 2214592566;
    memory.memory[115][3] = 2216690518;
    memory.memory[116][0] = 2080440320;
    memory.memory[116][1] = 2214592567;
    memory.memory[116][2] = 2216690519;
    memory.memory[116][3] = 2080440320;
    memory.memory[117][0] = 2214592568;
    memory.memory[117][1] = 2216690520;
    memory.memory[117][2] = 2080440320;
    memory.memory[117][3] = 2214592569;
    memory.memory[118][0] = 2216690521;
    memory.memory[118][1] = 2080440320;
    memory.memory[118][2] = 2214592570;
    memory.memory[118][3] = 2216690522;
    memory.memory[119][0] = 2080440320;
    memory.memory[119][1] = 2214592571;
    memory.memory[119][2] = 2216690523;
    memory.memory[119][3] = 2080440320;
    memory.memory[120][0] = 2214592572;
    memory.memory[120][1] = 2216690524;
    memory.memory[120][2] = 2080440320;
    memory.memory[120][3] = 2214592573;
    memory.memory[121][0] = 2216690525;
    memory.memory[121][1] = 2080440320;
    memory.memory[121][2] = 2214592574;
    memory.memory[121][3] = 2216690526;
    memory.memory[122][0] = 2080440320;
    memory.memory[122][1] = 2214592575;
    memory.memory[122][2] = 2216690527;
    memory.memory[122][3] = 2080440320;
    memory.memory[123][0] = 2214592576;
    memory.memory[123][1] = 2216690528;
    memory.memory[123][2] = 2080440320;
    memory.memory[123][3] = 2214592577;
    memory.memory[124][0] = 2216690529;
    memory.memory[124][1] = 2080440320;
    memory.memory[124][2] = 2214592578;
    memory.memory[124][3] = 2216690530;
    memory.memory[125][0] = 2080440320;
    memory.memory[125][1] = 2214592579;
    memory.memory[125][2] = 2216690531;
    memory.memory[125][3] = 2080440320;
    memory.memory[126][0] = 2214592580;
    memory.memory[126][1] = 2216690532;
    memory.memory[126][2] = 2080440320;
    memory.memory[126][3] = 2214592581;
    memory.memory[127][0] = 2216690533;
    memory.memory[127][1] = 2080440320;
    memory.memory[127][2] = 2214592582;
    memory.memory[127][3] = 2216690534;
    memory.memory[128][0] = 2080440320;
    memory.memory[128][1] = 2214592583;
    memory.memory[128][2] = 2216690535;
    memory.memory[128][3] = 2080440320;
    memory.memory[129][0] = 2214592584;
    memory.memory[129][1] = 2216690536;
    memory.memory[129][2] = 2080440320;
    memory.memory[129][3] = 2214592585;
    memory.memory[130][0] = 2216690537;
    memory.memory[130][1] = 2080440320;
    memory.memory[130][2] = 2214592586;
    memory.memory[130][3] = 2216690538;
    memory.memory[131][0] = 2080440320;
    memory.memory[131][1] = 2214592587;
    memory.memory[131][2] = 2216690539;
    memory.memory[131][3] = 2080440320;
    memory.memory[132][0] = 2214592588;
    memory.memory[132][1] = 2216690540;
    memory.memory[132][2] = 2080440320;
    memory.memory[132][3] = 2214592589;
    memory.memory[133][0] = 2216690541;
    memory.memory[133][1] = 2080440320;
    memory.memory[133][2] = 2214592590;
    memory.memory[133][3] = 2216690542;
    memory.memory[134][0] = 2080440320;
    memory.memory[134][1] = 2214592591;
    memory.memory[134][2] = 2216690543;
    memory.memory[134][3] = 2080440320;
    memory.memory[135][0] = 2214592592;
    memory.memory[135][1] = 2216690544;
    memory.memory[135][2] = 2080440320;
    memory.memory[135][3] = 2214592593;
    memory.memory[136][0] = 2216690545;
    memory.memory[136][1] = 2080440320;
    memory.memory[136][2] = 2214592594;
    memory.memory[136][3] = 2216690546;
    memory.memory[137][0] = 2080440320;
    memory.memory[137][1] = 2214592595;
    memory.memory[137][2] = 2216690547;
    memory.memory[137][3] = 2080440320;
    memory.memory[138][0] = 2214592596;
    memory.memory[138][1] = 2216690548;
    memory.memory[138][2] = 2080440320;
    memory.memory[138][3] = 2214592597;
    memory.memory[139][0] = 2216690549;
    memory.memory[139][1] = 2080440320;
    memory.memory[139][2] = 2214592598;
    memory.memory[139][3] = 2216690550;
    memory.memory[140][0] = 2080440320;
    memory.memory[140][1] = 2214592599;
    memory.memory[140][2] = 2216690551;
    memory.memory[140][3] = 2080440320;
    memory.memory[141][0] = 2214592600;
    memory.memory[141][1] = 2216690552;
    memory.memory[141][2] = 2080440320;
    memory.memory[141][3] = 2214592601;
    memory.memory[142][0] = 2216690553;
    memory.memory[142][1] = 2080440320;
    memory.memory[142][2] = 2214592602;
    memory.memory[142][3] = 2216690554;
    memory.memory[143][0] = 2080440320;
    memory.memory[143][1] = 2214592603;
    memory.memory[143][2] = 2216690555;
    memory.memory[143][3] = 2080440320;
    memory.memory[144][0] = 2214592604;
    memory.memory[144][1] = 2216690556;
    memory.memory[144][2] = 2080440320;
    memory.memory[144][3] = 2214592605;
    memory.memory[145][0] = 2216690557;
    memory.memory[145][1] = 2080440320;
    memory.memory[145][2] = 2214592606;
    memory.memory[145][3] = 2216690558;
    memory.memory[146][0] = 2080440320;
    memory.memory[146][1] = 2214592607;
    memory.memory[146][2] = 2216690559;
    memory.memory[146][3] = 2080440320;
    memory.memory[147][0] = 2214592608;
    memory.memory[147][1] = 2216690560;
    memory.memory[147][2] = 2080440320;
    memory.memory[147][3] = 2214592609;
    memory.memory[148][0] = 2216690561;
    memory.memory[148][1] = 2080440320;
    memory.memory[148][2] = 2214592610;
    memory.memory[148][3] = 2216690562;
    memory.memory[149][0] = 2080440320;
    memory.memory[149][1] = 2214592611;
    memory.memory[149][2] = 2216690563;
    memory.memory[149][3] = 2080440320;
    memory.memory[150][0] = 2214592522;
    memory.memory[150][1] = 2216689664;
    memory.memory[150][2] = 2218786816;
    memory.memory[150][3] = 2220883968;
    memory.memory[151][0] = 2222981120;
    memory.memory[151][1] = 2225078972;
    memory.memory[151][2] = 2227176224;
    memory.memory[151][3] = 2248146944;
    memory.memory[152][0] = 2216689664;
    memory.memory[152][1] = 2222981120;
    memory.memory[152][2] = 149028864;
    memory.memory[152][3] = 14956544;
    memory.memory[153][0] = 15022080;
    memory.memory[153][1] = 2164719616;
    memory.memory[153][2] = 153354240;
    memory.memory[153][3] = 19089408;
    memory.memory[154][0] = 19286016;
    memory.memory[154][1] = 2169044992;
    memory.memory[154][2] = 155734016;
    memory.memory[154][3] = 2183168;
    memory.memory[155][0] = 1552154625;
    memory.memory[155][1] = 2416181858;
    memory.memory[155][2] = 165806080;
    memory.memory[155][3] = 31684608;
    memory.memory[156][0] = 32536576;
    memory.memory[156][1] = 2083454976;
    memory.memory[156][2] = 1549991937;
    memory.memory[156][3] = 2416116320;
    memory.memory[157][0] = 1547829249;
    memory.memory[157][1] = 2220883968;
    memory.memory[157][2] = 2416050784;
    memory.memory[157][3] = 4227858432;
}

void load_instructions_1to100() {
  memory.memory[0][0] = 2214592512;
  memory.memory[0][1] = 2216689751;
  memory.memory[0][2] = 2082472156;
  memory.memory[0][3] = 2216689676;
  memory.memory[1][0] = 2082472157;
  memory.memory[1][1] = 2216689703;
  memory.memory[1][2] = 2082472158;
  memory.memory[1][3] = 2216689715;
  memory.memory[2][0] = 2082472159;
  memory.memory[2][1] = 2216689719;
  memory.memory[2][2] = 2082472160;
  memory.memory[2][3] = 2216689704;
  memory.memory[3][0] = 2082472161;
  memory.memory[3][1] = 2216689690;
  memory.memory[3][2] = 2082472162;
  memory.memory[3][3] = 2216689748;
  memory.memory[4][0] = 2082472163;
  memory.memory[4][1] = 2216689746;
  memory.memory[4][2] = 2082472164;
  memory.memory[4][3] = 2216689682;
  memory.memory[5][0] = 2082472165;
  memory.memory[5][1] = 2216689760;
  memory.memory[5][2] = 2082472166;
  memory.memory[5][3] = 2216689665;
  memory.memory[6][0] = 2082472167;
  memory.memory[6][1] = 2216689695;
  memory.memory[6][2] = 2082472168;
  memory.memory[6][3] = 2216689737;
  memory.memory[7][0] = 2082472169;
  memory.memory[7][1] = 2216689728;
  memory.memory[7][2] = 2082472170;
  memory.memory[7][3] = 2216689764;
  memory.memory[8][0] = 2082472171;
  memory.memory[8][1] = 2216689753;
  memory.memory[8][2] = 2082472172;
  memory.memory[8][3] = 2216689683;
  memory.memory[9][0] = 2082472173;
  memory.memory[9][1] = 2216689689;
  memory.memory[9][2] = 2082472174;
  memory.memory[9][3] = 2216689723;
  memory.memory[10][0] = 2082472175;
  memory.memory[10][1] = 2216689733;
  memory.memory[10][2] = 2082472176;
  memory.memory[10][3] = 2216689713;
  memory.memory[11][0] = 2082472177;
  memory.memory[11][1] = 2216689730;
  memory.memory[11][2] = 2082472178;
  memory.memory[11][3] = 2216689708;
  memory.memory[12][0] = 2082472179;
  memory.memory[12][1] = 2216689731;
  memory.memory[12][2] = 2082472180;
  memory.memory[12][3] = 2216689742;
  memory.memory[13][0] = 2082472181;
  memory.memory[13][1] = 2216689675;
  memory.memory[13][2] = 2082472182;
  memory.memory[13][3] = 2216689700;
  memory.memory[14][0] = 2082472183;
  memory.memory[14][1] = 2216689711;
  memory.memory[14][2] = 2082472184;
  memory.memory[14][3] = 2216689679;
  memory.memory[15][0] = 2082472185;
  memory.memory[15][1] = 2216689674;
  memory.memory[15][2] = 2082472186;
  memory.memory[15][3] = 2216689757;
  memory.memory[16][0] = 2082472187;
  memory.memory[16][1] = 2216689725;
  memory.memory[16][2] = 2082472188;
  memory.memory[16][3] = 2216689749;
  memory.memory[17][0] = 2082472189;
  memory.memory[17][1] = 2216689763;
  memory.memory[17][2] = 2082472190;
  memory.memory[17][3] = 2216689738;
  memory.memory[18][0] = 2082472191;
  memory.memory[18][1] = 2216689720;
  memory.memory[18][2] = 2082472192;
  memory.memory[18][3] = 2216689734;
  memory.memory[19][0] = 2082472193;
  memory.memory[19][1] = 2216689706;
  memory.memory[19][2] = 2082472194;
  memory.memory[19][3] = 2216689681;
  memory.memory[20][0] = 2082472195;
  memory.memory[20][1] = 2216689701;
  memory.memory[20][2] = 2082472196;
  memory.memory[20][3] = 2216689717;
  memory.memory[21][0] = 2082472197;
  memory.memory[21][1] = 2216689710;
  memory.memory[21][2] = 2082472198;
  memory.memory[21][3] = 2216689684;
  memory.memory[22][0] = 2082472199;
  memory.memory[22][1] = 2216689669;
  memory.memory[22][2] = 2082472200;
  memory.memory[22][3] = 2216689724;
  memory.memory[23][0] = 2082472201;
  memory.memory[23][1] = 2216689671;
  memory.memory[23][2] = 2082472202;
  memory.memory[23][3] = 2216689726;
  memory.memory[24][0] = 2082472203;
  memory.memory[24][1] = 2216689716;
  memory.memory[24][2] = 2082472204;
  memory.memory[24][3] = 2216689668;
  memory.memory[25][0] = 2082472205;
  memory.memory[25][1] = 2216689739;
  memory.memory[25][2] = 2082472206;
  memory.memory[25][3] = 2216689677;
  memory.memory[26][0] = 2082472207;
  memory.memory[26][1] = 2216689729;
  memory.memory[26][2] = 2082472208;
  memory.memory[26][3] = 2216689762;
  memory.memory[27][0] = 2082472209;
  memory.memory[27][1] = 2216689697;
  memory.memory[27][2] = 2082472210;
  memory.memory[27][3] = 2216689699;
  memory.memory[28][0] = 2082472211;
  memory.memory[28][1] = 2216689747;
  memory.memory[28][2] = 2082472212;
  memory.memory[28][3] = 2216689694;
  memory.memory[29][0] = 2082472213;
  memory.memory[29][1] = 2216689758;
  memory.memory[29][2] = 2082472214;
  memory.memory[29][3] = 2216689735;
  memory.memory[30][0] = 2082472215;
  memory.memory[30][1] = 2216689691;
  memory.memory[30][2] = 2082472216;
  memory.memory[30][3] = 2216689750;
  memory.memory[31][0] = 2082472217;
  memory.memory[31][1] = 2216689759;
  memory.memory[31][2] = 2082472218;
  memory.memory[31][3] = 2216689696;
  memory.memory[32][0] = 2082472219;
  memory.memory[32][1] = 2216689687;
  memory.memory[32][2] = 2082472220;
  memory.memory[32][3] = 2216689756;
  memory.memory[33][0] = 2082472221;
  memory.memory[33][1] = 2216689718;
  memory.memory[33][2] = 2082472222;
  memory.memory[33][3] = 2216689666;
  memory.memory[34][0] = 2082472223;
  memory.memory[34][1] = 2216689680;
  memory.memory[34][2] = 2082472224;
  memory.memory[34][3] = 2216689743;
  memory.memory[35][0] = 2082472225;
  memory.memory[35][1] = 2216689721;
  memory.memory[35][2] = 2082472226;
  memory.memory[35][3] = 2216689670;
  memory.memory[36][0] = 2082472227;
  memory.memory[36][1] = 2216689685;
  memory.memory[36][2] = 2082472228;
  memory.memory[36][3] = 2216689744;
  memory.memory[37][0] = 2082472229;
  memory.memory[37][1] = 2216689709;
  memory.memory[37][2] = 2082472230;
  memory.memory[37][3] = 2216689712;
  memory.memory[38][0] = 2082472231;
  memory.memory[38][1] = 2216689722;
  memory.memory[38][2] = 2082472232;
  memory.memory[38][3] = 2216689741;
  memory.memory[39][0] = 2082472233;
  memory.memory[39][1] = 2216689673;
  memory.memory[39][2] = 2082472234;
  memory.memory[39][3] = 2216689714;
  memory.memory[40][0] = 2082472235;
  memory.memory[40][1] = 2216689705;
  memory.memory[40][2] = 2082472236;
  memory.memory[40][3] = 2216689692;
  memory.memory[41][0] = 2082472237;
  memory.memory[41][1] = 2216689702;
  memory.memory[41][2] = 2082472238;
  memory.memory[41][3] = 2216689732;
  memory.memory[42][0] = 2082472239;
  memory.memory[42][1] = 2216689754;
  memory.memory[42][2] = 2082472240;
  memory.memory[42][3] = 2216689667;
  memory.memory[43][0] = 2082472241;
  memory.memory[43][1] = 2216689761;
  memory.memory[43][2] = 2082472242;
  memory.memory[43][3] = 2216689688;
  memory.memory[44][0] = 2082472243;
  memory.memory[44][1] = 2216689686;
  memory.memory[44][2] = 2082472244;
  memory.memory[44][3] = 2216689740;
  memory.memory[45][0] = 2082472245;
  memory.memory[45][1] = 2216689727;
  memory.memory[45][2] = 2082472246;
  memory.memory[45][3] = 2216689745;
  memory.memory[46][0] = 2082472247;
  memory.memory[46][1] = 2216689678;
  memory.memory[46][2] = 2082472248;
  memory.memory[46][3] = 2216689736;
  memory.memory[47][0] = 2082472249;
  memory.memory[47][1] = 2216689693;
  memory.memory[47][2] = 2082472250;
  memory.memory[47][3] = 2216689755;
  memory.memory[48][0] = 2082472251;
  memory.memory[48][1] = 2216689752;
  memory.memory[48][2] = 2082472252;
  memory.memory[48][3] = 2216689707;
  memory.memory[49][0] = 2082472253;
  memory.memory[49][1] = 2216689698;
  memory.memory[49][2] = 2082472254;
  memory.memory[49][3] = 2216689672;
  memory.memory[50][0] = 2082472255;
  memory.memory[50][1] = 2218786816;
  memory.memory[50][2] = 2220884067;
  memory.memory[50][3] = 2229272676;
  memory.memory[51][0] = 2353201368;
  memory.memory[51][1] = 1552023553;
  memory.memory[51][2] = 2357657814;
  memory.memory[51][3] = 2158231772;
  memory.memory[52][0] = 2160197852;
  memory.memory[52][1] = 2697265364;
  memory.memory[52][2] = 2090991836;
  memory.memory[52][3] = 2093220060;
  memory.memory[53][0] = 1552154625;
  memory.memory[53][1] = 3154116814;
  memory.memory[53][2] = 1547829249;
  memory.memory[53][3] = 3154116812;
  memory.memory[54][0] = 4227858432;
}

int main() {
    std::string temp;
    // initializations (right now, just confirming stuff gets instantiated)
    memory.set_initial_delay(0);
    std::cout << memory.initial_delay << std::endl;


    cache.set_initial_delay(0);
    std::cout << cache.initial_delay << std::endl;

    //load_instructions_1to100();
    load_instructions_matmul_huge();
    
    WritebackStage wb_stage(registers, &PROGRAM_COUNTER, dependency_list);
    MemoryStage mem_stage(wb_stage, mem_sys);
    ExecuteStage execute_stage(mem_stage);
    DecodeStage decode_stage(execute_stage, registers, dependency_list);
    FetchStage fetch_stage(&PROGRAM_COUNTER, mem_sys, decode_stage);
    //fetch_stage.disable_pipeline(); // disable pipeline
    // one can also disable the pipeline using the fetch constructor
    // fetch_stage(&PROGRAM_COUNTER, &cache, decode_stage, true);

    // disable_cache(fetch_stage, mem_stage, &memory); // disable cache

    while(true) {
        std::cout << "CLOCK: " << CLK << std::endl;
        std::cout << "PROGRAM COUNTER: " << PROGRAM_COUNTER << std::endl;
        if (wb_stage.exit) {
            break; // in gui code, just return
        }
        wb_stage.tick();
        if (wb_stage.exit || wb_stage.squashed) {
            std::cout << "!! CLEARING DEPENDENCY LIST  !!" << std::endl;
            dependency_list.clear();
            std::cout << "!! SQUASHING PREVIOUS STAGES !!" << std::endl;
            mem_stage.reset();
            execute_stage.reset();
            decode_stage.reset();
            fetch_stage.reset();
        } 
        else {
            mem_stage.tick();
            execute_stage.tick();
            decode_stage.tick();
            fetch_stage.tick();
        }
        CLK++;
    }

    return 0;
}
