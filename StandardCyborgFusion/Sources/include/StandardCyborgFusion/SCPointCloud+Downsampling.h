//
//  SCPointCloud+Downsampling.h
//  StandardCyborgFusion
//
//

#import <Foundation/Foundation.h>
#import <StandardCyborgFusion/SCPointCloud.h>

NS_ASSUME_NONNULL_BEGIN

@interface SCPointCloud (Downsampling)

/**
 Returns a point cloud containing at most maxPoints points, sampled at a fixed
 stride across the original point order. If the cloud already has maxPoints or
 fewer points, or maxPoints is 0, self is returned unchanged.
 */
- (SCPointCloud *)pointCloudByDownsamplingToMaxPoints:(NSUInteger)maxPoints;

@end

NS_ASSUME_NONNULL_END
