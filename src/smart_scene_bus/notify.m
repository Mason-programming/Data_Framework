// notify.m
#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>

void sendNotification(NSString *dccName) {
    UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];
    content.title = [NSString stringWithFormat:@"%@ Launched 🚀", dccName];
    content.subtitle = @"USD Bridge";
    content.body = @"Click here to load your last USD scene.";
    content.sound = [UNNotificationSound defaultSound];

    UNTimeIntervalNotificationTrigger *trigger = [UNTimeIntervalNotificationTrigger triggerWithTimeInterval:1 repeats:NO];

    UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:@"USDNotification"
                                                                          content:content
                                                                          trigger:trigger];

    [[UNUserNotificationCenter currentNotificationCenter]
        addNotificationRequest:request
        withCompletionHandler:^(NSError * _Nullable error) {
            if (error != nil) {
                NSLog(@"❌ Failed to send notification: %@", error);
            } else {
                NSLog(@"✅ Notification sent for %@", dccName);
            }
        }];
}

void requestNotificationPermissionAndNotify(NSString *dccName) {

        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        [center requestAuthorizationWithOptions:(UNAuthorizationOptionAlert + UNAuthorizationOptionSound)
                            completionHandler:^(BOOL granted, NSError * _Nullable error) {
            if (!granted) {
                NSLog(@"⚠️ Notification permission denied.");
            } else {
                NSLog(@"✅ Notification permission granted.");
                // Continue with sending notification here if needed
            }
        }];
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *dccName = @"Blender";

        // If a custom DCC name is passed from the command line
        if (argc > 1) {
            dccName = [NSString stringWithUTF8String:argv[1]];
        }
        requestNotificationPermissionAndNotify(dccName);

        // Keep runloop alive briefly to allow async notification delivery
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:2]];
    }
    return 0;
}
