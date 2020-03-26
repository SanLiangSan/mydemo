//
//  TPSpinLock.h
//  IOS_Lock
//
//  Created by xingling xu on 2020/3/24.
//  Copyright © 2020 xingling xu. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TPSpinLock : NSObject

- (instancetype)init;

- (void)lock;

- (void)unlock;
@end

NS_ASSUME_NONNULL_END
