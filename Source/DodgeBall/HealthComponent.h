// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthChanged);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DODGEBALL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	void UpdateHealth(const float& delta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float Maxhealth = 100.0f;

	UFUNCTION()
	void OnRepHealth();

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FHealthChanged OnHealthChanged;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
override;
};
