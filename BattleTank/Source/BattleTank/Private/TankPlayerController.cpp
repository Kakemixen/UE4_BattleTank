// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* TempTank = GetControlledTank();
	if (TempTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Player Has No Tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Has Tank %s"), *TempTank->GetName());
	}
	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PLayer controller not found aiming component"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;

	//Get World Location through(linetrace) crosshair
	if (GetSightRayHitLocation(OUT HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT HitLocation) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	//De-project screen pos of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,OUT LookDirection)) {
		// line-trace along that look direction (up to max range)
		return GetLookHitLocation(LookDirection, OUT HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookHitLocation(FVector LookDirection, FVector& OUT HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		OUT LookDirection
	);

}
