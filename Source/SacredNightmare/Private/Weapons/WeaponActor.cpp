#include "Weapons/WeaponActor.h"
#include "Components/StaticMeshComponent.h"

AWeaponActor::AWeaponActor()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}
