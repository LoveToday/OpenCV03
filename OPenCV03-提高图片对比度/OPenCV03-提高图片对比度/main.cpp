//
//  main.cpp
//  OPenCV03-提高图片对比度
//
//  Created by 陈江林 on 2019/9/8.
//  Copyright © 2019 陈江林. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // 矩阵的掩膜是通过计算来重新计算每个像素的像素值
    // 矩阵 [(0, -1, 0), (-1, 5, -1), (0, -1, 0)]
    // I(i, j) = 5 * I(i, j) - I(i - 1, j) - I(i + 1, j) - I(i, j - 1) - I(i, j + 1)
    
    string filePath = "/Users/chenjianglin/Documents/C++/OPenCV03/OPenCV03-提高图片对比度/Source/tupian.jpg";
    Mat image = imread(filePath);
    if (image.data == NULL) {
        cout << "图片加载失败" << endl;
        return -1;
    }
//    int rows = image.rows;
//    int cols = image.cols * image.channels();
//    int offsetx = image.channels();
//    // 所有的元素默认置为0
//    Mat dst = Mat::zeros(image.size(), image.type());
//    for (int row = 1; row < rows - 1; row++) {
//        const uchar *previous = image.ptr(row - 1);
//        const uchar *current = image.ptr(row);
//        const uchar *next = image.ptr(row + 1);
//        uchar *output = dst.ptr(row);
//        for (int col = 1; col < cols - 1; col++) {
//            output[col] = saturate_cast<uchar>(5 * current[col] - (previous[col] + current[col - offsetx] + current[col + offsetx] + next[col]));
//        }
//    }
    double t = getTickCount();
    // 以上方法是纯计算得出来的掩膜操作
    // 方法二
    Mat dst;
    // 掩膜的定义
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    // image.depth 表示位图的深度 有 32 24 8 等
    // 如果 image.depth() 传入 -1 表示原图的深度
    filter2D(image, dst, image.depth(), kernel);
    
    double timeconsume = (getTickCount() - t)/getTickFrequency();
    cout << timeconsume << endl;
    
    
    string window = "opencv-window01";
    namedWindow(window);
    imshow(window, dst);
    waitKey(0);
    
    // 像素范围处理 saturate_cast<uchar>
    // saturate_cast<uchar>(-100),返回0
    // saturate_cast<uchar>(288),返回 255
    // saturate_cast<uchar>(100)， 返回100
    // 这个函数的功能在于确保RGB值的返回在0到255之间
    
    
    return 0;
}
