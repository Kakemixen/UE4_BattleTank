// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set driving force, and limit those forces
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	
public:

	

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
	//MaxForce Pr track in N
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 20000000.0;

private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
	void DriveTrack();
	float CurrentThrottle = 0;
};
