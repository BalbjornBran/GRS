// Fill out your copyright notice in the Description page of Project Settings.


#include "Reactions/GR_ApplyGameplayCue.h"
#include "AbilitySystemComponent.h"
#include "GameplayCueManager.h"
#include "AbilitySystemGlobals.h"

void UGR_ApplyGameplayCue::ExecuteReaction_Implementation(AActor* InstigatorActor, AActor* TargetActor)
{
	if (!TargetActor || !GameplayCueTag.IsValid())
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (ASC)
	{
		ASC->ExecuteGameplayCue(GameplayCueTag);
	}
	else if (bAllowLocalPlay)
	{
		FGameplayCueParameters CueParams;
		CueParams.Instigator = InstigatorActor;
		CueParams.SourceObject = this;
		CueParams.EffectCauser = InstigatorActor;

		UGameplayCueManager* CueManager = UAbilitySystemGlobals::Get().GetGameplayCueManager();
		if (CueManager)
		{
			CueManager->HandleGameplayCue(TargetActor,GameplayCueTag, EGameplayCueEvent::Executed, CueParams);
		}
	}
	
}
