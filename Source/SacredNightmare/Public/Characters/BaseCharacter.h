#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SACREDNIGHTMARE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

protected:


public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float WalkingSpeed;

};
