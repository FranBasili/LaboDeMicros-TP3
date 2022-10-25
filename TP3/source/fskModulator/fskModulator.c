#include "fskModulator\fskModulator.h"

const uint8_t index_versions[][2] = {{fL1 / SINFREC, fH1 / SINFREC}, {fL2 / SINFREC, fH2 / SINFREC}};
static uint8_t index_step[2];

void fskModulatorInit(uint8_t config_version)
{
        index_step[0]=index_versions[config_version][0];
        index_step[1]=index_versions[config_version][1];
}

void fskModulate(uint8_t msg, uint16_t buffer[BUFFSIZE])
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