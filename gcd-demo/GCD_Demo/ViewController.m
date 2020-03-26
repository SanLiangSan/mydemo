//
//  ViewController.m
//  GCD_Demo
//
//  Created by xingling xu on 2020/3/5.
//  Copyright © 2020 xingling xu. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController {
    dispatch_group_t _group;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self groupDemo2];
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        [self groupDemo2];
//    });
}

///  同步函数 + 串行队列
- (void)sync_serial {
    dispatch_queue_t queue = dispatch_queue_create("sync_serial", DISPATCH_QUEUE_SERIAL);
    dispatch_sync(queue, ^{
        NSLog(@"1 is on %@",[NSThread currentThread]);
    });
    dispatch_sync(queue, ^{
        NSLog(@"2 is on %@",[NSThread currentThread]);
    });
    // print 1 2
}

/// 同步函数 + 并发队列
- (void)sync_concurrent {
    dispatch_queue_t queue = dispatch_queue_create("sync_concurrent", DISPATCH_QUEUE_CONCURRENT);
    dispatch_sync(queue, ^{
        NSLog(@"1 is on %@",[NSThread currentThread]);
    });
    dispatch_sync(queue, ^{
        NSLog(@"2 is on %@",[NSThread currentThread]);
    });
    // print 1 2
}

/// 异步函数 + 串行队列
- (void)async_serial {
    dispatch_queue_t queue = dispatch_queue_create("sync_serial", DISPATCH_QUEUE_SERIAL);
    dispatch_async(queue, ^{
        NSLog(@"1 is on %@",[NSThread currentThread]);
    });
    dispatch_async(queue, ^{
        NSLog(@"2 is on %@",[NSThread currentThread]);
    });
    // print 1 2
}

/// 异步函数 + 并发队列
- (void)async_concurrent {
    dispatch_queue_t queue = dispatch_queue_create("sync_concurrent", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^{
        NSLog(@"1 is on %@",[NSThread currentThread]);
    });
    dispatch_async(queue, ^{
        NSLog(@"2 is on %@",[NSThread currentThread]);
    });
    // print 2 1
}


#pragma mark - group demo

- (void)groupDemo {
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
        NSLog(@"异步请求1");
    });
    dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
        sleep(3);
        NSLog(@"异步请求2");
    });
    
    dispatch_group_notify(group, dispatch_get_global_queue(0, 0), ^{
        NSLog(@"1和2执行完了异步请求3");
    });
    
    dispatch_group_async(group, dispatch_get_global_queue(0, 0), ^{
        NSLog(@"异步请求4");
    });
    
}



- (void)groupDemo2 {
    dispatch_group_t group = dispatch_group_create();
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    
    dispatch_group_enter(group);
    dispatch_async(queue, ^{
        NSLog(@"异步请求1");
        dispatch_group_leave(group);
    });
    
    dispatch_group_enter(group);
    dispatch_async(queue, ^{
        sleep(3);
        NSLog(@"异步请求2");
        dispatch_group_leave(group);
    });
 
    
    dispatch_group_notify(group, dispatch_get_global_queue(0, 0), ^{
        NSLog(@"1和2执行完了异步请求3");
    });

}
@end
