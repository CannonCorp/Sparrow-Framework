//
//  SPAVSound.h
//  Sparrow
//
//  Created by Daniel Sperl on 29.05.10.
//  Copyright 2011-2015 Gamua. All rights reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the Simplified BSD License.
//

#import <Sparrow/SparrowBase.h>
#import <Sparrow/SPSound.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/** ------------------------------------------------------------------------------------------------

 The SPAVSound class is a concrete implementation of SPSound that uses AVAudioPlayer internally. 
 
 Don't create instances of this class manually. Use `[SPSound initWithContentsOfFile:]` instead.
 
 */

@interface SPAVSound : SPSound 

/// --------------------
/// @name Initialization
/// --------------------

/// Initializes a sound with the contents of a file and the known duration.
- (instancetype)initWithContentsOfFile:(NSString *)path duration:(double)duration;

/// -------------
/// @name methods
/// -------------

/// Creates an AVAudioPlayer object from the sound.
- (AVAudioPlayer *)createPlayer;

@end

NS_ASSUME_NONNULL_END
