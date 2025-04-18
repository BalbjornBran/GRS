// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#include "Reactions/GameplayReaction.h"
#include "GRLog.h"

void UGameplayReaction::ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor)
{
	// This does nothing here, can be overriden in blueprints or childs
}

void UGameplayReaction::TryExecuteReaction(AActor* InstigatorActor, AActor* TargetActor)
{
	// A valid actor is needed to trigger a delay, so we check for the actors here.
	AActor* ValidActor = TargetActor ? TargetActor : InstigatorActor;
	if (!ValidActor)
	{
		// As we didn't find any actor, we are just going to ignore the delay
		GR_LOG(Warning, "No valid actor to execute reaction and its not possible to active the delay.");
		ExecuteReaction(InstigatorActor, TargetActor);
		return;
	}

	// If we have a delay, we are going to use it.
	if (bUseDelay && DelaySeconds > 0.0f && ValidActor)
	{
		UWorld* World = ValidActor->GetWorld();
		if (World)
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("ExecuteReaction"), InstigatorActor, TargetActor);

			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DelaySeconds, false);
		}
	}
	else
	{
		ExecuteReaction(InstigatorActor, TargetActor);
	}
}

bool UGameplayReaction::ShouldTriggerReaction(float currentValue)
{
	// Switch for comparting the value
	switch (ActivationCondition)
	{
	case EReactionActivationCondition::Always:
		return true;
	case EReactionActivationCondition::GreaterThan:
		return currentValue > ThresholdValue;
	case EReactionActivationCondition::GreaterThanOrEqual:
		return currentValue >= ThresholdValue;
	case EReactionActivationCondition::Equal:
		return currentValue == ThresholdValue;
	case EReactionActivationCondition::LessThan:
		return currentValue < ThresholdValue;
	case EReactionActivationCondition::LessThanOrEqual:
		return currentValue <= ThresholdValue;
	default:
		return false;	
	}
}
