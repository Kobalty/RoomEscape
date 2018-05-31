// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); /// Look for attached physics handle

	if (PhysicsHandle == nullptr) /// Test to see if physics handle is empty
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle found for: %s "), *GetOwner()->GetName()); // logs out the warning if no physics handle is found and then specifies fo which object aka owner it failed for.
	}
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); /// look for attached input component

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); /// this is the function to actually do something with the action mappings (button presses) *this* referrs to this component, 
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased); /// this sees if the grab has been released.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No input Component found for: %s "), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	GetLineTraceEnd();
	/// lince trace aka (ray-cast) out to reach distance.
	FHitResult Hit;
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, LineTraceStart, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	AActor *ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Hit:  %s  "), *ActorHit->GetName());
	}
	return Hit;
}

void UGrabber::Grab()
{
	// line trace and see if we reach any actor with physicsbody collision channel set.
	auto HitResult = GetFirstPhysicsBodyInReach();

	auto ComponentToGrab = HitResult.GetComponent();
	
	// if we hit anything then attach a physics handle
	auto ActorHit = HitResult.GetActor();
	
	
	if (ActorHit != nullptr)
	{
		// attach Physics handle
		// This is the new version and slightly different from the course training.
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
	}
}

void UGrabber::GrabReleased()
{
	// TODO release phycis handle.
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FirstPlayerViewReport()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(FirstPlayerLocation, FirstPlayerRotation);/// passes two empty variables into the funcion and returns them with values this also a "top down"search. has to be ticked otherwise it displays intilaised or first called values.
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// if the phycis handle is attached
		// move object we are holding.
	
	FirstPlayerViewReport(); // going to disable this for the time being as its shitting up my log * dsiabling this kills the draw debug line

	GetLineTraceEnd();// (refactored)

	if (PhysicsHandle->GrabbedComponent)// if physics handle is attatched
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd); // move object were currently holding
	}
}

void UGrabber::GetLineTraceStart()
{
	LineTraceStart = FirstPlayerLocation;
}

void UGrabber::GetLineTraceEnd()
{
	LineTraceEnd = FirstPlayerLocation + FirstPlayerRotation.Vector() *Reach;
}


