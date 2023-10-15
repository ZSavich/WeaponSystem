// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "WSInputConfig.h"
#include "WSInputComponent.generated.h"

class AWSCharacter;

/**
 *  UWSInputComponent
 *
 *	Component used to manage input mappings and bindings using an input config data asset.
 */
UCLASS(Config = Input)
class WEAPONSYSTEM_API UWSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType>
	void BindNativeAction(const UWSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UWSInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename FuncType>
void UWSInputComponent::BindNativeAction(const UWSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* InputAction = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(InputAction, TriggerEvent, Object, MoveTemp(Func));
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UWSInputComponent::BindAbilityActions(const UWSInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);
	
	for (const FWSInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag).GetHandle();
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle();
			}
		}
	}
}
