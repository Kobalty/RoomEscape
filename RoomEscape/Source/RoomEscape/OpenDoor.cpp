// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "OpenDoor.h"


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
}

void UOpenDoor::OpenDoor()// this just opens the door to a certain agnle.
{
	

	FRotator StartRotation = FRotator(0.0f, OpenAngle, 0.0f);// sets the value of StartRotaion by defining the values of (Pitch, Yaw, Roll)

	Owner->SetActorRotation(StartRotation);// Feeds the new FRotator StartRoation into this function and works.



	FString OwnerRotation = *Owner->GetActorRotation().ToString();// allows the rotation to be outputted to the log.

	UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), *OwnerRotation);

}

void UOpenDoor::CloseDoor()// Closes the door after a certain time.
{
	

	FRotator EndRotation = FRotator(0.0f, -89.0f, 0.0f);// sets the value of StartRotaion by defining the values of (Pitch, Yaw, Roll)

	Owner->SetActorRotation(EndRotation);// Feeds the new FRotator StartRoation into this function and works.



	FString OwnerRotation = *Owner->GetActorRotation().ToString();// allows the rotation to be outputted to the log.

	UE_LOG(LogTemp, Warning, TEXT("Rotation is %s"), *OwnerRotation);

}

// Called every frame

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))// checks every frame to see if pressureplate is overlapping with the correct actor in this case the actor that opens...horrid fucking name.
	{
		OpenDoor();

		DoorLastOpenTime = GetWorld()->GetTimeSeconds(); 
	}
	
	if (DoorLastOpenTime + CloseDoorDelay == GetWorld()-> GetTimeSeconds())// this will make sure the door shuts after the delay has been checked/ waited for.
	{
		
		CloseDoor();
		

	}
	// Check to see if its time to close the door.
}

