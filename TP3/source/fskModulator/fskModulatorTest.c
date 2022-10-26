#include <stdint.h>
#include <stdio.h>


#define SINSAMPLES  256
#define SINFREC     200
#define DACFREQ     SINFREC*SINSAMPLES
#define BUFFSIZE    336

#define fL1     1200
#define fL2     1200
#define fH1     2200
#define fH2     2400

typedef uint16_t fskbuffer[BUFFSIZE]; 

const uint16_t senoidal[SINSAMPLES] = {2048, 2098, 2148, 2199, 2249, 2299, 2349, 2399, 2449, 2498, 2547, 2596,
                                       2644, 2692, 2740, 2787, 2834, 2880, 2926, 2972, 3016, 3061, 3104, 3147,
                                       3189, 3231, 3272, 3312, 3351, 3390, 3427, 3464, 3500, 3535, 3569, 3603,
                                       3635, 3667, 3697, 3726, 3755, 3782, 3808, 3834, 3858, 3881, 3903, 3924,
                                       3943, 3962, 3979, 3995, 4010, 4024, 4037, 4048, 4058, 4067, 4075, 4081,
                                       4087, 4091, 4094, 4095, 4095, 4095, 4092, 4089, 4084, 4078, 4071, 4063,
                                       4053, 4043, 4031, 4017, 4003, 3987, 3971, 3953, 3934, 3913, 3892, 3869,
                                       3846, 3821, 3795, 3769, 3741, 3712, 3682, 3651, 3619, 3586, 3552, 3518,
                                       3482, 3446, 3408, 3370, 3331, 3292, 3251, 3210, 3168, 3126, 3082, 3039,
                                       2994, 2949, 2903, 2857, 2811, 2764, 2716, 2668, 2620, 2571, 2523, 2473,
                                       2424, 2374, 2324, 2274, 2224, 2174, 2123, 2073, 2022, 1972, 1921, 1871,
                                       1821, 1771, 1721, 1671, 1622, 1572, 1524, 1475, 1427, 1379, 1331, 1284,
                                       1238, 1192, 1146, 1101, 1056, 1013,  969,  927,  885,  844,  803,  764,
                                        725,  687,  649,  613,  577,  543,  509,  476,  444,  413,  383,  354,
                                        326,  300,  274,  249,  226,  203,  182,  161,  142,  124,  108,   92,
                                         78,   64,   52,   42,   32,   24,   17,   11,    6,    3,    0,    0,
                                          0,    1,    4,    8,   14,   20,   28,   37,   47,   58,   71,   85,
                                        100,  116,  133,  152,  171,  192,  214,  237,  261,  287,  313,  340,
                                        369,  398,  428,  460,  492,  526,  560,  595,  631,  668,  705,  744,
                                        783,  823,  864,  906,  948,  991, 1034, 1079, 1123, 1169, 1215, 1261,
                                       1308, 1355, 1403, 1451, 1499, 1548, 1597, 1646, 1696, 1746, 1796, 1846,
                                       1896, 1947, 1997, 2047};

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
void fskModulatorInit(uint8_t config_version);
void fskModulate(uint8_t msg, fskbuffer buffer);

const uint8_t index_versions[][2] = {{fH1 / SINFREC, fL1 / SINFREC}, {fH2 / SINFREC, fL2 / SINFREC}};
static uint8_t index_step[2];

void fskModulatorInit(uint8_t config_version)
{
        index_step[0]=index_versions[config_version][0];
        index_step[1]=index_versions[config_version][1];
}

void fskModulate(uint8_t msg, fskbuffer buffer)
{
        uint16_t counter=0;
        uint8_t fsk_index=0, step; 
        for (int bit = 7; bit >= 0 && bit<=7; bit--){           
                step = index_step[(msg>>bit) & 0x01];           
                for (uint8_t cont = 0; cont<43; cont++){
                        buffer[counter++] = senoidal[fsk_index];
                        fsk_index+= step;                       
                }
        }
}

int main(){
    fskbuffer buff;
    fskModulatorInit(0);
    fskModulate((uint8_t)0b10100101, buff);
    
    for(long int i=0; i<(BUFFSIZE); i++){
        printf("%d ,", buff[i]);
    }
    
    return 1;
}

