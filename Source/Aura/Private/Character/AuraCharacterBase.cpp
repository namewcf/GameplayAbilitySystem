// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CreateDefaultSubobject用于在UObject/AActor派生类的构造函数中创建子对象
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");

	//将武器组件依附到角色骨骼网格体的指定Socket上
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//禁用武器组件碰撞检测
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

