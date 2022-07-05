#pragma once

// Name: AimGods, Version: Beta 2


#ifdef _MSC_VER
	#pragma pack(push, 0x01)
#endif

/*!!HELPER_DEF!!*/

/*!!DEFINE!!*/

namespace UFT
{
//---------------------------------------------------------------------------
// Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass WB_ErrorMessage.WB_ErrorMessage_C
// 0x0030 (FullSize[0x0260] - InheritedSize[0x0230])
class UWB_ErrorMessage_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                            // 0x0230(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UTextBlock*                                  TextBlock_123;                                             // 0x0238(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWB_Border_A_C*                              WB_Border_A;                                               // 0x0240(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWB_Btn_Generic_2_C*                         WB_Btn_Back;                                               // 0x0248(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	struct FString                                     ErrorMessageText;                                          // 0x0250(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, HasGetValueTypeHash)


	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass WB_ErrorMessage.WB_ErrorMessage_C");
		return ptr;
	}


	void BndEvt__WB_Btn_Back_K2Node_ComponentBoundEvent_2_Clicked__DelegateSignature();
	void ExecuteUbergraph_WB_ErrorMessage(int EntryPoint);
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
