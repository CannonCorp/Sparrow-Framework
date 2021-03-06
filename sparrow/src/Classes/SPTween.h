//
//  SPTween.h
//  Sparrow
//
//  Created by Daniel Sperl on 09.05.09.
//  Copyright 2011-2015 Gamua. All rights reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the Simplified BSD License.
//

#import <Sparrow/SparrowBase.h>
#import <Sparrow/SPAnimatable.h>
#import <Sparrow/SPEventDispatcher.h>

NS_ASSUME_NONNULL_BEGIN

typedef float (^SPTransitionBlock)(float);

/** ------------------------------------------------------------------------------------------------
 
 An SPTween animates numeric properties of objects. It uses different transition functions to give
 the animations various styles.
 
 The primary use of this class is to do standard animations like movement, fading, rotation, etc.
 But there are no limits on what to animate; as long as the property you want to animate is numeric
 (`int`, `uint`, `float`, `double`), the tween can handle it. For a list of available Transition 
 types, see `SPTransitions`. 
 
 Here is an example of a tween that moves an object, rotates it, and fades it out:
 
	SPTween *tween = [SPTween tweenWithTarget:object time:2.0 transition:SPTransitionEaseInOut];
	[tween moveToX:50.0f y:20.0f];
 	[tween animateProperty:@"rotation" targetValue:object.rotation + SPDeg2Rad(45)];
  	[tween fadeTo:0.0f];
 	[Sparrow.juggler addObject:tween];
 
 Note that the object is added to a juggler at the end. A tween will only be executed if its
 `advanceTime:` method is executed regularly - the juggler will do that for us, and will release
 the tween when it is finished.
 
 Tweens provide block-based callbacks that are executed in certain phases of their life time:
 
 - `onStart`:    Invoked once when the tween starts.
 - `onUpdate`:   Invoked every time it is advanced.
 - `onComplete`: Invoked when it reaches its target value.
 - `onRepeat`:   Invoked each time the tween finishes one repetition.
 
 Use the `repeatCount` property to repeat the tween several times. The `reverse` property defines
 the way in which the repetitions will be done (ping-pong 
 
------------------------------------------------------------------------------------------------- */

@interface SPTween : SPEventDispatcher <SPAnimatable>

/// --------------------
/// @name Initialization
/// --------------------

/// Initializes a tween with a target, duration (in seconds) and a transition function. 
/// _Designated Initializer_.
- (instancetype)initWithTarget:(id)target time:(double)time transition:(NSString *)transition;

/// Initializes a tween with a target, a time (in seconds) and a linear transition 
/// (`SPTransitionLinear`).
- (instancetype)initWithTarget:(id)target time:(double)time;

/// Factory method.
+ (instancetype)tweenWithTarget:(id)target time:(double)time transition:(NSString *)transition;

/// Factory method.
+ (instancetype)tweenWithTarget:(id)target time:(double)time;

/// -------------
/// @name Methods
/// -------------

/// Animates the property of an object to a target value. You can call this method multiple times
/// on one tween.
///
/// <p>Some property types are handled in a special way:</p>
/// <ul>
///     <li>If the property contains the string <code>color</code> or <code>Color</code>,
///         it will be treated as an unsigned integer with a color value
///         (e.g. <code>0xff0000</code> for red). Each color channel will be animated
///         individually.</li>
///     <li>The same happens if you append the string <code>#rgb</code> to the name.</li>
///     <li>If you append <code>#rad</code>, the property is treated as an angle in radians,
///         making sure it always uses the shortest possible arc for the rotation.</li>
///     <li>The string <code>#deg</code> does the same for angles in degrees.</li>
/// </ul>
- (void)animateProperty:(NSString *)property targetValue:(double)value;

/// Animates the properties of an object to the specified target values.
- (void)animateProperties:(SP_GENERIC(NSDictionary, NSString*, NSNumber*) *)properties;

/// Animates the `x` and `y` properties of an object simultaneously.
- (void)moveToX:(float)x y:(float)y;

/// Animates the `scaleX` and `scaleY` properties of an object simultaneously.
- (void)scaleTo:(float)scale;

/// Animates the `alpha` property.
- (void)fadeTo:(float)alpha;

/// Returns the end value a certain property is animated to. Throws an exception if the property
/// is not being animated.
- (float)endValueOfProperty:(NSString *)property;

/// ----------------
/// @name Properties
/// ----------------

/// The target object that is animated.
@property (nonatomic, readonly) id target;

/// The transition method used for the animation.
@property (nonatomic, copy) NSString *transition;

/// The optional transition block used for the animation; if this is set 'transition' is ignored.
@property (nonatomic, copy, nullable) SPTransitionBlock transitionBlock;

/// The total time the tween will take (in seconds).
@property (nonatomic, readonly) double totalTime;

/// The time that has passed since the tween was started (in seconds).
@property (nonatomic, readonly) double currentTime;

/// Indicates if the total time has passed and the tweened properties have finished.
@property (nonatomic, readonly) BOOL isComplete;

/// The current progress between 0 and 1, as calculated by the transition function or block.
@property (nonatomic, readonly) double progress;

/// The delay before the tween is started.
@property (nonatomic, assign) double delay;

/// The number of times the tween will be executed. Set to 0 to tween indefinitely. (Default: 1)
@property (nonatomic, assign) NSInteger repeatCount;

/// The number seconds to wait between repeat cycles. (Default: 0)
@property (nonatomic, assign) double repeatDelay;

/// Indicates if the tween should be reversed when it is repeating. If enabled,
/// every second repetition will be reversed. (Default: `NO`)
@property (nonatomic, assign) BOOL reverse;

/// Indicates if the numeric values should be cast to Integers. (Default: NO)
@property (nonatomic, assign) BOOL roundToInt;

/// A block that will be called when the tween starts (after a possible delay).
@property (nonatomic, copy, nullable) SPCallbackBlock onStart;

/// A block that will be called each time the tween is advanced.
@property (nonatomic, copy, nullable) SPCallbackBlock onUpdate;

/// A block that will be called each time the tween finishes one repetition
/// (except the last, which will trigger 'onComplete').
@property (nonatomic, copy, nullable) SPCallbackBlock onRepeat;

/// A block that will be called when the tween is complete.
@property (nonatomic, copy, nullable) SPCallbackBlock onComplete;

/// Another tween that will be started (i.e. added to the same juggler) as soon as
/// this tween is completed.
@property (nonatomic, strong, nullable) SPTween *nextTween;

@end

NS_ASSUME_NONNULL_END
