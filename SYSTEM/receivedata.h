

#ifndef __RECEIVEDATA_H
#define __RECEIVEDATA_H

/* 
    *  
    *  当app上没有按下任何键时，蓝牙传送的数据为0x00,
    *  当app上按下的是前进键时，蓝牙传送的数据为0x43，
    *  当app上按下的是后退键时，蓝牙传送的数据为0x44，
    *  当app上按下的是左转键时，蓝牙传送的数据为0x45，
    *  当app上按下的是右转键时，蓝牙传送的数据为0x46，
    *  当app上按下的是上梯键时，蓝牙传送的数据为0x82，
*/
#define Stop      0x00  //停止
#define TurnLeft  0x43  //左转
#define TurnRight 0x44  //右转
#define Forward   0x45  //前进转
#define Back      0x46  //后退转
#define UpLadder  0x82  //上梯子

#endif
