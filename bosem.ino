#include <Nextion.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <SPI.h>
#include <SD.h>
File myFile;
VL53L0X sensor;
const int SoilSensor = A0;

//buffers
char txtSensorSV[10] = {'0'};
uint16_t LentxtSensorSV = sizeof(txtSensorSV);
int bit_array[25];        // For storing the data bit. bit_array[0] = data bit 1 (LSB), bit_array[23] = data bit 24 (MSB).
unsigned long time_now;
//statics
char txSensorSV[10] = {'0'};
char result[10] = {0};

float batasBawah = 400;
// Pin Declarations
int DATA_PIN = 4;
int CLOCK_PIN = 5;
// Variables
int clock = 1;
int lastClock = 1;
unsigned long time = 0;
unsigned long timeStart = 0;
int out = 0;

//Acra seedling
//Tinggi
NexText tTinggi = NexText(2, 31, "tTinggi");
NexText tTingStat = NexText(2, 14, "tTingStat");
NexButton bUkurTinggi = NexButton(2, 19, "bUkurTinggi");

//RTC NEXTION

//Diameter
NexText tDim = NexText(2, 32, "tDim");
NexText tDimStat = NexText(2, 15, "tDimStat");
NexButton bUkurDim = NexButton(2, 20, "bUkurDim");

//Panjang internode
NexText tPjg = NexText(2, 34, "tPjg");
NexText tPjgTing = NexText(2, 33, "tPjgTing");
NexText tPjgStat = NexText(2, 16, "tPjgStat");
NexButton addPjg = NexButton(2, 21, "addPjg");
NexButton minPjg = NexButton(2, 27, "minPjg");

//HDRatio
NexText tHdrat = NexText(2, 35, "tHdrat");
NexText tHdratStat = NexText(2, 17, "tHdratStat");
NexButton bUkurHD = NexButton(2, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun = NexText(2, 36, "tJmlDaun");
NexText tJmlDaunStat = NexText(2, 18, "tJmlDaunStat");
NexButton addDaun = NexButton(2, 28, "addDaun");
NexButton minDaun = NexButton(2, 29, "minDaun");

//KelTanah
NexText tKelTanah = NexText(2, 37, "tKelTanah");
NexText tKelTanahStat = NexText(2, 25, "tKelTanahStat");
NexButton bUkurKelTanah = NexButton(2, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan = NexButton(2, 23, "bSimpan");
NexButton Analisa = NexButton(2, 30, "Analisa");
NexText tLulus = NexText(2, 13, "tLulus");
//End OF Acra seedling

//Acra Cutting
//Tinggi
NexText tTinggi2 = NexText(3, 31, "tTinggi");
NexText tTingStat2 = NexText(3, 14, "tTingStat");
NexButton bUkurTinggi2 = NexButton(3, 19, "bUkurTinggi");

//Diameter
NexText tDim2 = NexText(3, 32, "tDim");
NexText tDimStat2 = NexText(3, 15, "tDimStat");
NexButton bUkurDim2 = NexButton(3, 20, "bUkurDim");

//Panjang internode
NexText tPjg2 = NexText(3, 34, "tPjg");
NexText tPjgTing2 = NexText(3, 33, "tPjgTing");
NexText tPjgStat2 = NexText(3, 16, "tPjgStat");
NexButton addPjg2 = NexButton(3, 21, "addPjg");
NexButton minPjg2 = NexButton(3, 27, "minPjg");

//HDRatio
NexText tHdrat2 = NexText(3, 35, "tHdrat");
NexText tHdratStat2 = NexText(3, 17, "tHdratStat");
NexButton bUkurHD2 = NexButton(3, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun2 = NexText(3, 36, "tJmlDaun");
NexText tJmlDaunStat2 = NexText(3, 18, "tJmlDaunStat");
NexButton addDaun2 = NexButton(3, 28, "addDaun");
NexButton minDaun2 = NexButton(3, 29, "minDaun");

//KelTanah
NexText tKelTanah2 = NexText(3, 37, "tKelTanah");
NexText tKelTanahStat2 = NexText(3, 25, "tKelTanahStat");
NexButton bUkurKelTanah2 = NexButton(3, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan2 = NexButton(3, 23, "bSimpan");
NexButton Analisa2 = NexButton(3, 30, "Analisa");
NexText tLulus2 = NexText(3, 13, "tLulus");
//End OF Acra Cutting

//EP0077A PT
//Tinggi
NexText tTinggi3 = NexText(4, 31, "tTinggi");
NexText tTingStat3 = NexText(4, 14, "tTingStat");
NexButton bUkurTinggi3 = NexButton(4, 19, "bUkurTinggi");

//Diameter
NexText tDim3 = NexText(4, 32, "tDim");
NexText tDimStat3 = NexText(4, 15, "tDimStat");
NexButton bUkurDim3 = NexButton(4, 20, "bUkurDim");

//Panjang internode
NexText tPjg3 = NexText(4, 34, "tPjg");
NexText tPjgTing3 = NexText(4, 33, "tPjgTing");
NexText tPjgStat3 = NexText(4, 16, "tPjgStat");
NexButton addPjg3 = NexButton(4, 21, "addPjg");
NexButton minPjg3 = NexButton(4, 27, "minPjg");

//HDRatio
NexText tHdrat3 = NexText(4, 35, "tHdrat");
NexText tHdratStat3 = NexText(4, 17, "tHdratStat");
NexButton bUkurHD3 = NexButton(4, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun3 = NexText(4, 36, "tJmlDaun");
NexText tJmlDaunStat3 = NexText(4, 18, "tJmlDaunStat");
NexButton addDaun3 = NexButton(4, 28, "addDaun");
NexButton minDaun3 = NexButton(4, 29, "minDaun");

//KelTanah
NexText tKelTanah3 = NexText(4, 37, "tKelTanah");
NexText tKelTanahStat3 = NexText(4, 25, "tKelTanahStat");
NexButton bUkurKelTanah3 = NexButton(4, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan3 = NexButton(4, 23, "bSimpan");
NexButton Analisa3 = NexButton(4, 30, "Analisa");
NexText tLulus3 = NexText(4, 13, "tLulus");
//End OF EP0077A PT

//EP0361WK PT
//Tinggi
NexText tTinggi4 = NexText(5, 31, "tTinggi");
NexText tTingStat4 = NexText(5, 14, "tTingStat");
NexButton bUkurTinggi4 = NexButton(5, 19, "bUkurTinggi");

//Diameter
NexText tDim4 = NexText(5, 32, "tDim");
NexText tDimStat4 = NexText(5, 15, "tDimStat");
NexButton bUkurDim4 = NexButton(5, 20, "bUkurDim");

//Panjang internode
NexText tPjg4 = NexText(5, 34, "tPjg");
NexText tPjgTing4 = NexText(5, 33, "tPjgTing");
NexText tPjgStat4 = NexText(5, 16, "tPjgStat");
NexButton addPjg4 = NexButton(5, 21, "addPjg");
NexButton minPjg4 = NexButton(5, 27, "minPjg");

//HDRatio
NexText tHdrat4 = NexText(5, 35, "tHdrat");
NexText tHdratStat4 = NexText(5, 17, "tHdratStat");
NexButton bUkurHD4 = NexButton(5, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun4 = NexText(5, 36, "tJmlDaun");
NexText tJmlDaunStat4 = NexText(5, 18, "tJmlDaunStat");
NexButton addDaun4 = NexButton(5, 28, "addDaun");
NexButton minDaun4 = NexButton(5, 29, "minDaun");

//KelTanah
NexText tKelTanah4 = NexText(5, 37, "tKelTanah");
NexText tKelTanahStat4 = NexText(5, 25, "tKelTanahStat");
NexButton bUkurKelTanah4 = NexButton(5, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan4 = NexButton(5, 23, "bSimpan");
NexButton Analisa4 = NexButton(5, 30, "Analisa");
NexText tLulus4 = NexText(5, 13, "tLulus");
//End OF EP0361WK PT

//CLONE PT
//Tinggi
NexText tTinggi5 = NexText(6, 31, "tTinggi");
NexText tTingStat5 = NexText(6, 14, "tTingStat");
NexButton bUkurTinggi5 = NexButton(6, 19, "bUkurTinggi");

//Diameter
NexText tDim5 = NexText(6, 32, "tDim");
NexText tDimStat5 = NexText(6, 15, "tDimStat");
NexButton bUkurDim5 = NexButton(6, 20, "bUkurDim");

//Panjang internode
NexText tPjg5 = NexText(6, 34, "tPjg");
NexText tPjgTing5 = NexText(6, 33, "tPjgTing");
NexText tPjgStat5 = NexText(6, 16, "tPjgStat");
NexButton addPjg5 = NexButton(6, 21, "addPjg");
NexButton minPjg5 = NexButton(6, 27, "minPjg");

//HDRatio
NexText tHdrat5 = NexText(6, 35, "tHdrat");
NexText tHdratStat5 = NexText(6, 17, "tHdratStat");
NexButton bUkurHD5 = NexButton(6, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun5 = NexText(6, 36, "tJmlDaun");
NexText tJmlDaunStat5 = NexText(6, 18, "tJmlDaunStat");
NexButton addDaun5 = NexButton(6, 28, "addDaun");
NexButton minDaun5 = NexButton(6, 29, "minDaun");

//KelTanah
NexText tKelTanah5 = NexText(6, 37, "tKelTanah");
NexText tKelTanahStat5 = NexText(6, 25, "tKelTanahStat");
NexButton bUkurKelTanah5 = NexButton(6, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan5 = NexButton(6, 23, "bSimpan");
NexButton Analisa5 = NexButton(6, 30, "Analisa");
NexText tLulus5 = NexText(6, 13, "tLulus");
//End OF CLONE PT

//EP0077A PP
//Tinggi
NexText tTinggi6 = NexText(7, 31, "tTinggi");
NexText tTingStat6 = NexText(7, 14, "tTingStat");
NexButton bUkurTinggi6 = NexButton(7, 19, "bUkurTinggi");

//Diameter
NexText tDim6 = NexText(7, 32, "tDim");
NexText tDimStat6 = NexText(7, 15, "tDimStat");
NexButton bUkurDim6 = NexButton(7, 20, "bUkurDim");

//Panjang internode
NexText tPjg6 = NexText(7, 34, "tPjg");
NexText tPjgTing6 = NexText(7, 33, "tPjgTing");
NexText tPjgStat6 = NexText(7, 16, "tPjgStat");
NexButton addPjg6 = NexButton(7, 21, "addPjg");
NexButton minPjg6 = NexButton(7, 27, "minPjg");

//HDRatio
NexText tHdrat6 = NexText(7, 35, "tHdrat");
NexText tHdratStat6 = NexText(7, 17, "tHdratStat");
NexButton bUkurHD6 = NexButton(7, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun6 = NexText(7, 36, "tJmlDaun");
NexText tJmlDaunStat6 = NexText(7, 18, "tJmlDaunStat");
NexButton addDaun6 = NexButton(7, 28, "addDaun");
NexButton minDaun6 = NexButton(7, 29, "minDaun");

//KelTanah
NexText tKelTanah6 = NexText(7, 37, "tKelTanah");
NexText tKelTanahStat6 = NexText(7, 25, "tKelTanahStat");
NexButton bUkurKelTanah6 = NexButton(7, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan6 = NexButton(7, 23, "bSimpan");
NexButton Analisa6 = NexButton(7, 30, "Analisa");
NexText tLulus6 = NexText(7, 13, "tLulus");
//End OF EP0077AA PP

//EP0361WK PP
//Tinggi
NexText tTinggi7 = NexText(8, 31, "tTinggi");
NexText tTingStat7 = NexText(8, 14, "tTingStat");
NexButton bUkurTinggi7 = NexButton(8, 19, "bUkurTinggi");

//Diameter
NexText tDim7 = NexText(8, 32, "tDim");
NexText tDimStat7 = NexText(8, 15, "tDimStat");
NexButton bUkurDim7 = NexButton(8, 20, "bUkurDim");

//Panjang internode
NexText tPjg7 = NexText(8, 34, "tPjg");
NexText tPjgTing7 = NexText(8, 33, "tPjgTing");
NexText tPjgStat7 = NexText(8, 16, "tPjgStat");
NexButton addPjg7 = NexButton(8, 21, "addPjg");
NexButton minPjg7 = NexButton(8, 27, "minPjg");

//HDRatio
NexText tHdrat7 = NexText(8, 35, "tHdrat");
NexText tHdratStat7 = NexText(8, 17, "tHdratStat");
NexButton bUkurHD7 = NexButton(8, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun7 = NexText(8, 36, "tJmlDaun");
NexText tJmlDaunStat7 = NexText(8, 18, "tJmlDaunStat");
NexButton addDaun7 = NexButton(8, 28, "addDaun");
NexButton minDaun7 = NexButton(8, 29, "minDaun");

//KelTanah
NexText tKelTanah7 = NexText(8, 37, "tKelTanah");
NexText tKelTanahStat7 = NexText(8, 25, "tKelTanahStat");
NexButton bUkurKelTanah7 = NexButton(8, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan7 = NexButton(8, 23, "bSimpan");
NexButton Analisa7 = NexButton(8, 30, "Analisa");
NexText tLulus7 = NexText(8, 13, "tLulus");
//End OF EP0361WK PP

//CLONE PP
//Tinggi
NexText tTinggi8 = NexText(9, 31, "tTinggi");
NexText tTingStat8 = NexText(9, 14, "tTingStat");
NexButton bUkurTinggi8 = NexButton(9, 19, "bUkurTinggi");

//Diameter
NexText tDim8 = NexText(9, 32, "tDim");
NexText tDimStat8 = NexText(9, 15, "tDimStat");
NexButton bUkurDim8 = NexButton(9, 20, "bUkurDim");

//Panjang internode
NexText tPjg8 = NexText(9, 34, "tPjg");
NexText tPjgTing8 = NexText(9, 33, "tPjgTing");
NexText tPjgStat8 = NexText(9, 16, "tPjgStat");
NexButton addPjg8 = NexButton(9, 21, "addPjg");
NexButton minPjg8 = NexButton(9, 27, "minPjg");

//HDRatio
NexText tHdrat8 = NexText(9, 35, "tHdrat");
NexText tHdratStat8 = NexText(9, 17, "tHdratStat");
NexButton bUkurHD8 = NexButton(9, 22, "bUkurHD");

//JmlDaun
NexText tJmlDaun8 = NexText(9, 36, "tJmlDaun");
NexText tJmlDaunStat8 = NexText(9, 18, "tJmlDaunStat");
NexButton addDaun8 = NexButton(9, 28, "addDaun");
NexButton minDaun8 = NexButton(9, 29, "minDaun");

//KelTanah
NexText tKelTanah8 = NexText(9, 37, "tKelTanah");
NexText tKelTanahStat8 = NexText(9, 25, "tKelTanahStat");
NexButton bUkurKelTanah8 = NexButton(9, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan8 = NexButton(9, 23, "bSimpan");
NexButton Analisa8 = NexButton(9, 30, "Analisa");
NexText tLulus8 = NexText(9, 13, "tLulus");
//End OF CLONE PP

//SELEKSI
NexButton bUkur9 = NexButton(11, 8, "bUkur");
//Tinggi
NexText tTinggi9 = NexText(11, 5, "tTinggi");
//Grade
NexText tGrade9 = NexText(11, 7, "tGrade");
//Simpan data
NexButton bSimpan9 = NexButton(11, 3, "bSimpan");
//End OF SELEKSI

//UKUR DIAMETER
NexButton bUkur10 = NexButton(12, 6, "bUkur");
//Diameter
NexText tDim10 = NexText(12, 5, "tDim");
//Simpan data
NexButton bSimpan10 = NexButton(12, 3, "bSimpan");
//End OF UKUR DIAMAETER


//Register Button
NexTouch *nex_listen_list[] = {
  //acra seedling
  &bUkurTinggi,
  &bUkurDim,
  &addPjg,
  &minPjg,
  &bUkurHD,
  &addDaun,
  &minDaun,
  &bUkurKelTanah,
  &Analisa,
  &bSimpan,
  //acra cutting
  &bUkurTinggi2,
  &bUkurDim2,
  &addPjg2,
  &minPjg2,
  &bUkurHD2,
  &addDaun2,
  &minDaun2,
  &bUkurKelTanah2,
  &Analisa2,
  &bSimpan2,
  //EP0077A PT
  &bUkurTinggi3,
  &bUkurDim3,
  &addPjg3,
  &minPjg3,
  &bUkurHD3,
  &addDaun3,
  &minDaun3,
  &bUkurKelTanah3,
  &Analisa3,
  &bSimpan3,
  //EP0361WK PT
  &bUkurTinggi4,
  &bUkurDim4,
  &addPjg4,
  &minPjg4,
  &bUkurHD4,
  &addDaun4,
  &minDaun4,
  &bUkurKelTanah4,
  &Analisa4,
  &bSimpan4,
  //CLONE PT
  &bUkurTinggi5,
  &bUkurDim5,
  &addPjg5,
  &minPjg5,
  &bUkurHD5,
  &addDaun5,
  &minDaun5,
  &bUkurKelTanah5,
  &Analisa5,
  &bSimpan5,
  //EP0077AA PP
  &bUkurTinggi6,
  &bUkurDim6,
  &addPjg6,
  &minPjg6,
  &bUkurHD6,
  &addDaun6,
  &minDaun6,
  &bUkurKelTanah6,
  &Analisa6,
  &bSimpan6,
  //EP0361WK PP
  &bUkurTinggi7,
  &bUkurDim7,
  &addPjg7,
  &minPjg7,
  &bUkurHD7,
  &addDaun7,
  &minDaun7,
  &bUkurKelTanah7,
  &Analisa7,
  &bSimpan7,
  //CLONE PP
  &bUkurTinggi8,
  &bUkurDim8,
  &addPjg8,
  &minPjg8,
  &bUkurHD8,
  &addDaun8,
  &minDaun8,
  &bUkurKelTanah8,
  &Analisa8,
  &bSimpan8,
  //SELEKSI
  &tTinggi9,
  &tGrade9,
  &bSimpan9,
  &bUkur9,
  //DIAMETER
  &tDim10,
  &bSimpan10,
  &bUkur10,
  NULL
};

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  // Pin Set Up
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);
  nexInit();

  //Acra seedling
  bUkurTinggi.attachPop(bUkurTinggiCB, &bUkurTinggi);
  bUkurDim.attachPop(bUkurDimCB, &bUkurDim);
  addPjg.attachPop(bAddPjgCB, &addPjg);
  minPjg.attachPop(bMinPjgCB, &minPjg);
  bUkurHD.attachPop(bUkurHDCB, &bUkurHD);
  addDaun.attachPop(bAddDaunCB, &addDaun);
  minDaun.attachPop(bMinDaunCB, &minDaun);
  bUkurKelTanah.attachPop(bUkurKelTanahCB, &bUkurKelTanah);
  Analisa.attachPop(bAnalisaCB, &Analisa);
  bSimpan.attachPop(bSimpanCB, &bSimpan);

  //Acra cutting
  bUkurTinggi2.attachPop(bUkurTinggiCB2, &bUkurTinggi2);
  bUkurDim2.attachPop(bUkurDimCB2, &bUkurDim2);
  addPjg2.attachPop(bAddPjgCB2, &addPjg2);
  minPjg2.attachPop(bMinPjgCB2, &minPjg2);
  bUkurHD2.attachPop(bUkurHDCB2, &bUkurHD2);
  addDaun2.attachPop(bAddDaunCB2, &addDaun2);
  minDaun2.attachPop(bMinDaunCB2, &minDaun2);
  bUkurKelTanah2.attachPop(bUkurKelTanahCB2, &bUkurKelTanah2);
  Analisa2.attachPop(bAnalisaCB2, &Analisa2);
  bSimpan2.attachPop(bSimpanCB2, &bSimpan2);

  //EP0077A PT
  bUkurTinggi3.attachPop(bUkurTinggiCB3, &bUkurTinggi3);
  bUkurDim3.attachPop(bUkurDimCB3, &bUkurDim3);
  addPjg3.attachPop(bAddPjgCB3, &addPjg3);
  minPjg3.attachPop(bMinPjgCB3, &minPjg3);
  bUkurHD3.attachPop(bUkurHDCB3, &bUkurHD3);
  addDaun3.attachPop(bAddDaunCB3, &addDaun3);
  minDaun3.attachPop(bMinDaunCB3, &minDaun3);
  bUkurKelTanah3.attachPop(bUkurKelTanahCB3, &bUkurKelTanah3);
  Analisa3.attachPop(bAnalisaCB3, &Analisa3);
  bSimpan3.attachPop(bSimpanCB3, &bSimpan3);

  //EP0361WK PT
  bUkurTinggi4.attachPop(bUkurTinggiCB4, &bUkurTinggi4);
  bUkurDim4.attachPop(bUkurDimCB4, &bUkurDim4);
  addPjg4.attachPop(bAddPjgCB4, &addPjg4);
  minPjg4.attachPop(bMinPjgCB4, &minPjg4);
  bUkurHD4.attachPop(bUkurHDCB4, &bUkurHD4);
  addDaun4.attachPop(bAddDaunCB4, &addDaun4);
  minDaun4.attachPop(bMinDaunCB4, &minDaun4);
  bUkurKelTanah4.attachPop(bUkurKelTanahCB4, &bUkurKelTanah4);
  Analisa4.attachPop(bAnalisaCB4, &Analisa4);
  bSimpan4.attachPop(bSimpanCB4, &bSimpan4);

  //CLONE PT
  bUkurTinggi5.attachPop(bUkurTinggiCB5, &bUkurTinggi5);
  bUkurDim5.attachPop(bUkurDimCB5, &bUkurDim5);
  addPjg5.attachPop(bAddPjgCB5, &addPjg5);
  minPjg5.attachPop(bMinPjgCB5, &minPjg5);
  bUkurHD5.attachPop(bUkurHDCB5, &bUkurHD5);
  addDaun5.attachPop(bAddDaunCB5, &addDaun5);
  minDaun5.attachPop(bMinDaunCB5, &minDaun5);
  bUkurKelTanah5.attachPop(bUkurKelTanahCB5, &bUkurKelTanah5);
  Analisa5.attachPop(bAnalisaCB5, &Analisa5);
  bSimpan5.attachPop(bSimpanCB5, &bSimpan5);

  //EP0077AA PP
  bUkurTinggi6.attachPop(bUkurTinggiCB6, &bUkurTinggi6);
  bUkurDim6.attachPop(bUkurDimCB6, &bUkurDim6);
  addPjg6.attachPop(bAddPjgCB6, &addPjg6);
  minPjg6.attachPop(bMinPjgCB6, &minPjg6);
  bUkurHD6.attachPop(bUkurHDCB6, &bUkurHD6);
  addDaun6.attachPop(bAddDaunCB6, &addDaun6);
  minDaun6.attachPop(bMinDaunCB6, &minDaun6);
  bUkurKelTanah6.attachPop(bUkurKelTanahCB6, &bUkurKelTanah6);
  Analisa6.attachPop(bAnalisaCB6, &Analisa6);
  bSimpan6.attachPop(bSimpanCB6, &bSimpan6);

  //EP0361WK PP
  bUkurTinggi7.attachPop(bUkurTinggiCB7, &bUkurTinggi7);
  bUkurDim7.attachPop(bUkurDimCB7, &bUkurDim7);
  addPjg7.attachPop(bAddPjgCB7, &addPjg7);
  minPjg7.attachPop(bMinPjgCB7, &minPjg7);
  bUkurHD7.attachPop(bUkurHDCB7, &bUkurHD7);
  addDaun7.attachPop(bAddDaunCB7, &addDaun7);
  minDaun7.attachPop(bMinDaunCB7, &minDaun7);
  bUkurKelTanah7.attachPop(bUkurKelTanahCB7, &bUkurKelTanah7);
  Analisa7.attachPop(bAnalisaCB7, &Analisa7);
  bSimpan7.attachPop(bSimpanCB7, &bSimpan7);

  //CLONE PP
  bUkurTinggi8.attachPop(bUkurTinggiCB8, &bUkurTinggi8);
  bUkurDim8.attachPop(bUkurDimCB8, &bUkurDim8);
  addPjg8.attachPop(bAddPjgCB8, &addPjg8);
  minPjg8.attachPop(bMinPjgCB8, &minPjg8);
  bUkurHD8.attachPop(bUkurHDCB8, &bUkurHD8);
  addDaun8.attachPop(bAddDaunCB8, &addDaun8);
  minDaun8.attachPop(bMinDaunCB8, &minDaun8);
  bUkurKelTanah8.attachPop(bUkurKelTanahCB8, &bUkurKelTanah8);
  Analisa8.attachPop(bAnalisaCB8, &Analisa8);
  bSimpan8.attachPop(bSimpanCB8, &bSimpan8);

  //SELEKSI
  bUkur9.attachPop(bUkurCB9, &bUkur9);
  bSimpan9.attachPop(bSimpanCB9, &bSimpan9);

  //DIAMETER
  bUkur10.attachPop(bUkurCB10, &bUkur10);
  bSimpan10.attachPop(bSimpanCB10, &bSimpan10);

  dbSerialPrintln("setup done");

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  sensor.startContinuous();
  pinMode(SoilSensor, INPUT);
}

void loop(void)
{
  nexLoop(nex_listen_list);
}

//Acra Seddling
//ukur tinggi
void bUkurTinggiCB(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30) {
    tTingStat.setText("L");
  } else {
    tTingStat.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi.setText(tinggi);
}

//ukur diameter
void bUkurDimCB(void *ptr) {
  decode(3, 0);
}

//ukur pjg internode
void bAddPjgCB(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atoi(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing.setText(result);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat.setText("L");
  } else {
    tPjgStat.setText("TL");
  }
}

void bMinPjgCB(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing.setText(result);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat.setText("L");
  } else {
    tPjgStat.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD >= 3) {
    tHdratStat.setText("L");
  } else {
    tHdratStat.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat.setText(result);
}

//ukur jml daun
void bAddDaunCB(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun.setText(result);
  if (daun >= 4) {
    tJmlDaunStat.setText("L");
  } else {
    tJmlDaunStat.setText("TL");
  }
}

void bMinDaunCB(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun.setText(result);
  if (daun >= 4) {
    tJmlDaunStat.setText("L");
  } else {
    tJmlDaunStat.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah.setText(result);
  if (nilai >= 66) {
    tKelTanahStat.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat.setText("Kering");
  }
}

void bAnalisaCB(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus.setText("LULUS");
  } else {
    tLulus.setText("TIDAK LULUS");
  }
}

void bSimpanCB(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim.getText(txtSensorSV, LentxtSensorSV);
  String tDim = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg.getText(txtSensorSV, LentxtSensorSV);
  String tPjg = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus.getText(txtSensorSV, LentxtSensorSV);
  String tLulus = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Acra Seedling");
    myFile.print(',');
    myFile.print(tTinggi);
    myFile.print(',');
    myFile.print(tTingStat);
    myFile.print(',');
    myFile.print(tDim);
    myFile.print(',');
    myFile.print(tDimStat);
    myFile.print(',');
    myFile.print(tPjgTing);
    myFile.print(',');
    myFile.print(tPjg);
    myFile.print(',');
    myFile.print(tPjgStat);
    myFile.print(',');
    myFile.print(tHdrat);
    myFile.print(',');
    myFile.print(tHdratStat);
    myFile.print(',');
    myFile.print(tJmlDaun);
    myFile.print(',');
    myFile.print(tJmlDaunStat);
    myFile.print(',');
    myFile.print(tKelTanah);
    myFile.print(',');
    myFile.print(tKelTanahStat);
    myFile.print(',');
    myFile.print(tLulus);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End OF Acra Seedling

//Acra Cutting
//ukur tinggi
void bUkurTinggiCB2(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30) {
    tTingStat2.setText("L");
  } else {
    tTingStat2.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi2.setText(tinggi);
}

//ukur diameter
void bUkurDimCB2(void *ptr) {
  decode(3, 2);
}

//ukur pjg internode
void bAddPjgCB2(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi2.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg2.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg2.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing2.setText(result);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat2.setText("L");
  } else {
    tPjgStat2.setText("TL");
  }
}

void bMinPjgCB2(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi2.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg2.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg2.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing2.setText(result);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat2.setText("L");
  } else {
    tPjgStat2.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB2(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi2.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim2.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 12) {
    tHdratStat2.setText("L");
  } else {
    tHdratStat2.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat2.setText(result);
}

//ukur jml daun
void bAddDaunCB2(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun2.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun2.setText(result);
  if (daun >= 5) {
    tJmlDaunStat2.setText("L");
  } else {
    tJmlDaunStat2.setText("TL");
  }
}

void bMinDaunCB2(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun2.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun2.setText(result);
  if (daun >= 5) {
    tJmlDaunStat2.setText("L");
  } else {
    tJmlDaunStat2.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB2(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah2.setText(result);
  if (nilai >= 66) {
    tKelTanahStat2.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat2.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat2.setText("Kering");
  }
}

void bAnalisaCB2(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat2.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat2.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat2.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat2.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat2.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus2.setText("LULUS");
  } else {
    tLulus2.setText("TIDAK LULUS");
  }
}

void bSimpanCB2(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi2.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat2.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim2.getText(txtSensorSV, LentxtSensorSV);
  String tDim2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat2.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing2.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg2.getText(txtSensorSV, LentxtSensorSV);
  String tPjg2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat2.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat2.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat2.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun2.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat2.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah2.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat2.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat2 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus2.getText(txtSensorSV, LentxtSensorSV);
  String tLulus2 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Acra Cutting");
    myFile.print(',');
    myFile.print(tTinggi2);
    myFile.print(',');
    myFile.print(tTingStat2);
    myFile.print(',');
    myFile.print(tDim2);
    myFile.print(',');
    myFile.print(tDimStat2);
    myFile.print(',');
    myFile.print(tPjgTing2);
    myFile.print(',');
    myFile.print(tPjg2);
    myFile.print(',');
    myFile.print(tPjgStat2);
    myFile.print(',');
    myFile.print(tHdrat2);
    myFile.print(',');
    myFile.print(tHdratStat2);
    myFile.print(',');
    myFile.print(tJmlDaun2);
    myFile.print(',');
    myFile.print(tJmlDaunStat2);
    myFile.print(',');
    myFile.print(tKelTanah2);
    myFile.print(',');
    myFile.print(tKelTanahStat2);
    myFile.print(',');
    myFile.print(tLulus2);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of Acra Cutting

//EP0077A PT
//ukur tinggi
void bUkurTinggiCB3(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 25 && nilai <= 45) {
    tTingStat3.setText("L");
  } else {
    tTingStat3.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi3.setText(tinggi);
}

//ukur diameter
void bUkurDimCB3(void *ptr) {
  decode(2.2, 3);
}

//ukur pjg internode
void bAddPjgCB3(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi3.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg3.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg3.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing3.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat3.setText("L");
  } else {
    tPjgStat3.setText("TL");
  }
}

void bMinPjgCB3(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi3.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg3.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg3.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing3.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat3.setText("L");
  } else {
    tPjgStat3.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB3(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi3.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim3.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 11) {
    tHdratStat3.setText("L");
  } else {
    tHdratStat3.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat3.setText(result);
}

//ukur jml daun
void bAddDaunCB3(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun3.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun3.setText(result);
  if (daun >= 5) {
    tJmlDaunStat3.setText("L");
  } else {
    tJmlDaunStat3.setText("TL");
  }
}

void bMinDaunCB3(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun3.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun3.setText(result);
  if (daun >= 5) {
    tJmlDaunStat3.setText("L");
  } else {
    tJmlDaunStat3.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB3(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah3.setText(result);
  if (nilai >= 66) {
    tKelTanahStat3.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat3.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat3.setText("Kering");
  }
}

void bAnalisaCB3(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat3.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat3.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat3.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat3.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat3.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus3.setText("LULUS");
  } else {
    tLulus3.setText("TIDAK LULUS");
  }
}

void bSimpanCB3(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi3.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat3.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim3.getText(txtSensorSV, LentxtSensorSV);
  String tDim3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat3.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing3.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg3.getText(txtSensorSV, LentxtSensorSV);
  String tPjg3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat3.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat3.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat3.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun3.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat3.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah3.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat3.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat3 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus3.getText(txtSensorSV, LentxtSensorSV);
  String tLulus3 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Plastic Tube EP0077A");
    myFile.print(',');
    myFile.print(tTinggi3);
    myFile.print(',');
    myFile.print(tTingStat3);
    myFile.print(',');
    myFile.print(tDim3);
    myFile.print(',');
    myFile.print(tDimStat3);
    myFile.print(',');
    myFile.print(tPjgTing3);
    myFile.print(',');
    myFile.print(tPjg3);
    myFile.print(',');
    myFile.print(tPjgStat3);
    myFile.print(',');
    myFile.print(tHdrat3);
    myFile.print(',');
    myFile.print(tHdratStat3);
    myFile.print(',');
    myFile.print(tJmlDaun3);
    myFile.print(',');
    myFile.print(tJmlDaunStat3);
    myFile.print(',');
    myFile.print(tKelTanah3);
    myFile.print(',');
    myFile.print(tKelTanahStat3);
    myFile.print(',');
    myFile.print(tLulus3);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of EP0077A PT

//EP0361WK PT
//ukur tinggi
void bUkurTinggiCB4(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30 && nilai <= 50) {
    tTingStat4.setText("L");
  } else {
    tTingStat4.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi4.setText(tinggi);
}

//ukur diameter
void bUkurDimCB4(void *ptr) {
  decode(2.7, 4);
}

//ukur pjg internode
void bAddPjgCB4(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi4.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg4.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg4.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing4.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat4.setText("L");
  } else {
    tPjgStat4.setText("TL");
  }
}

void bMinPjgCB4(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi4.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg4.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg4.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing4.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat4.setText("L");
  } else {
    tPjgStat4.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB4(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi4.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim4.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 12) {
    tHdratStat4.setText("L");
  } else {
    tHdratStat4.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat4.setText(result);
}

//ukur jml daun
void bAddDaunCB4(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun4.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun4.setText(result);
  if (daun >= 5) {
    tJmlDaunStat4.setText("L");
  } else {
    tJmlDaunStat4.setText("TL");
  }
}

void bMinDaunCB4(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun4.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun4.setText(result);
  if (daun >= 5) {
    tJmlDaunStat4.setText("L");
  } else {
    tJmlDaunStat4.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB4(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah4.setText(result);
  if (nilai >= 66) {
    tKelTanahStat4.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat4.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat4.setText("Kering");
  }
}

void bAnalisaCB4(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat4.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat4.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat4.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat4.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat4.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus4.setText("LULUS");
  } else {
    tLulus4.setText("TIDAK LULUS");
  }
}

void bSimpanCB4(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi4.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat4.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim4.getText(txtSensorSV, LentxtSensorSV);
  String tDim4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat4.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing4.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg4.getText(txtSensorSV, LentxtSensorSV);
  String tPjg4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat4.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat4.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat4.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun4.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat4.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah4.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat4.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat4 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus4.getText(txtSensorSV, LentxtSensorSV);
  String tLulus4 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Plastic Tube EP0361WK");
    myFile.print(',');
    myFile.print(tTinggi4);
    myFile.print(',');
    myFile.print(tTingStat4);
    myFile.print(',');
    myFile.print(tDim4);
    myFile.print(',');
    myFile.print(tDimStat4);
    myFile.print(',');
    myFile.print(tPjgTing4);
    myFile.print(',');
    myFile.print(tPjg4);
    myFile.print(',');
    myFile.print(tPjgStat4);
    myFile.print(',');
    myFile.print(tHdrat4);
    myFile.print(',');
    myFile.print(tHdratStat4);
    myFile.print(',');
    myFile.print(tJmlDaun4);
    myFile.print(',');
    myFile.print(tJmlDaunStat4);
    myFile.print(',');
    myFile.print(tKelTanah4);
    myFile.print(',');
    myFile.print(tKelTanahStat4);
    myFile.print(',');
    myFile.print(tLulus4);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of EP0361WK PT

//CLONE PT
//ukur tinggi
void bUkurTinggiCB5(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 25 && nilai <= 50) {
    tTingStat5.setText("L");
  } else {
    tTingStat5.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi5.setText(tinggi);
}

//ukur diameter
void bUkurDimCB5(void *ptr) {
  decode(2.2, 5);
}

//ukur pjg internode
void bAddPjgCB5(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi5.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg5.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg5.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing5.setText(result);
  if (nilaiIn >= 1.4 && nilaiIn <= 2.2) {
    tPjgStat5.setText("L");
  } else {
    tPjgStat5.setText("TL");
  }
}

void bMinPjgCB5(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi5.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg5.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg5.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing5.setText(result);
  if (nilaiIn >= 1.4 && nilaiIn <= 2.2) {
    tPjgStat5.setText("L");
  } else {
    tPjgStat5.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB5(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi5.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim5.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 11) {
    tHdratStat5.setText("L");
  } else {
    tHdratStat5.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat5.setText(result);
}

//ukur jml daun
void bAddDaunCB5(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun5.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun5.setText(result);
  if (daun >= 5) {
    tJmlDaunStat5.setText("L");
  } else {
    tJmlDaunStat5.setText("TL");
  }
}

void bMinDaunCB5(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun5.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun5.setText(result);
  if (daun >= 5) {
    tJmlDaunStat5.setText("L");
  } else {
    tJmlDaunStat5.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB5(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah5.setText(result);
  if (nilai >= 66) {
    tKelTanahStat5.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat5.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat5.setText("Kering");
  }
}

void bAnalisaCB5(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat5.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat5.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat5.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat5.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat5.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus5.setText("LULUS");
  } else {
    tLulus5.setText("TIDAK LULUS");
  }
}

void bSimpanCB5(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi5.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat5.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim5.getText(txtSensorSV, LentxtSensorSV);
  String tDim5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat5.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing5.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg5.getText(txtSensorSV, LentxtSensorSV);
  String tPjg5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat5.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat5.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat5.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun5.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat5.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah5.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat5.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat5 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus5.getText(txtSensorSV, LentxtSensorSV);
  String tLulus5 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Plastic Tube Clone");
    myFile.print(',');
    myFile.print(tTinggi5);
    myFile.print(',');
    myFile.print(tTingStat5);
    myFile.print(',');
    myFile.print(tDim5);
    myFile.print(',');
    myFile.print(tDimStat5);
    myFile.print(',');
    myFile.print(tPjgTing5);
    myFile.print(',');
    myFile.print(tPjg5);
    myFile.print(',');
    myFile.print(tPjgStat5);
    myFile.print(',');
    myFile.print(tHdrat5);
    myFile.print(',');
    myFile.print(tHdratStat5);
    myFile.print(',');
    myFile.print(tJmlDaun5);
    myFile.print(',');
    myFile.print(tJmlDaunStat5);
    myFile.print(',');
    myFile.print(tKelTanah5);
    myFile.print(',');
    myFile.print(tKelTanahStat5);
    myFile.print(',');
    myFile.print(tLulus5);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of CLONE PT

//EP0077AA PP
//ukur tinggi
void bUkurTinggiCB6(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30 && nilai <= 50) {
    tTingStat6.setText("L");
  } else {
    tTingStat6.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi6.setText(tinggi);
}

//ukur diameter
void bUkurDimCB6(void *ptr) {
  decode(2.3, 6);
}

//ukur pjg internode
void bAddPjgCB6(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi6.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg6.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg6.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing6.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat6.setText("L");
  } else {
    tPjgStat6.setText("TL");
  }
}

void bMinPjgCB6(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi6.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg6.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg6.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing6.setText(result);

  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat6.setText("L");
  } else {
    tPjgStat6.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB6(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi6.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim6.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 11) {
    tHdratStat6.setText("L");
  } else {
    tHdratStat6.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat6.setText(result);
}

//ukur jml daun
void bAddDaunCB6(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun6.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun6.setText(result);
  if (daun >= 5) {
    tJmlDaunStat6.setText("L");
  } else {
    tJmlDaunStat6.setText("TL");
  }
}

void bMinDaunCB6(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun6.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun6.setText(result);
  if (daun >= 5) {
    tJmlDaunStat6.setText("L");
  } else {
    tJmlDaunStat6.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB6(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah6.setText(result);
  if (nilai >= 66) {
    tKelTanahStat6.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat6.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat6.setText("Kering");
  }
}

void bAnalisaCB6(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat6.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat6.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat6.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat6.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat6.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus6.setText("LULUS");
  } else {
    tLulus6.setText("TIDAK LULUS");
  }
}

void bSimpanCB6(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi6.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat6.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim6.getText(txtSensorSV, LentxtSensorSV);
  String tDim6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat6.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing6.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg6.getText(txtSensorSV, LentxtSensorSV);
  String tPjg6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat6.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat6.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat6.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun6.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat6.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah6.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat6.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat6 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus6.getText(txtSensorSV, LentxtSensorSV);
  String tLulus6 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Paper pot EP0077AA");
    myFile.print(',');
    myFile.print(tTinggi6);
    myFile.print(',');
    myFile.print(tTingStat6);
    myFile.print(',');
    myFile.print(tDim6);
    myFile.print(',');
    myFile.print(tDimStat6);
    myFile.print(',');
    myFile.print(tPjgTing6);
    myFile.print(',');
    myFile.print(tPjg6);
    myFile.print(',');
    myFile.print(tPjgStat6);
    myFile.print(',');
    myFile.print(tHdrat6);
    myFile.print(',');
    myFile.print(tHdratStat6);
    myFile.print(',');
    myFile.print(tJmlDaun6);
    myFile.print(',');
    myFile.print(tJmlDaunStat6);
    myFile.print(',');
    myFile.print(tKelTanah6);
    myFile.print(',');
    myFile.print(tKelTanahStat6);
    myFile.print(',');
    myFile.print(tLulus6);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of EP0077AA PP

//EP0361WK PP
//ukur tinggi
void bUkurTinggiCB7(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 35 && nilai <= 55) {
    tTingStat7.setText("L");
  } else {
    tTingStat7.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi7.setText(tinggi);
}

//ukur diameter
void bUkurDimCB7(void *ptr) {
  decode(3, 7);
}

//ukur pjg internode
void bAddPjgCB7(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi7.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg7.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg7.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);

  tPjgTing7.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.5) {
    tPjgStat7.setText("L");
  } else {
    tPjgStat7.setText("TL");
  }
}

void bMinPjgCB7(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi7.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg7.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg7.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);
  tPjgTing7.setText(result);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.5) {
    tPjgStat7.setText("L");
  } else {
    tPjgStat7.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB7(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi7.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim7.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  if (nilaiHD <= 12) {
    tHdratStat7.setText("L");
  } else {
    tHdratStat7.setText("TL");
  }
  dtostrf(nilaiHD, 10, 2, result);
  tHdrat7.setText(result);
}

//ukur jml daun
void bAddDaunCB7(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun7.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun7.setText(result);
  if (daun >= 5) {
    tJmlDaunStat7.setText("L");
  } else {
    tJmlDaunStat7.setText("TL");
  }
}

void bMinDaunCB7(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun7.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun7.setText(result);
  if (daun >= 5) {
    tJmlDaunStat7.setText("L");
  } else {
    tJmlDaunStat7.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB7(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah7.setText(result);
  if (nilai >= 66) {
    tKelTanahStat7.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat7.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat7.setText("Kering");
  }
}

void bAnalisaCB7(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat7.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat7.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat7.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat7.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat7.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus7.setText("LULUS");
  } else {
    tLulus7.setText("TIDAK LULUS");
  }
}

void bSimpanCB7(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi7.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat7.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim7.getText(txtSensorSV, LentxtSensorSV);
  String tDim7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat7.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing7.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg7.getText(txtSensorSV, LentxtSensorSV);
  String tPjg7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat7.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat7.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat7.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun8.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat7.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah7.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat7.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat7 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus7.getText(txtSensorSV, LentxtSensorSV);
  String tLulus7 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Paper pot EP0361WK");
    myFile.print(',');
    myFile.print(tTinggi7);
    myFile.print(',');
    myFile.print(tTingStat7);
    myFile.print(',');
    myFile.print(tDim7);
    myFile.print(',');
    myFile.print(tDimStat7);
    myFile.print(',');
    myFile.print(tPjgTing7);
    myFile.print(',');
    myFile.print(tPjg7);
    myFile.print(',');
    myFile.print(tPjgStat7);
    myFile.print(',');
    myFile.print(tHdrat7);
    myFile.print(',');
    myFile.print(tHdratStat7);
    myFile.print(',');
    myFile.print(tJmlDaun7);
    myFile.print(',');
    myFile.print(tJmlDaunStat7);
    myFile.print(',');
    myFile.print(tKelTanah7);
    myFile.print(',');
    myFile.print(tKelTanahStat7);
    myFile.print(',');
    myFile.print(tLulus7);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of EP0361WK PP

//CLONE PP
//ukur tinggi
void bUkurTinggiCB8(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30 && nilai <= 55) {
    tTingStat8.setText("L");
  } else {
    tTingStat8.setText("TL");
  }
  char tinggi[10];
  dtostrf(nilai, 10, 2, tinggi);
  tTinggi8.setText(tinggi);
}

//ukur diameter
void bUkurDimCB8(void *ptr) {
  decode(2.3, 8);
}

//ukur pjg internode
void bAddPjgCB8(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi8.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg8.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn += 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg8.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);;
  tPjgTing8.setText(result);
  if (nilaiIn >= 1.5 && nilaiIn <= 2.3) {
    tPjgStat8.setText("L");
  } else {
    tPjgStat8.setText("TL");
  }
}

void bMinPjgCB8(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi8.getText(txtSensorSV, LentxtSensorSV);
  float tinggi = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tPjg8.getText(txtSensorSV, LentxtSensorSV);
  int pjgIn = atoi(txtSensorSV);

  pjgIn -= 1;
  dtostrf(pjgIn, 10, 0, result);
  tPjg8.setText(result);

  float nilaiIn = tinggi / pjgIn;
  dtostrf(nilaiIn, 10, 2, result);
  tPjgTing8.setText(result);
  if (nilaiIn >= 1.5 && nilaiIn <= 2.3) {
    tPjgStat8.setText("L");
  } else {
    tPjgStat8.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB8(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tTinggi8.getText(txtSensorSV, LentxtSensorSV);
  float nilaiH = atof(txtSensorSV);
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tDim8.getText(txtSensorSV, LentxtSensorSV);
  float nilaiDim = atof(txtSensorSV);
  float nilaiHD = (nilaiH * 10) / nilaiDim;

  dtostrf(nilaiHD, 10, 2, result);

  if (nilaiHD <= 11) {
    tHdratStat8.setText("L");
  } else {
    tHdratStat8.setText("TL");
  }
  tHdrat8.setText(result);
}

//ukur jml daun
void bAddDaunCB8(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun8.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun += 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun8.setText(result);
  if (daun >= 5) {
    tJmlDaunStat8.setText("L");
  } else {
    tJmlDaunStat8.setText("TL");
  }
}

void bMinDaunCB8(void *ptr) {
  memset(txtSensorSV, 0, sizeof txtSensorSV);   tJmlDaun8.getText(txtSensorSV, LentxtSensorSV);
  int daun = atoi(txtSensorSV);
  daun -= 1;
  dtostrf(daun, 10, 0, result);
  tJmlDaun8.setText(result);
  if (daun >= 5) {
    tJmlDaunStat8.setText("L");
  } else {
    tJmlDaunStat8.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB8(void *ptr) {
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  dtostrf(nilai, 10, 2, result);
  tKelTanah8.setText(result);
  if (nilai >= 66) {
    tKelTanahStat8.setText("Basah");
  } else if (nilai >= 31) {
    tKelTanahStat8.setText("Normal");
  } else if (nilai <= 31) {
    tKelTanahStat8.setText("Kering");
  }
}

void bAnalisaCB8(void *ptr) {
  int L = 0;
  int TL = 0;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat8.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat = txtSensorSV;

  if (tTingStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat8.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat = txtSensorSV;
  if (tDimStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat8.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat = txtSensorSV;
  if (tPjgStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat8.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat = txtSensorSV;
  if (tHdratStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat8.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat = txtSensorSV;
  if (tJmlDaunStat == "L") {
    L += 1;
  } else {
    TL += 1;
  }

  if (L >= TL) {
    tLulus8.setText("LULUS");
  } else {
    tLulus8.setText("TIDAK LULUS");
  }
}

void bSimpanCB8(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi8.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTingStat8.getText(txtSensorSV, LentxtSensorSV);
  String tTingStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim8.getText(txtSensorSV, LentxtSensorSV);
  String tDim8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDimStat8.getText(txtSensorSV, LentxtSensorSV);
  String tDimStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgTing8.getText(txtSensorSV, LentxtSensorSV);
  String tPjgTing8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjg8.getText(txtSensorSV, LentxtSensorSV);
  String tPjg8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tPjgStat8.getText(txtSensorSV, LentxtSensorSV);
  String tPjgStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdrat8.getText(txtSensorSV, LentxtSensorSV);
  String tHdrat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tHdratStat8.getText(txtSensorSV, LentxtSensorSV);
  String tHdratStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaun8.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaun8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tJmlDaunStat8.getText(txtSensorSV, LentxtSensorSV);
  String tJmlDaunStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanah8.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanah8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tKelTanahStat8.getText(txtSensorSV, LentxtSensorSV);
  String tKelTanahStat8 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tLulus8.getText(txtSensorSV, LentxtSensorSV);
  String tLulus8 = txtSensorSV;

  SD.exists("DatUkr.csv");

  //OPEN FILE
  myFile = SD.open("DatUkr.csv", FILE_WRITE);
  if (myFile) {
    myFile.print("Paper pot clone");
    myFile.print(',');
    myFile.print(tTinggi8);
    myFile.print(',');
    myFile.print(tTingStat8);
    myFile.print(',');
    myFile.print(tDim8);
    myFile.print(',');
    myFile.print(tDimStat8);
    myFile.print(',');
    myFile.print(tPjgTing8);
    myFile.print(',');
    myFile.print(tPjg8);
    myFile.print(',');
    myFile.print(tPjgStat8);
    myFile.print(',');
    myFile.print(tHdrat8);
    myFile.print(',');
    myFile.print(tHdratStat8);
    myFile.print(',');
    myFile.print(tJmlDaun8);
    myFile.print(',');
    myFile.print(tJmlDaunStat8);
    myFile.print(',');
    myFile.print(tKelTanah8);
    myFile.print(',');
    myFile.print(tKelTanahStat8);
    myFile.print(',');
    myFile.print(tLulus8);
    myFile.print(',');
    myFile.println("");

    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatUkr.csv");
  }
}
//End Of CLONE PP

//SELEKSI
void bUkurCB9(void *ptr) {
  float nilai = (float)sensor.readRangeContinuousMillimeters() - batasBawah;
  nilai = nilai / 10;

  if (nilai >= 25) {
    tGrade9.setText("A");
  } else if (nilai >= 20) {
    tGrade9.setText("B");
  } else {
    tGrade9.setText("C");
  }
  char dim[10];
  dtostrf(nilai, 10, 2, dim);
  tTinggi9.setText(dim);
}

void bSimpanCB9(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tTinggi9.getText(txtSensorSV, LentxtSensorSV);
  String tTinggi9 = txtSensorSV;

  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tGrade9.getText(txtSensorSV, LentxtSensorSV);
  String tGrade9 = txtSensorSV;

  SD.exists("DatSel.csv");

  //OPEN FILE
  myFile = SD.open("DatSel.csv", FILE_WRITE);
  if (myFile) {
    myFile.print(tTinggi9);
    myFile.print(',');
    myFile.print(tGrade9);
    myFile.print(',');
    myFile.println("");
    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatSel.csv");
  }
}
//END OF SELEKSI

//DIAMETER
void bUkurCB10(void *ptr) {
  decode(0, 10);
}

void bSimpanCB10(void *ptr) {
  //GET VALUE FROM LCD
  memset(txtSensorSV, 0, sizeof txtSensorSV);
  tDim.getText(txtSensorSV, LentxtSensorSV);
  String tDim = txtSensorSV;
  SD.exists("DatDim.csv");

  //OPEN FILE
  myFile = SD.open("DatDim.csv", FILE_WRITE);
  if (myFile) {
    myFile.print(tDim);
    myFile.print(',');
    myFile.println("");
    myFile.close();
    Serial.println("Success write data");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening DatDim.csv");
  }
}
//END OF DIAMETER

void decode(float batas, int stat) {
  int sign = 1;
  int i = 0;
  float value = 0.0;
  float result = 0.0;

  bit_array[i] = digitalRead(DATA_PIN);       // Store the 1st bit (start bit) which is always 1.
  while (digitalRead(CLOCK_PIN) == HIGH) {};

  for (i = 1; i <= 24; i++) {
    while (digitalRead(CLOCK_PIN) == LOW) { } // Wait until clock returns to HIGH
    bit_array[i] = digitalRead(DATA_PIN);
    while (digitalRead(CLOCK_PIN) == HIGH) {} // Wait until clock returns to LOW
  }

  for (i = 0; i <= 24; i++) {                 // Show the content of the bit array. This is for verification only.
    Serial.print(bit_array[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (i = 1; i <= 20; i++) {                 // Turning the value in the bit array from binary to decimal.
    value = value + (pow(2, i - 1) * bit_array[i]);
  }

  if (bit_array[21] == 1) sign = -1;          // Bit 21 is the sign bit. 0 -> +, 1 => -

  if (bit_array[24] == 1) {                   // Bit 24 tells the measuring unit (1 -> in, 0 -> mm)
    result = (value * sign) / 2000.00;
    Serial.print(result, 3);                  // Print result with 3 decimals
    Serial.println(" in");
  } else {
    result = (value * sign) / 100.00;
    Serial.print(result, 2);                  // Print result with 2 decimals
    Serial.println(" mm");
  }

  float nilai = result;

  if (nilai >= batas) {
    if (stat == 0) {
      tDimStat.setText("L");
    } else if (stat == 2) {
      tDimStat2.setText("L");
    } else if (stat == 3) {
      tDimStat3.setText("L");
    } else if (stat == 4) {
      tDimStat4.setText("L");
    } else if (stat == 5) {
      tDimStat5.setText("L");
    } else if (stat == 6) {
      tDimStat6.setText("L");
    } else if (stat == 7) {
      tDimStat7.setText("L");
    } else if (stat == 8) {
      tDimStat8.setText("L");
    }
  } else {
    if (stat == 0) {
      tDimStat.setText("TL");
    } else if (stat == 2) {
      tDimStat2.setText("TL");
    } else if (stat == 3) {
      tDimStat3.setText("TL");
    } else if (stat == 4) {
      tDimStat4.setText("TL");
    } else if (stat == 5) {
      tDimStat5.setText("TL");
    } else if (stat == 6) {
      tDimStat6.setText("TL");
    } else if (stat == 7) {
      tDimStat7.setText("TL");
    } else if (stat == 8) {
      tDimStat8.setText("TL");
    }
  }
  char dim[10];
  dtostrf(nilai, 10, 2, dim);
  if (stat == 0) {
    tDim.setText(dim);
  } else if (stat == 2) {
    tDim2.setText(dim);
  } else if (stat == 3) {
    tDim3.setText(dim);
  } else if (stat == 4) {
    tDim4.setText(dim);
  } else if (stat == 5) {
    tDim5.setText(dim);
  } else if (stat == 6) {
    tDim6.setText(dim);
  } else if (stat == 7) {
    tDim7.setText(dim);
  } else if (stat == 8) {
    tDim8.setText(dim);
  } else if (stat == 10) {
    tDim10.setText(dim);
  }

}
