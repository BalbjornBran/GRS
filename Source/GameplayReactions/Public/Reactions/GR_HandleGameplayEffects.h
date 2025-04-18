// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayReaction.h"
#include "GR_HandleGameplayEffects.generated.h"

UENUM(BlueprintType)
enum class EGameplayEffectApplyMode : uint8
{
	Apply	UMETA(DisplayName = "Apply gameplay effect"),
	Remove	UMETA(DisplayName = "Remove gameplay effect")
};

/**
 * Represents a reaction that applies or removes a specified GameplayEffect to or from a target actor.
 * This class inherits from UReaction and executes the GameplayEffect logic when the reaction is triggered.
 */
UCLASS(Blueprintable, EditInlineNew)
class GAMEPLAYREACTIONS_API UGR_HandleGameplayEffects : public UGameplayReaction
{
	GENERATED_BODY()

	virtual void ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor) override;

	
protected:

	/** Whether to apply or remove the GameplayEffect */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayEffect")
	EGameplayEffectApplyMode ApplyMode = EGameplayEffectApplyMode::Apply;

	/** GameplayEffect to apply or remove */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayEffect")
	TSubclassOf<class UGameplayEffect> GameplayEffectToApply;

	/** Level at which to apply the GameplayEffect */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayEffect")
	float EffectLevel = 1.f;
	
};
