#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACREDNIGHTMARE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UWeaponComponent();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	class AWeaponActor* CurrentWeapon;

	UFUNCTION(BlueprintPure, Category="WeaponComponent")
	class APlayerCharacter* GetPlayerOwner() const;

	UFUNCTION(BlueprintCallable, Category="WeaponComponent")
	void SpawnAndAttachWeapon(TSubclassOf<class AWeaponActor> WeaponClass);

	UFUNCTION(Unreliable, Server, WithValidation, Category="WeaponComponent")
	void Server_SpawnAndAttachWeapon(TSubclassOf<AWeaponActor> WeaponClass);

private:

	UPROPERTY()
	APlayerCharacter* PlayerOwner;
	
};
