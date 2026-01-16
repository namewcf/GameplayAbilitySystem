// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//返回 Vigor 属性的FGameplayAttribute类型实例，让 GAS 能识别要捕获的具体属性
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	//指定捕获来源
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//
	VigorDef.bSnapshot = false;
	//RelevantAttributesToCapture 是MMC基类（UGameplayModMagnitudeCalculation）中的数组，用于存储 “所有需要 GAS 提前捕获的属性规则”。
	RelevantAttributesToCapture.Add(VigorDef);  
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//  Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 80.f + 2.5 * Vigor + 10.f * PlayerLevel;
}
