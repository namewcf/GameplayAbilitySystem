// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	//广播当前角色的生命值（Health）数值，通知所有绑定了该委托的对象（通常是 UI 组件）更新生命值显示。
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	//为生命值（Health）属性注册一个值变化委托，当生命值发生改变时，会自动调用 UOverlayWidgetController 中的 HealthChanged 函数进行处理。
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxManaAttribute()
	).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	    [this](const FGameplayTagContainer& AssetTags)
	    {
	    	for (const FGameplayTag& Tag : AssetTags)
	    	{
	    		// For example , say that Tag = Message.HealthPotion
	    		//"Message.HealthPotion".MatchesTag("Message") will return True,
	    		//"Message".MatchesTag("Message.HealthPotion") will return False If TagToCheck is not Valid it will always return False
	    		FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
	    		if (Tag.IsValid() && Tag.MatchesTag(MessageTag))
	    		{
	    			const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				    MessageWidgetRowDelegate.Broadcast(*Row);
	    		}
	    		else GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Green,TEXT("HHH"));
			}
	    }	
	);
}

