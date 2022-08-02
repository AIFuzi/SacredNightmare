#include "Objects/GridManager.h"

AGridManager::AGridManager() : GridSize(10), WorldGridSize(100)
{

}

void AGridManager::CreateGridWorld()
{
	GridArray.Empty();
	float WorldOffset = ((GridSize * WorldGridSize) * 0.5f) - (WorldGridSize * 0.5f);

	for(int y = 0; y < GridSize; y++)
	{
		for(int x = 0; x < GridSize; x++)
		{
			int xG = (x * WorldGridSize) * FMath::TruncToInt(WorldOffset);
			int yG = (y * WorldGridSize) * FMath::TruncToInt(WorldOffset);

			FVector SLoc = FVector(xG, yG, GetActorLocation().Z);

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			
			if(AActor* GridHelper = GetWorld()->SpawnActor<AActor>(GridCell, SLoc, FRotator(0, 0, 0), SpawnParameters))
				GridArray.Add(GridHelper);
		}
	}
}

FVector AGridManager::GetClosestGridPosition(FVector InPosition)
{
	FVector ClosestPosition = GridArray[0]->GetActorLocation();
	float ClosestDistance = FVector::Distance(InPosition, GridArray[0]->GetActorLocation());

	for(int i = 0; i < GridArray.Num(); i++)
	{
		if(FVector::Distance(GridArray[i]->GetActorLocation(), InPosition) < ClosestDistance)
		{
			ClosestPosition = GridArray[i]->GetActorLocation();
			ClosestDistance = FVector::Distance(GridArray[i]->GetActorLocation(), InPosition);
		}
	}
	
	return ClosestPosition;
}
