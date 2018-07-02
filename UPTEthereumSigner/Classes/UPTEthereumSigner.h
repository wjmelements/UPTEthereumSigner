//
//  UPTEthSigner.h
//  uPortMobile
//
//  Created by josh on 10/18/17.
//  Copyright © 2017 ConsenSys AG. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM( NSInteger, UPTEthKeychainProtectionLevel ) {
  /// @description stores key via VALValet with VALAccessibilityWhenUnlockedThisDeviceOnly
  UPTEthKeychainProtectionLevelNormal = 0,
  
  /// @description stores key via VALSynchronizableValet
  UPTEthKeychainProtectionLevelICloud,
  
  /// @description stores key via VALSecureEnclaveValet
  UPTEthKeychainProtectionLevelPromptSecureEnclave,
  
  /// @description stores key via VALSinglePromptSecureEnclaveValet
  UPTEthKeychainProtectionLevelSinglePromptSecureEnclave,
  
  /// @description Indicates an invalid unrecognized storage level
  ///  Debug strategy:
  ///  1. confirm no typo on react native sender side,
  ///  2. confirm parity with android levels
  ///  3. maybe update string constants in this class
  UPTEthKeychainProtectionLevelNotRecognized = NSNotFound
};

///
/// @description: these strings are the possible strings passed in from react native as indicated in clubhouse task 2565
///
FOUNDATION_EXPORT NSString *const ReactNativeKeychainProtectionLevelNormal;
FOUNDATION_EXPORT NSString *const ReactNativeKeychainProtectionLevelICloud;
FOUNDATION_EXPORT NSString *const ReactNativeKeychainProtectionLevelPromptSecureEnclave;
FOUNDATION_EXPORT NSString *const ReactNativeKeychainProtectionLevelSinglePromptSecureEnclave;

/// @description level param is not recognized by the system
/// @debugStrategy add support for new level value or fix possible typo or incompatibility error on react native js side
FOUNDATION_EXPORT NSString * const UPTSignerErrorCodeLevelParamNotRecognized;
FOUNDATION_EXPORT NSString * const UPTSignerErrorCodeLevelPrivateKeyNotFound;

/// @param ethAddress    an Ethereum adderss with prefix '0x'. May be nil if error occured
/// @param publicKey    a base 64 encoded representation of the NSData public key. Note: encoded with no line
///                     breaks. May be nil if error occured.
/// @param error        non-nil only if an error occured
typedef void (^UPTEthSignerKeyPairCreationResult)(NSString *ethAddress, NSString *publicKey, NSError *error);

typedef void (^UPTEthSignerTransactionSigningResult)(NSDictionary *signature, NSError *error);
typedef void (^UPTEthSignerJWTSigningResult)(NSData *signature, NSError *error);

@class VALValet;

@interface UPTEthereumSigner : NSObject

+ (void)createKeyPairWithStorageLevel:(UPTEthKeychainProtectionLevel)protectionLevel result:(UPTEthSignerKeyPairCreationResult)result;

+ (void)saveKey:(NSData *)privateKey protectionLevel:(UPTEthKeychainProtectionLevel)protectionLevel result:(UPTEthSignerKeyPairCreationResult)result;

+ (void)signTransaction:(NSString *)ethAddress data:(NSString *)payload userPrompt:(NSString*)userPromptText result:(UPTEthSignerTransactionSigningResult)result;

+ (void)signJwt:(NSString *)ethAddress userPrompt:(NSString*)userPromptText data:(NSData *)payload result:(UPTEthSignerJWTSigningResult)result;

+ (NSString *)ethAddressWithPublicKey:(NSData *)publicKey;

+ (NSArray *)allAddresses;

// utils

+ (UPTEthKeychainProtectionLevel)enumStorageLevelWithStorageLevel:(NSString *)storageLevel;

+ (NSData *)keccak256:(NSData *)input;

+ (NSString *)hexStringWithDataKey:(NSData *)dataPrivateKey;

+ (NSData *)dataFromHexString:(NSString *)originalHexString;

+ (NSString *)base64StringWithURLEncodedBase64String:(NSString *)URLEncodedBase64String;

+ (NSString *)URLEncodedBase64StringWithBase64String:(NSString *)base64String;

@end
