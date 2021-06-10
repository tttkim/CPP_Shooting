// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Log 카테고리 추가
DECLARE_LOG_CATEGORY_EXTERN(Shooting, Log, All)

// 어디에서 로그를 찍고 있는지, 줄번호까지 알려주는 기능
#define CALLINFO ( FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")") )
#define PRINT_CALLINFO() UE_LOG(Shooting, Warning, TEXT("%s"), *CALLINFO)

#define PRINTLOG(fmt, ...) UE_LOG(Shooting, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))
