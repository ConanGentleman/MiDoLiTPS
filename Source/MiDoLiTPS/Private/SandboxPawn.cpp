// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	//添加到组件生成的结构层次中(设置父类）
	StaticMeshComponent->SetupAttachment(GetRootComponent());//这里的GetRootComponent() = SceneComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
	//StaticMeshComponent->SetRelativeLocation(); //设置相对于父类的位置
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//移动计算        （可以附加判断条件IsControlled 防止 在按住移动键时切换Pawn，原来的Pawn会一直运动下去
	if (!VelocityVector.IsZero()) {
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		//防止 在按住移动键时切换Pawn，原来的Pawn会一直运动下去
		VelocityVector = FVector::ZeroVector;
	}

}

// Called to bind functionality to input 绑定输入
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent) {
		//映射名称、指向对象的指针、调用函数的引用
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	}
}

void ASandboxPawn::MoveForward(float Amount)
{
	//UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount);
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	//UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount);
	VelocityVector.Y = Amount;
}

void ASandboxPawn::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	if (!NewController) return;
	UE_LOG(LogSandboxPawn, Error, TEXT("%s possessed %s"), *GetName(),*NewController->GetName());
}
//当丢失Pawn的控制权时调用 
void ASandboxPawn::UnPossessed() {
	Super::UnPossessed();
	UE_LOG(LogSandboxPawn, Warning, TEXT("%s unpossessed"), *GetName());
}