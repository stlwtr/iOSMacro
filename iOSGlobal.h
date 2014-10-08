//
//  iOSGlobal.h
//
//  Created by stlwtr on 13-10-11.
//  Copyright (c) 2013年 stlwtr. All rights reserved.
//

#ifndef iOSGlobal_h
#define iOSGlobal_h
#import <Availability.h>

#pragma mark - Device && Screen
/// 判断是否是iPhone5
#define isPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
/// 是否iPad
#define isPad (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
/// 是否模拟器
#ifdef TARGET_IPHONE_SIMULATOR
#define isSimulator TARGET_IPHONE_SIMULATOR
#endif

/// 屏幕高度、宽度
#define Screen_height   [[UIScreen mainScreen] bounds].size.height
#define Screen_width    [[UIScreen mainScreen] bounds].size.width

#pragma mark - System Version
/// 当前系统版本大于等于某版本
#define IOS_SYSTEM_VERSION_EQUAL_OR_ABOVE(v) (([[[UIDevice currentDevice] systemVersion] floatValue] >= (v))? (YES):(NO))
/// 当前系统版本小于等于某版本
#define IOS_SYSTEM_VERSION_EQUAL_OR_BELOW(v) (([[[UIDevice currentDevice] systemVersion] floatValue] <= (v))? (YES):(NO))
/// 当前系统版本
#define IOS_SYSTEM_VERSION [[[UIDevice currentDevice] systemVersion] floatValue]

#define iOS7 (IOS_SYSTEM_VERSION >= 7.0)

/// 系统语言
#define IOS_SYSTEM_Language ([[NSLocale preferredLanguages] objectAtIndex:0])

/// 当前应用版本号
#define AppVersion [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]

#pragma mark - common path
/// 常用文件路径
#define PathForDocument NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0]
#define PathForLibrary  NSSearchPathForDirectoriesInDomains (NSLibraryDirectory, NSUserDomainMask, YES)[0]
#define PathForCaches   NSSearchPathForDirectoriesInDomains (NSCachesDirectory, NSUserDomainMask, YES)[0]

#pragma mark - shared tool

#define SharedUserDefault         [NSUserDefaults standardUserDefaults]
#define SharedNotificationCenter  [NSNotificationCenter defaultCenter]
#define SharedFileManager         [NSFileManager defaultManager]
#define SharedApplicationDelegate [[UIApplication sharedApplication] delegate]

#pragma mark - image && color
/// 加载图片
#define UIImageLoad(name, type)     [UIImage imageWithContentsOfFile:[[NSBundle mainBundle]pathForResource:name ofType:type]]
#define UIImageNamed( name )    [UIImage imageNamed: name]
/// 颜色
#define UIColorWithRGBHex(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]
#define UIColorWithRGBA(r, g, b, a) [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:a]
#define UIColorWithRGB(r, g, b) [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:1.0]
/// 方正黑体简体字体定义
#define UIFontWithSize( __size__ ) [UIFont systemFontOfSize: __size__]
#define UIFontBoldWithSize( __size__ ) [UIFont boldSystemFontOfSize: __size__]

#pragma mark - GCD
/** 全局线程执行方法 */
static inline void st_dispatch_async_global(dispatch_block_t block) {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), block);
}
/** 主线程执行方法 */
static inline void st_dispatch_async_main(dispatch_block_t block) {
    dispatch_async(dispatch_get_main_queue(), block);
}
/** 主线程延时执行方法 */
static inline void st_dispatch_async_main_after(NSTimeInterval ti, dispatch_block_t block) {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(ti * NSEC_PER_SEC)), dispatch_get_main_queue(), block);
}

#pragma mark - view size, frame
/** 根据字符串、最大尺寸、字体计算字符串最合适尺寸 */
static inline CGSize CGSizeOfString(NSString * text, CGSize maxSize, UIFont * font) {
    CGSize fitSize;
#ifdef __IPHONE_7_0
    fitSize = [text boundingRectWithSize:maxSize options:NSStringDrawingUsesFontLeading | NSStringDrawingTruncatesLastVisibleLine | NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName: font} context:nil].size;
#else
    fitSize = [text sizeWithFont:font constrainedToSize:maxSize];
#endif
    return fitSize;
}
/** 设置视图大小，原点不变 */
static inline void UIViewSetSize(UIView *view, CGSize size) { CGRect frame = view.frame; frame.size = size; view.frame = frame;}
/** 设置视图宽度，其他不变 */
static inline void UIViewSetSizeWidth(UIView *view, CGFloat width) { CGRect frame = view.frame; frame.size.width = width; view.frame = frame; }
/** 设置视图高度，其他不变 */
static inline void UIViewSetSizeHeight(UIView *view, CGFloat height) { CGRect frame = view.frame; frame.size.height = height; view.frame = frame; }
/** 设置视图原点，大小不变 */
static inline void UIViewSetOrigin(UIView *view, CGPoint pt) { CGRect frame = view.frame; frame.origin = pt; view.frame = frame; }
/** 设置视图原点x坐标，大小不变 */
static inline void UIViewSetOriginX(UIView *view, CGFloat x) { CGRect frame = view.frame; frame.origin.x = x; view.frame = frame; }
/** 设置视图原点y坐标，大小不变 */
static inline void UIViewSetOriginY(UIView *view, CGFloat y) { CGRect frame = view.frame; frame.origin.y = y; view.frame = frame; }

#pragma mark - NSString format
/** data format */

#define NSStringFromNumber_c( __v__ ) [NSString stringWithFormat:@"%@", @(__v__)]
#define NSStringFromObject_oc( __v__ ) [NSString stringWithFormat:@"%@", __v__]

static inline void UIAlertViewShowMessage(NSString *message) { UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:message delegate:nil cancelButtonTitle:@"确定" otherButtonTitles: nil]; [alert show]; }

#pragma mark - DEBUG
/** ======================= 调试相关宏定义 ========================== */
/// 添加调试控制台输出
#ifdef DEBUG
#define DLog(fmt, ...) NSLog((@"%s [Line %d]\n😄 " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#define ELog(fmt, ...) NSLog((@"%s [Line %d]\n😥 " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define DLog(...)
#define ELog(...)
#define NSLog(...)
#endif
/// 是否输出dealloc log
//#define Dealloc
#ifdef Dealloc
#define DeallocLog(fmt, ...) NSLog((fmt @"dealloc ..."), ##__VA_ARGS__);
#else
#define DeallocLog(...)
#endif

#endif
