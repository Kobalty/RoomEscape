// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector FirstPlayerLocation;
	FRotator FirstPlayerRotation;
	FVector LineTraceEnd; // the end of the line trace, the start would be the current FirstPlayerLocation + FirstPlayerRotation *Reach.

	void FirstPlayerViewReport();// function to do stuff with the location and rotation :P
	void FindPhysicsHandleComponent();// Checks to see if there is a physics component and logs accordingly.
	void SetupInputComponent();// Sets up the input component and allows *grab* to be pressed or released.
	const FHitResult GetFirstPhysicsBodyInReach(); // returns a hit for the first physics body in reach.
	void LineTraceEndResult();// function to return the line trace end.

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 100.f; //How far ahead of the player we can reach in cm 

	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	
	UInputComponent *InputComponent = nullptr;

	
	void Grab();// ray-cast and grab whats in reach.
	void GrabReleased(); // logs out the released grab
};
