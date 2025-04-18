// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/AttributeReaction.h"
#include "GameplayReactionsDataAsset.generated.h"

/**
 * UGameplayReactionDataAsset is a data asset class that holds a collection
 * of attribute reaction data used within a gameplay ability system. This class
 * facilitates defining and organizing attribute-based reactions in a reusable and
 * centralized manner.
 */
UCLASS()
class GAMEPLAYREACTIONS_API UGameplayReactionsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * AttributeReactions is an array of attribute reaction data, where each entry
	 * specifies an observed gameplay attribute and the associated reactions that should
	 * be triggered upon changes to that attribute's value. This property is utilized within
	 * the gameplay ability system to manage attribute-based reactions in a modular and
	 * configurable manner.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAttributeReaction> AttributeReactions;
};
