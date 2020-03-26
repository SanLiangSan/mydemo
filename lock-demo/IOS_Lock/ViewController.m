//
//  ViewController.m
//  IOS_Lock
//
//  Created by xingling xu on 2020/3/19.
//  Copyright © 2020 xingling xu. All rights reserved.
//

#import "ViewController.h"
#import "TPSpinLock.h"


@interface ViewController ()
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, strong) NSMutableArray *array2;
@property (atomic, assign) NSInteger number;
@property (nonatomic, strong) TPSpinLock *spinLock;
@end


@implementation ViewController



- (void)viewDidLoad {
    [super viewDidLoad];
//    self.spinLock = [[TPSpinLock alloc] init];
//    self.array = [NSMutableArray array];
//    [self ss_crash];
//    [self synchronized_crash];
    
//    static NSString *token = @"synchronized-token";
//    @synchronized (token) {
//        self.array1 = [NSMutableArray array];
//    }
//
//    static NSString *another_token = @"another_token";
//    @synchronized (another_token) {
//        self.array2 = [NSMutableArray array];
//    }

    [self blockTest];
}

- (void)spinLock1 {
    dispatch_queue_t queue = dispatch_queue_create("hahahha", DISPATCH_QUEUE_CONCURRENT);
    
    dispatch_async(queue, ^{
        for (int i = 0; i < 10000; i++) {
            [self.spinLock lock];
            self.number = self.number + 1;
            [self.spinLock unlock];
            NSLog(@"a number is %ld",self.number);
        }
    });
    
    
    dispatch_async(queue, ^{
        for (int i = 0; i < 10000; i++) {
            [self.spinLock lock];
            self.number = self.number + 1;
            [self.spinLock unlock];
            NSLog(@"b number is %ld",self.number);
        }
    });
    
    dispatch_barrier_async(queue, ^{
        NSLog(@"hahha total number is %ld",self.number);
    });
    
    dispatch_async(queue, ^{
        NSLog(@"total number is %ld",self.number);
    });
    
}


- (void)ss_crash {
    for (NSInteger i = 0; i < 20000; i ++) {
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            self->_array = [NSMutableArray array];
        });
    }
}

- (void)synchronized_crash {
    for (NSInteger i = 0; i < 20000; i ++) {
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            @synchronized (self->_array) {
                self->_array = [NSMutableArray array];
            }
        });
    }
}

- (void)atomicTest {
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 10000; i ++) {
            self.number = self.number + 1;
            NSLog(@"A-self.number is %ld",self.number);
        }
    });
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        for (int i = 0; i < 10000; i ++) {
            self.number = self.number + 1;
            NSLog(@"B-self.number is %ld",self.number);
        }
    });
    
}

// block
- (void)blockTest {
    // Case 1
    void (^testBlock)(void) = ^{
        NSLog(@"this is block");
    };
    testBlock();
    NSLog(@"block is %@",testBlock); // block is <__NSGlobalBlock__: 0x10746e118>
    
    // Case 2
    int a = 10;
    void (^testBlock1)(void) = ^{
        NSLog(@"a is %d",a);
    };
    testBlock1();
    NSLog(@"block1 is %@",testBlock1);// block1 is <__NSMallocBlock__: 0x6000037c7a80>
    
    // Case 3
    NSLog(@"block copy 之前是 %@",^{   // block copy 之前是 <__NSStackBlock__: 0x7ffee400c7e8>
        NSLog(@"a is %d",a);
    });

}




@end
