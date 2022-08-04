#include "Objects/GridManager.h"

AGridManager::AGridManager() : GridSize(10), WorldGridSize(100)
{

}

void AGridManager::CreateGridWorld()
{
	GridArray.Empty();
	const float WorldOffset = ((GridSize * WorldGridSize) * 0.5f) - (WorldGridSize * 0.5f);

	for(int y = 0; y < GridSize; y++)
	{
		for(int x = 0; x < GridSize; x++)
		{
			const int XGrid = (x * WorldGridSize) * FMath::TruncToInt(WorldOffset);
			const int YGrid = (y * WorldGridSize) * FMath::TruncToInt(WorldOffset);

			FVector SLoc = FVector(XGrid, YGrid, GetActorLocation().Z) + GetActorLocation();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			if(AActor* GridHelper = GetWorld()->SpawnActor<AActor>(GridCell, SLoc, FRotator(0, 0, 0), SpawnParameters))
			{
				GridHelper->SetActorHiddenInGame(false);
				GridHelper->SetActorEnableCollision(false);
				
				GridArray.Add(GridHelper);
			}
		}
	}
}

FVector AGridManager::GetClosestGridPosition(FVector InPosition)
{
	FVector ClosestPosition;
	
	if(GridArray.Num() > 0)
	{
		ClosestPosition = GridArray[0]->GetActorLocation();
		float ClosestDistance = FVector::Distance(InPosition, GridArray[0]->GetActorLocation());

		for(int i = 0; i < GridArray.Num(); i++)
		{
			if(FVector::Distance(GridArray[i]->GetActorLocation(), InPosition) < ClosestDistance)
			{
				ClosestPosition = GridArray[i]->GetActorLocation();
				ClosestDistance = FVector::Distance(GridArray[i]->GetActorLocation(), InPosition);
			}
		}
	}
	
	return ClosestPosition;
}
