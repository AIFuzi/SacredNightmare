#include "Components/WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

APlayerCharacter* UWeaponComponent::GetPlayerOwner() const
{
	return PlayerOwner;
}

