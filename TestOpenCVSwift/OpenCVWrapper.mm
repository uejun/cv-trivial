//
//  OpenCVWrapper.m
//  TestOpenCVSwift
//
//  Created by 上田 純也 on 5/20/16.
//  Copyright © 2016 uejun. All rights reserved.
//

#import "OpenCVWrapper.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>

@implementation OpenCVWrapper

+(NSString *)opencvVersionString {
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}


+(UIImage *) makeGrayImageFromUIImage: (UIImage*) image {
    cv::Mat imageMat;
    UIImageToMat(image, imageMat);
    
    if(imageMat.channels() == 1) return image;
    
    cv::Mat grayMat;
    cv::cvtColor(imageMat, grayMat, CV_BGR2GRAY);
    
    return MatToUIImage(grayMat);
}
@end
