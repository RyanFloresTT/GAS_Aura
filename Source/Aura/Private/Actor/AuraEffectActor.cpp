// Copyright Ryan Flores :)


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto InstantGameplayEffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto DurationGameplayEffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		for (const auto InfiniteEffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
		}
	}
	
	if (bDestroyOnEffectRemoval)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto InstantGameplayEffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto DurationGameplayEffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		for (const auto InfiniteGameplayEffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!TargetAbilitySystemComponent) return;

		TArray<FActiveGameplayEffectHandle> ActiveEffectHandlesToRemove;
		
		for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& ActiveEffectHandle : ActiveEffectHandles)
		{
			if (TargetAbilitySystemComponent != ActiveEffectHandle.Value) return;
			TargetAbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
			ActiveEffectHandlesToRemove.Add(ActiveEffectHandle.Key);
		}
		
		for (const FActiveGameplayEffectHandle& ActiveEffectHandle : ActiveEffectHandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(ActiveEffectHandle);
		}
	}
	
	if (bDestroyOnEffectRemoval)
	{
		Destroy();
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAbilitySystemComponent) return;
	
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext(); 
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	const FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec);

	if (EffectSpec->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	}
}
