// Copyright Erik 2020

#include "Containers/Array.h"
#include <iostream>
#include "Engine.h"
#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	for (int32 i = 0; i < 3; i++)
	{
		Items.Add(i);
	}
	
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::ShowInventoryComp()
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, TEXT("Element %i, %s", i, *Items[i]));
		}
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, TEXT("HERE ARE SOME STUFF"));
	}
}


