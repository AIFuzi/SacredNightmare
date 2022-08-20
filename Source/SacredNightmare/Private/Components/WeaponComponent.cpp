#include "Components/WeaponComponent.h"
#include "Characters/PlayerCharacter.h"

UWeaponComponent::UWeaponComponent()
{

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerOwner = Cast<APlayerCharacter>(GetOwner());
}

APlayerCharacter* UWeaponComponent::GetPlayerOwner() const
{
	return PlayerOwner;
}

