// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GRDevSettings.h"

GAMEPLAYREACTIONS_API DECLARE_LOG_CATEGORY_EXTERN(GRLog, Log, All);

/**
 * Creates appropriate messages for the GAS category.
 * 
 * @param Verbosity		Verbosity level of this message. See ELogVerbosity.
 * @param Message		Message string literal.
 */
#define GR_LOG(Verbosity, Message) \
do \
{ \
	if (GEngine && WITH_EDITOR) \
	{ \
		if (const UGRDevSettings* Settings = GetDefault<UGRDevSettings>()) \
		{ \
			if (Settings->bShowLogMessages) \
			{ \
				UE_LOG(GRLog, Verbosity, TEXT("%s: %s"), TEXT(__FUNCTION__), TEXT(Message)); \
			} \
		} \
	} \
} while (0)


/**
 * Creates appropriate messages for the GAS category, with format arguments.
 * 
 * @param Verbosity		Verbosity level of this message. See ELogVerbosity.
 * @param Format		Format string literal in the style of printf.
 * @param Args			Comma-separated arguments used to format the message.
 */
#define GR_LOG_ARGS(Verbosity, Format, ...) \
do \
{ \
	if (GEngine && WITH_EDITOR) \
	{ \
		if (const UGRDevSettings* Settings = GetDefault<UGRDevSettings>()) \
		{ \
			if (Settings->bShowLogMessages) \
			{ \
				UE_LOG(GRLog, Verbosity, TEXT("%s: %s"), TEXT(__FUNCTION__), *FString::Printf(TEXT(Format), ##__VA_ARGS__)); \
			} \
		} \
	} \
} while (0)
		
