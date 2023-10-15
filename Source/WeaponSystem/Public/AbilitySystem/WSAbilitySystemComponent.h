// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WSAbilitySystemComponent.generated.h"

class UWSAbilitySet;

UCLASS()
class WEAPONSYSTEM_API UWSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TObjectPtr<UWSAbilitySet> AbilitySet;
	
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
	
public:
	virtual void BeginPlay() override;

	static UWSAbilitySystemComponent* GetWSAbilitySystemComponentFromController(const AController* Controller);
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

	void CancelInputActivatedAbilities();

protected:
	void HandleAbilityInputTag(const FGameplayTag& InputTag, TArray<FGameplayAbilitySpecHandle>& SpecHandles, const bool bIsReleased);
	
};
