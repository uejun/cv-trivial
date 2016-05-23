//
//  OpenCVWrapper.h
//  TestOpenCVSwift
//
//  Created by 上田 純也 on 5/20/16.
//  Copyright © 2016 uejun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface OpenCVWrapper : NSObject

+(NSString *) opencvVersionString;

+(UIImage *) makeGrayImageFromUIImage: (UIImage*) image;

@end
