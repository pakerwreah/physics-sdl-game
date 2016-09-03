//
//  compat.m
//  SDLTeste
//
//  Created by Paker on 25/04/16.
//  Copyright © 2016 Paker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "compat.h"

void setup() {
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
}
