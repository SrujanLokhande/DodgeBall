// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "DodgeBallCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Ball Movement"));

	SetRootComponent(Collider);

	BallMesh->SetupAttachment(RootComponent);
	Collider->SetSphereRadius(BallRadius);

	ProjectileMovementComp->SetUpdatedComponent(RootComponent);
	ProjectileMovementComp->InitialSpeed = 2000.0f;
	ProjectileMovementComp->MaxSpeed = 4000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->ProjectileGravityScale = 1.0f;

	SetLifeSpan(5.0f);

	DamageAmount = 25.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
	bNetLoadOnClient = true;
}

void ABall::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const TObjectPtr<AActor> actorHit = SweepResult.GetActor();

	if(IsValid(actorHit))
	{
		UGameplayStatics::ApplyDamage(actorHit, DamageAmount, nullptr, this, UDamageType::StaticClass());
	}
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBulletOverlap);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

