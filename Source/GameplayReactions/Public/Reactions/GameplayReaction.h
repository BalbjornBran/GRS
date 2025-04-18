// Copyright (c) 2025, Balbjorn Bran. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayReaction.generated.h"

/**
 * @enum EReactionActivationCondition
 * A blueprintable enumeration defining the conditions for activating a reaction.
 *
 * Enumerators:
 * - Always: Reaction is always activated regardless of the conditions.
 * - GreaterThan: Reaction is activated if the value is greater than a specified threshold.
 * - GreaterThanOrEqual: Reaction is activated if the value is greater than or equal to a specified threshold.
 * - Equal: Reaction is activated if the value is equal to a specified threshold.
 * - LessThan: Reaction is activated if the value is less than a specified threshold.
 * - LessThanOrEqual: Reaction is activated if the value is less than or equal to a specified threshold.
 */
UENUM(BlueprintType)
enum class EReactionActivationCondition : uint8
{
	Always UMETA(DisplayName = "Always activate"),
	GreaterThan UMETA(DisplayName = "Greater Than Threshold"),
	GreaterThanOrEqual UMETA(DisplayName = "Greater Than Or Equal To Threshold"),
	Equal UMETA(DisplayName = "Equal To Threshold"),
	LessThan UMETA(DisplayName = "Less Than Threshold"),
	LessThanOrEqual UMETA(DisplayName = "Less Than Or Equal To Threshold")
};

UENUM(BlueprintType)
enum class EAttributeChangeDirection : uint8
{
	Any        UMETA(DisplayName="Any Change"),
	Increase   UMETA(DisplayName="Increase Only"),
	Decrease   UMETA(DisplayName="Decrease Only")
};

/**
 * @class UGameplayReaction
 * Abstract base class for a reaction system that allows for different behaviors to be executed
 * based on activation conditions, thresholds, and optional delays.
 *
 * Methods can be overridden or extended to implement custom reactions.
 */
UCLASS(Abstract,Blueprintable,EditInlineNew)
class GAMEPLAYREACTIONS_API UGameplayReaction : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Executes a reaction based on the provided instigator and target actors.
	 * This function is meant to be overridden in Blueprints or derived classes to define specific reaction logic.
	 *
	 * @param InstigatorActor The actor initiating the reaction. This can be used to identify the source of the reaction.
	 * @param TargetActor The actor receiving the reaction. This can be used to determine the effect or target of the action.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "Reaction")
	void ExecuteReaction(AActor* InstigatorActor, AActor* TargetActor);

	/**
	 * Attempts to execute a reaction using the provided instigator and target actors.
	 * This function will either execute the reaction immediately or delay the execution
	 * based on configuration.
	 *
	 * @param InstigatorActor The actor that initiates the reaction. Used as the source of the reaction.
	 * @param TargetActor The actor that the reaction is targeted towards. Can be null, in which case the instigator is used as the valid actor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Reaction")
	void TryExecuteReaction(AActor* InstigatorActor, AActor* TargetActor);

	/**
	 * Determines whether a reaction should be triggered based on the current value and the predefined activation condition.
	 * This method evaluates the condition and returns true if the reaction criteria are met.
	 *
	 * @param currentValue The current value to be evaluated against the activation condition and threshold.
	 * @return true if the reaction should be triggered according to the activation condition; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Activation")
	virtual bool ShouldTriggerReaction(float currentValue);

	UFUNCTION(BlueprintCallable, Category = "Activation")
	EAttributeChangeDirection GetChangeDirection() const { return ActivationDirection; }
protected:
	
	/** ActivationCondition: Determines the condition under which the reaction will be activated, such as always active or based on a threshold. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activation")
	EReactionActivationCondition ActivationCondition = EReactionActivationCondition::Always;
	
	/** ThresholdValue: The value used as a reference point for activation conditions such as GreaterThan, LessThan, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activation", meta = (EditCondition = "ActivationCondition != EReactionActivationCondition::Always"))
	float ThresholdValue = 0.0f;
	
	/** bUseDelay: Indicates whether the reaction execution should be delayed or not.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delay")
	bool bUseDelay = false;
	
	/** DelaySeconds: Specifies the duration in seconds to delay the execution of the reaction if bUseDelay is true. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delay", meta = (EditCondition = "bUseDelay", ClampMin = "0.0"))
	float DelaySeconds = 0.0f;

	/** Defines if this Reaction should trigger on attribute increase, decrease, or any change */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activation")
	EAttributeChangeDirection ActivationDirection = EAttributeChangeDirection::Any;
};
