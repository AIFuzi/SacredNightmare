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

	UFUNCTION(BlueprintPure, Category="WeaponComponent")
	class APlayerCharacter* GetPlayerOwner() const;

private:

	UPROPERTY()
	APlayerCharacter* PlayerOwner;
		
};
