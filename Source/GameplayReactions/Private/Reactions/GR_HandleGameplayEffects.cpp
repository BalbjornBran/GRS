// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#include "Reactions/GR_HandleGameplayEffects.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGR_HandleGameplayEffects::ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor)
{
	if (!GameplayEffectToApply || !TargetActor)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (ASC)
	{
		if (ApplyMode == EGameplayEffectApplyMode::Apply)
		{
			FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
			if (InstigatorActor)
			{
				ContextHandle.AddInstigator(InstigatorActor, nullptr);
			}
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectToApply, EffectLevel, ContextHandle);
			if (SpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
		else if (ApplyMode == EGameplayEffectApplyMode::Remove)
		{
			FGameplayEffectQuery Query;
			Query.EffectDefinition = GameplayEffectToApply.Get();
			ASC->RemoveActiveEffects(Query);
		}
	}
}
