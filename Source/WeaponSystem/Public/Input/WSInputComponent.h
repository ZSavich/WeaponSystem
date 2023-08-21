// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "WSInputConfig.h"
#include "WSInputComponent.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UWSAbilitySystemComponent;

UCLASS()
class WEAPONSYSTEM_API UWSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UWSInputComponent();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UWSInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> DefaultMapping;

	TWeakObjectPtr<UWSAbilitySystemComponent> OwnerASC;
	
public:
	template<class UserClass, typename FuncType>
	void BindNativeAction(const UWSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UWSInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
	
	void InitializePlayerInputs(UEnhancedInputLocalPlayerSubsystem* Subsystem);

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	void Input_Move(const FInputActionValue& InputActionValue);
};