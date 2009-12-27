#import <UIKit/UIKit.h>

// Events

@interface LAEvent : NSObject {
@private
	NSString *_name;
	BOOL _handled;
}
+ (id)eventWithName:(NSString *)name;
- (id)initWithName:(NSString *)name;

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, getter=isHandled) BOOL handled;

@end

extern NSString * const LAEventNameMenuPressAtSpringBoard;
extern NSString * const LAEventNameMenuPressSingle;
extern NSString * const LAEventNameMenuPressDouble;
extern NSString * const LAEventNameMenuPressTriple; // libactivator 1.0.1+
extern NSString * const LAEventNameMenuHoldShort;

extern NSString * const LAEventNameLockHoldShort;
extern NSString * const LAEventNameLockPressDouble; // libactivator 1.0.1+

extern NSString * const LAEventNameSpringBoardPinch;
extern NSString * const LAEventNameSpringBoardSpread;

extern NSString * const LAEventNameStatusBarSwipeRight;
extern NSString * const LAEventNameStatusBarSwipeLeft;
extern NSString * const LAEventNameStatusBarSwipeDown;
extern NSString * const LAEventNameStatusBarTapDouble;
extern NSString * const LAEventNameStatusBarHold;

extern NSString * const LAEventNameVolumeDownUp; // libactivator 1.0.1+
extern NSString * const LAEventNameVolumeUpDown; // libactivator 1.0.1+

extern NSString * const LAEventNameSlideInFromBottom; // libactivator 1.0.1+

// Activator

@protocol LAListener;

@interface LAActivator : NSObject {
@private
	NSMutableDictionary *_listeners;
	NSDictionary *_preferences;
}
+ (LAActivator *)sharedInstance;

- (id<LAListener>)listenerForEvent:(LAEvent *)event;
- (void)sendEventToListener:(LAEvent *)event;
- (void)sendAbortToListener:(LAEvent *)event;

- (void)registerListener:(id<LAListener>)listener forName:(NSString *)name;
- (void)unregisterListenerWithName:(NSString *)name;

- (void)reloadPreferences;

- (BOOL)hasSeenListenerWithName:(NSString *)name; // libactivator 1.0.1+

- (void)assignEventName:(NSString *)eventName toListenerWithName:(NSString *)listenerName; // libactivator 1.0.1+
- (void)unassignEventName:(NSString *)eventName; // libactivator 1.0.1+

@end

// Listeners

@protocol LAListener <NSObject>
@required
- (void)activator:(LAActivator *)activator receiveEvent:(LAEvent *)event;
@optional
- (void)activator:(LAActivator *)activator abortEvent:(LAEvent *)event;
@end

// Settings Controller

@interface LAListenerSettingsViewController : UIViewController {
@private
	NSString *_listenerName;
	NSMutableDictionary *_events;
	NSMutableDictionary *_eventData;
	NSMutableDictionary *_preferences;	
}

- (id)init;
@property (nonatomic, copy) NSString *listenerName;

@end

