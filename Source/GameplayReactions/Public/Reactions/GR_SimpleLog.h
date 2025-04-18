// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayReaction.h"
#include "GRLog.h"
#include "GR_SimpleLog.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYREACTIONS_API UGR_SimpleLog : public UGameplayReaction
{
	GENERATED_BODY()

public:
	virtual void ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|CustomLog")
	FString LogMessage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|CustomLog")
	EGRLogVerbosity LogVerbosity = EGRLogVerbosity::Warning;
};
