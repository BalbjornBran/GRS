// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AttributeReaction.generated.h"

class UGameplayReaction;

USTRUCT(BlueprintType)
struct GAMEPLAYREACTIONS_API FAttributeReaction
{
	GENERATED_BODY()

public:
	/**
	 * AttributeToObserve defines the specific gameplay attribute to monitor for changes in value.
	 * This variable is a part of the FAttributeReactionData structure and is used to determine
	 * which attribute should be tracked by the associated system. When the observed attribute changes,
	 * it triggers reactions or behaviors defined within the system. This functionality is essential
	 * for creating dynamic systems that respond to attribute changes, such as health, mana, or other gameplay metrics.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute AttributeToObserve;

	/**
	 * ReactionsOnChange is a collection of reaction objects that are triggered when the associated attribute changes.
	 * Each reaction in this array represents a specific behavior or action to execute in response to the observed attribute change.
	 * The reactions are customizable and can be instantiated as part of a blueprint or derived code.
	 * This array supports the creation of reactive systems in which gameplay mechanics adapt dynamically to changes in attributes.
	 */
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	TArray<TObjectPtr<UGameplayReaction>> ReactionsOnChange;
	
};
