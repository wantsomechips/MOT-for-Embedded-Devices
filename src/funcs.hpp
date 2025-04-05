#pragma once

#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>

#include<vector>
using std::vector;

#include <array>
using std::array;

#include <string>
using std::string;

using std::cin, std::cout, std::endl;
using cv::Mat, cv::Rect, cv::Point, cv::Size;

/* seqinfo.ini of test set. */
#define NAME "PETS09-S2L1"
#define imDir "img1"
#define frameRate 1
#define seqLength 795
#define imWidth 768
#define imHeight 576
#define imExt ".jpg"

/* Minmum IoU requirement. */
#define MIN_IOU_REQ (0.5)


namespace func{

    float IoU(const Rect& bbox_a, const Rect& bbox_b);
    bool MOT(string input);
}

#endif