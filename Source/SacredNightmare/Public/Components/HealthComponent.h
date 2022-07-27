#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACREDNIGHTMARE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth;

	UFUNCTION(BlueprintCallable, Category="Health")
	void DamageChar(float Damage);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Health")
	void Server_DamageChar(float Damage);
};








