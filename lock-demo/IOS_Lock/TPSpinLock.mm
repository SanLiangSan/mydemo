
//
//  TPSpinLock.m
//  IOS_Lock
//
//  Created by xingling xu on 2020/3/24.
//  Copyright © 2020 xingling xu. All rights reserved.
//

#import "TPSpinLock.h"

struct spinlock {
    int flag;
};

@implementation TPSpinLock {
    spinlock _lock;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _lock = spinlock{0};
    }
    return self;
}

- (void)lock {
    while (test_and_set(&_lock.flag, 1)) {
        // wait
    }
}

- (void)unlock {
    _lock.flag = 0;
}


int test_and_set(int *old_ptr, int _new) {
    int old = *old_ptr;
    *old_ptr = _new;
    return old;
}

@end
