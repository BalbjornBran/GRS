// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GRDevSettings.generated.h"

UENUM(BlueprintType)
enum class EGRLogVerbosity : uint8
{
	Fatal UMETA(DisplayName = "Fatal"),
	Error UMETA(DisplayName = "Error"),
	Warning UMETA(DisplayName = "Warning"),
	Log UMETA(DisplayName = "Log"),
	Verbose UMETA(DisplayName = "Verbose"),
	VeryVerbose UMETA(DisplayName = "Very Verbose")
};

/**
 * Define customizable configs for the reaction system.
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Gameplay Reactions"))
class GAMEPLAYREACTIONS_API UGRDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug|Log")
	bool bShowLogMessages;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug|Log", meta = (EditCondition = "bShowLogMessages"))
	EGRLogVerbosity LogVerbosity;


	UGRDevSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
