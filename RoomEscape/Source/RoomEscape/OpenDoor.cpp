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

void UOpenDoor::OpenDoor()// this just opens the door to a certain agnle.
{
	

	//FRotator StartRotation = FRotator(0.0f, OpenAngle, 0.0f);// sets the value of StartRotaion by defining the values of (Pitch, Yaw, Roll)

	//Owner->SetActorRotation(StartRotation);// Feeds the new FRotator StartRoation into this function and works.

	OnOpenRequest.Broadcast();

	//FString OwnerRotation = *Owner->GetActorRotation().ToString();// allows the rotation to be outputted to the log.

	//UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), *OwnerRotation);

}

void UOpenDoor::CloseDoor()// Closes the door after a certain time.
{
	

	FRotator EndRotation = FRotator(0.0f, -89.0f, 0.0f);// sets the value of StartRotaion by defining the values of (Pitch, Yaw, Roll)

	Owner->SetActorRotation(EndRotation);// Feeds the new FRotator StartRoation into this function and works.



	FString OwnerRotation = *Owner->GetActorRotation().ToString();// allows the rotation to be outputted to the log.

	//UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), *OwnerRotation);

}

// Called every frame

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOfActorsOnPlate() > 59.f)//TODO make checked value into a parameter.
	{
		OpenDoor();

		DoorLastOpenTime = GetWorld()->GetTimeSeconds(); 
	}
	
	
	// Check to see if its time to close the door.
	if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime > CloseDoorDelay)// take the time in seconds remove the time value of when the door was opened and see if the new time is greater than the delay value.
	{
		CloseDoor();

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