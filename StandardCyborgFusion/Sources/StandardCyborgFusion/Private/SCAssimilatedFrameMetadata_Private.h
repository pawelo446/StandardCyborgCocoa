//
//  SCAssimilatedFrameMetadata_Private.h
//  StandardCyborgFusion
//
//  Created by Aaron Thompson on 12/20/18.
//

#import <StandardCyborgFusion/SCAssimilatedFrameMetadata.h>

#import "PBFAssimilatedFrameMetadata.hpp"
#import "EigenHelpers.hpp"

/** Default number of consecutive un-assimilable frames after which scanning is declared failed/ended. */
static const NSInteger kDefaultMaxConsecutiveFailedFrameCount = 8;

static SCAssimilatedFrameMetadata
SCAssimilatedFrameMetadataFromPBFAssimilatedFrameMetadata(PBFAssimilatedFrameMetadata pbfMetadata,
                                                          NSInteger consecutiveFailedFrameCount,
                                                          NSInteger maxConsecutiveFailedFrameCount)
{
    static const float kPoorTrackingQualityThreshold = 0.1;

    SCAssimilatedFrameMetadata metadata;
    metadata.viewMatrix = toSimdFloat4x4(pbfMetadata.viewMatrix);

    metadata.projectionMatrix = toSimdFloat4x4(pbfMetadata.projectionMatrix);
    metadata.colorBuffer = NULL;
    metadata.depthBuffer = NULL;

    if (pbfMetadata.isMerged == false && consecutiveFailedFrameCount + 1 >= maxConsecutiveFailedFrameCount) {
        metadata.result = SCAssimilatedFrameResultFailed;
    } else if (pbfMetadata.isMerged == false) {
        metadata.result = SCAssimilatedFrameResultLostTracking;
    } else if (pbfMetadata.icpUnusedIterationFraction < kPoorTrackingQualityThreshold) {
        metadata.result = SCAssimilatedFrameResultPoorTracking;
    } else {
        metadata.result = SCAssimilatedFrameResultSucceeded;
    }
    
    return metadata;
}
