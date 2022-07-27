#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SACREDNIGHTMARE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;

public:

	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PlayerAssets")
	class USpringArmComponent* PlayerSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PlayerAssets")
	class UCameraComponent* PlayerCamera;
};
