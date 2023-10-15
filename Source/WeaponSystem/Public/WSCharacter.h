// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WSCharacter.generated.h"

class UWSInputConfig;
class UWSAbilitySystemComponent;
class UInputMappingContext;

UCLASS()
class WEAPONSYSTEM_API AWSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWSCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UWSInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> DefaultMapping;

	TWeakObjectPtr<UWSAbilitySystemComponent> AbilitySystemComponentWeak;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
};
