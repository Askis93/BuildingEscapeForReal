// Copyright Erik 2020


#include "LineTracer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

// Sets default values for this component's properties
ULineTracer::ULineTracer()
{
	
}


// Called when the game starts
void ULineTracer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AActor* ULineTracer::LineTraceSingle(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionParams;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner()); //Ignores player

	if (GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		Start,
		End,
		CollisionParams,
		CollisionQueryParams
	))
	{
		return HitResult.GetActor();
	}
	else
	{
		return nullptr;
	}
}

AActor* ULineTracer::LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine)
{
	AActor* Actor = LineTraceSingle(Start, End);
	if (ShowDebugLine)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f, 0, 5.0f);
	}
	return Actor;
}




