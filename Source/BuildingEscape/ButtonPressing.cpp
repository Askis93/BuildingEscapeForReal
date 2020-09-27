// Copyright Erik 2020

#include "ButtonPressing.h"
#include "DoorSlideOpen.h"

// Sets default values for this component's properties
UButtonPressing::UButtonPressing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UButtonPressing::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();
	
}

void UButtonPressing::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("PushButton", IE_Pressed, this, &UButtonPressing::ButtonPress);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Does not have input"), *GetOwner()->GetName());
	}
}

void UButtonPressing::FindTriggedDoor()
{
//	TriggedDoor = GetOwner()->GetClass()->GetDefaultObject();
	if (!TriggedDoor)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Does not have TriggerBox"), *GetOwner()->GetName());
	}
}

void UButtonPressing::ButtonPress()
{
	FHitResult IsItButton;
	IsItButton.Init();
	IsItButton = GetFirstTriggerInReach();
	//UPrimitiveComponent* ComponentToGrab = IsItButton.GetComponent();
	
	 
	AActor* ActorHit = IsItButton.GetActor();
	if (ActorHit)
	{
		if (!TriggedDoor) { return; }
		UE_LOG(LogTemp, Warning, TEXT("%s trigger is found"), *ActorHit->GetName());
		//TriggedDoor->GetGrabbedComponent();
	}
}

// Called every frame
void UButtonPressing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (!TriggedDoor) { return; }
	//if (TriggedDoor->GrabbedComponent)
	//{
		//UDoorSlideOpen OpenDoor;
		//OpenDoor.OpenTheDoor = true;
	//}

}

FVector UButtonPressing::GetPlayerReach() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
}

FVector UButtonPressing::GetPlayerWorldPos() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	return PlayerViewpointLocation;
}

FHitResult UButtonPressing::GetFirstTriggerInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParams
	);

	return Hit;
}


