// Copyright Erik 2020

#include "InventoryComponent.h"
//#include "Containers/Array.h"
#include "Engine.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	TimeRemaining = 50.0f;
	// ...
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeRemaining -= 0.01f;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInput();
}

void UInventoryComponent::SetupPlayerInput()
{
	PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &UInventoryComponent::ShowInventoryComp);
		PlayerInputComponent->BindAction("ShowTime", IE_Pressed, this, &UInventoryComponent::ShowTime);
	}
}

void UInventoryComponent::ShowTime()
{
	if (GEngine)
	{
		FString TheFloatStr = FString::SanitizeFloat(TimeRemaining);
		FString Time = "Time Remaining is: " + TheFloatStr;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Time);
	}
}

void UInventoryComponent::AddTime(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Please work"));
	TimeRemaining += 500.0f;
}


void UInventoryComponent::ShowInventoryComp()
{
	for (int32 i : Items)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, TEXT("TEST"));
		}
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, TEXT("HERE ARE SOME STUFF"));
	}
}

