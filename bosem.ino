#include <Nextion.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
const int SoilSensor = A0;

//Declare Nextion State (page id = 0, component id = 1, component name = "b0")
//Tinggi
NexNumber tTinggi = NexNumber(2, 30, "tTinggi");
NexText tTingStat = NexText(2, 14, "tTingStat");
NexButton bUkurTinggi = NexButton(2, 19, "bUkurTinggi");

//Diameter
NexNumber tDim = NexNumber(2, 31, "tDim");
NexText tDimStat = NexText(2, 15, "tDimStat");
NexButton bUkurDim = NexButton(2, 20, "bUkurDim");

//Panjang internode
NexNumber tPjg = NexNumber(2, 32, "tPjg");
NexNumber tPjgTing = NexNumber(2, 36, "tPjgTing");
NexText tPjgStat = NexText(2, 16, "tPjgStat");
NexButton addPjg = NexButton(2, 21, "addPjg");
NexButton minPjg = NexButton(2, 27, "minPjg");

//HDRatio
NexNumber tHdrat = NexNumber(2, 33, "tHdrat");
NexText tHdratStat = NexText(2, 17, "tHdratStat");
NexButton bUkurHD = NexButton(2, 22, "bUkurHD");

//JmlDaun
NexNumber tJmlDaun = NexNumber(2, 34, "tJmlDaun");
NexText tJmlDaunStat = NexText(2, 18, "tJmlDaunStat");
NexButton addDaun = NexButton(2, 28, "addDaun");
NexButton minDaun = NexButton(2, 29, "minDaun");

//KelTanah
NexNumber tKelTanah = NexNumber(2, 35, "tKelTanah");
NexText tKelTanahStat = NexText(2, 25, "tKelTanahStat");
NexButton bUkurKelTanah = NexButton(2, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan = NexButton(2, 23, "bSimpan");
NexText tLulus = NexText(2, 13, "tLulus");

//Register Button
NexTouch *nex_listen_list[] = {
  &bUkurTinggi,
  &bUkurDim,
  &addPjg,
  &minPjg,
  &bUkurHD,
  &addDaun,
  &minDaun,
  &bUkurKelTanah,
  &bSimpan,
  NULL
};

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  nexInit();
  bUkurTinggi.attachPop(bUkurTinggiCB, &bUkurTinggi);
  bUkurDim.attachPop(bUkurDimCB, &bUkurDim);
  addPjg.attachPop(bAddPjgCB, &addPjg);
  minPjg.attachPop(bMinPjgCB, &minPjg);
  bUkurHD.attachPop(bUkurHDCB, &bUkurHD);
  addDaun.attachPop(bAddDaunCB, &addDaun);
  minDaun.attachPop(bMinDaunCB, &minDaun);
  bUkurKelTanah.attachPop(bUkurKelTanahCB, &bUkurKelTanah);
  dbSerialPrintln("setup done");

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
  pinMode(SoilSensor, INPUT);
}

void loop(void)
{
  nexLoop(nex_listen_list);
}

//ukur tinggi
void bUkurTinggiCB(void *ptr) {
  float nilai = sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30) {
    tTingStat.setText("L");
  } else {
    tTingStat.setText("TL");
  }
  tTinggi.setValue(nilai);
}

//ukur diameter
void bUkurDimCB(void *ptr) {
  int nilai = sensor.readRangeContinuousMillimeters();
  if (nilai >= 3) {
    tDimStat.setText("L");
  } else {
    tDimStat.setText("TL");
  }
  tDim.setValue(nilai);
}

//ukur pjg internode
void bAddPjgCB(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg.getValue(&pjgIn);
  pjgIn += 1;
  tPjg.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing.setValue(nilaiIn);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat.setText("L");
  } else {
    tPjgStat.setText("TL");
  }
}

void bMinPjgCB(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg.getValue(&pjgIn);
  pjgIn -= 1;
  tPjg.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing.setValue(nilaiIn);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat.setText("L");
  } else {
    tPjgStat.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB(void *ptr) {
  uint32_t nilaiH = 0;
  tTinggi.getValue(&nilaiH);
  uint32_t nilaiDim = 0;
  tDim.getValue(&nilaiDim);
  float nilaiHD = (nilaiH * 10) / nilaiDim;
  if (nilaiHD <= 12) {
    tHdratStat.setText("L");
  } else {
    tHdratStat.setText("TL");
  }
  tHdrat.setValue(nilaiHD);
}

//ukur jml daun
void bAddDaunCB(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun.getValue(&daun);
  daun += 1;
  tJmlDaun.setValue(daun);
  if (daun >= 4) {
    tJmlDaunStat.setText("L");
  } else {
    tJmlDaunStat.setText("TL");
  }
}

void bMinDaunCB(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun.getValue(&daun);
  daun -= 1;
  tJmlDaun.setValue(daun);
  if (daun >= 4) {
    tJmlDaunStat.setText("L");
  } else {
    tJmlDaunStat.setText("TL");
  }
}

//ukur Kel.Tanah
void bUkurKelTanahCB(void *ptr) {
  int nilai = analogRead(SoilSensor);
  tKelTanah.setValue(nilai);
  if (nilai <= 350) {
    tKelTanahStat.setText("Basah");
  } else if(nilai <= 700) {
    tKelTanahStat.setText("Normal");
  } else if(nilai > 700) {
    tKelTanahStat.setText("Kering");
  }
}
