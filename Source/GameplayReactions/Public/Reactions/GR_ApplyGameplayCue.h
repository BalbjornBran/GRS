// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayReaction.h"
#include "GameplayTagContainer.h"
#include "GR_ApplyGameplayCue.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYREACTIONS_API UGR_ApplyGameplayCue : public UGameplayReaction
{
	GENERATED_BODY()
public:
	virtual void ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayCue", meta = (Categories = "GameplayCue"))
	FGameplayTag GameplayCueTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction|GameplayCue")
	bool bAllowLocalPlay = true;
};
