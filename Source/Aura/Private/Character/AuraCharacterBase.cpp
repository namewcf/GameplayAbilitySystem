// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CreateDefaultSubobject用于在UObject/AActor派生类的构造函数中创建子对象
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");

	//设置Socket
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//设置碰撞
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

