#include "Components/WeaponComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Weapons/WeaponActor.h"

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

void UWeaponComponent::SpawnAndAttachWeapon(TSubclassOf<AWeaponActor> WeaponClass)
{
	Server_SpawnAndAttachWeapon(WeaponClass);
}

void UWeaponComponent::Server_SpawnAndAttachWeapon_Implementation(TSubclassOf<AWeaponActor> WeaponClass)
{
	if(WeaponClass && PlayerOwner)
	{
		const FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
		const FRotator SpawnRot = FRotator(0.f, 0.f, 0.f);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if(AWeaponActor* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass, SpawnLoc, SpawnRot, SpawnParameters))
		{
			CurrentWeapon = SpawnedWeapon;
			
			SpawnedWeapon->SetActorEnableCollision(false);
			SpawnedWeapon->AttachToComponent(PlayerOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SK_WeaponRHand");

			SpawnedWeapon->WeaponOwner = PlayerOwner;
			SpawnedWeapon->OnRep_WeaponOwner();
		}
	}
}

bool UWeaponComponent::Server_SpawnAndAttachWeapon_Validate(TSubclassOf<AWeaponActor> WeaponClass) { return true; }

