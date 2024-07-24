/**
 *	@file Rcb4BaseClass.cpp
 *	@brief RCB4 base library
 *	@author Kondo Kagaku Co.,Ltd.
 *	@version 1.1.0
 *
 *	@date	2018/02/01
 *	@date	2019/01/16�@V1.1.0
 *			�EgetConfig�̕s����C��
 *			�EmoveRamToComCmdSynchronize��memcopy�̕s��Ή�
 *
 *	@copyright &copy; Kondo Kagaku Co.,Ltd. 2019
 **/

#include "Rcb4BaseClass.hpp"

bool Rcb4BaseClass::getConfig() {
  byte wkbuf[10];
  if (moveRamToComCmdSynchronize(ConfigRamAddress, 0x02, wkbuf) != 0xffff) {
    configData.byte.low = wkbuf[0];
    configData.byte.high = wkbuf[1];
    return true;
  } else {
    return false;
  }
}

bool Rcb4BaseClass::getConfig(unsigned short *confData) {
  if (getConfig() == false)
    return false;

  *confData = configData.word;
  delay(100);
  return true;
}

bool Rcb4BaseClass::checkuning(byte *txData) {
  return (_isSynchronize == true && txBuf == txData) ? false : true;
}

int Rcb4BaseClass::moveComToRamCmd(byte *txData, int destAddr, byte destData[],
                                   int destDataSize) {
  if (checkuning(txData) == false || destDataSize > 249) {
    return -1;
  }

  byte *ptr;
  WordByte wk;

  wk.word = destAddr;
  ptr = txData;

  *ptr++ = (byte)destDataSize + 7;
  *ptr++ = Move;
  *ptr++ = 0x02;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  *ptr++ = 0x00;
  for (int i = 0; i < destDataSize; i++) {
    *ptr++ = destData[i];
  }
  setCheckSum(txData);

  return destDataSize + 7;
}

int Rcb4BaseClass::moveComToRamCmd(int destAddr, byte destData[],
                                   int destDataSize) {
  return moveComToRamCmd(txBuf, destAddr, destData, destDataSize);
}

int Rcb4BaseClass::moveRamToComCmd(byte *txData, int scrAddr, int scrDataSize) {
  if (checkuning(txData) == false)
    return -1;

  byte *ptr;
  WordByte wk;

  wk.word = scrAddr;

  ptr = txData;

  *ptr++ = 0x0a;
  *ptr++ = Move;
  *ptr++ = 0x20;
  *ptr++ = 0x00;
  *ptr++ = 0x00;
  *ptr++ = 0x00;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  *ptr++ = (byte)scrDataSize;

  setCheckSum(txData);
  return 0x0a;
}

int Rcb4BaseClass::moveRamToComCmd(int scrAddr, int scrDataSize) {
  return moveRamToComCmd(txBuf, scrAddr, scrDataSize);
}

int Rcb4BaseClass::moveComToDeviceCmd(byte *txData, byte icsNum, byte offset,
                                      int data) {
  if (checkuning(txData) == false)
    return -1;

  byte *ptr;
  WordByte wk;

  ptr = txData;
  wk.word = data;

  *ptr++ = 0x09;
  *ptr++ = Move;
  *ptr++ = 0x12;
  *ptr++ = offset;
  *ptr++ = icsNum;
  *ptr++ = 0x00;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  setCheckSum(txData);
  return 0x09;
}

int Rcb4BaseClass::moveComToDeviceCmd(byte *txData, byte idNum, byte sioNum,
                                      byte offset, int data) {
  return moveComToDeviceCmd(txData, icsNum2id(idNum, sioNum), offset, data);
}

int Rcb4BaseClass::moveComToDeviceCmd(byte icsNum, byte offset, int data) {
  return moveComToDeviceCmd(txBuf, icsNum, offset, data);
}

int Rcb4BaseClass::moveComToDeviceCmd(byte idNum, byte sioNum, byte offset,
                                      int data) {
  return moveComToDeviceCmd(txBuf, icsNum2id(idNum, sioNum), offset, data);
}

int Rcb4BaseClass::moveDeviceToComCmd(byte *txData, byte icsNum, byte offset,
                                      byte dataSize) {
  if (checkuning(txData) == false)
    return -1;

  byte *ptr;

  ptr = txData;

  *ptr++ = 0x0a;
  *ptr++ = Move;
  *ptr++ = 0x21;
  *ptr++ = offset;
  *ptr++ = 0x00;
  *ptr++ = 0x00;
  *ptr++ = 0x00;
  *ptr++ = icsNum;
  *ptr++ = dataSize;
  setCheckSum(txData);
  return 0x0a;
}

int Rcb4BaseClass::moveDeviceToComCmd(byte *txData, byte idNum, byte sioNum,
                                      byte offset, byte dataSize) {
  return moveDeviceToComCmd(txData, icsNum2id(idNum, sioNum), offset, dataSize);
}

int Rcb4BaseClass::moveDeviceToComCmd(byte icsNum, byte offset, byte dataSize) {
  return moveDeviceToComCmd(txBuf, icsNum, offset, dataSize);
}

int Rcb4BaseClass::moveDeviceToComCmd(byte idNum, byte sioNum, byte offset,
                                      byte dataSize) {
  return moveDeviceToComCmd(txBuf, icsNum2id(idNum, sioNum), offset, dataSize);
}

int Rcb4BaseClass::callCmd(byte *txData, long romAddr) {
  if (checkuning(txData) == false)
    return -1;

  byte *ptr;
  DwordByte wk;

  wk.dword = (uint32_t)romAddr;
  ptr = txData;

  *ptr++ = 0x07;
  *ptr++ = Call;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  *ptr++ = wk.byte[2];
  *ptr++ = 0x00;
  setCheckSum(txData);
  return 0x07;
}

int Rcb4BaseClass::callCmd(long romAddr) { return callCmd(txBuf, romAddr); }

int Rcb4BaseClass::runSingleServoCmd(byte *txData, ServoData servoData,
                                     byte frame) {
  return runSingleServoCmd(txData, servoData.Id, servoData.Sio, servoData.Data,
                           frame);
}

int Rcb4BaseClass::runSingleServoCmd(ServoData servoData, byte frame) {
  return runSingleServoCmd(txBuf, servoData.Id, servoData.Sio, servoData.Data,
                           frame);
}

int Rcb4BaseClass::runSingleServoCmd(byte *txData, byte idNum, byte sioNum,
                                     int pos, byte frame) {
  if (checkuning(txData) == false)
    return -1;

  byte *ptr;
  WordByte wk;

  ptr = txData;
  wk.word = pos;

  *ptr++ = 0x07;
  *ptr++ = SingleServo;
  *ptr++ = icsNum2id(idNum, sioNum);
  *ptr++ = frame;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  setCheckSum(txData);
  return 0x07;
}

int Rcb4BaseClass::runSingleServoCmd(byte idNum, byte sioNum, int pos,
                                     byte frame) {
  return runSingleServoCmd(txBuf, idNum, sioNum, pos, frame);
}

int64_t Rcb4BaseClass::setServoNo(ServoData servoDatas[], byte servoCount) {
  byte no;
  int64_t ret = 0;
  for (int i = 0; i < servoCount; i++) {
    no = icsNum2id(servoDatas[i].Id, servoDatas[i].Sio);
    int64_t sf = 0x1;
    ret |= (sf << no);
  }

  return ret;
}

bool Rcb4BaseClass::sortServoDatas(ServoData servoDatas[], byte servoCount) {
  const int servoMaxCount = 36;

  if (servoCount > servoMaxCount) {
    return false;
  }

  ServoData bufServoDatas[servoMaxCount];

  int i;

  for (i = 0; i < servoMaxCount; i++) {
    bufServoDatas[i].Id = 0xFF;
    bufServoDatas[i].Sio = 0xFF;
  }

  for (i = 0; i < servoCount; i++) {
    byte sioNum = icsNum2id(servoDatas[i].Id, servoDatas[i].Sio);

    if (sioNum > servoMaxCount) {
      return false;
    }

    bufServoDatas[sioNum].Id = servoDatas[i].Id;
    bufServoDatas[sioNum].Sio = servoDatas[i].Sio;
    bufServoDatas[sioNum].Data = servoDatas[i].Data;
  }

  byte j = 0;

  for (i = 0; i < servoMaxCount; i++) {
    if (bufServoDatas[i].Id != 0xFF) {

      servoDatas[j].Id = bufServoDatas[i].Id;
      servoDatas[j].Sio = bufServoDatas[i].Sio;
      servoDatas[j].Data = bufServoDatas[i].Data;

      j++;

      if (j >= servoCount) {
        break;
      }
    }
  }

  return true;
}

int Rcb4BaseClass::runConstFrameServoCmd(byte *txData, ServoData servoDatas[],
                                         byte servoCount, byte frame) {

  if (checkuning(txData) == false)
    return -1;

  ServoData sDataBuf[servoCount];
  memcpy(sDataBuf, servoDatas, sizeof(ServoData) * servoCount);

  byte *ptr;
  QwordByte wk;

  ptr = txData;

  wk.qword = setServoNo(sDataBuf, servoCount);

  *ptr++ = servoCount * 2 + 9;
  *ptr++ = ConstFrameServo;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  *ptr++ = wk.byte[2];
  *ptr++ = wk.byte[3];
  *ptr++ = wk.byte[4];
  *ptr++ = frame;

  if (sortServoDatas(sDataBuf, servoCount) == false) {
    return -1;
  }

  for (int i = 0; i < servoCount; i++) {
    wk.word[0] = sDataBuf[i].Data;
    *ptr++ = wk.byte[0];
    *ptr++ = wk.byte[1];
  }

  setCheckSum(txData);

  return servoCount * 2 + 9;
}

int Rcb4BaseClass::runConstFrameServoCmd(ServoData servoDatas[],
                                         byte servoCount, byte frame) {
  return runConstFrameServoCmd(txBuf, servoDatas, servoCount, frame);
}

int Rcb4BaseClass::setParametersBaseCmd(byte *txData, byte servoParameter,
                                        ServoData servoDatas[],
                                        byte servoCount) {
  if (checkuning(txData) == false)
    return -1;

  ServoData sDataBuf[servoCount];
  memcpy(sDataBuf, servoDatas, sizeof(ServoData) * servoCount);

  byte *ptr;
  QwordByte wk;

  ptr = txData;

  if (sortServoDatas(sDataBuf, servoCount) == false) {
    return -1;
  }

  wk.qword = setServoNo(sDataBuf, servoCount);

  *ptr++ = servoCount + 9;
  *ptr++ = ServoParam;
  *ptr++ = wk.byte[0];
  *ptr++ = wk.byte[1];
  *ptr++ = wk.byte[2];
  *ptr++ = wk.byte[3];
  *ptr++ = wk.byte[4];
  *ptr++ = servoParameter;
  for (int i = 0; i < servoCount; i++) {
    *ptr++ = (byte)(sDataBuf[i].Data & 0x00ff);
  }
  setCheckSum(txData);
  return servoCount + 9;
}

int Rcb4BaseClass::setParametersBaseCmd(byte servoParameter,
                                        ServoData servoDatas[],
                                        byte servoCount) {
  return setParametersBaseCmd(txBuf, servoParameter, servoDatas, servoCount);
}

int Rcb4BaseClass::setSpeedCmd(byte *txData, ServoData servoDatas[],
                               byte servoCount) {
  return setParametersBaseCmd(txData, 0x02, servoDatas, servoCount);
}

int Rcb4BaseClass::setSpeedCmd(ServoData servoDatas[], byte servoCount) {
  return setParametersBaseCmd(txBuf, 0x02, servoDatas, servoCount);
}

int Rcb4BaseClass::setStretchCmd(byte *txData, ServoData servoDatas[],
                                 byte servoCount) {
  return setParametersBaseCmd(txData, 0x01, servoDatas, servoCount);
}

int Rcb4BaseClass::setStretchCmd(ServoData servoDatas[], byte servoCount) {
  return setParametersBaseCmd(txBuf, 0x01, servoDatas, servoCount);
}

int Rcb4BaseClass::acknowledgeCmd(byte *txData) {
  byte *ptr;
  ptr = txData;

  *ptr++ = 0x04;
  *ptr++ = AckCheck;
  *ptr++ = Ack;
  setCheckSum(txData);
  return 0x04;
}

int Rcb4BaseClass::acknowledgeCmd() { return acknowledgeCmd(txBuf); }

bool Rcb4BaseClass::checkAcknowledge() {
  bool checkFlag = true;

  acknowledgeCmd(txBuf);

  checkFlag = synchronize(txBuf, txBuf[0], rxBuf, 4);

  if (false == checkFlag || rxBuf[2] == Nack) {
    return false;
  } else {
    return true;
  }
}

byte Rcb4BaseClass::CheckSum(byte dataBytes[]) {
  byte sum = 0;
  for (int i = 0; i < dataBytes[0] - 1; i++) {
    sum += dataBytes[i];
  }
  return sum;
}

bool Rcb4BaseClass::setCheckSum(byte dataBytes[]) {
  if (dataBytes[0] == 0) {
    return false;
  } else {
    dataBytes[dataBytes[0] - 1] = CheckSum(dataBytes);
    return true;
  }
}

bool Rcb4BaseClass::checkCheckSum(byte dataBytes[]) {
  if (dataBytes[0] == 0) {
    return false;
  } else {
    if (dataBytes[dataBytes[0] - 1] == CheckSum(dataBytes)) {
      return true;
    } else {
      return false;
    }
  }
}

bool Rcb4BaseClass::checkReverceCmd(byte dataBytes[], byte cmd) {

  if (checkCheckSum(dataBytes) == true && dataBytes[1] == cmd) {
    return true;
  } else {
    return false;
  }
}

unsigned short Rcb4BaseClass::moveRamToComCmdSynchronize(int scrAddr,
                                                         byte scrDataSize,
                                                         byte rxDara[]) {

  if (moveRamToComCmd(scrAddr, scrDataSize) == -1)
    return 0xffff;

  if (synchronize(txBuf, txBuf[0], rxBuf, scrDataSize + 3) == true) {

    for (int i = 0; i < scrDataSize; i++) {
      rxDara[i] = rxBuf[i + 2];
    }

    return scrDataSize;

    return 0xffff;
  } else {

    return 0xffff;
  }
}

bool Rcb4BaseClass::moveComToRamCmdSynchronize(int scrAddr, byte destData[],
                                               int destDataSize) {

  if (moveComToRamCmd(scrAddr, destData, destDataSize) == -1)
    return false;

  if (synchronize(txBuf, txBuf[0], rxBuf, 4) == true) {
    return rxBuf[2] == Ack ? true : false;
  } else {
    return false;
  }
}

bool Rcb4BaseClass::SynchronizeAck(byte *txData) {
  if (synchronize(txData, *txData, rxBuf, 4) == true) {
    return rxBuf[2] == Ack ? true : false;
  } else {
    return false;
  }
}

unsigned short Rcb4BaseClass::getPio() {
  byte wkbuf[10];
  if (moveRamToComCmdSynchronize(PioAddress, 0x02, wkbuf) != 0xffff) {
    WordByte wk;
    wk.byte[0] = wkbuf[0];
    wk.byte[1] = wkbuf[1];

    wk.word &= 0x03FF;

    return wk.word;
  } else {
    return 0xffff;
  }
}

bool Rcb4BaseClass::setPio(unsigned short pioData) {
  return moveComToRamCmdSynchronize(PioAddress, (byte *)&pioData, 2);
}

unsigned short Rcb4BaseClass::getPioMode() {
  byte wkbuf[10];
  if (moveRamToComCmdSynchronize(PioModeAddres, 0x02, wkbuf) != 0xffff) {
    WordByte wk;
    wk.byte[0] = wkbuf[0];
    wk.byte[1] = wkbuf[1];

    wk.word &= 0x03FF;

    return wk.word;
  } else {
    return 0xffff;
  }
}

bool Rcb4BaseClass::setPioMode(unsigned short pioModeData) {
  return moveComToRamCmdSynchronize(PioModeAddres, (byte *)&pioModeData, 2);
}

unsigned short Rcb4BaseClass::getAdData(int adPort) {
  byte wkbuf[10];
  if (moveRamToComCmdSynchronize(AdcRamAddress + adPort * 2, 0x02, wkbuf) !=
      0xffff) {
    WordByte wk;
    wk.byte[0] = wkbuf[0];
    wk.byte[1] = wkbuf[1];

    return wk.word;
  } else {
    return 0xffff;
  }
}

bool Rcb4BaseClass::getAllAdData(int adDatas[]) {
  byte wkbuf[30];

  if (moveRamToComCmdSynchronize(AdcRamAddress, AdcDataCount, wkbuf) !=
      0xffff) {
    int *iptr = (int *)&wkbuf;

    for (int i = 0; i < AdcCount; i++) {
      adDatas[i] = *iptr++;
    }
    return true;
  } else {
    return false;
  }
}

bool Rcb4BaseClass::setKrrData(unsigned short buttonData, byte adData[]) {
  byte wk[6];
  WordByte wwk;

  wwk.word = buttonData;

  wk[0] = wwk.byte[0];
  wk[1] = wwk.byte[1];
  memcpy(&wk[2], adData, 4);
  return moveComToRamCmdSynchronize(KrrButtonDataAddress, wk, 6);
}

bool Rcb4BaseClass::setKrrButtonData(unsigned short buttonData) {
  byte wk[2];

  WordByte wwk;

  wwk.word = buttonData;

  wk[0] = wwk.byte[1];
  wk[1] = wwk.byte[0];

  return moveComToRamCmdSynchronize(KrrButtonDataAddress, wk, 2);
}

bool Rcb4BaseClass::setKrrAdData(byte paPort, byte adData) {
  byte wk[2];

  wk[0] = adData;
  return moveComToRamCmdSynchronize(KrrPa1Address + (paPort - 1), wk, 1);
}

bool Rcb4BaseClass::setSingleServo(byte id, byte sio, int pos, byte frame) {
  if (runSingleServoCmd(id, sio, pos, frame) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setSingleServo(ServoData servoData, byte frame) {
  if (runConstFrameServoCmd(&servoData, 1, frame) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setFreeSingleServo(byte id, byte sio) {
  if (runSingleServoCmd(id, sio, 0x8000, 1) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setHoldSingleServo(byte id, byte sio) {
  if (runSingleServoCmd(id, sio, 0x7FFF, 1) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setServoPos(ServoData servoDatas[], byte servoCount,
                                byte frame) {
  if (runConstFrameServoCmd(servoDatas, servoCount, frame) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setFreePos(ServoData servoDatas[], byte servoCount) {
  for (int i = 0; i < servoCount; i++) {
    servoDatas[i].Data = 0x8000;
  }
  return setServoPos(servoDatas, servoCount, 1);
}

bool Rcb4BaseClass::setHoldPos(ServoData servoDatas[], byte servoCount) {
  for (int i = 0; i < servoCount; i++) {
    servoDatas[i].Data = 0x7FFF;
  }
  return setServoPos(servoDatas, servoCount, 1);
}

int Rcb4BaseClass::getSinglePos(byte id, byte sio) {
  if (moveDeviceToComCmd(id, sio, MotorPositionAddressOffset, 2) == -1)
    return -1;
  if (synchronize(txBuf, txBuf[0], rxBuf, 5) == true) {
    WordByte wk;
    wk.byte[0] = rxBuf[2];
    wk.byte[1] = rxBuf[2];
    return wk.word;
  } else {
    return -1;
  }
}

bool Rcb4BaseClass::setServoSpeed(ServoData servoDatas[], byte servoCount) {

  if (setSpeedCmd(servoDatas, servoCount) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::setServoStretch(ServoData servoDatas[], byte servoCount) {

  if (setStretchCmd(servoDatas, servoCount) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

byte Rcb4BaseClass::icsNum2id(byte id, byte sio) { return id * 2 + (sio - 1); }

bool Rcb4BaseClass::motionPlay(int motionNum) {

  if (suspend() == false)
    return false;

  if (resetProgramCounter() == false)
    return false;

  if (setMotionNum(motionNum) == false)
    return false;

  return resume();
}

bool Rcb4BaseClass::suspend() { return suspend(&(configData.word)); }

bool Rcb4BaseClass::suspend(unsigned short *config) {
  ConfigData *cData = (ConfigData *)config;

  cData->bit.EnableRunEeprom = 0;

  cData->bit.EnableReferenceTable = 0;

  return moveComToRamCmdSynchronize(ConfigRamAddress, (byte *)config, 2);
}

bool Rcb4BaseClass::setMotionNum(byte motionNum) {
  if (callCmd(txBuf, motionAddr2motionNum(motionNum)) == -1)
    return false;
  return SynchronizeAck(txBuf);
}

bool Rcb4BaseClass::resetProgramCounter() {
  WordByte wwk;
  byte wk[10];

  wwk.word = MainLoopCmd;
  memset(wk, 0x00, 10);
  wk[0] = wwk.byte[0];
  wk[1] = wwk.byte[1];
  return moveComToRamCmdSynchronize(ProgramCounterRamAddress, wk, 10);
}

bool Rcb4BaseClass::resume() { return resume(&(configData.word)); }

bool Rcb4BaseClass::resume(unsigned short *config) {
  ConfigData *cData = (ConfigData *)config;

  cData->bit.EnableRunEeprom = 1;

  cData->bit.EnableReferenceTable = 1;

  return moveComToRamCmdSynchronize(ConfigRamAddress, (byte *)config, 2);
}

long Rcb4BaseClass::motionAddr2motionNum(byte motionNum) {

  return (long)(motionNum - 1) * (long)MotionSingleDataCount + MotionRomAddress;
}
