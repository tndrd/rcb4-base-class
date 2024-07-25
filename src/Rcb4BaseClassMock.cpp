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

#include "rcb4-base-class/Rcb4BaseClass.hpp"

#define MOCK(ret)                                                              \
  { return ret; }

bool Rcb4BaseClass::getConfig() MOCK(true);

bool Rcb4BaseClass::getConfig(unsigned short *confData) MOCK(true);

bool Rcb4BaseClass::checkuning(byte *txData) MOCK(true);

int Rcb4BaseClass::moveComToRamCmd(byte *txData, int destAddr, byte destData[],
                                   int destDataSize) MOCK(0);

int Rcb4BaseClass::moveComToRamCmd(int destAddr, byte destData[],
                                   int destDataSize) MOCK(0);

int Rcb4BaseClass::moveRamToComCmd(byte *txData, int scrAddr, int scrDataSize)
    MOCK(0);

int Rcb4BaseClass::moveRamToComCmd(int scrAddr, int scrDataSize) MOCK(0);

int Rcb4BaseClass::moveComToDeviceCmd(byte *txData, byte icsNum, byte offset,
                                      int data) MOCK(0);

int Rcb4BaseClass::moveComToDeviceCmd(byte *txData, byte idNum, byte sioNum,
                                      byte offset, int data) MOCK(0);

int Rcb4BaseClass::moveComToDeviceCmd(byte icsNum, byte offset, int data)
    MOCK(0);

int Rcb4BaseClass::moveComToDeviceCmd(byte idNum, byte sioNum, byte offset,
                                      int data) MOCK(0);

int Rcb4BaseClass::moveDeviceToComCmd(byte *txData, byte icsNum, byte offset,
                                      byte dataSize) MOCK(0);

int Rcb4BaseClass::moveDeviceToComCmd(byte *txData, byte idNum, byte sioNum,
                                      byte offset, byte dataSize) MOCK(0);

int Rcb4BaseClass::moveDeviceToComCmd(byte icsNum, byte offset, byte dataSize)
    MOCK(0);

int Rcb4BaseClass::moveDeviceToComCmd(byte idNum, byte sioNum, byte offset,
                                      byte dataSize) MOCK(0);

int Rcb4BaseClass::callCmd(byte *txData, long romAddr) MOCK(0);

int Rcb4BaseClass::callCmd(long romAddr) MOCK(0);

int Rcb4BaseClass::runSingleServoCmd(byte *txData, ServoData servoData,
                                     byte frame) MOCK(0);

int Rcb4BaseClass::runSingleServoCmd(ServoData servoData, byte frame) MOCK(0);

int Rcb4BaseClass::runSingleServoCmd(byte *txData, byte idNum, byte sioNum,
                                     int pos, byte frame) MOCK(0);

int Rcb4BaseClass::runSingleServoCmd(byte idNum, byte sioNum, int pos,
                                     byte frame) MOCK(0);

int64_t Rcb4BaseClass::setServoNo(ServoData servoDatas[], byte servoCount)
    MOCK(0);

bool Rcb4BaseClass::sortServoDatas(ServoData servoDatas[], byte servoCount)
    MOCK(true);

int Rcb4BaseClass::runConstFrameServoCmd(byte *txData, ServoData servoDatas[],
                                         byte servoCount, byte frame) MOCK(0);

int Rcb4BaseClass::runConstFrameServoCmd(ServoData servoDatas[],
                                         byte servoCount, byte frame) MOCK(0);

int Rcb4BaseClass::setParametersBaseCmd(byte *txData, byte servoParameter,
                                        ServoData servoDatas[], byte servoCount)
    MOCK(0);

int Rcb4BaseClass::setParametersBaseCmd(byte servoParameter,
                                        ServoData servoDatas[], byte servoCount)
    MOCK(0);

int Rcb4BaseClass::setSpeedCmd(byte *txData, ServoData servoDatas[],
                               byte servoCount) MOCK(0);

int Rcb4BaseClass::setSpeedCmd(ServoData servoDatas[], byte servoCount) MOCK(0);

int Rcb4BaseClass::setStretchCmd(byte *txData, ServoData servoDatas[],
                                 byte servoCount) MOCK(0);

int Rcb4BaseClass::setStretchCmd(ServoData servoDatas[], byte servoCount)
    MOCK(0);

int Rcb4BaseClass::acknowledgeCmd(byte *txData) MOCK(0);

int Rcb4BaseClass::acknowledgeCmd() MOCK(0);

bool Rcb4BaseClass::checkAcknowledge() MOCK(true);

byte Rcb4BaseClass::CheckSum(byte dataBytes[]) MOCK(0);

bool Rcb4BaseClass::setCheckSum(byte dataBytes[]) MOCK(true);

bool Rcb4BaseClass::checkCheckSum(byte dataBytes[]) MOCK(true);

bool Rcb4BaseClass::checkReverceCmd(byte dataBytes[], byte cmd) MOCK(true);

unsigned short Rcb4BaseClass::moveRamToComCmdSynchronize(int scrAddr,
                                                         byte scrDataSize,
                                                         byte rxDara[])
    MOCK(scrDataSize);

bool Rcb4BaseClass::moveComToRamCmdSynchronize(int scrAddr, byte destData[],
                                               int destDataSize) MOCK(true);

bool Rcb4BaseClass::SynchronizeAck(byte *txData) MOCK(true);

unsigned short Rcb4BaseClass::getPio() MOCK(0);

bool Rcb4BaseClass::setPio(unsigned short pioData) MOCK(true);

unsigned short Rcb4BaseClass::getPioMode() MOCK(0);

bool Rcb4BaseClass::setPioMode(unsigned short pioModeData) MOCK(true);

unsigned short Rcb4BaseClass::getAdData(int adPort) MOCK(0);

bool Rcb4BaseClass::getAllAdData(int adDatas[]) MOCK(true);

bool Rcb4BaseClass::setKrrData(unsigned short buttonData, byte adData[])
    MOCK(true);

bool Rcb4BaseClass::setKrrButtonData(unsigned short buttonData) MOCK(true);

bool Rcb4BaseClass::setKrrAdData(byte paPort, byte adData) MOCK(true);

bool Rcb4BaseClass::setSingleServo(byte id, byte sio, int pos, byte frame)
    MOCK(true);

bool Rcb4BaseClass::setSingleServo(ServoData servoData, byte frame) MOCK(true);

bool Rcb4BaseClass::setFreeSingleServo(byte id, byte sio) MOCK(true);

bool Rcb4BaseClass::setHoldSingleServo(byte id, byte sio) MOCK(true);

bool Rcb4BaseClass::setServoPos(ServoData servoDatas[], byte servoCount,
                                byte frame) MOCK(true);

bool Rcb4BaseClass::setFreePos(ServoData servoDatas[], byte servoCount)
    MOCK(true);

bool Rcb4BaseClass::setHoldPos(ServoData servoDatas[], byte servoCount)
    MOCK(true);

int Rcb4BaseClass::getSinglePos(byte id, byte sio) MOCK(0);

bool Rcb4BaseClass::setServoSpeed(ServoData servoDatas[], byte servoCount)
    MOCK(true);

bool Rcb4BaseClass::setServoStretch(ServoData servoDatas[], byte servoCount)
    MOCK(true);

byte Rcb4BaseClass::icsNum2id(byte id, byte sio) MOCK(0);

bool Rcb4BaseClass::motionPlay(int motionNum) MOCK(true);

bool Rcb4BaseClass::suspend() MOCK(true);

bool Rcb4BaseClass::suspend(unsigned short *config) MOCK(true);

bool Rcb4BaseClass::setMotionNum(byte motionNum) MOCK(true);

bool Rcb4BaseClass::resetProgramCounter() MOCK(true);

bool Rcb4BaseClass::resume() MOCK(true);

bool Rcb4BaseClass::resume(unsigned short *config) MOCK(true);

long Rcb4BaseClass::motionAddr2motionNum(byte motionNum) MOCK(0);
