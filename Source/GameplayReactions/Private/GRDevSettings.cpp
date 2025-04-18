// Copyright (c) 2025, Balbjorn Bran. All rights reserved.


#include "GRDevSettings.h"
#include "Engine/Engine.h"
#include "GRLog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

UGRDevSettings::UGRDevSettings()
{
	bShowLogMessages = false;
	LogVerbosity = EGRLogVerbosity::Warning;
}

ELogVerbosity::Type ToUnrealVerbosity(EGRLogVerbosity InVerbosity)
{
	switch (InVerbosity)
	{
	case EGRLogVerbosity::Fatal: return ELogVerbosity::Fatal;
	case EGRLogVerbosity::Error: return ELogVerbosity::Error;
	case EGRLogVerbosity::Warning: return ELogVerbosity::Warning;
	case EGRLogVerbosity::Log: return ELogVerbosity::Log;
	case EGRLogVerbosity::Verbose: return ELogVerbosity::Verbose;
	case EGRLogVerbosity::VeryVerbose: return ELogVerbosity::VeryVerbose;
	default: return ELogVerbosity::Warning;
	}
}

void ApplyLogVerbosity()
{
		ELogVerbosity::Type NewVerbosity;
		const UGRDevSettings *Settings = GetDefault<UGRDevSettings>();
		switch (Settings->LogVerbosity)
		{
		case EGRLogVerbosity::Fatal: NewVerbosity = ELogVerbosity::Fatal; break;
		case EGRLogVerbosity::Error: NewVerbosity = ELogVerbosity::Error; break;
		case EGRLogVerbosity::Warning: NewVerbosity = ELogVerbosity::Warning; break;
		case EGRLogVerbosity::Log: NewVerbosity = ELogVerbosity::Log; break;
		case EGRLogVerbosity::Verbose: NewVerbosity = ELogVerbosity::Verbose; break;
		case EGRLogVerbosity::VeryVerbose: NewVerbosity = ELogVerbosity::VeryVerbose; break;
		default: NewVerbosity = ELogVerbosity::Warning; break;
		}

		GRLog.SetVerbosity(NewVerbosity);
}

#if WITH_EDITOR
void UGRDevSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
	? PropertyChangedEvent.Property->GetFName()
	: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UGRDevSettings, LogVerbosity))
	{
		ApplyLogVerbosity();

		FNotificationInfo Info(FText::FromString(FString::Printf(TEXT("Gameplay Reactions: Log verbosity updated to %s"), *StaticEnum<EGRLogVerbosity>()->GetValueAsString(LogVerbosity))));
		Info.FadeInDuration = 0.1f;
		Info.FadeOutDuration = 0.5f;
		Info.ExpireDuration = 2.0f;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = true;
		Info.bUseLargeFont = false;
		Info.bFireAndForget = true;

		FSlateNotificationManager::Get().AddNotification(Info);
	}
	
}
#endif