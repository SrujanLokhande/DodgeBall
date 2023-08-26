// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ball.generated.h"

UCLASS()
class DODGEBALL_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

protected:

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Ball")
	TObjectPtr<USphereComponent> Collider;
	
	UPROPERTY(EditAnywhere, Category = "Ball")
	TObjectPtr<UStaticMeshComponent> BallMesh;
	
	UPROPERTY(EditAnywhere, Category = "Ball")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
	float BallRadius = 10.0f;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
