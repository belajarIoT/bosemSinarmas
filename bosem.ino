#include <Nextion.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
const int SoilSensor = A0;

//Acra seedling
//Tinggi
NexNumber tTinggi = NexNumber(2, 30, "tTinggi");
NexText tTingStat = NexText(2, 14, "tTingStat");
NexButton bUkurTinggi = NexButton(2, 19, "bUkurTinggi");

//Diameter
NexNumber tDim = NexNumber(2, 37, "tDim");
NexText tDimStat = NexText(2, 15, "tDimStat");
NexButton bUkurDim = NexButton(2, 20, "bUkurDim");

//Panjang internode
NexNumber tPjg = NexNumber(2, 31, "tPjg");
NexNumber tPjgTing = NexNumber(2, 34, "tPjgTing");
NexText tPjgStat = NexText(2, 16, "tPjgStat");
NexButton addPjg = NexButton(2, 21, "addPjg");
NexButton minPjg = NexButton(2, 27, "minPjg");

//HDRatio
NexNumber tHdrat = NexNumber(2, 32, "tHdrat");
NexText tHdratStat = NexText(2, 17, "tHdratStat");
NexButton bUkurHD = NexButton(2, 22, "bUkurHD");

//JmlDaun
NexNumber tJmlDaun = NexNumber(2, 33, "tJmlDaun");
NexText tJmlDaunStat = NexText(2, 18, "tJmlDaunStat");
NexButton addDaun = NexButton(2, 28, "addDaun");
NexButton minDaun = NexButton(2, 29, "minDaun");

//KelTanah
NexNumber tKelTanah = NexNumber(2, 35, "tKelTanah");
NexText tKelTanahStat = NexText(2, 25, "tKelTanahStat");
NexButton bUkurKelTanah = NexButton(2, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan = NexButton(2, 23, "bSimpan");
NexButton Analisa = NexButton(2, 36, "Analisa");
NexText tLulus = NexText(2, 13, "tLulus");
//End OF Acra seedling

//Acra Cutting
//Tinggi
NexNumber tTinggi2 = NexNumber(3, 30, "tTinggi");
NexText tTingStat2 = NexText(3, 14, "tTingStat");
NexButton bUkurTinggi2 = NexButton(3, 19, "bUkurTinggi");

//Diameter
NexNumber tDim2 = NexNumber(3, 37, "tDim");
NexText tDimStat2 = NexText(3, 15, "tDimStat");
NexButton bUkurDim2 = NexButton(3, 20, "bUkurDim");

//Panjang internode
NexNumber tPjg2 = NexNumber(3, 31, "tPjg");
NexNumber tPjgTing2 = NexNumber(3, 34, "tPjgTing");
NexText tPjgStat2 = NexText(3, 16, "tPjgStat");
NexButton addPjg2 = NexButton(3, 21, "addPjg");
NexButton minPjg2 = NexButton(3, 27, "minPjg");

//HDRatio
NexNumber tHdrat2 = NexNumber(3, 32, "tHdrat");
NexText tHdratStat2 = NexText(3, 17, "tHdratStat");
NexButton bUkurHD2 = NexButton(3, 22, "bUkurHD");

//JmlDaun
NexNumber tJmlDaun2 = NexNumber(3, 33, "tJmlDaun");
NexText tJmlDaunStat2 = NexText(3, 18, "tJmlDaunStat");
NexButton addDaun2 = NexButton(3, 28, "addDaun");
NexButton minDaun2 = NexButton(3, 29, "minDaun");

//KelTanah
NexNumber tKelTanah2 = NexNumber(3, 35, "tKelTanah");
NexText tKelTanahStat2 = NexText(3, 25, "tKelTanahStat");
NexButton bUkurKelTanah2 = NexButton(3, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan2 = NexButton(3, 23, "bSimpan");
NexButton Analisa2 = NexButton(3, 36, "Analisa");
NexText tLulus2 = NexText(3, 13, "tLulus");
//End OF Acra Cutting

//EP0077A PT
//Tinggi
NexNumber tTinggi3 = NexNumber(4, 30, "tTinggi");
NexText tTingStat3 = NexText(4, 14, "tTingStat");
NexButton bUkurTinggi3 = NexButton(4, 19, "bUkurTinggi");

//Diameter
NexNumber tDim3 = NexNumber(4, 37, "tDim");
NexText tDimStat3 = NexText(4, 15, "tDimStat");
NexButton bUkurDim3 = NexButton(4, 20, "bUkurDim");

//Panjang internode
NexNumber tPjg3 = NexNumber(4, 31, "tPjg");
NexNumber tPjgTing3 = NexNumber(4, 34, "tPjgTing");
NexText tPjgStat3 = NexText(4, 16, "tPjgStat");
NexButton addPjg3 = NexButton(4, 21, "addPjg");
NexButton minPjg3 = NexButton(4, 27, "minPjg");

//HDRatio
NexNumber tHdrat3 = NexNumber(4, 32, "tHdrat");
NexText tHdratStat3 = NexText(4, 17, "tHdratStat");
NexButton bUkurHD3 = NexButton(4, 22, "bUkurHD");

//JmlDaun
NexNumber tJmlDaun3 = NexNumber(4, 33, "tJmlDaun");
NexText tJmlDaunStat3 = NexText(4, 18, "tJmlDaunStat");
NexButton addDaun3 = NexButton(4, 28, "addDaun");
NexButton minDaun3 = NexButton(4, 29, "minDaun");

//KelTanah
NexNumber tKelTanah3 = NexNumber(4, 35, "tKelTanah");
NexText tKelTanahStat3 = NexText(4, 25, "tKelTanahStat");
NexButton bUkurKelTanah3 = NexButton(4, 26, "bUkurKelTanah");

//Simpan data
NexButton bSimpan3 = NexButton(4, 23, "bSimpan");
NexButton Analisa3 = NexButton(4, 36, "Analisa");
NexText tLulus3 = NexText(4, 13, "tLulus");
//End OF EP0077A PT



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
  NULL
};

void setup()
{
  Serial.begin(9600);
  Wire.begin();
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

//Acra Seddling
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
  float nilai = sensor.readRangeContinuousMillimeters();
  nilai = nilai - 30;
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
  if (nilaiHD >= 3) {
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
  float nilai = (1023 - analogRead(SoilSensor));
  nilai = nilai / 1023;
  nilai = nilai * 100;
  tKelTanah.setValue(nilai);
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
  uint32_t tinggi = 0;
  uint32_t diameter = 0;
  uint32_t panjang = 0;
  uint32_t hdrat = 0;
  uint32_t daun = 0;

  tTinggi.getValue(&tinggi);
  if (tinggi >= 30) {
    L += 1;
  } else {
    TL += 1;
  }

  tDim.getValue(&diameter);
  if (diameter >= 3) {
    L += 1;
  } else {
    TL += 1;
  }

  tPjgTing.getValue(&panjang);
  if (panjang >= 2 && panjang <= 4.5) {
    L += 1;
  } else {
    TL += 1;
  }

  tHdrat.getValue(&hdrat);
  if (hdrat >= 3) {
    L += 1;
  } else {
    TL += 1;
  }

  tJmlDaun.getValue(&daun);
  if (daun >= 4) {
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

}
//End OF Acra Seedling

//Acra Cutting
//ukur tinggi
void bUkurTinggiCB2(void *ptr) {
  float nilai = sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 30) {
    tTingStat2.setText("L");
  } else {
    tTingStat2.setText("TL");
  }
  tTinggi2.setValue(nilai);
}

//ukur diameter
void bUkurDimCB2(void *ptr) {
  float nilai = sensor.readRangeContinuousMillimeters();
  nilai = nilai - 30;
  if (nilai >= 3) {
    tDimStat2.setText("L");
  } else {
    tDimStat2.setText("TL");
  }
  tDim2.setValue(nilai);
}

//ukur pjg internode
void bAddPjgCB2(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi2.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg2.getValue(&pjgIn);
  pjgIn += 1;
  tPjg.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing2.setValue(nilaiIn);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat2.setText("L");
  } else {
    tPjgStat2.setText("TL");
  }
}

void bMinPjgCB2(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi2.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg2.getValue(&pjgIn);
  pjgIn -= 1;
  tPjg2.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing2.setValue(nilaiIn);
  if (nilaiIn >= 2 && nilaiIn <= 4.5) {
    tPjgStat2.setText("L");
  } else {
    tPjgStat2.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB2(void *ptr) {
  uint32_t nilaiH = 0;
  tTinggi2.getValue(&nilaiH);
  uint32_t nilaiDim = 0;
  tDim2.getValue(&nilaiDim);
  float nilaiHD = (nilaiH * 10) / nilaiDim;
  if (nilaiHD <= 12) {
    tHdratStat2.setText("L");
  } else {
    tHdratStat2.setText("TL");
  }
  tHdrat2.setValue(nilaiHD);
}

//ukur jml daun
void bAddDaunCB2(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun2.getValue(&daun);
  daun += 1;
  tJmlDaun2.setValue(daun);
  if (daun >= 5) {
    tJmlDaunStat2.setText("L");
  } else {
    tJmlDaunStat2.setText("TL");
  }
}

void bMinDaunCB2(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun2.getValue(&daun);
  daun -= 1;
  tJmlDaun2.setValue(daun);
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
  tKelTanah2.setValue(nilai);
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
  uint32_t tinggi = 0;
  uint32_t diameter = 0;
  uint32_t panjang = 0;
  uint32_t hdrat = 0;
  uint32_t daun = 0;

  tTinggi2.getValue(&tinggi);
  if (tinggi >= 30) {
    L += 1;
  } else {
    TL += 1;
  }

  tDim2.getValue(&diameter);
  if (diameter >= 3) {
    L += 1;
  } else {
    TL += 1;
  }

  tPjgTing2.getValue(&panjang);
  if (panjang >= 2 && panjang <= 4.5) {
    L += 1;
  } else {
    TL += 1;
  }

  tHdrat2.getValue(&hdrat);
  if (hdrat <= 12) {
    L += 1;
  } else {
    TL += 1;
  }

  tJmlDaun2.getValue(&daun);
  if (daun >= 5) {
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

}
//End Of Acra Cutting

//EP0077A PT
//ukur tinggi
void bUkurTinggiCB3(void *ptr) {
  float nilai = sensor.readRangeContinuousMillimeters() / 10;
  if (nilai >= 25 && nilai <= 45) {
    tTingStat3.setText("L");
  } else {
    tTingStat3.setText("TL");
  }
  tTinggi3.setValue(nilai);
}

//ukur diameter
void bUkurDimCB3(void *ptr) {
  float nilai = sensor.readRangeContinuousMillimeters();
  nilai = nilai - 30;
  if (nilai >= 2.2) {
    tDimStat3.setText("L");
  } else {
    tDimStat3.setText("TL");
  }
  tDim3.setValue(nilai);
}

//ukur pjg internode
void bAddPjgCB3(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi3.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg3.getValue(&pjgIn);
  pjgIn += 1;
  tPjg.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing3.setValue(nilaiIn);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat3.setText("L");
  } else {
    tPjgStat3.setText("TL");
  }
}

void bMinPjgCB3(void *ptr) {
  uint32_t tinggi = 0;
  tTinggi3.getValue(&tinggi);

  uint32_t pjgIn = 0;
  tPjg3.getValue(&pjgIn);
  pjgIn -= 1;
  tPjg3.setValue(pjgIn);

  float nilaiIn = tinggi / pjgIn;
  tPjgTing3.setValue(nilaiIn);
  if (nilaiIn >= 1.2 && nilaiIn <= 2.4) {
    tPjgStat3.setText("L");
  } else {
    tPjgStat3.setText("TL");
  }
}

//ukur HD Rat
void bUkurHDCB3(void *ptr) {
  uint32_t nilaiH = 0;
  tTinggi3.getValue(&nilaiH);
  uint32_t nilaiDim = 0;
  tDim3.getValue(&nilaiDim);
  float nilaiHD = (nilaiH * 10) / nilaiDim;
  if (nilaiHD <= 11) {
    tHdratStat3.setText("L");
  } else {
    tHdratStat3.setText("TL");
  }
  tHdrat3.setValue(nilaiHD);
}

//ukur jml daun
void bAddDaunCB3(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun3.getValue(&daun);
  daun += 1;
  tJmlDaun2.setValue(daun);
  if (daun >= 5) {
    tJmlDaunStat3.setText("L");
  } else {
    tJmlDaunStat3.setText("TL");
  }
}

void bMinDaunCB3(void *ptr) {
  uint32_t daun = 0;
  tJmlDaun3.getValue(&daun);
  daun -= 1;
  tJmlDaun3.setValue(daun);
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
  tKelTanah3.setValue(nilai);
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
  uint32_t tinggi = 0;
  uint32_t diameter = 0;
  uint32_t panjang = 0;
  uint32_t hdrat = 0;
  uint32_t daun = 0;

  tTinggi3.getValue(&tinggi);
  if (tinggi >= 25 && tinggi <= 45) {
    L += 1;
  } else {
    TL += 1;
  }

  tDim3.getValue(&diameter);
  if (diameter >= 2.2) {
    L += 1;
  } else {
    TL += 1;
  }

  tPjgTing3.getValue(&panjang);
  if (panjang >= 1.2 && panjang <= 2.4) {
    L += 1;
  } else {
    TL += 1;
  }

  tHdrat3.getValue(&hdrat);
  if (hdrat <= 11) {
    L += 1;
  } else {
    TL += 1;
  }

  tJmlDaun3.getValue(&daun);
  if (daun >= 5) {
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

}

