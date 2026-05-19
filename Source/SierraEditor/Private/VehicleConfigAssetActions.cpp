// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "VehicleConfigAssetActions.h"
#include "VehicleConfigXmlImporter.h"
#include "DesktopPlatformModule.h"
#include "Framework/Application/SlateApplication.h"

void FVehicleConfigAssetActions::GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section)
{
	TArray<TWeakObjectPtr<UObject>> WeakObjects;
	for (UObject* Obj : InObjects)
		WeakObjects.Add(Obj);

	Section.AddMenuEntry(
		"ImportFromXml",
		INVTEXT("Import from XML..."),
		INVTEXT("Import vehicle config values from an NFS Heat XML export"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateStatic(&FVehicleConfigAssetActions::ExecuteImportFromXml, WeakObjects))
	);
}

void FVehicleConfigAssetActions::ExecuteImportFromXml(TArray<TWeakObjectPtr<UObject>> WeakObjects)
{
	IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
	if (!Platform) return;

	TArray<FString> OutFiles;
	const FString DefaultPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Docs/Config"));

	Platform->OpenFileDialog(
		FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
		TEXT("Select NFS Heat XML Config"),
		DefaultPath,
		TEXT(""),
		TEXT("XML Files (*.xml)|*.xml"),
		EFileDialogFlags::None,
		OutFiles
	);

	if (OutFiles.Num() == 0) return;

	for (TWeakObjectPtr<UObject>& WeakObj : WeakObjects)
	{
		UObject* Obj = WeakObj.Get();
		if (!Obj) continue;

		if (FVehicleConfigXmlImporter::ImportFile(OutFiles[0], Obj))
		{
			Obj->PostLoad();
			Obj->MarkPackageDirty();
		}
	}
}
