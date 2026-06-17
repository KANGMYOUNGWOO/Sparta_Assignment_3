#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SPARTA_EDUCATION1_API APlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    APlayerPawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComp;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* LookAction;

    FVector2D MoveInput;
    FVector2D LookInput;

    UPROPERTY(EditAnywhere, Category="Movement")
    float MoveSpeed = 600.0f;

    UPROPERTY(EditAnywhere, Category="Movement")
    float LookSpeed = 100.0f;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
};