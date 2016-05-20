//
//  OpenCVWrapper.m
//  TestOpenCVSwift
//
//  Created by 上田 純也 on 5/20/16.
//  Copyright © 2016 uejun. All rights reserved.
//

#import "OpenCVWrapper.h"
#import <opencv2/opencv.hpp>

@implementation OpenCVWrapper

+(NSString *)opencvVersionString {
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}
@end
