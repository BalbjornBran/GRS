// Copyright (c) 2025, Balbjorn Bran. All rights reserved.


#include "Reactions/GR_HandleGameplayEvent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGR_HandleGameplayEvent::ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor)
{
	if (!TargetActor || !GameplayEventTag.IsValid())
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (ASC)
	{
		FGameplayEventData EventData;
		EventData.Instigator = InstigatorActor;
		EventData.Target = TargetActor;
		EventData.EventTag = GameplayEventTag;
		
		ASC->HandleGameplayEvent(GameplayEventTag, &EventData);
	}
}
