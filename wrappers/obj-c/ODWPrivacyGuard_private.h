//
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: Apache-2.0
//
#include "objc_begin.h"
#include "ILogger.hpp"
#import "ODWPrivacyGuard.h"
#import "ODWPrivacyGuardInitConfig.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 The <b>ODWPrivacyGuard</b> class represents Privacy Guard Hook.
*/
@interface ODWPrivacyGuard (Private)

#pragma mark Initialization methods

/*!
 @brief Initializes Privacy Guard
 @param logger Logger used for reporting concerns
 @param commonDataContextsObject Common Data Contexts
 */
+(void)initializePrivacyGuard:(ILogger *)logger withODWPrivacyGuardInitConfig:(ODWPrivacyGuardInitConfig *)initConfigObject;
@end

NS_ASSUME_NONNULL_END
#include "objc_end.h"
