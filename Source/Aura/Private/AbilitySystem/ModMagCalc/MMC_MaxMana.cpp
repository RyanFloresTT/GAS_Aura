// Copyright Ryan Flores :)


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntellectDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntellectDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntellectDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(IntellectDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	
	float Intellect = 0.f;
	GetCapturedAttributeMagnitude(IntellectDef, Spec, EvaluateParams, Intellect);
	Intellect = FMath::Max(Intellect, 0.f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 50.f + Intellect * 2.5f + PlayerLevel * 15.f;
}


