//
//  SCPointCloud+Downsampling.mm
//  StandardCyborgFusion
//
//

#import <math.h>

#import "SCPointCloud+Downsampling.h"
#import "SCPointCloud_Private.h"

@implementation SCPointCloud (Downsampling)

- (SCPointCloud *)pointCloudByDownsamplingToMaxPoints:(NSUInteger)maxPoints
{
    NSUInteger pointCount = (NSUInteger)self.pointCount;

    if (maxPoints == 0 || pointCount <= maxPoints) {
        return self;
    }

    // Creation-order stride sampling keeps the result spatially ~uniform without the
    // cost of a voxel grid, since surfels are appended in scan-traversal order.
    NSUInteger stride = (NSUInteger)ceil((double)pointCount / (double)maxPoints);
    size_t pointStride = [SCPointCloud pointStride];
    const uint8_t *sourceBytes = (const uint8_t *)[self.pointsData bytes];

    NSMutableData *downsampledData = [NSMutableData data];
    for (NSUInteger i = 0; i < pointCount; i += stride) {
        [downsampledData appendBytes:sourceBytes + i * pointStride length:pointStride];
    }

    return [[SCPointCloud alloc] initWithSurfelData:downsampledData gravity:self.gravity];
}

@end
