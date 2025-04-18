// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayReaction.h"
#include "GameplayTagContainer.h"
#include "GR_HandleGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYREACTIONS_API UGR_HandleGameplayEvent : public UGameplayReaction
{
	GENERATED_BODY()

	
public:
	virtual void ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayEvent", meta = (Categories = "Event"))
	FGameplayTag GameplayEventTag;
};
