// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, +1);
	FVector Force = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(Force, ForceLocation);
}

