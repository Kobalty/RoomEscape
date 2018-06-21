// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "OpenDoor.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); //since ATO *atcor that opens* is a instance of actor class and pawn is inhertied from actor you can store the result of getpawn in ATO.

	if (!PressurePlate) // if Pressure plate not found log accordingly this. this is done at begin of play and logs out the name of the object which the trigger volue is attatched/associated with.
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s's  PressurePlate is not found"), *GetOwner()->GetName());
	}

}


// Called every frame

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();

	}
	
}

float UOpenDoor::GetMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray <AActor*> OverlappingActors;

	if (!PressurePlate) { return TotalMass; } // if pressure not found then return out of this function with the value of 0.f aka TotalMass

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"),*Actor->GetName());
	}
	
	return TotalMass;
}