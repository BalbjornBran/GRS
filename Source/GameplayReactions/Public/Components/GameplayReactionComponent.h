// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "GameplayReactionComponent.generated.h"

/*
 TODO FUTURE: Improve capturing the real Instigator.
 Currently using GetOwner() as Instigator. To capture the true instigator,
 listen to GameplayEffect applications and extract the Instigator from the EffectContext.
 This will allow more accurate reactions based on who caused the attribute change.
*/

class UGameplayReactionsDataAsset;
struct FOnAttributeChangeData;


/**
 * A gameplay ability system component that observes and reacts to attribute changes.
 * This component binds to changes in specific attributes and performs defined reactions based on data
 * in a GameplayAttributeReactionDataAsset. Suitable for use with an Ability System Component.
 */
UCLASS(ClassGroup=("Gameplay Reactions"), meta=(BlueprintSpawnableComponent))
class GAMEPLAYREACTIONS_API UGameplayReactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Constructor
	UGameplayReactionComponent();

	/**
	 * A data asset that encapsulates attribute reactions for a gameplay ability system.
	 * This variable references a UGameplayAttributeReactionDataAsset containing a collection of attribute-specific reactions.
	 * Used to configure and manage the response behavior triggered by changes in gameplay attributes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TObjectPtr<UGameplayReactionsDataAsset> GameplayReactionsDataAsset;

	/**
	 * Responds to changes in a monitored gameplay attribute.
	 * This method is triggered whenever an observed attribute's value changes. It processes
	 * the change using the provided data and triggers any associated reactions defined
	 * in the linked AttributeReactionDataAsset.
	 *
	 * @param ChangeData Contains information about the attribute change, including the old value, new value,
	 *        the affected attribute, and any relevant gameplay effect modification data.
	 */
	void OnAttributeChanged(const FOnAttributeChangeData& ChangeData) const;

	
protected:
	// ----------------------------------------------------------------------------------------------------------------
	// Begin Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// ----------------------------------------------------------------------------------------------------------------
	// End Overriden Parent Functions
	// ----------------------------------------------------------------------------------------------------------------

private:
	/**
	 * A pointer to an Ability System Component associated with the owner of this component.
	 * This variable holds a reference to the UAbilitySystemComponent on the actor, allowing access
	 * to gameplay attributes and the ability system for binding, observing, and reacting to attribute changes.
	 * Automatically initialized by finding the component on the owning actor in BeginPlay.
	 */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/**
	 * Binds the component to observe and react to changes in specific attributes.
	 * This method iterates through the attributes defined in the linked AttributeReactionDataAsset
	 * and establishes delegates for monitoring changes by leveraging the Ability System Component.
	 * Any associated reactions defined in the data asset are configured to trigger upon attribute modification.
	 *
	 * Ensures valid references to the Ability System Component and Attribute Reaction Data Asset.
	 * Logs warnings and errors for invalid configurations, such as missing assets or attributes.
	 */
	void BindToAttributeChanges();
};
