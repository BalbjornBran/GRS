// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#include "Components/GameplayReactionComponent.h"
#include "GRLog.h"
#include "Reactions/GameplayReaction.h"
#include "Data/GameplayReactionsDataAsset.h"
#include "Types/AttributeReaction.h"

// Sets default values for this component's properties
UGameplayReactionComponent::UGameplayReactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameplayReactionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	//We are assuming that this component can go in different classes, not just characters, so thats why we use AActor
	if (Owner)
	{
		AbilitySystemComponent = Owner->FindComponentByClass<UAbilitySystemComponent>();
		if (AbilitySystemComponent)
		{
			GR_LOG_ARGS(Log, "Found Ability System Component on %s", *Owner->GetName());

			BindToAttributeChanges();
		}
		else
		{
			GR_LOG_ARGS(Error, "No Ability System Component found on %s", *Owner->GetName());
		}
	}
}

void UGameplayReactionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (AbilitySystemComponent && GameplayReactionsDataAsset)
	{
		for (const FAttributeReaction& ReactionData : GameplayReactionsDataAsset->AttributeReactions)
		{
			if (ReactionData.AttributeToObserve.IsValid())
			{
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ReactionData.AttributeToObserve).RemoveAll(this);
			}
		}
	}
}

void UGameplayReactionComponent::BindToAttributeChanges()
{
	if (!AbilitySystemComponent || !GameplayReactionsDataAsset)
	{
		GR_LOG(Error, "No Ability System Component or Attribute Reaction Data Asset found.");
		return;
	}

	// for each reactionData, bind to the Attribute change delegate
	for (const FAttributeReaction& ReactionData : GameplayReactionsDataAsset->AttributeReactions)
	{
		if (ReactionData.AttributeToObserve.IsValid())
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ReactionData.AttributeToObserve).AddUObject(this, &UGameplayReactionComponent::OnAttributeChanged);

			GR_LOG_ARGS(Verbose, "Correctly binding to attribute: %s", *ReactionData.AttributeToObserve.AttributeName);
		}
		else
		{
			GR_LOG(Error, "Attribute Reaction Data Asset contains an invalid Attribute to Observe.");
		}
	}
	
}

void UGameplayReactionComponent::OnAttributeChanged(const FOnAttributeChangeData& ChangeData) const
{
	//not sure if this is a bug, but the delegate triggers twice every attribute change. This is a quick fix for now.
	if (FMath::IsNearlyEqual(ChangeData.OldValue, ChangeData.NewValue))
	{
		//GR_LOG(Log, "Ignored Attribute change because was nearly 0");
		return;
	}
	
	GR_LOG_ARGS(Verbose, "Attribute Changed: Old Value: %f, New Value: %f", ChangeData.OldValue,ChangeData.NewValue);

	// Loop to go through all possible attributes that are being listened
	for (const FAttributeReaction& ReactionData : GameplayReactionsDataAsset->AttributeReactions)
	{
		if (ReactionData.AttributeToObserve.IsValid() && ReactionData.AttributeToObserve == ChangeData.Attribute)
		{
			for (UGameplayReaction* Reaction : ReactionData.ReactionsOnChange)
			{
				if (!Reaction)
				{
					continue;
				}

				if (Reaction->ShouldTriggerReaction(ChangeData.NewValue))
				{
					bool bDirectionMatches = false;
					switch (Reaction->GetChangeDirection())
					{
						case EAttributeChangeDirection::Any:
							bDirectionMatches = true;
							break;
						case EAttributeChangeDirection::Increase:
							bDirectionMatches = (ChangeData.NewValue > ChangeData.OldValue);
							break;
						case EAttributeChangeDirection::Decrease:
							bDirectionMatches = (ChangeData.NewValue < ChangeData.OldValue);
							break;						
					}

					if (bDirectionMatches)
					{
						GR_LOG_ARGS(Verbose, "Triggering Reaction: %s", *Reaction->GetName());
						Reaction->TryExecuteReaction(GetOwner(),GetOwner());
					}
					else
					{
						GR_LOG_ARGS(Verbose, "Reaction %s not triggered because direction did not match.", *Reaction->GetName());
					}
				}
			}
			//Once the attribute is found, exit the loop
			break;
		}
	}
}



