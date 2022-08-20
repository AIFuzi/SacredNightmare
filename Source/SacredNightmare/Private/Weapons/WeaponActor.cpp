#include "Weapons/WeaponActor.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

AWeaponActor::AWeaponActor()
{
	bReplicates = true;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponActor, WeaponOwner);
}

void AWeaponActor::OnRep_WeaponOwner()
{
	if(WeaponOwner)
	{
		SetInstigator(WeaponOwner);
		SetOwner(WeaponOwner);
	}
	else
	{
		SetOwner(nullptr);
		SetInstigator(nullptr);
	}
}
