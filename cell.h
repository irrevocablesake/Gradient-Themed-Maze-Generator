#pragma once
#ifndef _CELL_H_
#define _CELL_H_

const unsigned char topMask = 0b0000'0001;
const unsigned char rightMask = 0b0000'0010;
const unsigned char bottomMask = 0b0000'0100;
const unsigned char leftMask = 0b0000'1000;
const unsigned char visitedMask = 0b0001'0000;

#endif