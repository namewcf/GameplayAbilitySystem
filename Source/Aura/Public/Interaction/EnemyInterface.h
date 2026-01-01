// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//声明纯虚函数的核心写法，用于定义「Actor 高亮 / 取消高亮」的抽象接口，强制子类实现具体的高亮逻辑。
	virtual void HighLightActor() = 0;
	virtual void UnHighLightActor() = 0;
};
