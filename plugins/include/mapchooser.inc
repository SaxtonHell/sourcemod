/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod (C)2004-2014 AlliedModders LLC.  All rights reserved.
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
#if defined _mapchooser_included_
  #endinput
#endif
#define _mapchooser_included_


#define MAPCHOOSER_VOTE_EXTEND "##extend##"			/* Extend current map */
#define MAPCHOOSER_VOTE_DONTCHANGE "##dontchange##"	/* Don't change current map */
#define MAPCHOOSER_VOTE_SPACER "##spacer##"			/* Invisible spacer */


enum NominateResult
{
	Nominate_Added,			/** The map was added to the nominate list */
	Nominate_Replaced,		/** A clients existing nomination was replaced */
	Nominate_AlreadyInVote,	/** Specified map was already in the vote */
	Nominate_InvalidMap,	/** Mapname specifed wasn't a valid map */
	Nominate_VoteFull,		/** This will only occur if force was set to false */
};

enum MapVoteResult
{
	MapVoteResult_Extended,	/** The map vote ended and the current map has been extended */
	MapVoteResult_NoChange,	/** The map vote ended and 'No Change' won */
	MapVoteResult_NoVotes,	/** The map vote ended with no votes and the next map was randomly selected if the sm_mapvote_novote convar was enabled */
	MapVoteResult_Canceled,	/** The map vote was canceled before a winner could be selected */
	MapVoteResult_NewMap,	/** The map vote ended and a new map was selected */
};

enum MapChange
{
	MapChange_Instant,		/** Change map as soon as the voting results have come in */
	MapChange_RoundEnd,		/** Change map at the end of the round */
	MapChange_MapEnd,		/** Change the sm_nextmap cvar */
};

/**
 * Attempt to add a map to the mapchooser map list.
 *
 * @param map		Map to add.
 * @param force		Should we force the map in even if it requires overwriting an existing nomination?
 * @param owner		Client index of the nominater. If the client disconnects the nomination will be removed. Use 0 for constant nominations
 * @return			Nominate Result of the outcome
 */
native NominateResult NominateMap(const char[] map, bool force, int owner);

/**
 * Attempt to remove a map from the mapchooser map list.
 *
 * @param map		Map to remove.
 * @return			True if the nomination was found and removed, or false if the nomination was not found.
 */
native bool RemoveNominationByMap(const char[] map);

/**
 * Attempt to remove a map from the mapchooser map list.
 *
 * @param owner		Client index of the nominater.
 * @return			True if the nomination was found and removed, or false if the nomination was not found.
 */
native bool RemoveNominationByOwner(int owner);

/**
 * Gets the current list of excluded maps.
 *
 * @param array		An ADT array handle to add the map strings to.
 * @noreturn
 */
native void GetExcludeMapList(ArrayList array);

/**
 * Gets the current list of nominated maps.
 *
 * @param maparray		An ADT array handle to add the map strings to.
 * @param ownerarray	An optional ADT array handle to add the nominator client indexes to.
 * @noreturn
 */
native void GetNominatedMapList(ArrayList maparray, ArrayList ownerarray = null);

/**
 * Checks if MapChooser will allow a vote
 *
 * @return			True if a vote can be held, or false if mapchooser is already holding a vote.
 */
native bool CanMapChooserStartVote();

/**
 * Initiates a MapChooser map vote
 *
 * Note: If no input array is specified mapchooser will use its internal list. This includes
 * any nominations and excluded maps (as per mapchoosers convars).
 *
 * @param when			MapChange consant of when the resulting mapchange should occur.
 * @param inputarray	ADT array list of maps to add to the vote.
 */
native void InitiateMapChooserVote(MapChange when, ArrayList inputarray=null);

/**
 * Checks if MapChooser's end of map vote has completed.
 *
 * @return			True if complete, false otherwise.
 */
native bool HasEndOfMapVoteFinished();

/**
 * Checks if MapChooser is set to run an end of map vote.
 *
 * @return			True if enabled, false otherwise.
 */
native bool EndOfMapVoteEnabled();

/**
 * Called when mapchooser removes a nomination from its list.
 * Nominations cleared on map start will not trigger this forward
 */
forward void OnNominationRemoved(const char[] map, int owner);

/**
 * Called when mapchooser has initialized the map vote timer.
 * Note: This could be called multiple times.
 *
 * @param timeToMapVote		The amount of time (in seconds) until mapchooser begins a map vote.
 */
forward OnMapVoteTimerInitialized(Float:timeToMapVote);

/**
 * Called when mapchooser starts a Map Vote.
 */
forward void OnMapVoteStarted();

/**
 * Called when a client selects a menu option during a map vote.
 *
 * @param client		The client that selected a map vote option.
 * @param info			The menu item info of the selected item, often the map name or one of the MAPCHOOSER_VOTE string defines.
 * @param displayText	The display text for the menu item that was selected.
 */
forward OnMapVoteItemSelected(client, const String:info[], const String:displayText[]);

/**
 * Called when a map vote item is displayed to a client, in order for the display text to be modified if needed.
 *
 * @param client			The client that the menu item is displayed for.
 * @param info				The menu item info of the displayed item, often the map name or one of the MAPCHOOSER_VOTE string defines.
 * @param displayText 		A copyback string buffer used to modify the display text of the menu item.
 * @param maxDisplayText	The maximum size of the copyback displayText string buffer.
 *
 * @return					Plugin_Continue to use the default display text, otherwise use the display text in the displayText buffer.
 */
forward Action:OnMapVoteItemDisplayed(client, const String:info[], String:displayText[], maxDisplayText);

/**
 * Called when mapchooser finishes a Map Vote.
 *
 * @param result	The result of the map vote.
 * @param nextMap	The map that was selected to be the next map, or the current map if the results specified no map change to occur.
 */
forward OnMapVoteFinished(MapVoteResult:result, const String:nextMap[]);

public SharedPlugin __pl_mapchooser = 
{
	name = "mapchooser",
	file = "mapchooser.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};

public void __pl_mapchooser_SetNTVOptional()
{
	MarkNativeAsOptional("NominateMap");
	MarkNativeAsOptional("RemoveNominationByMap");
	MarkNativeAsOptional("RemoveNominationByOwner");
	MarkNativeAsOptional("GetExcludeMapList");
	MarkNativeAsOptional("GetNominatedMapList");
	MarkNativeAsOptional("CanMapChooserStartVote");
	MarkNativeAsOptional("InitiateMapChooserVote");
	MarkNativeAsOptional("HasEndOfMapVoteFinished");
	MarkNativeAsOptional("EndOfMapVoteEnabled");
}

