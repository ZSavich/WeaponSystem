// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/WSAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WSGameplayAbility.h"

DEFINE_LOG_CATEGORY_STATIC(LogAbilitySet, All, All);

void FWSAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.AddUnique(Handle);
	}
}

void FWSAbilitySet_GrantedHandles::TakeFromAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent)
{
	check(AbilitySystemComponent);

	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}
	
	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystemComponent->ClearAbility(Handle);
		}
	}
	AbilitySpecHandles.Reset();
}

void UWSAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent, FWSAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	check(AbilitySystemComponent);

	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}

	// Grant the Gameplay Abilities
	for (const FWSAbilitySet_GameplayAbility& AbilityToGrant : GrantedGameplayAbilities)
	{
		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogAbilitySet, Error, TEXT("GrantedGameplayAbilities on ability set [%s] is not valid."), *GetNameSafe(this));
			continue;
		}

		if (UWSGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UWSGameplayAbility>())
		{
			FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
			AbilitySpec.SourceObject = SourceObject;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

			const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);

			if (OutGrantedHandles)
			{
				OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
			}
		}
	}
}
