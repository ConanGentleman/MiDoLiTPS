// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

//声明多播委托的宏（DYNAMIC用于运行时绑定，可用于蓝图；另一个是编译时绑定，不可用于蓝图）
//参数：调用函数；参数1类型，参数1在蓝图中的变量名
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished,AActor*);

//声明枚举  明明以E开头
UENUM(BlueprintType)
enum class EMovementType:uint8
{
	Sin,
	Static,
};
//声明结构体 命名以F开头
USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate=3.0f;
};

UCLASS() 
class MIDOLITPS_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	//函数体少的函数可以直接在.h文件内定义
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData; }

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	FOnTimerFinished OnTimerFinished;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//在被删除前调用 在这里重写
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category="Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 24.231f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FVector InitialLocation;
	FTimerHandle TimerHandle;

	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	void PrintTypes();

	void PrintStringTypes();
	void PrintTransform();
	void HandleMovement();

	void SetColor(const FLinearColor& Color);

	void OnTimerFired();
};
