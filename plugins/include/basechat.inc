/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod (C)2004-2011 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This file is part of the SourceMod/SourcePawn SDK.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */
 
#if defined _basechat_included
 #endinput
#endif
#define _basechat_included

/**
 * Various types of admin related chat messages.
 */
enum BaseChatType
{
	BaseChatType_AllSay	= 0,	/**< Admin-to-all chat resulting from sm_say usage. */
	BaseChatType_CSay = 1,		/**< Admin-to-all chat resulting from sm_csay usage. */
	BaseChatType_HSay = 2,		/**< Admin-to-all chat resulting from sm_hsay usage. */
	BaseChatType_TSay = 3,		/**< Admin-to-all chat resulting from sm_tsay usage. */
	BaseChatType_AdminChat = 4,	/**< Admin only chat resulting from sm_chat usage. */
	BaseChatType_MSay = 5,		/**< Admin-to-all chat resulting from sm_msay usage. */
};

/**
 * Called when a client makes use of an admin chat command
 *
 * @param	client		Client index of the user who initiated the command.
 * @param	chatType	The type of chat message that was performed.
 * @param	message		The message that was sent.
 */
forward BaseChat_OnAdminChat(client, BaseChatType:chatType, const String:message[]);

/**
 * Called when a client makes use of an admin sm_psay command
 *
 * @param	clientFrom	Client index of the user who initiated the command.
 * @param	clientTo	Client index of the user who the message was sent to.
 * @param	message		The message that was sent.
 */
forward BaseChat_OnPrivateChat(clientFrom, clientTo, const String:message[]);


/* DO NOT EDIT BELOW THIS LINE */

public SharedPlugin:__pl_basechat = 
{
	name = "basechat",
	file = "basechat.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
