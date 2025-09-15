﻿#pragma once

UENUM()
enum class ESmartPhoneScreenState : uint8
{
	None,
	RoomList,
	AllChat,
	TeamChat
};


UENUM(BlueprintType)
enum class EChattingRoomType : uint8
{
	AllChatRoom,
	TeamChatRoom
};