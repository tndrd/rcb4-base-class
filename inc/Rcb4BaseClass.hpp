
/**
 *  @file Rcb4BaseClass.h
 * @brief Rcb4 arduino library header file
 * @date 2018/01/29
 * @version 1.1.0
 * @copyright &copy; Kondo Kagaku Co.,Ltd. 2019
 **/

#ifndef __RCB4_BASE_CLASS_H__
#define __RCB4_BASE_CLASS_H__

#include <cstring>
#include <stdint.h>
#include <unistd.h>

typedef uint8_t byte;

#define delay(milis) usleep(milis * 1000)

class Rcb4BaseClass {

public:
  static constexpr int Version = 220;

  enum AckType : byte { Ack = 0x06, Nack = 0x15 };

  enum CommandTypes : byte {
    Move = 0x00,
    Jump = 0x0B,
    Call = 0x0C,
    SingleServo = 0x0F,
    ConstFrameServo = 0x10,
    ServoParam = 0x12,
    AckCheck = 0xFE,
    None = 0xFF
  };

  enum SubMoveCmd : byte {
    RamToCom = 0x20,
    ComToRam = 0x02,
    DeviceToCom = 0x21,
    ComToDevice = 0x12,
  };

  enum RamAddr : unsigned short {
    ConfigRamAddress = 0x0000,
    ProgramCounterRamAddress = 0x0002,
    AdcRamAddress = 0x0022,
    PioModeAddres = 0x0038,
    PioAddress = 0x003A,
    KrrButtonDataAddress = 0x0350,
    KrrPa1Address = 0x0352,

  };

  enum RomAddr : long {
    StartupCmdRomAddress = 0x0444,
    MainLoopCmd = 0x044B,
    MotionRomAddress = 0x0b80
  };

  static constexpr int AdcCount = 11;
  static constexpr int AdcSingleDataCount = 2;
  static constexpr int AdcDataCount = AdcCount * AdcSingleDataCount;

  enum DeviceAddrOffset : byte {
    CategoryAddressOffset = 0x00,
    IDAddressOffset = 0x01,
    TrimAddressOffset = 0x02,
    MotorPositionAddressOffset = 0x04,
    PositionAddressOffset = 0x06,
    frameAddressOffset = 0x08,
    Mixing1AddressOffset = 0x0E,
    Mixing1RatioAddressOffset = 0x10,
    Mixing2AddressOffset = 0x11,
    Mixing2RatioAddressOffset = 0x13
  };

  enum SioNum : byte { SIO1_4 = 0x01, SIO5_8 = 0x02 };

  enum KRR_BUTTON : unsigned short {
    KRR_BUTTON_NONE = 0x0000,
    KRR_BUTTON_UP = 0x0001,
    KRR_BUTTON_DOWN = 0x0002,
    KRR_BUTTON_RIGHT = 0x0004,
    KRR_BUTTON_LEFT = 0x0008,
    KRR_BUTTON_TRIANGLE = 0x0010,
    KRR_BUTTON_CROSS = 0x0020,
    KRR_BUTTON_CIRCLE = 0x0040,
    KRR_BUTTON_SQUARE = 0x0100,
    KRR_BUTTON_S1 = 0x0200,
    KRR_BUTTON_S2 = 0x0400,
    KRR_BUTTON_S3 = 0x0800,
    KRR_BUTTON_S4 = 0x1000,
    KRR_BUTTON_FALSE = 0xFFFF
  };
  static constexpr int MotionSingleDataCount = 2048;
  static constexpr int MaxMotionCount = 120;
  static constexpr long MotionDataCount = 2048 * 120;

  struct ServoData {
    byte Id;
    byte Sio;
    int Data;
  };

public:
  typedef union {

    struct {
      byte EnableSio : 1;
      byte EnableRunEeprom : 1;
      byte EnableServoResponse : 1;
      byte EnableReferenceTable : 1;
      byte Frame : 2;
      byte Baudrate : 2;
      byte ZeroFlag : 1;
      byte CarrayFlag : 1;
      byte ProgramError : 1;
      byte RFU : 1;
      byte IcsBaudrate : 2;
      byte GreenLED : 1;
    } bit;

    struct {
      byte low;
      byte high;
    } byte;
    unsigned short word;
  } ConfigData;

  ConfigData configData;

protected:
  typedef union {
    uint8_t byte[2];
    uint16_t word;
  } WordByte;

  typedef union {
    uint8_t byte[4];
    uint16_t word[2];
    uint32_t dword;
  } DwordByte;
  typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint32_t dword[2];
    uint64_t qword;
  } QwordByte;

protected:
  byte txBuf[128];
  byte rxBuf[128];

  bool _isSynchronize = false;

private:
public:
  bool isSynchronize() { return _isSynchronize; }

  bool getConfig(unsigned short *confData);
  bool getConfig();

  int moveComToRamCmd(byte *txData, int destAddr, byte destData[],
                      int destDataSize);
  int moveComToRamCmd(int destAddr, byte destData[], int destDataSize);

  int moveRamToComCmd(byte *txData, int scrAddr, int scrDataSize);
  int moveRamToComCmd(int scrAddr, int scrDataSize);

  int moveComToDeviceCmd(byte *txData, byte idNum, byte sioNum, byte offset,
                         int data);
  int moveComToDeviceCmd(byte idNum, byte sioNum, byte offset, int data);
  int moveComToDeviceCmd(byte *txData, byte icsNum, byte offset, int data);
  int moveComToDeviceCmd(byte icsNum, byte offset, int data);

  int moveDeviceToComCmd(byte *txData, byte idNum, byte sioNum, byte offset,
                         byte dataSize);
  int moveDeviceToComCmd(byte idNum, byte sioNum, byte offset, byte dataSize);
  int moveDeviceToComCmd(byte *txData, byte icsNum, byte offset, byte dataSize);
  int moveDeviceToComCmd(byte icsNum, byte offset, byte dataSize);

  int callCmd(byte *txData, long romAddr);
  int callCmd(long romAddr);

  int runSingleServoCmd(byte *txData, ServoData servoData, byte frame);
  int runSingleServoCmd(ServoData servoData, byte frame);

  int runSingleServoCmd(byte *txData, byte idNum, byte sioNum, int pos,
                        byte frame);
  int runSingleServoCmd(byte idNum, byte sioNum, int pos, byte frame);

  int runConstFrameServoCmd(byte *txData, ServoData servoDatas[],
                            byte servoCount, byte frame);
  int runConstFrameServoCmd(ServoData servoData[], byte servoCount, byte frame);

  int setParametersBaseCmd(byte *txData, byte servoParameter,
                           ServoData servoDatas[], byte servoCount);
  int setParametersBaseCmd(byte servoParameter, ServoData servoData[],
                           byte servoCount);

  int setSpeedCmd(byte *txData, ServoData servoDatas[], byte servoCount);
  int setSpeedCmd(ServoData servoData[], byte servoCount);

  int setStretchCmd(byte *txData, ServoData servoDatas[], byte servoCount);
  int setStretchCmd(ServoData servoData[], byte servoCount);

  int acknowledgeCmd(byte *txData);
  int acknowledgeCmd();

  virtual bool synchronize(byte txBuf[], byte txLen, byte rxBuf[], byte rxLen) {
    return false;
  };

  bool checkAcknowledge();
  bool setCheckSum(byte dataBytes[]);
  bool checkCheckSum(byte dataBytes[]);
  bool checkReverceCmd(byte dataBytes[], byte cmd);

  unsigned short getPio();
  bool setPio(unsigned short pioData);
  unsigned short getPioMode();
  bool setPioMode(unsigned short pioModeData);

  unsigned short getAdData(int adPort);
  bool getAllAdData(int adDatas[11]);

  bool setKrrData(unsigned short buttonData, byte adData[4]);
  bool setKrrButtonData(unsigned short buttonData);
  bool setKrrAdData(byte paPort, byte adData);

  bool setSingleServo(byte id, byte sio, int pos, byte frame);
  bool setSingleServo(ServoData servoData, byte frame);
  bool setFreeSingleServo(byte id, byte sio);
  bool setHoldSingleServo(byte id, byte sio);

  bool setServoPos(ServoData servoDatas[], byte servoCount, byte frame);
  bool setFreePos(ServoData servoDatas[], byte servoCount);
  bool setHoldPos(ServoData servoDatas[], byte servoCount);

  int getSinglePos(byte id, byte sio);

  bool setServoSpeed(ServoData servoDatas[], byte servoCount);
  bool setServoStretch(ServoData servoDatas[], byte servoCount);

  byte icsNum2id(byte id, byte sio);

  bool motionPlay(int motionNum);
  bool suspend();
  bool suspend(unsigned short *config);
  bool setMotionNum(byte motionNum);
  bool resetProgramCounter();

  bool resume(unsigned short *configData);
  bool resume();

  long motionAddr2motionNum(byte motionNum);

protected:
  byte CheckSum(byte dataBytes[]);
  bool checkuning(byte *txData);
  int64_t setServoNo(ServoData servoDatas[], byte servoCount);
  bool sortServoDatas(ServoData servoDatas[], byte ServoCount);

  unsigned short moveRamToComCmdSynchronize(int scrAddr, byte scrDataSize,
                                            byte rxDara[]);
  bool moveComToRamCmdSynchronize(int scrAddr, byte destData[],
                                  int destDataSize);
  bool SynchronizeAck(byte *txData);

private:
};

#endif